#include "observer.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void ConsoleObserver::Update(const std::string& event) {
    std::cout << "[LOG] " << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename) : filename_(filename) {}

void FileObserver::Update(const std::string& event) {
    std::ofstream file(filename_, std::ios::app);
    if (file.is_open()) {
        file << event << std::endl;
        file.close();
    }
}

EventBroadcaster& EventBroadcaster::GetInstance() {
    static EventBroadcaster instance;
    return instance;
}

void EventBroadcaster::Subscribe(std::shared_ptr<Observer> observer) {
    observers_.push_back(observer);
}

void EventBroadcaster::Unsubscribe(std::shared_ptr<Observer> observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void EventBroadcaster::Notify(const std::string& event) {
    for (auto& observer : observers_) {
        observer->Update(event);
    }
}
