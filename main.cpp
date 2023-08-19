#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <stdlib.h>
#include <sys/types.h>
#include <CL/cl.h>
#include <iostream>
#include <random>
#include "define.h"
#include "GPU/GPUWrapper.h"
#include <time.h>
#include <vector>


int main() {
    std::cout << "Sequence length: " << Setting::VECTOR_SIZE << std::endl;
    
    cl_platform_id platform;
    cl_int err;
    std::vector<int> res(Setting::UNIQUE_COUNT, 0);
    
    std::vector<int> arr;
    arr.reserve(Setting::VECTOR_SIZE);
    std::cout << "Vector initialization" << std::endl;    

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(Setting::MIN, Setting::MAX);
    
    for (size_t i=0; i <Setting::VECTOR_SIZE; ++i){
        arr.push_back(distrib(gen));
    }

    clGetPlatformIDs(1, &platform, NULL); //Sorry, but I really only have CPU. You can set your parameters. This code will run on GPU too.
    GPU::DeviceWrapper dwrapper(platform);
    cl_kernel& kernel = dwrapper.GetKernel();
    cl_command_queue& queue = dwrapper.GetQueue(); 
    cl_context context = dwrapper.GetContext();
    std::cout << "Device arguments initialization" << std::endl;

    cl_mem a_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*Setting::VECTOR_SIZE, arr.data(), &err);
    cl_mem res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int)*Setting::UNIQUE_COUNT, NULL, &err);
    
    
    std::cout << "Add arguments" << std::endl;
    dwrapper.AddParametrInProgram(0, sizeof(cl_mem), &a_buff);
    dwrapper.AddParametrInProgram(1, sizeof(cl_mem), &res_buff); 

    std::cout << "Run algorithm\n\n";
    const clock_t begin_time = clock();
    OCL_SAFE_CALL(clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &Setting::VECTOR_SIZE, NULL, 0, NULL, NULL));
    OCL_SAFE_CALL(clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0, sizeof(int)*Setting::UNIQUE_COUNT, res.data(), 0, NULL, NULL));

    std::cout << "time execute algorithm and read buffer: " <<  float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;

    for (size_t i =0; i < res.size();  ++i) {
        if (i>0 && i %50 == 0) {
            std::cout << std::endl;
        }
        std::cout << i << " ";
    }
    clReleaseMemObject(a_buff);
    clReleaseMemObject(res_buff);

    return 0;
}

