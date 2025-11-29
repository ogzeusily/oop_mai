#include "battle.h"
#include "observer.h"
#include <iostream>

BattleEngine::BattleCombatant::BattleCombatant(NPC* opponent, double range)
    : opponent(opponent), range(range), combatantAlive(true) {}

void BattleEngine::BattleCombatant::visit(Bear& bear) {
    if (!bear.isAlive() || !opponent->isAlive()) {
        combatantAlive = bear.isAlive();
        return;
    }
    
    double distance = bear.getPosition().distance(opponent->getPosition());
    if (distance <= range && bear.canKill(opponent->getType())) {
        opponent->setAlive(false);
        EventManager::notifyKill(bear.getName(), bear.getTypeName(),
                                opponent->getName(), opponent->getTypeName());
    }
}

void BattleEngine::BattleCombatant::visit(Elf& elf) {
    if (!elf.isAlive() || !opponent->isAlive()) {
        combatantAlive = elf.isAlive();
        return;
    }
    
    double distance = elf.getPosition().distance(opponent->getPosition());
    if (distance <= range && elf.canKill(opponent->getType())) {
        opponent->setAlive(false);
        EventManager::notifyKill(elf.getName(), elf.getTypeName(),
                                opponent->getName(), opponent->getTypeName());
    }
}

void BattleEngine::BattleCombatant::visit(Rogue& rogue) {
    if (!rogue.isAlive() || !opponent->isAlive()) {
        combatantAlive = rogue.isAlive();
        return;
    }
    
    double distance = rogue.getPosition().distance(opponent->getPosition());
    if (distance <= range && rogue.canKill(opponent->getType())) {
        opponent->setAlive(false);
        EventManager::notifyKill(rogue.getName(), rogue.getTypeName(),
                                opponent->getName(), opponent->getTypeName());
    }
}

bool BattleEngine::BattleCombatant::isCombatantAlive() const {
    return combatantAlive;
}

void BattleEngine::executeBattle(std::shared_ptr<NPC>& npc1, std::shared_ptr<NPC>& npc2, double range) {
    if (!npc1->isAlive() || !npc2->isAlive()) {
        return;
    }
    
    BattleCombatant npc1_attacks(npc2.get(), range);
    npc1->accept(npc1_attacks);
    
    BattleCombatant npc2_attacks(npc1.get(), range);
    npc2->accept(npc2_attacks);
}
