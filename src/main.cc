#include <vector>
#include <iostream>
#include <mutex>
#include <list>
#include <algorithm>
#include <thread>
#include <memory>

using namespace std;

shared_ptr<int> resource_ptr;
once_flag resource_flag;

void init_resource() {
    resource_ptr.reset(new int(10));
    cout << "init resource called: " << std::this_thread::get_id() << endl;
}

void test001() {
    cout << "Current thread: " << std::this_thread::get_id() << endl;
    call_once(resource_flag, init_resource);
}

int main() {
    // test001();
    thread t1(test001);
    thread t2(test001);
    t1.join();
    t2.join();
    return 0;
}
