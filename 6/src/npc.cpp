#include "npc.h"
#include "visitor.h"
#include <cmath>

NPC::NPC(const std::string& name, const Point& position, NPCType type)
    : name_(name), position_(position), type_(type), alive_(true) {}

std::string NPC::GetName() const {
    return name_;
}

Point NPC::GetPosition() const {
    return position_;
}

NPCType NPC::GetType() const {
    return type_;
}

std::string NPC::GetTypeString() const {
    switch (type_) {
        case NPCType::BEAR: return "Bear";
        case NPCType::ELF: return "Elf";
        case NPCType::ROGUE: return "Rogue";
    }
    return "Unknown";
}

bool NPC::IsAlive() const {
    return alive_;
}

double NPC::Distance(const std::shared_ptr<NPC>& other) const {
    return position_.Distance(other->GetPosition());
}

// Bear implementation
Bear::Bear(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::BEAR) {}

void Bear::Accept(BattleVisitor& visitor) {
    visitor.Visit(*this);
}

bool Bear::Kill(NPCType killer_type) {
    // Медведь может быть убит только медведем (то есть не может быть убит)
    // Медведь убивает эльфов, но это проверяется на стороне атакующего
    return false;
}

// Elf implementation
Elf::Elf(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::ELF) {}

void Elf::Accept(BattleVisitor& visitor) {
    visitor.Visit(*this);
}

bool Elf::Kill(NPCType killer_type) {
    // Эльф может быть убит медведем
    if (killer_type == NPCType::BEAR) {
        alive_ = false;
        return true;
    }
    return false;
}

// Rogue implementation
Rogue::Rogue(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::ROGUE) {}

void Rogue::Accept(BattleVisitor& visitor) {
    visitor.Visit(*this);
}

bool Rogue::Kill(NPCType killer_type) {
    if (killer_type == NPCType::ELF || killer_type == NPCType::ROGUE) {
        alive_ = false;
        return true;
    }
    return false;
}
