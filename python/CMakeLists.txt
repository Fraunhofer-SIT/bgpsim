set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(SWIG REQUIRED)
include(UseSWIG)

# Setup Python
find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

# include path
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(../src)

set_property(SOURCE pybgpsim.i PROPERTY CPLUSPLUS ON)

swig_add_library(pybgpsim
  	             LANGUAGE python
                 SOURCES pybgpsim.i)

swig_link_libraries(pybgpsim bgpsim ${PYTHON_LIBRARIES})

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
                OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
install(TARGETS _pybgpsim DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ${CMAKE_BINARY_DIR}/python/pybgpsim.py DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ${CMAKE_BINARY_DIR}/src/libbgpsim.so DESTINATION ${PYTHON_SITE_PACKAGES})
