#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdio>
#include "Tape.h"
#include "Config.h"
#include "ExternalSort.h"

void ExternalSort::sort(Tape &inputTape, Tape &outputTape) {
    std::vector<std::string> sortedChunks = splitAndSortChunks(inputTape);
    mergeChunks(sortedChunks, outputTape);
    cleanupChunks(sortedChunks);
}

std::vector<std::string> ExternalSort::splitAndSortChunks(Tape &inputTape) {
    std::vector<std::string> chunkFiles;
    std::vector<int> chunk;
    int number;

    while (inputTape.read(number)) {
        chunk.push_back(number);

        if (chunk.size() * sizeof(int) >= BUFFER_SIZE) {
            std::sort(chunk.begin(), chunk.end());
            std::string chunkFile = saveChunkToFile(chunk);
            chunkFiles.push_back(chunkFile);
            chunk.clear();
        }
    }

    if (!chunk.empty()) {
        std::sort(chunk.begin(), chunk.end());
        std::string chunkFile = saveChunkToFile(chunk);
        chunkFiles.push_back(chunkFile);
    }

    return chunkFiles;
}

std::string ExternalSort::saveChunkToFile(const std::vector<int> &chunk) {
    std::string chunkFile = std::tmpnam(nullptr);
    Tape tmpTape(chunkFile, true);

    for (int number: chunk) {
        tmpTape.write(number);
    }

    return chunkFile;
}

bool ExternalSort::compare::operator()(std::pair<int, Tape *> &a, std::pair<int, Tape *> &b) {
    return a.first > b.first;
}

void ExternalSort::mergeChunks(const std::vector<std::string> &chunkFiles, Tape &outputTape) {
    std::priority_queue<std::pair<int, Tape *>, std::vector<std::pair<int, Tape *>>, compare> minHeap;
    std::vector<Tape *> tapes;

    for (const std::string &chunkFile: chunkFiles) {
        Tape *tape = new Tape(chunkFile, false);
        int number;
        if (tape->read(number)) {
            minHeap.emplace(number, tape);
        }
        tapes.push_back(tape);
    }

    while (!minHeap.empty()) {
        auto [number, tape] = minHeap.top();
        minHeap.pop();
        outputTape.write(number);

        if (tape->read(number)) {
            minHeap.emplace(number, tape);
        }
    }

    for (Tape *tape: tapes) {
        delete tape;
    }
}

void ExternalSort::cleanupChunks(const std::vector<std::string> &chunkFiles) {
    for (const std::string &chunkFile: chunkFiles) {
        std::remove(chunkFile.c_str());
    }
}
