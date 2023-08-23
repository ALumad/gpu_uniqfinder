#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "Worker.h"

#include <stdlib.h>
#include <sys/types.h>
#include <CL/cl.h>

#include <random>
#include "GPUWrapper.h"
#include "MemoryManager.h"
#include "define.h"
#include <iostream>


std::vector<int> GPUWorker::Run(std::vector<int>& inarr, const size_t out_size){
  
    std::vector<int> res(out_size, 0);
    cl_platform_id platform;
    cl_int err;
    
    clGetPlatformIDs(1, &platform, NULL); //Sorry, but I really only have CPU. You can set your parameters. This code will run on GPU too.
    GPU::DeviceWrapper dwrapper(platform);
    cl_kernel& kernel = dwrapper.GetKernel();
    cl_command_queue& queue = dwrapper.GetQueue(); 
    cl_context context = dwrapper.GetContext();

    cl_mem a_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*inarr.size(), inarr.data(), &err);
    cl_mem res_buff = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int)*out_size, res.data(), &err);
    
    dwrapper.AddParametrInProgram(0, sizeof(cl_mem), &a_buff);
    dwrapper.AddParametrInProgram(1, sizeof(cl_mem), &res_buff); 
    dwrapper.AddParametrInProgram(2, sizeof(int), (void*)&out_size); 

    const clock_t begin_time = clock();
    const auto VECTOR_SIZE = inarr.size();

    OCL_SAFE_CALL(clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &VECTOR_SIZE, NULL, 0, NULL, NULL));
    OCL_SAFE_CALL(clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0, sizeof(int)*out_size, res.data(), 0, NULL, NULL));

    clReleaseMemObject(a_buff);
    clReleaseMemObject(res_buff);
    return res;
}