#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

void worker(std::promise<int> prom) {
    cout << "Worker thread calculating...\n";
    prom.set_value(42);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t(worker, std::move(prom));
    cout << "Main thread waiting...\n";
    int value = fut.get();  // blocks until worker set the value
    cout << "Get value: " << value << "\n";
    t.join();
    return 0;
}
