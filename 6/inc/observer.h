#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "npc.h"

class EventObserver {
public:
    virtual ~EventObserver() = default;
    virtual void onKill(const std::string& killerName, const std::string& killerType,
                       const std::string& victimName, const std::string& victimType) = 0;
};

class ConsoleObserver : public EventObserver {
public:
    void onKill(const std::string& killerName, const std::string& killerType,
               const std::string& victimName, const std::string& victimType) override;
};

class FileObserver : public EventObserver {
private:
    std::string filename;

public:
    FileObserver(const std::string& filename = "log.txt");
    void onKill(const std::string& killerName, const std::string& killerType,
               const std::string& victimName, const std::string& victimType) override;
};

class EventManager {
private:
    static std::vector<std::shared_ptr<EventObserver>> observers;

public:
    static void subscribe(std::shared_ptr<EventObserver> observer);
    static void unsubscribe(std::shared_ptr<EventObserver> observer);
    static void notifyKill(const std::string& killerName, const std::string& killerType,
                          const std::string& victimName, const std::string& victimType);
    static void clear();
};
