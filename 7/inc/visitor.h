#pragma once

#include <memory>
#include <random>

class Bear;
class Elf;
class Rogue;
class NPC;

class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    
    virtual void Visit(Bear& bear) = 0;
    virtual void Visit(Elf& elf) = 0;
    virtual void Visit(Rogue& rogue) = 0;
};

class CombatVisitor : public BattleVisitor {
public:
    CombatVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);
    
    void Visit(Bear& bear) override;
    void Visit(Elf& elf) override;
    void Visit(Rogue& rogue) override;
    
    bool DidDefenderDie() const;

private:
    std::shared_ptr<NPC> attacker_;
    std::shared_ptr<NPC> defender_;
    bool defender_died_;
    
    int RollDice();
    bool CanAttack();
};
