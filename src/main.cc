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

double compute_square(int x, double y) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Compute Square thread " << std::this_thread::get_id() << endl;
    cout << "Data is: " << x * x + y << endl;
    return x * x * y + y;
}

int main() {
    cout << "Main Thread: " << std::this_thread::get_id() << endl;

    // Future + async
    // cout << "Starting async task ...\n";
    // std::future<int> result = std::async(std::launch::async, compute_square, 10);
    // cout << "Doing something else while waiting...\n";
    // int value = result.get();  // Waits until the computation finishes
    // cout << "Result: " << value << "\n";

    // Future + packaged_task
    std::packaged_task<double(int, double)> task(compute_square);
    auto fut = task.get_future();
    std::thread t(std::move(task), 10, 11.2);
    cout << "Main is free to do other work...\n";
    double result = fut.get();
    std::cout << "Result: " << result << "\n";
    t.join();
    return 0;
}
