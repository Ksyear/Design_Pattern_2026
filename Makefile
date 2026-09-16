# CMake 없이도 쓸 수 있는 최소 빌드 파일
#   make            -> 완성 예제 전체 빌드 (build/bin/)
#   make 01_Strategy-> 해당 패턴만 빌드
#   make run-01_Strategy -> 빌드 후 바로 실행
#   make ex         -> 연습 스켈레톤 전체 빌드
#   make run-all    -> 완성 예제 22개 순서대로 실행
#   make clean      -> build/ 삭제
#
# 폴더 구조 규약
#   NN_PatternName/main.cpp       진입점 - 객체를 조립하고 호출만 한다
#   NN_PatternName/<기능>/*.h     선언 - 인터페이스와 클래스마다 한 파일
#   NN_PatternName/<기능>/*.cpp   정의 - 같은 이름의 헤더와 짝을 이룬다
# 예) 01_Strategy -> duck/ (오리 본체) fly/ (나는 기능) quack/ (우는 기능)
# main.cpp 와 기능 폴더의 모든 .cpp 를 모아 실행 파일 하나로 묶는다

CXX      ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O1
BIN      := build/bin

DIRS     := $(sort $(patsubst %/,%,$(dir $(wildcard [0-9][0-9]_*/main.cpp))))
TARGETS  := $(addprefix $(BIN)/,$(DIRS))
EXDIRS   := $(sort $(patsubst %/,%,$(dir $(wildcard [0-9][0-9]_*/exercise.cpp))))
EXTARGETS:= $(addsuffix _ex,$(addprefix $(BIN)/,$(EXDIRS)))

.PHONY: all ex run-all clean $(DIRS) $(addprefix run-,$(DIRS))

all: $(TARGETS)

ex: $(EXTARGETS)

# 연습 스켈레톤은 지금도 단일 파일이라 규칙이 그대로다
$(BIN)/%_ex: %/exercise.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

# 폴더마다 소스 목록이 다르므로 규칙을 하나씩 찍어 낸다.
# 기능 폴더가 몇 겹이 되든 상관없도록 find 로 훑는다 (exercise.cpp 는 별도 타깃이라 제외).
# 헤더도 선행 조건에 넣어야 .h 만 고쳐도 다시 빌드된다 -> 컴파일러에는 .cpp 만 넘긴다.
# -I$(1) 덕분에 기능 폴더끼리 "../" 없이 #include "fly/FlyBehavior.h" 로 참조할 수 있다.
define PATTERN_RULE
$(BIN)/$(1): $(shell find $(1) -name '*.cpp' ! -name 'exercise.cpp') $(shell find $(1) -name '*.h') | $(BIN)
	$$(CXX) $$(CXXFLAGS) -I$(1) -o $$@ $$(filter %.cpp,$$^)
endef
$(foreach d,$(DIRS),$(eval $(call PATTERN_RULE,$(d))))

$(BIN):
	@mkdir -p $(BIN)

# 폴더 이름만으로 빌드/실행할 수 있게 하는 단축 규칙
$(DIRS): %: $(BIN)/%

$(addprefix run-,$(DIRS)): run-%: $(BIN)/%
	@echo "===== $* ====="
	@$<

run-all: all
	@for t in $(DIRS); do echo "===== $$t ====="; $(BIN)/$$t; echo; done

clean:
	rm -rf build
