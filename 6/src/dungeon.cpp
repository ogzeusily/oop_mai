#include "dungeon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Dungeon::Dungeon() {}

bool Dungeon::validateCoordinates(double x, double y) const {
    return x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y;
}

bool Dungeon::hasUniqueNames() const {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->getName() == npcs[j]->getName()) {
                return false;
            }
        }
    }
    return true;
}

bool Dungeon::addNPC(const std::string& type, const std::string& name, double x, double y) {
    if (!validateCoordinates(x, y)) {
        std::cout << "Error: Coordinates must be in range [0, 500]\n";
        return false;
    }
    
    for (const auto& npc : npcs) {
        if (npc->getName() == name) {
            std::cout << "Error: NPC with name '" << name << "' already exists\n";
            return false;
        }
    }
    
    auto newNPC = NPCFactory::createNPC(type, name, x, y);
    if (!newNPC) {
        std::cout << "Error: Unknown NPC type '" << type << "'\n";
        return false;
    }
    
    npcs.push_back(newNPC);
    return true;
}

void Dungeon::listNPCs() const {
    if (npcs.empty()) {
        std::cout << "Dungeon is empty.\n";
        return;
    }
    
    std::cout << "\n========== Dungeon NPCs ==========\n";
    std::cout << std::left << std::setw(15) << "Type" << std::setw(20) << "Name" 
              << std::setw(12) << "X" << std::setw(12) << "Y" << std::setw(10) << "Status\n";
    std::cout << "===================================\n";
    
    for (const auto& npc : npcs) {
        std::cout << std::left << std::setw(15) << npc->getTypeName()
                  << std::setw(20) << npc->getName()
                  << std::fixed << std::setprecision(1)
                  << std::setw(12) << npc->getPosition().getX()
                  << std::setw(12) << npc->getPosition().getY()
                  << std::setw(10) << (npc->isAlive() ? "Alive" : "Dead") << "\n";
    }
    std::cout << "===================================\n\n";
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << " for writing\n";
        return;
    }
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npc->getTypeName() << " "
                 << npc->getName() << " "
                 << std::fixed << std::setprecision(1)
                 << npc->getPosition().getX() << " "
                 << npc->getPosition().getY() << "\n";
        }
    }
    
    file.close();
    std::cout << "Dungeon saved to " << filename << "\n";
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << " for reading\n";
        return;
    }
    
    npcs.clear();
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string type, name;
        double x, y;
        
        if (iss >> type >> name >> x >> y) {
            if (addNPC(type, name, x, y)) {
                count++;
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " NPCs from " << filename << "\n";
}

std::vector<std::shared_ptr<NPC>>& Dungeon::getNPCs() {
    return npcs;
}

const std::vector<std::shared_ptr<NPC>>& Dungeon::getNPCs() const {
    return npcs;
}

std::shared_ptr<NPC> NPCFactory::createNPC(NPCType type, const std::string& name, const Point& position) {
    switch (type) {
        case NPCType::BEAR:
            return std::make_shared<Bear>(name, position);
        case NPCType::ELF:
            return std::make_shared<Elf>(name, position);
        case NPCType::ROGUE:
            return std::make_shared<Rogue>(name, position);
        default:
            return nullptr;
    }
}

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& typeStr, const std::string& name, double x, double y) {
    NPCType type = stringToType(typeStr);
    return createNPC(type, name, Point(x, y));
}

NPCType NPCFactory::stringToType(const std::string& typeStr) {
    if (typeStr == "Bear" || typeStr == "bear" || typeStr == "BEAR") {
        return NPCType::BEAR;
    } else if (typeStr == "Elf" || typeStr == "elf" || typeStr == "ELF") {
        return NPCType::ELF;
    } else if (typeStr == "Rogue" || typeStr == "rogue" || typeStr == "ROGUE") {
        return NPCType::ROGUE;
    }
    return NPCType::BEAR;
}

std::string NPCFactory::typeToString(NPCType type) {
    switch (type) {
        case NPCType::BEAR:
            return "Bear";
        case NPCType::ELF:
            return "Elf";
        case NPCType::ROGUE:
            return "Rogue";
        default:
            return "Unknown";
    }
}
