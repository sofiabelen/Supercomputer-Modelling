#include <chrono>
#include <cstddef>
#include <iostream>
using namespace std;
using namespace std::chrono;


int main() {
    float a = 0;
    size_t N = 1000000000;
    auto t_1 = high_resolution_clock::now();
    for (size_t i = 0; i<N; i++){
        a ++;
    }
    auto t_2 = high_resolution_clock::now();
    auto t = duration_cast<microseconds>(t_2-t_1).count()/1.0e6;
    float performance = N/t/1.0e9;
    cout << "Time: " << t <<" seconds; " << "Performance: " << performance << " GFlops" << endl;
}