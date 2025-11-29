#pragma once

#include <string>
#include <memory>
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
    NPCType GetType() const;
    std::string GetTypeString() const;
    bool IsAlive() const;
    
    virtual void Accept(BattleVisitor& visitor) = 0;
    virtual bool Kill(NPCType killer_type) = 0;
    
    double Distance(const std::shared_ptr<NPC>& other) const;

protected:
    std::string name_;
    Point position_;
    NPCType type_;
    bool alive_;
};

class Bear : public NPC {
public:
    Bear(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
};

class Rogue : public NPC {
public:
    Rogue(const std::string& name, const Point& position);
    void Accept(BattleVisitor& visitor) override;
    bool Kill(NPCType killer_type) override;
};
