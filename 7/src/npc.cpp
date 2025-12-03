#include "npc.h"
#include "visitor.h"
#include <cmath>
#include <shared_mutex>

NPC::NPC(const std::string& name, const Point& position, NPCType type)
    : name_(name), position_(position), type_(type), alive_(true) {}

std::string NPC::GetName() const {
    return name_;
}

Point NPC::GetPosition() const {
    std::shared_lock<std::shared_mutex> lock(position_mutex_);
    return position_;
}

void NPC::SetPosition(const Point& position) {
    std::lock_guard<std::shared_mutex> lock(position_mutex_);
    position_ = position;
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
    std::shared_lock<std::shared_mutex> lock(alive_mutex_);
    return alive_;
}

void NPC::SetAlive(bool alive) {
    std::lock_guard<std::shared_mutex> lock(alive_mutex_);
    alive_ = alive;
}

double NPC::Distance(const std::shared_ptr<NPC>& other) const {
    return GetPosition().Distance(other->GetPosition());
}

std::shared_mutex& NPC::GetPositionMutex() const {
    return position_mutex_;
}

std::shared_mutex& NPC::GetAliveMutex() const {
    return alive_mutex_;
}

Bear::Bear(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::BEAR) {}

void Bear::Accept(BattleVisitor& visitor) {
    visitor.Visit(*this);
}

bool Bear::Kill(NPCType killer_type) {
    return false;
}

Elf::Elf(const std::string& name, const Point& position)
    : NPC(name, position, NPCType::ELF) {}

void Elf::Accept(BattleVisitor& visitor) {
    visitor.Visit(*this);
}

bool Elf::Kill(NPCType killer_type) {
    if (killer_type == NPCType::BEAR) {
        alive_ = false;
        return true;
    }
    return false;
}

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
