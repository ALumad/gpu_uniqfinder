add_library(${LIB_NAME} 
    GPUWrapper.cpp
    Worker.cpp
    MemoryManager.cpp
)

target_link_libraries(${LIB_NAME}  OpenCL)