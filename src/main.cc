#include <iostream>
#include <future>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

int worker(int x) {
    if (x < 0) {
        throw std::out_of_range("x < 0");
    }
    return x * x;
}

int main() {
    auto f = std::async(std::launch::async, worker, 1);
    cout << "result is: " << f.get() << endl;
    return 0;
}
