#pragma once

#include <memory>
#include "npc.h"

class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    virtual void visit(Bear& bear) = 0;
    virtual void visit(Elf& elf) = 0;
    virtual void visit(Rogue& rogue) = 0;
};

class BattleEngine {
private:
    class BattleCombatant : public BattleVisitor {
    private:
        NPC* opponent;
        double range;
        bool combatantAlive;

    public:
        BattleCombatant(NPC* opponent, double range);
        
        void visit(Bear& bear) override;
        void visit(Elf& elf) override;
        void visit(Rogue& rogue) override;
        
        bool isCombatantAlive() const;
    };

public:
    static void executeBattle(std::shared_ptr<NPC>& npc1, std::shared_ptr<NPC>& npc2, double range);
};
