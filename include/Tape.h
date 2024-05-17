#ifndef TAPE_H
#define TAPE_H

#include <string>
#include <fstream>

class Tape {
private:
    std::fstream file;
    bool writeMode;

public:
    Tape(const std::string& fileName, bool writeMode);
    ~Tape();

    bool read(int& value);
    void write(int value);
    void rewind(int offset);
};

#endif // TAPE_H