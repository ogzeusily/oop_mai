#include "observer.h"
#include <iostream>
#include <fstream>

std::vector<std::shared_ptr<EventObserver>> EventManager::observers;

void ConsoleObserver::onKill(const std::string& killerName, const std::string& killerType,
                            const std::string& victimName, const std::string& victimType) {
    std::cout << "[KILL] " << killerType << " '" << killerName << "' has killed "
              << victimType << " '" << victimName << "'\n";
}

FileObserver::FileObserver(const std::string& filename) : filename(filename) {}

void FileObserver::onKill(const std::string& killerName, const std::string& killerType,
                         const std::string& victimName, const std::string& victimType) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "[KILL] " << killerType << " '" << killerName << "' has killed "
             << victimType << " '" << victimName << "'\n";
        file.close();
    }
}

void EventManager::subscribe(std::shared_ptr<EventObserver> observer) {
    observers.push_back(observer);
}

void EventManager::unsubscribe(std::shared_ptr<EventObserver> observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void EventManager::notifyKill(const std::string& killerName, const std::string& killerType,
                             const std::string& victimName, const std::string& victimType) {
    for (const auto& observer : observers) {
        observer->onKill(killerName, killerType, victimName, victimType);
    }
}

void EventManager::clear() {
    observers.clear();
}
