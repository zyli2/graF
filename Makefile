# CXX=clang++
CXX_FLAGS=g++ -std=c++14

exec: bin/exec
tests: bin/tests

bin/exec: ./src/graph.cpp ./src/utilities.cpp ./entry/main.cpp
    $(CXX_FLAGS) $^ -o $@

bin/tests: ./tests/tests-bfs.cpp ./tests/tests-dataparsing.cpp ./src/graph.cpp ./src/utilities.cpp
    $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
    rm -f bin/*