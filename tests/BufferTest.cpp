
#include "../Buffer.hpp"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class BufferTest : public testing::Test {
protected:

    virtual void SetUp() {
        char buffertestfile[] = "buffertestfile";
        b = new Buffer(buffertestfile);
    }

    virtual void TearDown() {
        delete b;
    }

    Buffer *b;
};

TEST_F(BufferTest, Open) {
    EXPECT_TRUE(b->isOpen());
}

TEST_F(BufferTest, Read) {
    cout << endl << endl << endl << endl;
    for (int i=0; i<500; i++) {
        char c = b->getchar();
        cout << c;
    }
    cout << endl;
}
