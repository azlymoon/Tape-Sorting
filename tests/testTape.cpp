#include <gtest/gtest.h>
#include "Tape.h"

class TapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream outFile("test_input_tape.txt");
        for (int i = 10; i > 0; --i) {
            outFile << i << " ";
        }
        outFile.close();
    }

    void TearDown() override {
        std::remove("test_input_tape.txt");
        std::remove("test_output_tape.txt");
    }
};

TEST_F(TapeTest, Read) {
    Tape inputTape("test_input_tape.txt", false);
    int value;
    std::vector<int> values;
    while (inputTape.read(value)) {
        values.push_back(value);
    }
    std::vector<int> expected = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    EXPECT_EQ(values, expected);
}

TEST_F(TapeTest, Write) {
    Tape* outputTape = new Tape("test_output_tape.txt", true);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int v : values) {
        outputTape->write(v);
    }
    delete outputTape;

    std::ifstream inFile("test_output_tape.txt");
    int fileValue;
    for (int i = 1; i <= 10; ++i) {
        inFile >> fileValue;
        EXPECT_EQ(fileValue, i);
    }
}

TEST_F(TapeTest, Rewind) {
    Tape inputTape("test_input_tape.txt", false);
    int value;
    inputTape.read(value);
    inputTape.rewind(2);
    inputTape.read(value);
    EXPECT_EQ(value, 8);
}

TEST_F(TapeTest, ReadError) {
    Tape outputTape("test_output_tape.txt", true);
    int value;
    EXPECT_THROW(outputTape.read(value), std::runtime_error);
}

TEST_F(TapeTest, WriteError) {
    Tape inputTape("test_input_tape.txt", false);
    EXPECT_THROW(inputTape.write(1), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
