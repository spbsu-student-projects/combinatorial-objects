name = composition
sources = $(name).cpp runner.cpp $(incpath)/combinatorial_object.cpp
incpath = ../combinatorial_object
headers = $(name).h $(incpath)/combinatorial_object.h

$(name): $(sources) $(headers)
	g++ -I$(incpath) --std=c++11 -Wall $(sources) -o $(name)

clean:
	rm -f $(name){,.exe}
