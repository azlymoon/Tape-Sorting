#include <gtest/gtest.h>
#include "ExternalSort.h"
#include "Tape.h"

class ExternalSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream outFile("test_input.txt");
        for (int i = 10; i > 0; --i) {
            outFile << i << " ";
        }
        outFile.close();
    }

    void TearDown() override {
        std::remove("test_input.txt");
        std::remove("test_output.txt");
    }
};

TEST_F(ExternalSortTest, Sort) {
    Tape* inputTape = new Tape("test_input.txt", false);
    Tape* outputTape = new Tape("test_output.txt", true);

    ExternalSort::sort(*inputTape, *outputTape);

    delete inputTape;
    delete outputTape;

    std::ifstream inFile("test_output.txt");
    int value;
    for (int i = 1; i <= 10; ++i) {
        inFile >> value;
        EXPECT_EQ(value, i);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
