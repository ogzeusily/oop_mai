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
protected:
    std::string name;
    Point position;
    bool alive;
    NPCType type;

public:
    NPC(const std::string& name, const Point& position, NPCType type);
    virtual ~NPC() = default;
    
    virtual std::string getTypeName() const = 0;
    NPCType getType() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    bool isAlive() const;
    void setAlive(bool alive);
    
    virtual void accept(BattleVisitor& visitor) = 0;
    virtual bool canKill(NPCType targetType) const = 0;
};

class Bear : public NPC {
public:
    Bear(const std::string& name, const Point& position);
    std::string getTypeName() const override;
    void accept(BattleVisitor& visitor) override;
    bool canKill(NPCType targetType) const override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, const Point& position);
    std::string getTypeName() const override;
    void accept(BattleVisitor& visitor) override;
    bool canKill(NPCType targetType) const override;
};

class Rogue : public NPC {
public:
    Rogue(const std::string& name, const Point& position);
    std::string getTypeName() const override;
    void accept(BattleVisitor& visitor) override;
    bool canKill(NPCType targetType) const override;
};
