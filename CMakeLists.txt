cmake_minimum_required(VERSION 2.8)
project(CGP)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    main.cpp
    cartesian/Abs.h
	cartesian/Add.h
	cartesian/Avg.h
	cartesian/Cartesian.cpp
	cartesian/CartesianCrxHalfUniform.cpp
	cartesian/CartesianCrxHalfUniform.h
	cartesian/CartesianCrxOnePoint.cpp
	cartesian/CartesianCrxOnePoint.h
	cartesian/CartesianCrxUniform.cpp
	cartesian/CartesianCrxUniform.h
	cartesian/CartesianGene.h
	cartesian/Cartesian_genotype.h
	cartesian/Cartesian.h
	cartesian/Ceil.h
	cartesian/Cos.h
	cartesian/Div.h
	cartesian/Floor.h
	cartesian/Frac.h
	cartesian/Function.h
	cartesian/FunctionSet.cpp
	cartesian/FunctionSet.h
	cartesian/Ln.h
	cartesian/Max.h
	cartesian/Min.h
	cartesian/Mul.h
	cartesian/MutConnection.cpp
	cartesian/MutConnection.h
	cartesian/MutConnectionSilent.cpp
	cartesian/MutConnectionSilent.h
	cartesian/MutFunction.cpp
	cartesian/MutFunction.h
	cartesian/MutFunctionSilent.cpp
	cartesian/MutFunctionSilent.h
	cartesian/MutFunctionSwap.cpp
	cartesian/MutFunctionSwap.h
	cartesian/MutIntoSilent.cpp
	cartesian/MutIntoSilent.h
	cartesian/Neg.h
	cartesian/Nop.h
	cartesian/Ramp.h
	cartesian/Reciprical.h
	cartesian/RSqrt.h
	cartesian/Sigm.h
	cartesian/Sin.h
	cartesian/Sq_exp.h
	cartesian/Sqrt.h
	cartesian/Step.h
	cartesian/Sub.h
	utility/expression_evaluation.cpp
	utility/expression_evaluation.h
	utility/fileparser.cpp
	utility/fileparser.h
	utility/measures.cpp
	utility/measures.h
	utility/utility.cpp
	utility/utility.h
	utility/utilityrng.h
	ImageProcessingOp.h
	ImageProcessingOp.cpp
	IP.h)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(../../)
include_directories(../)
add_executable(CGP ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(CGP ${CMAKE_CURRENT_SOURCE_DIR}/../../debug/libECF.a)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(CGP ${CMAKE_CURRENT_SOURCE_DIR}/../../release/libECF.a)
endif()

