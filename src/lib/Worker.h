#pragma once
#include <vector>
#include <cstddef>

class GPUWorker {
public:
    static std::vector<int> Run(std::vector<int>& inarr, const size_t out_size);
};