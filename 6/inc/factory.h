#pragma once

#include <string>
#include <memory>
#include <vector>
#include "npc.h"
#include "point.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> CreateNPC(const std::string& type, 
                                          const std::string& name, 
                                          const Point& position);
    
    static std::shared_ptr<NPC> CreateBear(const std::string& name, const Point& position);
    static std::shared_ptr<NPC> CreateElf(const std::string& name, const Point& position);
    static std::shared_ptr<NPC> CreateRogue(const std::string& name, const Point& position);
};

class NPCFileLoader {
public:
    static std::vector<std::shared_ptr<NPC>> LoadFromFile(const std::string& filename);
    static void SaveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, 
                          const std::string& filename);
};
