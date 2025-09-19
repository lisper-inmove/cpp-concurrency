#include <exception>
#include <iostream>
#include <future>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "quick_sort.h"

using namespace std;

template <typename T>
void print_list(const std::list<T> &lst, const std::string& name) {
    cout << name << ": ";
    for (auto const& val : lst) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    std::list<int> data;
    for (int i = 0; i < 2000; i++) {
        data.push_back(rand() % 100000);
    }

    // cout << "Original: ";
    // for (auto v: data) cout << v << " ";
    // cout << "\n";

    auto start_seq = std::chrono::high_resolution_clock::now();
    auto sorted_seq = sequential_quick_sort(data);
    auto end_seq = std::chrono::high_resolution_clock::now();
    auto dur_seq = std::chrono::duration_cast<std::chrono::milliseconds>(end_seq - start_seq).count();
    cout << "Sequential Time Consum: " << dur_seq << "\n";
    // print_list(sorted_seq, "Sequential Quick Sort");

    auto start_par = std::chrono::high_resolution_clock::now();
    auto sorted_par = parallel_quick_sort(data);
    auto end_par = std::chrono::high_resolution_clock::now();
    auto dur_par = std::chrono::duration_cast<std::chrono::milliseconds>(end_par - start_par).count();
    cout << "Parallel Time Consum: " << dur_par << "\n";
    // print_list(sorted_par, "Parallel Quick Sort");
    return 0;
}
