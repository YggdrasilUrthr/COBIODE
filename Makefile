CXX := g++

all: search_alg search_alg_rev search_alg_2 test_gen

search_alg: search_alg.cpp
	$(CXX) search_alg.cpp -g -o search_alg

search_alg_rev: search_alg_rev.cpp
	$(CXX) search_alg_rev.cpp -g -o search_alg_rev

search_alg_2: search_alg_2.cpp
	$(CXX) search_alg_2.cpp -g -o search_alg_2

test_gen: test_gen.cpp
	$(CXX) test_gen.cpp -g -o test_gen