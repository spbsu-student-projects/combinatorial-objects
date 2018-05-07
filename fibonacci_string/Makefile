name = FibonacciString
incpath = ../combinatorial_object
sources = fibonacci_string.cpp $(incpath)/combinatorial_object.cpp $(incpath)/runner.cpp
headers = $(incpath)/combinatorial_object.h $(incpath)/runner.h

$(name): $(sources) $(headers)
	g++ -I$(incpath) --std=c++11 -Wall $(sources) -o $(name)

clean:
	rm -f $(name){,.exe}
