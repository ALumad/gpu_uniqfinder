#include <gtest/gtest.h>
#include <random>
#include "lib/GPUWrapper.h"
#include "lib/Worker.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <limits>

void run_test(std::vector<int>& arr, size_t size){
    auto res = GPUWorker::Run(arr, size);
    
    std::sort(res.begin(), res.end());
    std::sort(arr.begin(), arr.end());
    
    auto last = std::unique(arr.begin(), arr.end());
    arr.erase(last, arr.end());
    
    ASSERT_EQ(arr.size(), res.size()) << "Vectors size is not the same";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(arr[i], res[i]) << "Line: " << i;
    }  
}

TEST(GPUFindUniq, test_1000_and_10_000_000_MIN_1_MAX_1000){
    const size_t VECTOR_SIZE = 10000000;
    const size_t UNIQUE_SIZE = 1000;
    std::vector<int> arr;
    arr.reserve(VECTOR_SIZE);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);
            
    for (size_t i=0; i <VECTOR_SIZE; ++i){
        arr.push_back(distrib(gen));
    }

    run_test(arr, UNIQUE_SIZE);
}


TEST(GPUFindUniq, test_1000_and_10_000_000_RANDOM_1000){
    const size_t VECTOR_SIZE = 10000000;
    const size_t UNIQUE_SIZE = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, std::numeric_limits<int>::max());

    std::unordered_set<int> tmp;
    while(tmp.size() < UNIQUE_SIZE) {
       tmp.insert(distrib(gen));
    }

    std::vector<int> arr(tmp.begin(), tmp.end());
    run_test(arr, UNIQUE_SIZE);
}


TEST(GPUFindUniq, test_10_and_10_RANDOM_10){
    const size_t VECTOR_SIZE = 10;
    const size_t UNIQUE_SIZE = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, std::numeric_limits<int>::max());

    std::unordered_set<int> tmp;
    while(tmp.size() < UNIQUE_SIZE) {
       tmp.insert(distrib(gen));
    }

    std::vector<int> arr(tmp.begin(), tmp.end());
    run_test(arr, UNIQUE_SIZE);
}

TEST(GPUFindUniq, test_1_and_10_RANDOM_1){
    const size_t VECTOR_SIZE = 10;
    const size_t UNIQUE_SIZE = 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, std::numeric_limits<int>::max());

    std::unordered_set<int> tmp;
    while(tmp.size() < UNIQUE_SIZE) {
       tmp.insert(distrib(gen));
    }

    std::vector<int> arr(tmp.begin(), tmp.end());
    run_test(arr, UNIQUE_SIZE);
}


TEST(GPUFindUniq, test_99_and_111111_MIN_99_MAX_1){
    const size_t VECTOR_SIZE = 111111;
    const size_t UNIQUE_SIZE = 99;

    std::vector<int> arr;
    arr.reserve(VECTOR_SIZE);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-99, -1);
            
    for (size_t i=0; i <VECTOR_SIZE; ++i){
        arr.push_back(distrib(gen));
    }

    run_test(arr, UNIQUE_SIZE);
}