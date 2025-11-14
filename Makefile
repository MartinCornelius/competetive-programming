CXX = g++
CXXFLAGS = -std=c++20 -O2

ifeq ($(OS),Windows_NT)
    # Windows
    EXE=.exe
    DISP=type
    RUNPIPE=|
else
    # Unix
    EXE=
    DISP=cat
    RUNPIPE=<
endif

.PHONY: run clean

run:
	@$(MAKE) _run FILE="$(file)" MODE="$(mode)"

_run:
	$(CXX) $(CXXFLAGS) $(FILE) -o $(basename $(FILE))$(EXE)
ifeq ($(OS),Windows_NT)
ifeq ($(MODE),TEST)
	@$(DISP) $(dir $(FILE))test.txt $(RUNPIPE) $(basename $(FILE))$(EXE)
else ifeq ($(MODE),INPUT)
	@$(DISP) $(dir $(FILE))input.txt $(RUNPIPE) $(basename $(FILE))$(EXE)
else
	@echo "Usage: make run aoc/day02/sol.cpp TEST|INPUT"
	@false
endif
else
ifeq ($(MODE),TEST)
	@./$(basename $(FILE))$(EXE) < $(dir $(FILE))test.txt
else ifeq ($(MODE),INPUT)
	@./$(basename $(FILE))$(EXE) < $(dir $(FILE))input.txt
else
	@echo "Usage: make run aoc/day02/sol.cpp TEST|INPUT"
	@false
endif
endif

ifeq (run,$(firstword $(MAKECMDGOALS)))
  file := $(word 2, $(MAKECMDGOALS))
  mode := $(word 3, $(MAKECMDGOALS))
  $(eval $(file):;@:)
  $(eval $(mode):;@:)
endif

clean:
	-find . -type f \( -name 'sol' -o -name 'sol.exe' \) -delete 2>/dev/null || true
