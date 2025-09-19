#include <exception>
#include <iostream>
#include <future>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

int compute_value() {
    cout << "Computing value ... \n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
}

int main() {
    std::packaged_task<int()> task(compute_value);
    std::future<int> fut = task.get_future();
    auto shared_fut = fut.share();
    // std::shared_future<int> shared_fut = fut.share();
    // std::shared_future<int> shared_fut(std::move(fut)); // 也可以用move
    std::thread t(std::move(task));

    std::thread consumer1([shared_fut] {
        cout << "Consumer 1 waiting ...\n";
        int value = shared_fut.get();
        cout << "Consumer 1 got value: " << value << "\n";
    });

    std::thread consumer2([shared_fut] {
        cout << "Consumer 2 waiting ...\n";
        int value = shared_fut.get();
        cout << "Consumer 2 got value: " << value << "\n";
    });

    consumer1.join();
    consumer2.join();
    t.join();
    return 0;
}
