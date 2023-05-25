#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Test
{
#pragma region 测试数据

class TestClass
{
public:
    TestClass() : id(-1), Val(-1) { std::cout << "Init default TestClass() ID: " << id << std::endl; }
    TestClass(int _id) : id(_id), Val(_id)
    {
        std::cout << "Init TestClass() ID: " << id << std::endl;
    }

    TestClass(const TestClass &t)
    {
        this->id  = t.id;
        this->Val = t.Val;
        std::cout << "Cpoied TestClass ID: " << t.id << std::endl;
    }

    TestClass(TestClass &&t)
    {
        this->id  = t.id;
        this->Val = t.Val;
        std::cout << "Moved TestClass ID: " << t.id << std::endl;
        t.id  = -9999;
        t.Val = -9999;
    }

    TestClass &operator=(const TestClass &t)
    {
        this->id  = t.id;
        this->Val = t.Val;
        std::cout << "Copied TestClass by operator= ID: " << t.id << std::endl;
        return *this;
    }

    TestClass &operator=(TestClass &&t)
    {
        this->id  = t.id;
        this->Val = t.Val;
        std::cout << "Moved TestClass operator= ID: " << t.id << std::endl;
        t.id  = -9999;
        t.Val = -9999;
        return *this;
    }

    ~TestClass() { std::cout << "Destructed TestClass ID: " << id << std::endl; }

    void print() { std::cout << "TestClass::print::ID : " << id << std::endl; }

    int Val;

private:
    int id;
};

class comma_numpunct : public std::numpunct<char>
{
protected:
    virtual char do_thousands_sep() const { return ','; }

    virtual std::string do_grouping() const { return "\03"; }
};

class MicrosecondsTimer
{
public:
    static void UnitTest(std::function<void()> func, int loop_times)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < loop_times; i++) {
            func();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::locale comma_locale(std::locale(), new comma_numpunct());
        std::cout.imbue(comma_locale);
        std::cout << "Time: " << std::setprecision(2)
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << std::setprecision(0) << " us\n";
    }

    virtual void Update() {}

    void StartTest(int loop_times)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < loop_times; i++) {
            Update();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::locale comma_locale(std::locale(), new comma_numpunct());
        std::cout.imbue(comma_locale);
        std::cout << "Time: " << std::setprecision(2)
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << std::setprecision(0) << " us\n";
    }
};
namespace show_copy
{
int copy_count     = 0;
int move_count     = 0;
int init_count     = 0;
int destruct_count = 0;

void reset()
{
    copy_count     = 0;
    move_count     = 0;
    init_count     = 0;
    destruct_count = 0;
}

struct Node
{
    int Val;

    Node(int _val) : Val(_val) { init_count++; }

    Node() : Val(-2147483647) { init_count++; }

    Node(const Node &n)
    {
        Val = n.Val;
        copy_count++;
    }

    Node(Node &&n)
    {
        Val = n.Val;
        move_count++;
    }

    ~Node() { destruct_count++; }

    Node &operator=(const Node &n)
    {
        Val = n.Val;
        copy_count++;
        return *this;
    }

    Node &operator=(Node &&n)
    {
        Val = n.Val;
        move_count++;
        return *this;
    }
};

void print()
{
    std::cout << "Copy: " << copy_count << " Move: " << move_count << " Init: " << init_count
              << " Destruct: " << destruct_count << std::endl;
}
} // namespace show_copy
#pragma endregion
} // namespace Test