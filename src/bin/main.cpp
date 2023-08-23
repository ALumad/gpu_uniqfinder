#include <iostream>
#include <random>
#include "lib/GPUWrapper.h"
#include "lib/Worker.h"
#include <vector>
#include <algorithm>

namespace Setting {
    const size_t VECTOR_SIZE = 10000000;
    const size_t MIN = 1;
    const size_t MAX = 1000;
    const size_t UNIQUE_COUNT = 1000;
    
};


int check(std::vector<int>& a, std::vector<int>& b){
    std::sort(a.begin(), a.end());
    std::unique(a.begin(), a.end());

    for (size_t i =0; i < b.size();  ++i) {
        if (a[i] != b[i]) {
            std::cout << i << " " << a[i] << " " << a[i];
            return 1;
        }
    }    
    return 0;
}

int main() {
    std::cout << "Sequence length: " << Setting::VECTOR_SIZE << std::endl;

    std::vector<int> arr;
    arr.reserve(Setting::VECTOR_SIZE);
    std::cout << "Vector initialization" << std::endl;    
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(Setting::MIN, Setting::MAX);
            
    for (size_t i=0; i <Setting::VECTOR_SIZE; ++i){
        arr.push_back(distrib(gen));
    }

    auto res = GPUWorker::Run(arr, Setting::UNIQUE_COUNT);
     
    return check(arr, res);
}