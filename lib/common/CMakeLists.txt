# Template for header only module

set(MODULE_NAME common)

# list of libs to combine as one interface lib
set(SUB_LIBS 
Eigen3::Eigen
)

####### Do not modify !

add_library(${MODULE_NAME} INTERFACE)

target_include_directories(${MODULE_NAME} INTERFACE include)

target_link_libraries(${MODULE_NAME} INTERFACE ${SUB_LIBS})

