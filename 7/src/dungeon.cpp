#include "dungeon.h"
#include "factory.h"
#include "visitor.h"
#include "observer.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

const double Dungeon::MAP_SIZE = 100.0;

Dungeon::Dungeon() {}

Dungeon::~Dungeon() {
    StopGame();
}

void Dungeon::AddNPC(std::shared_ptr<NPC> npc) {
    if (!npc) return;
    
    Point pos = npc->GetPosition();
    if (pos.GetX() < 0 || pos.GetX() > MAP_SIZE || 
        pos.GetY() < 0 || pos.GetY() > MAP_SIZE) {
        return;
    }
    
    {
        std::shared_lock<std::shared_mutex> lock(npcs_mutex_);
        for (const auto& existing : npcs_) {
            if (existing->GetName() == npc->GetName()) {
                return;
            }
        }
    }
    
    {
        std::lock_guard<std::shared_mutex> lock(npcs_mutex_);
        npcs_.push_back(npc);
    }
    
    {
        std::lock_guard<std::mutex> lock(cout_mutex_);
    }
}

void Dungeon::RemoveNPC(const std::string& name) {
    std::lock_guard<std::shared_mutex> lock(npcs_mutex_);
    auto it = std::find_if(npcs_.begin(), npcs_.end(),
        [&name](const std::shared_ptr<NPC>& npc) { return npc->GetName() == name; });
    
    if (it != npcs_.end()) {
        npcs_.erase(it);
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
    }
}

void Dungeon::PrintNPCs() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex_);
    std::lock_guard<std::mutex> cout_lock(cout_mutex_);
    
    if (npcs_.empty()) {
        std::cout << "Dungeon is empty." << std::endl;
        return;
    }
    
    int i = 1;
    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            Point pos = npc->GetPosition();
            std::cout << i << ". " << npc->GetTypeString() << " '" << npc->GetName() 
                     << "' на (" << pos.GetX() << ", " << pos.GetY() << ")" << std::endl;
            i++;
        }
    }
}

void Dungeon::SaveToFile(const std::string& filename) const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex_);
    NPCFileLoader::SaveToFile(npcs_, filename);
    
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        std::cout << "сохранен в '" << filename << "'" << std::endl;
    }
}

void Dungeon::LoadFromFile(const std::string& filename) {
    auto loaded_npcs = NPCFileLoader::LoadFromFile(filename);
    
    {
        std::lock_guard<std::shared_mutex> lock(npcs_mutex_);
        npcs_ = loaded_npcs;
    }
    
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        std::cout << "загружен " << loaded_npcs.size() << " нпс из '" << filename << "'" << std::endl;
    }
}

std::vector<std::shared_ptr<NPC>> Dungeon::GetAliveNPCs() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex_);
    std::vector<std::shared_ptr<NPC>> alive;
    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            alive.push_back(npc);
        }
    }
    return alive;
}

void Dungeon::AddBattleTask(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) {
    {
        std::lock_guard<std::mutex> lock(battle_queue_mutex_);
        battle_queue_.push({attacker, defender});
    }
    battle_queue_cv_.notify_one();
}

void Dungeon::MovementThreadFunc() {
    while (running_) {
        auto alive = GetAliveNPCs();
        
        for (auto& npc : alive) {
            if (!npc->IsAlive()) continue;
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis_angle(0, 2 * M_PI);
            std::uniform_real_distribution<> dis_dist(0, npc->GetMoveDistance());
            
            double angle = dis_angle(gen);
            double distance = dis_dist(gen);
            
            Point current = npc->GetPosition();
            double new_x = current.GetX() + distance * std::cos(angle);
            double new_y = current.GetY() + distance * std::sin(angle);
            
            new_x = std::max(0.0, std::min(new_x, MAP_SIZE));
            new_y = std::max(0.0, std::min(new_y, MAP_SIZE));
            
            npc->SetPosition(Point(new_x, new_y));
            
            for (auto& other : alive) {
                if (other == npc || !other->IsAlive() || !npc->IsAlive()) continue;
                
                double dist = npc->Distance(other);
                if (dist <= other->GetKillDistance()) {
                    AddBattleTask(other, npc);
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Dungeon::BattleThreadFunc() {
    while (running_) {
        std::unique_lock<std::mutex> lock(battle_queue_mutex_);
        
        if (battle_queue_cv_.wait_for(lock, std::chrono::milliseconds(100), 
            [this]() { return !battle_queue_.empty(); })) {
            
            BattleTask task = battle_queue_.front();
            battle_queue_.pop();
            lock.unlock();
            
            if (task.attacker->IsAlive() && task.defender->IsAlive()) {
                CombatVisitor visitor(task.attacker, task.defender);
                task.defender->Accept(visitor);
            }
        }
    }
}

void Dungeon::PrintMapThreadFunc() {
    while (running_) {
        PrintNPCs();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Dungeon::StartGame(int duration_seconds) {
    if (running_) return;
    
    running_ = true;
    
    movement_thread_ = std::thread(&Dungeon::MovementThreadFunc, this);
    battle_thread_ = std::thread(&Dungeon::BattleThreadFunc, this);
    print_thread_ = std::thread(&Dungeon::PrintMapThreadFunc, this);
    
    std::this_thread::sleep_for(std::chrono::seconds(duration_seconds));
    
    StopGame();
}

void Dungeon::StopGame() {
    if (!running_) return;
    
    running_ = false;
    
    battle_queue_cv_.notify_one();
    
    if (movement_thread_.joinable()) movement_thread_.join();
    if (battle_thread_.joinable()) battle_thread_.join();
    if (print_thread_.joinable()) print_thread_.join();
    
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        std::cout << "\n GAME OVER " << std::endl;
    }
    
    auto survivors = GetAliveNPCs();
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        if (survivors.empty()) {
            std::cout << "все подохли(" << std::endl;
        } else {
            int i = 1;
            for (const auto& npc : survivors) {
                Point pos = npc->GetPosition();
                std::cout << i << ". " << npc->GetTypeString() << " '" << npc->GetName() 
                         << "' на (" << pos.GetX() << ", " << pos.GetY() << ")" << std::endl;
                i++;
            }
        }
    }
}
