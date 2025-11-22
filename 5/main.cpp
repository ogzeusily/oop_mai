#include "queue.h"
#include <iostream>
#include <string>
#include "queue.h"
#include "memory_resourse.h"


int main() {
    MemoryResource mem_res;
    Queue<int> q_int(&mem_res);
    for (int i = 1; i <= 5; ++i) q_int.Push(i * 10);
    std::cout << "Front: " << q_int.Front() << ", Back: " << q_int.Back() << ", Size: " << q_int.Size() << std::endl;
    for (auto it = q_int.Begin(); it != q_int.End(); ++it) std::cout << *it << ' ';
    std::cout << std::endl;
    q_int.Pop();
    std::cout << "After Pop, Front: " << q_int.Front() << ", Size: " << q_int.Size() << std::endl;
    struct MyStruct {
        int id;
        std::string name;
    };
    Queue<MyStruct> q_struct(&mem_res);
    q_struct.Push({1, "Alice"});
    q_struct.Push({2, "Bob"});
    for (auto it = q_struct.Begin(); it != q_struct.End(); ++it)
        std::cout << "id: " << it->id << ", name: " << it->name << std::endl;
    q_struct.Pop();
    std::cout << "After Pop, Front: id=" << q_struct.Front().id << ", name=" << q_struct.Front().name << std::endl;
    return 0;
}