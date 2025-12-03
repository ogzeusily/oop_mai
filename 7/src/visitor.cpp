#include "visitor.h"
#include "npc.h"
#include "observer.h"
#include <random>
#include <mutex>

static std::mutex dice_mutex;

CombatVisitor::CombatVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
    : attacker_(attacker), defender_(defender), defender_died_(false) {}

int CombatVisitor::RollDice() {
    std::lock_guard<std::mutex> lock(dice_mutex);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

bool CombatVisitor::CanAttack() {
    if (!attacker_->IsAlive() || !defender_->IsAlive()) {
        return false;
    }
    
    double dist = attacker_->Distance(defender_);
    double kill_distance = attacker_->GetKillDistance();
    
    return dist <= kill_distance;
}

void CombatVisitor::Visit(Bear& bear) {
    if (!CanAttack()) {
        return;
    }
    
    int attacker_strength = RollDice();
    int defender_strength = RollDice();
    
    if (attacker_strength > defender_strength) {
        if (bear.Kill(attacker_->GetType())) {
            defender_died_ = true;
            std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                               ") killed " + bear.GetName() + " (Bear) [" + 
                               std::to_string(attacker_strength) + " vs " + 
                               std::to_string(defender_strength) + "]";
            EventBroadcaster::GetInstance().Notify(event);
        }
    }
}

void CombatVisitor::Visit(Elf& elf) {
    if (!CanAttack()) {
        return;
    }
    
    int attacker_strength = RollDice();
    int defender_strength = RollDice();
    
    if (attacker_strength > defender_strength) {
        if (elf.Kill(attacker_->GetType())) {
            defender_died_ = true;
            std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                               ") killed " + elf.GetName() + " (Elf) [" + 
                               std::to_string(attacker_strength) + " vs " + 
                               std::to_string(defender_strength) + "]";
            EventBroadcaster::GetInstance().Notify(event);
        }
    }
}

void CombatVisitor::Visit(Rogue& rogue) {
    if (!CanAttack()) {
        return;
    }
    
    int attacker_strength = RollDice();
    int defender_strength = RollDice();
    
    if (attacker_strength > defender_strength) {
        if (rogue.Kill(attacker_->GetType())) {
            defender_died_ = true;
            std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                               ") killed " + rogue.GetName() + " (Rogue) [" + 
                               std::to_string(attacker_strength) + " vs " + 
                               std::to_string(defender_strength) + "]";
            EventBroadcaster::GetInstance().Notify(event);
        }
    }
}

bool CombatVisitor::DidDefenderDie() const {
    return defender_died_;
}
