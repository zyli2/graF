EXENAME = main
OBJS = main.o openflights.o flightmap.o
OBJS_DIR = .objs
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

all : $(EXENAME)


$(EXENAME): output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

main.o : main.cpp openflights.cpp flightmap.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	-rm -f *.o .txt $(EXENAME) test