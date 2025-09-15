#include "parallel_accumulate.h"
#include <vector>
#include <iostream>

using namespace std;

void test001() {
    vector<int> v(10000, 1);
    int sum = parallel_accumulate(v.begin(), v.end(), 0);
    cout << "Sum of parallel accumulate: " << sum << endl;
}

int main() {
    test001();
    return 0;
}
