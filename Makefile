
CXX_FLAGS=g++ -std=c++11


exec: bin/exec
tests: bin/tests

bin/exec: ./src/graph.cpp ./src/utilities.cpp ./drawing/drawing.cpp ./cs225/PNG.cpp ./cs225/HSLAPixel.cpp ./lodepng/lodepng.cpp ./entry/main.cpp
	$(CXX_FLAGS) $^ -o $@

bin/tests: ./tests/tests-bfs.cpp ./tests/tests-dataparsing.cpp ./src/graph.cpp ./src/utilities.cpp
	$(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
	rm -f bin/*