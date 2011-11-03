
#include "../Buffer.hpp"
#include <gtest/gtest.h>
#include <string.h>

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



/*
TEST_F(BufferTest, Read) {
    char expected[] = "babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";
    int len = strlen(expected);
    for (int i=0; i < len; i++) {
        char c = b->getchar();
        EXPECT_EQ(expected[i], c);
        //cout << c << endl;
    }
    //cout << endl;
}
*/
