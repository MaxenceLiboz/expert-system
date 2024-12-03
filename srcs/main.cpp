#include "main.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello world" << std::endl;
    std::cout << "Number of args: " <<  (argc - 1) << std::endl;
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}