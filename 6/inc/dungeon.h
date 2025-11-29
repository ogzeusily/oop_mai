#pragma once

#include <memory>
#include <vector>
#include <string>
#include "npc.h"
#include "point.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NPCType type, const std::string& name, const Point& position);
    static std::shared_ptr<NPC> createNPC(const std::string& typeStr, const std::string& name, double x, double y);
    static NPCType stringToType(const std::string& typeStr);
    static std::string typeToString(NPCType type);
};

class Dungeon {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    const double MAX_X = 500.0;
    const double MAX_Y = 500.0;

public:
    Dungeon();
    
    bool addNPC(const std::string& type, const std::string& name, double x, double y);
    void listNPCs() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    std::vector<std::shared_ptr<NPC>>& getNPCs();
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const;
    
    bool validateCoordinates(double x, double y) const;
    bool hasUniqueNames() const;
};
