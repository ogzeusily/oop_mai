#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>
#include "point.h"
#include "npc.h"
#include "factory.h"
#include "dungeon.h"
#include "visitor.h"
#include "observer.h"

class PointTest : public ::testing::Test {
protected:
    Point p1{10.0, 20.0};
    Point p2{13.0, 24.0};
};

TEST_F(PointTest, ConstructorInitialization) {
    Point p(5.0, 10.0);
    EXPECT_EQ(p.GetX(), 5.0);
    EXPECT_EQ(p.GetY(), 10.0);
}

TEST_F(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.GetX(), 0.0);
    EXPECT_EQ(p.GetY(), 0.0);
}

TEST_F(PointTest, DistanceCalculation) {
    double dist = p1.Distance(p2);
    EXPECT_NEAR(dist, 5.0, 0.001);
}

TEST_F(PointTest, DistanceSamePoint) {
    Point p(15.0, 25.0);
    EXPECT_NEAR(p.Distance(p), 0.0, 0.001);
}

// NPC Factory Tests
class NPCFactoryTest : public ::testing::Test {};

TEST_F(NPCFactoryTest, CreateBear) {
    Point pos(50.0, 50.0);
    auto bear = NPCFactory::CreateBear("Misha", pos);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->GetName(), "Misha");
    EXPECT_EQ(bear->GetType(), NPCType::BEAR);
    EXPECT_EQ(bear->GetTypeString(), "Bear");
    EXPECT_TRUE(bear->IsAlive());
}

TEST_F(NPCFactoryTest, CreateElf) {
    Point pos(100.0, 100.0);
    auto elf = NPCFactory::CreateElf("Legolas", pos);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetName(), "Legolas");
    EXPECT_EQ(elf->GetType(), NPCType::ELF);
    EXPECT_EQ(elf->GetTypeString(), "Elf");
}

TEST_F(NPCFactoryTest, CreateRogue) {
    Point pos(150.0, 150.0);
    auto rogue = NPCFactory::CreateRogue("Robin", pos);
    ASSERT_NE(rogue, nullptr);
    EXPECT_EQ(rogue->GetName(), "Robin");
    EXPECT_EQ(rogue->GetType(), NPCType::ROGUE);
    EXPECT_EQ(rogue->GetTypeString(), "Rogue");
}

TEST_F(NPCFactoryTest, CreateNPCByTypeString) {
    Point pos(50.0, 50.0);
    auto bear = NPCFactory::CreateNPC("Bear", "TestBear", pos);
    auto elf = NPCFactory::CreateNPC("Elf", "TestElf", pos);
    auto rogue = NPCFactory::CreateNPC("Rogue", "TestRogue", pos);
    
    ASSERT_NE(bear, nullptr);
    ASSERT_NE(elf, nullptr);
    ASSERT_NE(rogue, nullptr);
    EXPECT_EQ(bear->GetType(), NPCType::BEAR);
    EXPECT_EQ(elf->GetType(), NPCType::ELF);
    EXPECT_EQ(rogue->GetType(), NPCType::ROGUE);
}

TEST_F(NPCFactoryTest, CreateNPCInvalidType) {
    Point pos(50.0, 50.0);
    auto npc = NPCFactory::CreateNPC("Dragon", "InvalidNPC", pos);
    EXPECT_EQ(npc, nullptr);
}

// NPC Kill Tests
class NPCKillTest : public ::testing::Test {
protected:
    Point pos{250.0, 250.0};
};

TEST_F(NPCKillTest, ElfKillsRogue) {
    auto elf = NPCFactory::CreateElf("TestElf", pos);
    auto rogue = std::make_shared<Rogue>("TestRogue", pos);
    
    EXPECT_TRUE(rogue->Kill(NPCType::ELF));
    EXPECT_FALSE(rogue->IsAlive());
}

TEST_F(NPCKillTest, RogueKillsRogue) {
    auto rogue1 = std::make_shared<Rogue>("TestRogue1", pos);
    auto rogue2 = std::make_shared<Rogue>("TestRogue2", pos);
    
    EXPECT_TRUE(rogue2->Kill(NPCType::ROGUE));
    EXPECT_FALSE(rogue2->IsAlive());
}

TEST_F(NPCKillTest, BearKillsElf) {
    auto bear = std::make_shared<Bear>("TestBear", pos);
    auto elf = std::make_shared<Elf>("TestElf", pos);
    
    EXPECT_TRUE(elf->Kill(NPCType::BEAR));
    EXPECT_FALSE(elf->IsAlive());
}

TEST_F(NPCKillTest, BearCantBeKilled) {
    auto bear = std::make_shared<Bear>("TestBear", pos);
    
    EXPECT_FALSE(bear->Kill(NPCType::ROGUE));
    EXPECT_FALSE(bear->Kill(NPCType::ELF));
    EXPECT_FALSE(bear->Kill(NPCType::BEAR));
    EXPECT_TRUE(bear->IsAlive());
}

TEST_F(NPCKillTest, RogueCantBeKilledByBear) {
    auto rogue = std::make_shared<Rogue>("TestRogue", pos);
    
    EXPECT_FALSE(rogue->Kill(NPCType::BEAR));
    EXPECT_TRUE(rogue->IsAlive());
}

TEST_F(NPCKillTest, ElfCantBeKilledByRogue) {
    auto elf = std::make_shared<Elf>("TestElf", pos);
    
    EXPECT_FALSE(elf->Kill(NPCType::ROGUE));
    EXPECT_TRUE(elf->IsAlive());
}

// Dungeon Tests
class DungeonTest : public ::testing::Test {
protected:
    Dungeon dungeon;
    Point p1{50.0, 50.0};
    Point p2{100.0, 100.0};
    Point p3{200.0, 200.0};
    
    void SetUp() override {
        // Clear log file before each test
        std::ofstream file("log.txt");
        file.close();
    }
};

TEST_F(DungeonTest, AddNPC) {
    auto bear = NPCFactory::CreateBear("TestBear", p1);
    dungeon.AddNPC(bear);
    EXPECT_EQ(dungeon.GetNPCs().size(), 1);
}

TEST_F(DungeonTest, AddMultipleNPCs) {
    auto bear = NPCFactory::CreateBear("Bear1", p1);
    auto elf = NPCFactory::CreateElf("Elf1", p2);
    auto rogue = NPCFactory::CreateRogue("Rogue1", p3);
    
    dungeon.AddNPC(bear);
    dungeon.AddNPC(elf);
    dungeon.AddNPC(rogue);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 3);
}

TEST_F(DungeonTest, RemoveNPC) {
    auto bear = NPCFactory::CreateBear("TestBear", p1);
    dungeon.AddNPC(bear);
    EXPECT_EQ(dungeon.GetNPCs().size(), 1);
    
    dungeon.RemoveNPC("TestBear");
    EXPECT_EQ(dungeon.GetNPCs().size(), 0);
}

TEST_F(DungeonTest, RemoveNonexistentNPC) {
    auto bear = NPCFactory::CreateBear("TestBear", p1);
    dungeon.AddNPC(bear);
    
    dungeon.RemoveNPC("NonExistent");
    EXPECT_EQ(dungeon.GetNPCs().size(), 1);
}

TEST_F(DungeonTest, DuplicateNPCName) {
    auto bear1 = NPCFactory::CreateBear("Misha", p1);
    auto bear2 = NPCFactory::CreateBear("Misha", p2);
    
    dungeon.AddNPC(bear1);
    dungeon.AddNPC(bear2);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 1);
}

TEST_F(DungeonTest, NPCOutOfBounds) {
    Point out_of_bounds(600.0, 600.0);
    auto bear = NPCFactory::CreateBear("OutOfBounds", out_of_bounds);
    dungeon.AddNPC(bear);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 0);
}

TEST_F(DungeonTest, SaveToFile) {
    auto bear = NPCFactory::CreateBear("SaveBear", p1);
    auto elf = NPCFactory::CreateElf("SaveElf", p2);
    
    dungeon.AddNPC(bear);
    dungeon.AddNPC(elf);
    
    dungeon.SaveToFile("test_save.txt");
    
    // Check if file was created
    std::ifstream file("test_save.txt");
    EXPECT_TRUE(file.is_open());
    file.close();
}

TEST_F(DungeonTest, LoadFromFile) {
    {
        Dungeon d1;
        auto bear = NPCFactory::CreateBear("LoadBear", p1);
        auto elf = NPCFactory::CreateElf("LoadElf", p2);
        d1.AddNPC(bear);
        d1.AddNPC(elf);
        d1.SaveToFile("test_load.txt");
    }
    
    Dungeon d2;
    d2.LoadFromFile("test_load.txt");
    
    EXPECT_EQ(d2.GetNPCs().size(), 2);
    EXPECT_EQ(d2.GetNPCs()[0]->GetName(), "LoadBear");
    EXPECT_EQ(d2.GetNPCs()[1]->GetName(), "LoadElf");
}

class BattleVisitorTest : public ::testing::Test {
protected:
    Point p1{50.0, 50.0};
    Point p2{60.0, 60.0};
    Point p3{150.0, 150.0};
};

TEST_F(BattleVisitorTest, ElfAttacksRogue) {
    auto elf = NPCFactory::CreateElf("TestElf", p1);
    auto rogue = std::make_shared<Rogue>("TestRogue", p2);
    
    CombatVisitor visitor(elf, rogue, 20.0);
    rogue->Accept(visitor);
    
    EXPECT_FALSE(rogue->IsAlive());
}

TEST_F(BattleVisitorTest, RogueAttacksRogue) {
    auto rogue1 = NPCFactory::CreateRogue("TestRogue1", p1);
    auto rogue2 = std::make_shared<Rogue>("TestRogue2", p2);
    
    CombatVisitor visitor(rogue1, rogue2, 20.0);
    rogue2->Accept(visitor);
    
    EXPECT_FALSE(rogue2->IsAlive());
}

TEST_F(BattleVisitorTest, BearAttacksElf) {
    auto bear = NPCFactory::CreateBear("TestBear", p1);
    auto elf = std::make_shared<Elf>("TestElf", p2);
    
    CombatVisitor visitor(bear, elf, 20.0);
    elf->Accept(visitor);
    
    EXPECT_FALSE(elf->IsAlive());
}

TEST_F(BattleVisitorTest, OutOfRange) {
    auto elf = NPCFactory::CreateElf("TestElf", p1);
    auto rogue = std::make_shared<Rogue>("TestRogue", p3);
    
    CombatVisitor visitor(elf, rogue, 50.0);
    rogue->Accept(visitor);
    
    EXPECT_TRUE(rogue->IsAlive());
}

class ObserverTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream file("test_log.txt");
        file.close();
    }
    
    void TearDown() override {
        std::remove("test_log.txt");
    }
};

TEST_F(ObserverTest, FileObserverLogsEvent) {
    FileObserver observer("test_log.txt");
    observer.Update("Test event message");
    
    std::ifstream file("test_log.txt");
    std::string line;
    std::getline(file, line);
    file.close();
    
    EXPECT_EQ(line, "Test event message");
}

TEST_F(ObserverTest, EventBroadcaster) {
    EventBroadcaster& broadcaster = EventBroadcaster::GetInstance();
    
    auto observer1 = std::make_shared<FileObserver>("test_log.txt");
    broadcaster.Subscribe(observer1);
    broadcaster.Notify("Test broadcast message");
    
    std::ifstream file("test_log.txt");
    std::string line;
    std::getline(file, line);
    file.close();
    
    EXPECT_EQ(line, "Test broadcast message");
}

class IntegrationTest : public ::testing::Test {
protected:
    Dungeon dungeon;
    Point p1{50.0, 50.0};
    Point p2{60.0, 60.0};
    Point p3{70.0, 70.0};
    
    void SetUp() override {
        std::ofstream file("log.txt");
        file.close();
        
        EventBroadcaster::GetInstance().Subscribe(std::make_shared<ConsoleObserver>());
    }
};

TEST_F(IntegrationTest, BattleElfVsRogue) {
    auto elf = NPCFactory::CreateElf("TestElf", p1);
    auto rogue = NPCFactory::CreateRogue("TestRogue", p2);
    
    dungeon.AddNPC(elf);
    dungeon.AddNPC(rogue);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 2);
    
    dungeon.StartBattle(20.0);
    
    EXPECT_FALSE(dungeon.GetNPCs()[1]->IsAlive());
}

TEST_F(IntegrationTest, BattleRogueVsBear) {
    auto bear = NPCFactory::CreateBear("TestBear", p1);
    auto rogue = NPCFactory::CreateRogue("TestRogue", p2);
    
    dungeon.AddNPC(bear);
    dungeon.AddNPC(rogue);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 2);
    
    dungeon.StartBattle(20.0);
    
    // Bear should survive
    EXPECT_TRUE(dungeon.GetNPCs()[0]->IsAlive());
}

TEST_F(IntegrationTest, BattleMultipleFactions) {
    auto bear = NPCFactory::CreateBear("Misha", p1);
    auto elf = NPCFactory::CreateElf("Legolas", p2);
    auto rogue = NPCFactory::CreateRogue("Robin", p3);
    
    dungeon.AddNPC(bear);
    dungeon.AddNPC(elf);
    dungeon.AddNPC(rogue);
    
    EXPECT_EQ(dungeon.GetNPCs().size(), 3);
    
    dungeon.StartBattle(30.0);
    
    int alive_count = 0;
    for (const auto& npc : dungeon.GetNPCs()) {
        if (npc->IsAlive()) alive_count++;
    }
    EXPECT_LT(alive_count, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}