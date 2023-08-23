add_executable(${PROJECT_NAME} 
	"main.cpp"
)
add_dependencies(${PROJECT_NAME} ${LIB_NAME})
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})
