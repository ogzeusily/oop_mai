#pragma once

#include <vector>
#include <memory>
#include <string>
#include <shared_mutex>
#include <thread>
#include <queue>
#include <atomic>
#include <condition_variable>
#include "npc.h"

struct BattleTask {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class Dungeon {
public:
    Dungeon();
    ~Dungeon();
    
    void AddNPC(std::shared_ptr<NPC> npc);
    void RemoveNPC(const std::string& name);
    void PrintNPCs() const;
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void StartGame(int duration_seconds = 30);
    void StopGame();
    
    std::vector<std::shared_ptr<NPC>> GetAliveNPCs() const;
    static const double MAP_SIZE;

private:
    void MovementThreadFunc();
    void BattleThreadFunc();
    void PrintMapThreadFunc();
    void AddBattleTask(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);
    
    mutable std::shared_mutex npcs_mutex_;
    std::vector<std::shared_ptr<NPC>> npcs_;
    
    std::atomic<bool> running_{false};
    std::thread movement_thread_;
    std::thread battle_thread_;
    std::thread print_thread_;
    
    mutable std::mutex battle_queue_mutex_;
    mutable std::condition_variable battle_queue_cv_;
    std::queue<BattleTask> battle_queue_;
    
    mutable std::mutex cout_mutex_;
};
