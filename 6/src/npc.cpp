#include "npc.h"
#include "battle.h"

NPC::NPC(const std::string& name, const Point& position, NPCType type)
    : name(name), position(position), alive(true), type(type) {}

NPCType NPC::getType() const {
    return type;
}

const std::string& NPC::getName() const {
    return name;
}

const Point& NPC::getPosition() const {
    return position;
}

bool NPC::isAlive() const {
    return alive;
}

void NPC::setAlive(bool alive) {
    this->alive = alive;
}

// ===== BEAR =====
Bear::Bear(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::BEAR) {}

std::string Bear::getTypeName() const {
    return "Bear";
}

void Bear::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Bear::canKill(NPCType targetType) const {
    return targetType == NPCType::ELF;
}

// ===== ELF =====
Elf::Elf(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::ELF) {}

std::string Elf::getTypeName() const {
    return "Elf";
}

void Elf::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Elf::canKill(NPCType targetType) const {
    return targetType == NPCType::ROGUE;
}

// ===== ROGUE =====
Rogue::Rogue(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::ROGUE) {}

std::string Rogue::getTypeName() const {
    return "Rogue";
}

void Rogue::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Rogue::canKill(NPCType targetType) const {
    return targetType == NPCType::ROGUE;
}
