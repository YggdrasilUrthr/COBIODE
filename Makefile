CXX := g++

search_alg: search_alg.cpp
	$(CXX) search_alg.cpp -g -o search_alg

test_gen: test_gen.cpp
	$(CXX) test_gen.cpp -g -o test_gen