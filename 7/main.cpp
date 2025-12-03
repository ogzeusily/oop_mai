#include <iostream>
#include <memory>
#include <random>
#include "inc/dungeon.h"
#include "inc/factory.h"
#include "inc/observer.h"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   NPC Battle Simulator - 30 Seconds" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Create dungeon
    Dungeon dungeon;
    
    // Setup observers for logging
    auto console_observer = std::make_shared<ConsoleObserver>();
    auto file_observer = std::make_shared<FileObserver>("game_log.txt");
    
    EventBroadcaster::GetInstance().Subscribe(console_observer);
    EventBroadcaster::GetInstance().Subscribe(file_observer);
    
    std::cout << "\nInitializing 50 NPCs at random locations..." << std::endl;
    std::cout << "Map size: 100x100 meters" << std::endl;
    std::cout << "NPC types: Bear (5m move, 10m kill), Elf (10m move, 50m kill), Rogue (10m move, 10m kill)" << std::endl;
    
    // Create 50 NPCs at random locations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, Dungeon::MAP_SIZE);
    
    const char* NPC_NAMES[] = {
        "Bear1", "Elf1", "Rogue1", "Bear2", "Elf2", "Rogue2", "Bear3", "Elf3", "Rogue3", "Bear4",
        "Elf4", "Rogue4", "Bear5", "Elf5", "Rogue5", "Bear6", "Elf6", "Rogue6", "Bear7", "Elf7",
        "Rogue7", "Bear8", "Elf8", "Rogue8", "Bear9", "Elf9", "Rogue9", "Bear10", "Elf10", "Rogue10",
        "Bear11", "Elf11", "Rogue11", "Bear12", "Elf12", "Rogue12", "Bear13", "Elf13", "Rogue13", "Bear14",
        "Elf14", "Rogue14", "Bear15", "Elf15", "Rogue15", "Bear16", "Elf16", "Rogue16", "Bear17", "Elf17"
    };
    
    int bear_count = 0, elf_count = 0, rogue_count = 0;
    
    for (int i = 0; i < 50; i++) {
        double x = dis(gen);
        double y = dis(gen);
        Point pos(x, y);
        
        int type_idx = i % 3;
        std::shared_ptr<NPC> npc;
        
        switch (type_idx) {
            case 0:
                npc = NPCFactory::CreateBear(NPC_NAMES[i], pos);
                bear_count++;
                break;
            case 1:
                npc = NPCFactory::CreateElf(NPC_NAMES[i], pos);
                elf_count++;
                break;
            case 2:
                npc = NPCFactory::CreateRogue(NPC_NAMES[i], pos);
                rogue_count++;
                break;
        }
        
        if (npc) {
            dungeon.AddNPC(npc);
        }
    }
    
    std::cout << "\nNPC Summary:" << std::endl;
    std::cout << "  Bears:  " << bear_count << std::endl;
    std::cout << "  Elves:  " << elf_count << std::endl;
    std::cout << "  Rogues: " << rogue_count << std::endl;
    
    std::cout << "\nStarting game for 30 seconds..." << std::endl;
    std::cout << "Three threads are running:" << std::endl;
    std::cout << "  1. Movement thread: Moves NPCs randomly" << std::endl;
    std::cout << "  2. Battle thread: Processes fights when NPCs are in range" << std::endl;
    std::cout << "  3. Display thread: Shows map every second" << std::endl;
    std::cout << "\n";
    
    // Start game for 30 seconds
    dungeon.StartGame(30);
    
    std::cout << "\nGame ended. Check 'game_log.txt' for detailed battle log." << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}