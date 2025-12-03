#include "factory.h"
#include <fstream>
#include <sstream>

std::shared_ptr<NPC> NPCFactory::CreateNPC(const std::string& type,
                                           const std::string& name,
                                           const Point& position) {
    if (type == "Bear") {
        return CreateBear(name, position);
    } else if (type == "Elf") {
        return CreateElf(name, position);
    } else if (type == "Rogue") {
        return CreateRogue(name, position);
    }
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::CreateBear(const std::string& name, const Point& position) {
    return std::make_shared<Bear>(name, position);
}

std::shared_ptr<NPC> NPCFactory::CreateElf(const std::string& name, const Point& position) {
    return std::make_shared<Elf>(name, position);
}

std::shared_ptr<NPC> NPCFactory::CreateRogue(const std::string& name, const Point& position) {
    return std::make_shared<Rogue>(name, position);
}

std::vector<std::shared_ptr<NPC>> NPCFileLoader::LoadFromFile(const std::string& filename) {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        return npcs;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        double x, y;
        
        if (iss >> type >> name >> x >> y) {
            Point pos(x, y);
            auto npc = NPCFactory::CreateNPC(type, name, pos);
            if (npc) {
                npcs.push_back(npc);
            }
        }
    }
    
    file.close();
    return npcs;
}

void NPCFileLoader::SaveToFile(const std::vector<std::shared_ptr<NPC>>& npcs,
                               const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        return;
    }
    
    for (const auto& npc : npcs) {
        if (npc && npc->IsAlive()) {
            file << npc->GetTypeString() << " " 
                 << npc->GetName() << " " 
                 << npc->GetPosition().GetX() << " " 
                 << npc->GetPosition().GetY() << std::endl;
        }
    }
    
    file.close();
}
