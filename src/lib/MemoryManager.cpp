#include "MemoryManager.h"
namespace GPU {

MemoryManager::~MemoryManager() {
    for (auto& ptr: ptrs_){
        clReleaseMemObject(ptr);
    }

}

cl_mem& MemoryManager::AddParametr(cl_context context, cl_mem_flags flags, size_t size, void* ost_ptr, cl_int* errcode_ret){
    ptrs_.emplace_back(clCreateBuffer(context, flags, size, ost_ptr, errcode_ret));
    return ptrs_.back();
}

}