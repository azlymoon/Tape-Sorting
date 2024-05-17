#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include "Tape.h"

class ExternalSort {
public:
    static void sort(Tape& inputTape, Tape& outputTape);

private:
    static std::vector<std::string> splitAndSortChunks(Tape& inputTape);
    static std::string saveChunkToFile(const std::vector<int>& chunk);
    static void mergeChunks(const std::vector<std::string> &chunkFiles, Tape &outputTape);
    static void cleanupChunks(const std::vector<std::string>& chunkFiles);
    struct compare {
        bool operator()(std::pair<int, Tape*>& a, std::pair<int, Tape*>& b);
    };
};

#endif // EXTERNAL_SORT_H
