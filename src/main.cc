#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

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
