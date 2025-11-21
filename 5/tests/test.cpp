
#include <gtest/gtest.h>
#include <string>
#include "queue.h"
#include "memory_resourse.h"


// add for pr
TEST(QueueTest, IntBasicOperations) {
    MemoryResource mem_res;
    Queue<int> q(&mem_res);
    EXPECT_TRUE(q.IsEmpty());
    q.Push(1);
    q.Push(2);
    q.Push(3);
    EXPECT_EQ(q.Size(), 3);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 3);
    q.Pop();
    EXPECT_EQ(q.Front(), 2);
    q.Clear();
    EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueTest, IteratorWorks) {
    MemoryResource mem_res;
    Queue<int> q(&mem_res);
    for (int i = 0; i < 5; ++i) q.Push(i);
    int sum = 0;
    for (auto it = q.Begin(); it != q.End(); ++it) sum += *it;
    EXPECT_EQ(sum, 0+1+2+3+4);
}

struct MyStruct {
    int id;
    std::string name;
    bool operator==(const MyStruct& other) const { return id == other.id && name == other.name; }
};

TEST(QueueTest, CustomStruct) {
    MemoryResource mem_res;
    Queue<MyStruct> q(&mem_res);
    q.Push({1, "A"});
    q.Push({2, "B"});
    EXPECT_EQ(q.Front().id, 1);
    EXPECT_EQ(q.Back().name, "B");
    q.Pop();
    EXPECT_EQ(q.Front().id, 2);
    q.Clear();
    EXPECT_TRUE(q.IsEmpty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}