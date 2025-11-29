#include "dungeon.h"
#include "factory.h"
#include "visitor.h"
#include <iostream>
#include <algorithm>

const double Dungeon::MAX_X = 500.0;
const double Dungeon::MAX_Y = 500.0;

Dungeon::Dungeon() {}

void Dungeon::AddNPC(std::shared_ptr<NPC> npc) {
    if (!npc) return;
    
    Point pos = npc->GetPosition();
    if (pos.GetX() < 0 || pos.GetX() > MAX_X || 
        pos.GetY() < 0 || pos.GetY() > MAX_Y) {
        std::cerr << "Error: NPC position is out of bounds!" << std::endl;
        return;
    }
    
    for (const auto& existing : npcs_) {
        if (existing->GetName() == npc->GetName()) {
            std::cerr << "Error: NPC with name '" << npc->GetName() << "' already exists!" << std::endl;
            return;
        }
    }
    
    npcs_.push_back(npc);
    std::cout << "Added " << npc->GetTypeString() << " '" << npc->GetName() << "'" << std::endl;
}

void Dungeon::RemoveNPC(const std::string& name) {
    auto it = std::find_if(npcs_.begin(), npcs_.end(),
        [&name](const std::shared_ptr<NPC>& npc) { return npc->GetName() == name; });
    
    if (it != npcs_.end()) {
        npcs_.erase(it);
        std::cout << "Removed NPC '" << name << "'" << std::endl;
    } else {
        std::cerr << "NPC '" << name << "' not found!" << std::endl;
    }
}

void Dungeon::PrintNPCs() const {
    if (npcs_.empty()) {
        std::cout << "Dungeon is empty." << std::endl;
        return;
    }
    
    std::cout << "\n=== Dungeon NPCs ===" << std::endl;
    int i = 1;
    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            std::cout << i << ". " << npc->GetTypeString() << " '" << npc->GetName() 
                     << "' at (" << npc->GetPosition().GetX() << ", " 
                     << npc->GetPosition().GetY() << ")" << std::endl;
            i++;
        }
    }
    std::cout << "===================\n" << std::endl;
}

void Dungeon::SaveToFile(const std::string& filename) const {
    NPCFileLoader::SaveToFile(npcs_, filename);
    std::cout << "Saved dungeon to '" << filename << "'" << std::endl;
}

void Dungeon::LoadFromFile(const std::string& filename) {
    npcs_ = NPCFileLoader::LoadFromFile(filename);
    std::cout << "Loaded " << npcs_.size() << " NPCs from '" << filename << "'" << std::endl;
}

void Dungeon::StartBattle(double range) {
    std::cout << "\n=== Battle Started (Range: " << range << ") ===" << std::endl;
    
    bool battle_ongoing = true;
    int rounds = 0;
    
    while (battle_ongoing && rounds < 100) {
        rounds++;
        battle_ongoing = false;
        
        std::vector<std::shared_ptr<NPC>> alive_npcs;
        for (const auto& npc : npcs_) {
            if (npc->IsAlive()) {
                alive_npcs.push_back(npc);
            }
        }
        
        if (alive_npcs.size() <= 1) {
            break;
        }
        
        // Each alive NPC tries to attack others
        for (auto& attacker : alive_npcs) {
            if (!attacker->IsAlive()) continue;
            
            for (auto& defender : alive_npcs) {
                if (attacker == defender || !defender->IsAlive()) continue;
                
                CombatVisitor visitor(attacker, defender, range);
                
                defender->Accept(visitor);
                
                if (visitor.DidDefenderDie()) {
                    battle_ongoing = true;
                }
            }
        }
    }
    
    std::cout << "=== Battle Ended ===" << std::endl;
    PrintNPCs();
}

std::vector<std::shared_ptr<NPC>>& Dungeon::GetNPCs() {
    return npcs_;
}
