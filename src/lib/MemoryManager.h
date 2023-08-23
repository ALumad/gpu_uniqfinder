#pragma once
#include <CL/cl.h>
#include <vector>
namespace GPU {
    class MemoryManager {
        public:
            ~MemoryManager();
            cl_mem& AddParametr(cl_context   /* context */,
                                cl_mem_flags /* flags */,
                                size_t       /* size */,
                                void *       /* host_ptr */,
                                cl_int *     /* errcode_ret */);
        private:
            std::vector<cl_mem> ptrs_;
    };



}