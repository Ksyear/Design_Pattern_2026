cmake_minimum_required(VERSION 3.16)
project(HeadFirstDesignPatternsCpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
	add_compile_options(/W4 /utf-8)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 패턴 폴더(NN_PatternName)를 훑어서
#   main.cpp + 기능 폴더의 모든 .cpp -> 실행 파일 NN_PatternName
#   exercise.cpp                      -> 실행 파일 NN_PatternName_ex
# 를 자동으로 만든다. 새 폴더를 추가하면 cmake를 다시 돌리기만 하면 됨.
#
# 클래스는 "기능 폴더"에 헤더/구현 짝으로 들어간다.
#   예) 01_Strategy/duck/Duck.h + 01_Strategy/duck/Duck.cpp
#       01_Strategy/fly/FlyWithWings.h + .cpp
# CONFIGURE_DEPENDS 덕분에 파일을 추가해도 빌드할 때 알아서 다시 훑는다.
file(GLOB PATTERN_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/[0-9][0-9]_*)

set(ALL_TARGETS "")
set(EX_TARGETS "")

foreach(dir ${PATTERN_DIRS})
	if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/main.cpp)
			file(GLOB_RECURSE ${dir}_SUB_SRCS CONFIGURE_DEPENDS
				${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp)
			list(REMOVE_ITEM ${dir}_SUB_SRCS
				${CMAKE_CURRENT_SOURCE_DIR}/${dir}/main.cpp
				${CMAKE_CURRENT_SOURCE_DIR}/${dir}/exercise.cpp)
			add_executable(${dir} ${dir}/main.cpp ${${dir}_SUB_SRCS})
			# 기능 폴더끼리 "../" 없이 참조하게 해 주는 include 경로
			target_include_directories(${dir} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
			list(APPEND ALL_TARGETS ${dir})
		endif()
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/exercise.cpp)
			add_executable(${dir}_ex ${dir}/exercise.cpp)
			list(APPEND EX_TARGETS ${dir}_ex)
		endif()
	endif()
endforeach()

# 완성 예제 전체를 차례로 실행: cmake --build . --target run_all
add_custom_target(run_all COMMENT "완성 예제 22개를 순서대로 실행")
foreach(t ${ALL_TARGETS})
	add_custom_command(TARGET run_all POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E echo "===== ${t} ====="
		COMMAND $<TARGET_FILE:${t}>)
	add_dependencies(run_all ${t})
endforeach()

# 연습 문제 전체 빌드: cmake --build . --target exercises
add_custom_target(exercises DEPENDS ${EX_TARGETS} COMMENT "연습 스켈레톤 전체 빌드")
