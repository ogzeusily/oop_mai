#pragma once


#include <memory>

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
    CombatVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, double range);
    
    void Visit(Bear& bear) override;
    void Visit(Elf& elf) override;
    void Visit(Rogue& rogue) override;
    
    bool ShouldAttack();
    bool DidDefenderDie() const;

private:
    std::shared_ptr<NPC> attacker_;
    std::shared_ptr<NPC> defender_;
    double range_;
    bool defender_died_;
};
