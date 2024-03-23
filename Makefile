CPPFLAGS = -std=c++20 -c

.PHONY: all clean distclean

all: main 

multiv_min.o: multiv_min.cpp
	$(CXX) $(CPPFLAGS) multiv_min.cpp

main.o: main.cpp
	$(CXX) $(CPPFLAGS) main.cpp

main: main.o multiv_min.o
	$(CXX) main.o multiv_min.o -o main 


clean:
	$(RM) *.o

distclean: clean
	$(RM) main
