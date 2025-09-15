#include <iostream>
#include <thread>

using namespace std;

void do_some_work() {
    // 函数作为thread入口
    cout << "Do Some Work" << endl;
}

class BackgroundTask {
   public:
    void operator()() const { cout << "Background Task" << endl; }
};

class Task {
   public:
    void run() { cout << "Task run" << endl; }
};

void test001() {
    /**

       thread的析构函数中会调用 std::terminate来终止线程
       1. 使用 join() 来等待线程结束, detach() 不等待线程结束

     */
    std::thread thread0(do_some_work);

    BackgroundTask task;
    std::thread thread1(task);

    // Error: C++编译器会将其解析为函数声明，而不是类型对象的定义
    // std::thread thread2(BackgroundTask());
    // thread2.join();

    // No Error
    // std::thread thread3((BackgroundTask()));
    // std::thread thread4{BackgroundTask()};

    // 用Lambda表达式创建线程
    std::thread thread5([] { cout << "Thread in a lambda function" << endl; });

    Task task6;
    std::thread thread6(&Task::run, &task6);

    cout << std::thread::hardware_concurrency() << endl;

    thread0.join();
    thread1.join();
    thread6.join();
    thread5.join();
}

int main() {
    test001();
    return 0;
}
