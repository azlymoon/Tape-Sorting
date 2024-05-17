#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include "Tape.h"
#include "ExternalSort.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_tape_file> <output_tape_file>" << std::endl;
        return 1;
    }

    std::string inputTapeFile = argv[1];
    std::string outputTapeFile = argv[2];

    try {
        auto start = std::chrono::high_resolution_clock::now();

        Tape inputTape(inputTapeFile, false);
        Tape outputTape(outputTapeFile, true);

        ExternalSort::sort(inputTape, outputTape);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "Sorting completed successfully." << std::endl;
        std::cout << "Time taken: " << duration.count() << " seconds." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
