#include "Tape.h"
#include <thread>
#include "Config.h"

Tape::Tape(const std::string& fileName, bool writeMode) : writeMode(writeMode) {
    if (writeMode) {
        file.open(fileName, std::ios::out);
    } else {
        file.open(fileName, std::ios::in);
    }

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }
}

Tape::~Tape() {
    if (file.is_open()) {
        file.close();
    }
}

bool Tape::read(int &value) {
    std::this_thread::sleep_for(std::chrono::microseconds(READ_DELAY));
    if (writeMode) {
        throw std::runtime_error("Attempt to read in write mode");
    }
    if (!(file >> value)) {
        if (file.eof()) {
            return false;
        } else {
            throw std::runtime_error("Error reading from file");
        }
    }
    return true;
}

void Tape::write(int value) {
    std::this_thread::sleep_for(std::chrono::microseconds(WRITE_DELAY));
    if (!writeMode) {
        throw std::runtime_error("Attempt to write in read mode");
    }
    if (!(file << value << ' ')) {
        throw std::runtime_error("Error writing to file");
    }
}

void Tape::rewind(int offset) {
    std::this_thread::sleep_for(std::chrono::microseconds(REWIND_DELAY));
    if (writeMode) {
        file.seekp(offset, std::ios::cur);
        if (!file) {
            throw std::runtime_error("Error seeking in file (write mode)");
        }
    } else {
        file.seekg(offset, std::ios::cur);
        if (!file) {
            throw std::runtime_error("Error seeking in file (read mode)");
        }
    }
}