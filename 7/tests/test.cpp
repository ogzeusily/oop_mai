#include <gtest/gtest.h>
#include "../inc/dungeon.h"
#include "../inc/factory.h"
#include "../inc/observer.h"
#include <thread>
#include <chrono>
#include <random>
#include <cmath>
#include <memory>

class DungeonTest : public ::testing::Test {
protected:
    Dungeon dungeon;
};

TEST_F(DungeonTest, CreateBear) {
    auto bear = NPCFactory::CreateBear("TestBear", Point(10, 10));
    EXPECT_NE(bear, nullptr);
    EXPECT_EQ(bear->GetName(), "TestBear");
    EXPECT_EQ(bear->GetType(), NPCType::BEAR);
    EXPECT_EQ(bear->GetTypeString(), "Bear");
    EXPECT_TRUE(bear->IsAlive());
}

TEST_F(DungeonTest, CreateElf) {
    auto elf = NPCFactory::CreateElf("TestElf", Point(20, 20));
    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetName(), "TestElf");
    EXPECT_EQ(elf->GetType(), NPCType::ELF);
    EXPECT_EQ(elf->GetTypeString(), "Elf");
    EXPECT_TRUE(elf->IsAlive());
}

TEST_F(DungeonTest, CreateRogue) {
    auto rogue = NPCFactory::CreateRogue("TestRogue", Point(30, 30));
    EXPECT_NE(rogue, nullptr);
    EXPECT_EQ(rogue->GetName(), "TestRogue");
    EXPECT_EQ(rogue->GetType(), NPCType::ROGUE);
    EXPECT_EQ(rogue->GetTypeString(), "Rogue");
    EXPECT_TRUE(rogue->IsAlive());
}

TEST_F(DungeonTest, BearMoveDistance) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    EXPECT_DOUBLE_EQ(bear->GetMoveDistance(), 5.0);
}

TEST_F(DungeonTest, ElfMoveDistance) {
    auto elf = NPCFactory::CreateElf("Elf1", Point(20, 20));
    EXPECT_DOUBLE_EQ(elf->GetMoveDistance(), 10.0);
}

TEST_F(DungeonTest, RogueMoveDistance) {
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(30, 30));
    EXPECT_DOUBLE_EQ(rogue->GetMoveDistance(), 10.0);
}


TEST_F(DungeonTest, BearKillDistance) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    EXPECT_DOUBLE_EQ(bear->GetKillDistance(), 10.0);
}

TEST_F(DungeonTest, ElfKillDistance) {
    auto elf = NPCFactory::CreateElf("Elf1", Point(20, 20));
    EXPECT_DOUBLE_EQ(elf->GetKillDistance(), 50.0);
}

TEST_F(DungeonTest, RogueKillDistance) {
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(30, 30));
    EXPECT_DOUBLE_EQ(rogue->GetKillDistance(), 10.0);
}


TEST_F(DungeonTest, NPCPosition) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10.5, 20.5));
    Point pos = bear->GetPosition();
    EXPECT_DOUBLE_EQ(pos.GetX(), 10.5);
    EXPECT_DOUBLE_EQ(pos.GetY(), 20.5);
}

TEST_F(DungeonTest, NPCSetPosition) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    bear->SetPosition(Point(30, 40));
    Point pos = bear->GetPosition();
    EXPECT_DOUBLE_EQ(pos.GetX(), 30.0);
    EXPECT_DOUBLE_EQ(pos.GetY(), 40.0);
}


TEST_F(DungeonTest, NPCDistance) {
    auto npc1 = NPCFactory::CreateBear("Bear1", Point(0, 0));
    auto npc2 = NPCFactory::CreateElf("Elf1", Point(3, 4));
    
    double dist = npc1->Distance(npc2);
    EXPECT_DOUBLE_EQ(dist, 5.0);
}

TEST_F(DungeonTest, NPCDistanceZero) {
    auto npc1 = NPCFactory::CreateBear("Bear1", Point(50, 50));
    auto npc2 = NPCFactory::CreateRogue("Rogue1", Point(50, 50));
    
    double dist = npc1->Distance(npc2);
    EXPECT_DOUBLE_EQ(dist, 0.0);
}


TEST_F(DungeonTest, BearCannotBeKilledByElf) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    EXPECT_TRUE(bear->IsAlive());
    
    bool killed = bear->Kill(NPCType::ELF);
    EXPECT_FALSE(killed);
    EXPECT_TRUE(bear->IsAlive());
}

TEST_F(DungeonTest, BearCannotBeKilledByRogue) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    EXPECT_TRUE(bear->IsAlive());
    
    bool killed = bear->Kill(NPCType::ROGUE);
    EXPECT_FALSE(killed);
    EXPECT_TRUE(bear->IsAlive());
}

TEST_F(DungeonTest, ElfKilledByBear) {
    auto elf = NPCFactory::CreateElf("Elf1", Point(10, 10));
    EXPECT_TRUE(elf->IsAlive());
    
    bool killed = elf->Kill(NPCType::BEAR);
    EXPECT_TRUE(killed);
    EXPECT_FALSE(elf->IsAlive());
}

TEST_F(DungeonTest, ElfCannotBeKilledByRogue) {
    auto elf = NPCFactory::CreateElf("Elf1", Point(10, 10));
    EXPECT_TRUE(elf->IsAlive());
    
    bool killed = elf->Kill(NPCType::ROGUE);
    EXPECT_FALSE(killed);
    EXPECT_TRUE(elf->IsAlive());
}

TEST_F(DungeonTest, RogueKilledByElf) {
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(10, 10));
    EXPECT_TRUE(rogue->IsAlive());
    
    bool killed = rogue->Kill(NPCType::ELF);
    EXPECT_TRUE(killed);
    EXPECT_FALSE(rogue->IsAlive());
}

TEST_F(DungeonTest, RogueKilledByRogue) {
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(10, 10));
    EXPECT_TRUE(rogue->IsAlive());
    
    bool killed = rogue->Kill(NPCType::ROGUE);
    EXPECT_TRUE(killed);
    EXPECT_FALSE(rogue->IsAlive());
}

TEST_F(DungeonTest, RogueCannotBeKilledByBear) {
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(10, 10));
    EXPECT_TRUE(rogue->IsAlive());
    
    bool killed = rogue->Kill(NPCType::BEAR);
    EXPECT_FALSE(killed);
    EXPECT_TRUE(rogue->IsAlive());
}


TEST_F(DungeonTest, AddSingleNPC) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    dungeon.AddNPC(bear);
    
    auto alive = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive.size(), 1);
    EXPECT_EQ(alive[0]->GetName(), "Bear1");
}

TEST_F(DungeonTest, AddMultipleNPCs) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    auto elf = NPCFactory::CreateElf("Elf1", Point(20, 20));
    auto rogue = NPCFactory::CreateRogue("Rogue1", Point(30, 30));
    
    dungeon.AddNPC(bear);
    dungeon.AddNPC(elf);
    dungeon.AddNPC(rogue);
    
    auto alive = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive.size(), 3);
}

TEST_F(DungeonTest, MapBoundaries) {
    // Test that NPC is within map boundaries
    auto bear = NPCFactory::CreateBear("Bear1", Point(50, 50));
    dungeon.AddNPC(bear);
    
    auto alive = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive.size(), 1);
    
    Point pos = alive[0]->GetPosition();
    EXPECT_GE(pos.GetX(), 0);
    EXPECT_LE(pos.GetX(), Dungeon::MAP_SIZE);
    EXPECT_GE(pos.GetY(), 0);
    EXPECT_LE(pos.GetY(), Dungeon::MAP_SIZE);
}

TEST_F(DungeonTest, RemoveNPC) {
    auto bear = NPCFactory::CreateBear("Bear1", Point(10, 10));
    dungeon.AddNPC(bear);
    
    auto alive1 = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive1.size(), 1);
    
    dungeon.RemoveNPC("Bear1");
    
    auto alive2 = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive2.size(), 0);
}


TEST_F(DungeonTest, FactoryCreateNPC) {
    auto bear = NPCFactory::CreateNPC("Bear", "TestBear", Point(10, 10));
    EXPECT_NE(bear, nullptr);
    EXPECT_EQ(bear->GetType(), NPCType::BEAR);
    
    auto elf = NPCFactory::CreateNPC("Elf", "TestElf", Point(20, 20));
    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetType(), NPCType::ELF);
    
    auto rogue = NPCFactory::CreateNPC("Rogue", "TestRogue", Point(30, 30));
    EXPECT_NE(rogue, nullptr);
    EXPECT_EQ(rogue->GetType(), NPCType::ROGUE);
}

TEST_F(DungeonTest, FactoryCreateInvalidType) {
    auto invalid = NPCFactory::CreateNPC("InvalidType", "Test", Point(10, 10));
    EXPECT_EQ(invalid, nullptr);
}


TEST_F(DungeonTest, EventBroadcaster) {
    int event_count = 0;
    
    class CountingObserver : public Observer {
    public:
        CountingObserver(int* count) : count_(count) {}
        void Update(const std::string& event) override {
            (*count_)++;
        }
    private:
        int* count_;
    };
    
    auto observer = std::make_shared<CountingObserver>(&event_count);
    EventBroadcaster::GetInstance().Subscribe(observer);
    
    EventBroadcaster::GetInstance().Notify("Test event 1");
    EXPECT_EQ(event_count, 1);
    
    EventBroadcaster::GetInstance().Notify("Test event 2");
    EXPECT_EQ(event_count, 2);
    
    EventBroadcaster::GetInstance().Unsubscribe(observer);
}


TEST_F(DungeonTest, LargeScaleCreation) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, Dungeon::MAP_SIZE);
    
    for (int i = 0; i < 50; i++) {
        double x = dis(gen);
        double y = dis(gen);
        Point pos(x, y);
        
        int type_idx = i % 3;
        std::shared_ptr<NPC> npc;
        
        switch (type_idx) {
            case 0:
                npc = NPCFactory::CreateBear("Bear" + std::to_string(i), pos);
                break;
            case 1:
                npc = NPCFactory::CreateElf("Elf" + std::to_string(i), pos);
                break;
            case 2:
                npc = NPCFactory::CreateRogue("Rogue" + std::to_string(i), pos);
                break;
        }
        
        if (npc) {
            dungeon.AddNPC(npc);
        }
    }
    
    auto alive = dungeon.GetAliveNPCs();
    EXPECT_EQ(alive.size(), 50);
}

TEST_F(DungeonTest, AllAliveBoundaries) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, Dungeon::MAP_SIZE);
    
    for (int i = 0; i < 20; i++) {
        double x = dis(gen);
        double y = dis(gen);
        Point pos(x, y);
        
        auto npc = NPCFactory::CreateBear("Bear" + std::to_string(i), pos);
        dungeon.AddNPC(npc);
    }
    
    auto alive = dungeon.GetAliveNPCs();
    for (const auto& npc : alive) {
        Point pos = npc->GetPosition();
        EXPECT_GE(pos.GetX(), 0);
        EXPECT_LE(pos.GetX(), Dungeon::MAP_SIZE);
        EXPECT_GE(pos.GetY(), 0);
        EXPECT_LE(pos.GetY(), Dungeon::MAP_SIZE);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}