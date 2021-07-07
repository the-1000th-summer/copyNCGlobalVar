cmake_minimum_required(VERSION 3.0.0)
project(copyNCGlobalVar VERSION 0.1.0)

include(CTest)
enable_testing()

set(nccxxDir /home/bill/software/netCDF-CXX4/real_clang)
set(nccDir /home/bill/software/netCDF-C/real_clang)

include_directories(
    ${nccxxDir}/include
    ${nccDir}/include
)

aux_source_directory(./src SRC_LIST)

add_executable(copyNCGlobalVar main.cpp ${SRC_LIST})

find_library(libncPath netcdf ${nccDir}/lib)
find_library(libncxxPath netcdf_c++4 ${nccxxDir}/lib)
target_link_libraries(copyNCGlobalVar ${libncPath} ${libncxxPath})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
