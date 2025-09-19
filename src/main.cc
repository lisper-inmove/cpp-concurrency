#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

void worker(std::promise<int> prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Worker thread calculating..." << std::this_thread::get_id() << "\n";
    // prom.set_value(42);  // set result
    // raise an error
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t(worker, std::move(prom));

    std::cout << "Main thread waiting..." << std::this_thread::get_id() << "\n";
    try {
        int value = fut.get();  // blocks until worker sets the value
        std::cout << "Got value: " << value << "\n";
    } catch (const std::future_error &e) {
        cout << "Prom destroyed" << endl;
    }
    t.join();
    return 0;
}
