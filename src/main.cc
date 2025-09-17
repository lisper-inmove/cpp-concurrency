#include <vector>
#include <iostream>
#include <mutex>
#include <list>
#include <algorithm>
#include <thread>
#include <memory>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mut;
std::queue<int> data_queue;
condition_variable data_cond;

void data_preparation_thread() {
    this_thread::sleep_for(chrono::milliseconds(5000));
    {
        lock_guard lk(mut);
        data_queue.push(1000);
    }
    cout << "Put data to queue: " << std::this_thread::get_id() << endl;
    data_cond.notify_one();
}

void data_processing_thread() {
    while (true) {
        unique_lock lk(mut);
        cout << "Before Wait: " << std::this_thread::get_id() << endl;
        data_cond.wait(lk, [] { return !data_queue.empty(); });
        cout << "After Wait: " << std::this_thread::get_id() << endl;
        int data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        // do something
        break;
    }
}

int main() {
    // test001();
    thread t1(data_preparation_thread);
    thread t2(data_processing_thread);
    t1.join();
    t2.join();
    return 0;
}
