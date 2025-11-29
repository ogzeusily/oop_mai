#pragma once

#include <string>
#include <vector>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const std::string& event) = 0;
};

class ConsoleObserver : public Observer {
public:
    void Update(const std::string& event) override;
};

class FileObserver : public Observer {
public:
    FileObserver(const std::string& filename = "log.txt");
    void Update(const std::string& event) override;

private:
    std::string filename_;
};

class EventBroadcaster {
public:
    static EventBroadcaster& GetInstance();
    
    void Subscribe(std::shared_ptr<Observer> observer);
    void Unsubscribe(std::shared_ptr<Observer> observer);
    void Notify(const std::string& event);

private:
    EventBroadcaster() = default;
    std::vector<std::shared_ptr<Observer>> observers_;
};