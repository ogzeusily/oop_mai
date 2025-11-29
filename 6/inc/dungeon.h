#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <memory>
#include <string>
#include "npc.h"

class Dungeon {
public:
    Dungeon();
    
    void AddNPC(std::shared_ptr<NPC> npc);
    void RemoveNPC(const std::string& name);
    void PrintNPCs() const;
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void StartBattle(double range);
    std::vector<std::shared_ptr<NPC>>& GetNPCs();
    
    static const double MAX_X;
    static const double MAX_Y;

private:
    std::vector<std::shared_ptr<NPC>> npcs_;
};

#endif // DUNGEON_H
