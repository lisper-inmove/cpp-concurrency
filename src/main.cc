#include <exception>
#include <thread>
#include <latch>
#include <iostream>
#include <atomic>
#include <chrono>

using namespace std;

atomic_flag lock= ATOMIC_FLAG_INIT;

void critical_section(int id) {

    // 这就相当于一个自旋锁
    while(lock.test_and_set(std::memory_order_acquire)) {}

    cout << "Thread " << id << " entering critical section\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Thread " << id << " leaving critical section\n";
    lock.clear(std::memory_order_release);
}

int main() {
    std::thread t1(critical_section, 1);
    std::thread t2(critical_section, 2);

    t1.join();
    t2.join();
    return 0;
}
