#include <iostream>
#include <memory>
#include <string>
#include <cctype>
#include <algorithm>
#include "inc/point.h"
#include "inc/npc.h"
#include "inc/dungeon.h"
#include "inc/battle.h"
#include "inc/observer.h"

void printMenu() {
    std::cout << "\n========== Dungeon Editor Menu ==========\n";
    std::cout << "1. Add NPC\n";
    std::cout << "2. List NPCs\n";
    std::cout << "3. Start Battle Mode\n";
    std::cout << "4. Save to file\n";
    std::cout << "5. Load from file\n";
    std::cout << "6. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Choose option: ";
}

void printNPCTypes() {
    std::cout << "Available NPC types:\n";
    std::cout << "  - Bear\n";
    std::cout << "  - Elf\n";
    std::cout << "  - Rogue\n";
}

void addNPCMenu(Dungeon& dungeon) {
    std::cout << "\n----- Add NPC -----\n";
    printNPCTypes();
    
    std::string type, name;
    double x, y;
    
    std::cout << "Enter NPC type: ";
    std::getline(std::cin, type);
    type.erase(0, type.find_first_not_of(" \t"));
    type.erase(type.find_last_not_of(" \t") + 1);
    
    std::cout << "Enter NPC name: ";
    std::getline(std::cin, name);
    name.erase(0, name.find_first_not_of(" \t"));
    name.erase(name.find_last_not_of(" \t") + 1);
    
    std::cout << "Enter X coordinate (0-500): ";
    std::cin >> x;
    
    std::cout << "Enter Y coordinate (0-500): ";
    std::cin >> y;
    
    std::cin.ignore();
    
    if (dungeon.addNPC(type, name, x, y)) {
        std::cout << "NPC '" << name << "' added successfully!\n";
    } else {
        std::cout << "Failed to add NPC.\n";
    }
}

void battleModeMenu(Dungeon& dungeon) {
    std::cout << "\n----- Battle Mode -----\n";
    
    if (dungeon.getNPCs().size() < 2) {
        std::cout << "Error: Need at least 2 NPCs to start battle\n";
        return;
    }
    
    double range;
    std::cout << "Enter battle range (meters): ";
    std::cin >> range;
    std::cin.ignore();
    
    std::cout << "\nStarting battle with range: " << range << " meters\n";
    std::cout << "============================\n";
    
    auto& npcs = dungeon.getNPCs();
    bool anyBattle = false;
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->isAlive() && npcs[j]->isAlive()) {
                double distance = npcs[i]->getPosition().distance(npcs[j]->getPosition());
                if (distance <= range) {
                    anyBattle = true;
                    std::cout << "\nBattle between " << npcs[i]->getTypeName() << " '" 
                              << npcs[i]->getName() << "' and " << npcs[j]->getTypeName() 
                              << " '" << npcs[j]->getName() << "' (distance: " 
                              << distance << "m)\n";
                    BattleEngine::executeBattle(npcs[i], npcs[j], range);
                }
            }
        }
    }
    
    if (!anyBattle) {
        std::cout << "No NPCs in range for battle.\n";
    }
    
    std::cout << "\n====== Battle Results ======\n";
    dungeon.listNPCs();
}

int main() {
    Dungeon dungeon;
    
    // Set up observers
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");
    
    EventManager::subscribe(consoleObserver);
    EventManager::subscribe(fileObserver);
    
    std::cout << "========== Dungeon Editor for Balagur Fate 3 ==========\n";
    std::cout << "Design Pattern: Factory, Visitor, Observer\n";
    std::cout << "======================================================\n";
    
    std::string choice;
    bool running = true;
    
    while (running) {
        printMenu();
        std::getline(std::cin, choice);
        choice.erase(0, choice.find_first_not_of(" \t"));
        choice.erase(choice.find_last_not_of(" \t") + 1);
        
        if (choice == "1") {
            addNPCMenu(dungeon);
        } else if (choice == "2") {
            dungeon.listNPCs();
        } else if (choice == "3") {
            battleModeMenu(dungeon);
        } else if (choice == "4") {
            std::string filename;
            std::cout << "Enter filename (default: dungeon.txt): ";
            std::getline(std::cin, filename);
            if (filename.empty()) filename = "dungeon.txt";
            dungeon.saveToFile(filename);
        } else if (choice == "5") {
            std::string filename;
            std::cout << "Enter filename (default: dungeon.txt): ";
            std::getline(std::cin, filename);
            if (filename.empty()) filename = "dungeon.txt";
            dungeon.loadFromFile(filename);
        } else if (choice == "6") {
            std::cout << "Exiting dungeon editor. Goodbye!\n";
            running = false;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    EventManager::clear();
    return 0;
}
