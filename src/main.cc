#include <exception>
#include <iostream>
#include <future>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

void worker(std::promise<int> p, bool fail) {
    try {
        if (fail) {
            throw std::runtime_error("something went wrong");
        }
        p.set_value(42);
    } catch (...) {
        // p.set_exception(std::current_exception());
        p.set_exception(std::make_exception_ptr(std::logic_error("An Error")));
    }
}

int main() {
    std::promise<int> p;
    auto f = p.get_future();
    std::thread t(worker, std::move(p), true);
    t.join();
    try {
        int result = f.get();
        cout << "Got result: " << result << "\n";
    } catch (const std::exception &e) {
        cout << "Caught exception: " << e.what() << "\n";
    }
    return 0;
}
