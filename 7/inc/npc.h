#pragma once

#include <string>
#include <memory>
#include <shared_mutex>
#include "point.h"

class BattleVisitor;

enum class NPCType {
    BEAR,
    ELF,
    ROGUE
};

class NPC {
public:
    NPC(const std::string& name, const Point& position, NPCType type);
    virtual ~NPC() = default;
    
    std::string GetName() const;
    Point GetPosition() const;
    void SetPosition(const Point& position);
    NPCType GetType() const;
    std::string GetTypeString() const;
    bool IsAlive() const;
    void SetAlive(bool alive);
    
    virtual void Accept(BattleVisitor& visitor) = 0;
    virtual bool Kill(NPCType killer_type) = 0;
    
    virtual double GetMoveDistance() const = 0;
    virtual double GetKillDistance() const = 0;
    
    double Distance(const std::shared_ptr<NPC>& other) const;
    std::shared_mutex& GetPositionMutex() const;
    std::shared_mutex& GetAliveMutex() const;

protected:
    std::string name_;
    mutable Point position_;
    mutable std::shared_mutex position_mutex_;
    NPCType type_;
    mutable bool alive_;
    mutable std::shared_mutex alive_mutex_;
};

class Bear : public NPC {
public:
    Bear(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
    double GetMoveDistance() const override { return 5.0; }
    double GetKillDistance() const override { return 10.0; }
};

class Elf : public NPC {
public:
    Elf(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
    double GetMoveDistance() const override { return 10.0; }
    double GetKillDistance() const override { return 50.0; }
};

class Rogue : public NPC {
public:
    Rogue(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
    double GetMoveDistance() const override { return 10.0; }
    double GetKillDistance() const override { return 10.0; }
};
