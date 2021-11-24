CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wpedantic
OBJS = \
	main.o

.PHONY: all clean

all: scr_seq

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	$(RM) scr_seq scr_seq.exe *.o

scr_seq: $(OBJS)
	$(CXX) -o $@ $^ 
