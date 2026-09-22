# robot/<패턴>/Makefile - 이 폴더 하나만 단독으로 빌드한다
#
#   make        -> build/<패턴이름> 으로 실행 파일 생성
#   make run    -> 빌드하고 바로 실행
#   make clean  -> build/ 삭제
#
# 저장소 루트(../../)에서 전체를 다루려면
#   make robot                  -> 로봇 예제 22개 전부 빌드
#   make run-robot-<패턴이름>   -> 하나만 빌드하고 실행
#   make run-robot-all          -> 22개 순서대로 실행
#
# 빌드 옵션은 루트 Makefile 과 같다. 경고 0개를 유지한다.
# -I. 덕분에 기능 폴더끼리 "../" 없이 #include "controller/ControllerPlugin.h" 로 참조된다.

CXX      ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O1

# 주의: $(notdir $(CURDIR)) 를 쓰면 안 된다.
#       make 의 문자열 함수는 공백으로 단어를 쪼개므로, 경로에 공백이 있으면
#       ("Design Pattern/..." 처럼) 폴더 이름이 산산조각 난다.
#       basename 은 셸에 따옴표째 넘기므로 공백이 있어도 안전하다.
NAME := $(shell basename "$(CURDIR)")
BIN  := build/$(NAME)

# 기능 폴더가 몇 겹이든 상관없도록 find 로 훑는다.
# 헤더도 선행 조건에 넣어야 .h 만 고쳐도 다시 빌드된다 -> 컴파일러에는 .cpp 만 넘긴다.
SRCS := $(shell find . -name '*.cpp' -not -path './build/*')
HDRS := $(shell find . -name '*.h' -not -path './build/*')

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRCS) $(HDRS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -I. -o $@ $(SRCS)

run: $(BIN)
	@echo "===== robot/$(NAME) ====="
	@./$(BIN)

clean:
	rm -rf build
