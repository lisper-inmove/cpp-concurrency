#include <vector>
#include <iostream>
#include <mutex>
#include <list>
#include <algorithm>
#include <thread>

using namespace std;

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    // std::lock_guard<std::mutex> guard(some_mutex);
    std::lock_guard guard(some_mutex);
    bool flag = std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
    std::cout << "find value result: " << flag << std::endl;
    return flag;
}

void test001() {
    std::thread t1(add_to_list, 3);
    std::thread t2(list_contains, 3);

    t2.join();
    t1.join();
}

int main() {
    test001();
    return 0;
}
