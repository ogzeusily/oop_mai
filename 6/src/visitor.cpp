#include "visitor.h"
#include "npc.h"
#include "observer.h"

CombatVisitor::CombatVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, double range)
    : attacker_(attacker), defender_(defender), range_(range), defender_died_(false) {}

bool CombatVisitor::ShouldAttack() {
    if (!attacker_->IsAlive() || !defender_->IsAlive()) {
        return false;
    }
    
    double dist = attacker_->Distance(defender_);
    return dist <= range_;
}

bool CombatVisitor::DidDefenderDie() const {
    return defender_died_;
}

void CombatVisitor::Visit(Bear& bear) {
    if (!ShouldAttack()) {
        return;
    }
    
    if (bear.Kill(attacker_->GetType())) {
        defender_died_ = true;
        std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                           ") killed " + bear.GetName() + " (Bear)";
        EventBroadcaster::GetInstance().Notify(event);
    }
}

void CombatVisitor::Visit(Elf& elf) {
    if (!ShouldAttack()) {
        return;
    }
    
    if (elf.Kill(attacker_->GetType())) {
        defender_died_ = true;
        std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                           ") killed " + elf.GetName() + " (Elf)";
        EventBroadcaster::GetInstance().Notify(event);
    }
}

void CombatVisitor::Visit(Rogue& rogue) {
    if (!ShouldAttack()) {
        return;
    }
    
    if (rogue.Kill(attacker_->GetType())) {
        defender_died_ = true;
        std::string event = attacker_->GetName() + " (" + attacker_->GetTypeString() + 
                           ") killed " + rogue.GetName() + " (Rogue)";
        EventBroadcaster::GetInstance().Notify(event);
    }
}
