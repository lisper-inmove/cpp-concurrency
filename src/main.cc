#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

/**

   std::async
   policy: 默认值为 std::launch::async | std::launch::deferred，由实现自行决定
       std::launch::async: 新线程里立即执行
       std::launch::deferred: 直到future.get 或 future.wait时才执行

 */

int compute_square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}

int main() {
    cout << "Starting async task ...\n";
    std::future<int> result = std::async(std::launch::async, compute_square, 10);
    cout << "Doing something else while waiting...\n";

    int value = result.get();  // Waits until the computation finishes
    cout << "Result: " << value << "\n";
    return 0;
}
