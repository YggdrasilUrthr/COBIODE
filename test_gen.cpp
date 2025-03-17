#include <iostream>
#include <fstream>
#include <random>

const static uint32_t seed = 0;
const static char nucleobases[4] = {'A', 'C', 'G', 'T'};
const static std::string path = "./Data/";

int main(int argc, char ** argv) {

    std::mt19937 gen(seed); 
    std::uniform_int_distribution<> distrib(0, 3);

    std::string fname = "data.txt";
    uint32_t seq_len = 4096;

    if(argc > 1) {
        fname = std::string(argv[1]) + ".txt";
    }
    if(argc > 2) {
        seq_len = std::stoi(std::string(argv[2]));
    }
    
    std::cout << fname << std::endl;
    std::cout << seq_len << std::endl;

    std::ofstream data_file(path + fname);

    for (size_t i = 0; i < seq_len; i++) {
        uint32_t idx = distrib(gen);
        data_file << nucleobases[idx];
    }
    
    data_file.close();

    return 0;

}