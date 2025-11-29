#include <iostream>
#include <memory>
#include <string>
#include "dungeon.h"
#include "factory.h"
#include "observer.h"

void PrintMenu() {
    std::cout << "\n===== Dungeon Editor Menu =====" << std::endl;
    std::cout << "1. Add NPC" << std::endl;
    std::cout << "2. Remove NPC" << std::endl;
    std::cout << "3. List NPCs" << std::endl;
    std::cout << "4. Save to file" << std::endl;
    std::cout << "5. Load from file" << std::endl;
    std::cout << "6. Start Battle" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "================================" << std::endl;
}

int main() {
    Dungeon dungeon;
    
    auto console_observer = std::make_shared<ConsoleObserver>();
    auto file_observer = std::make_shared<FileObserver>("log.txt");
    
    EventBroadcaster::GetInstance().Subscribe(console_observer);
    EventBroadcaster::GetInstance().Subscribe(file_observer);
    
    std::string choice;
    
    while (true) {
        PrintMenu();
        std::cout << "Enter choice: ";
        std::getline(std::cin, choice);
        
        if (choice == "1") {
            std::string type, name;
            double x, y;
            
            std::cout << "Enter NPC type (Bear/Elf/Rogue): ";
            std::getline(std::cin, type);
            
            std::cout << "Enter NPC name: ";
            std::getline(std::cin, name);
            
            std::cout << "Enter X coordinate (0-500): ";
            std::cin >> x;
            std::cout << "Enter Y coordinate (0-500): ";
            std::cin >> y;
            std::cin.ignore();
            
            Point pos(x, y);
            auto npc = NPCFactory::CreateNPC(type, name, pos);
            if (npc) {
                dungeon.AddNPC(npc);
            } else {
                std::cerr << "Unknown NPC type!" << std::endl;
            }
        }
        else if (choice == "2") {
            std::string name;
            std::cout << "Enter NPC name to remove: ";
            std::getline(std::cin, name);
            dungeon.RemoveNPC(name);
        }
        else if (choice == "3") {
            dungeon.PrintNPCs();
        }
        else if (choice == "4") {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            dungeon.SaveToFile(filename);
        }
        else if (choice == "5") {
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            dungeon.LoadFromFile(filename);
        }
        else if (choice == "6") {
            double range;
            std::cout << "Enter battle range: ";
            std::cin >> range;
            std::cin.ignore();
            dungeon.StartBattle(range);
        }
        else if (choice == "7") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }
    
    return 0;
}
