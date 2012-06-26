
#include "../Buffer.hpp"
#include <gtest/gtest.h>
#include <string.h>

using namespace std;

class BufferTest : public testing::Test {
protected:

    virtual void SetUp() {
        char buffertestfile[] = "/tmp/buffertestfile";
        b = new Buffer(buffertestfile, true);
    }

    virtual void TearDown() {
        delete b;
    }

    Buffer *b;
};


TEST_F(BufferTest, Read) {
    char expected[] = "babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";
//    cout << sizeof(expected) << endl;

    int len = strlen(expected);
    for (int i=0; i < len * 8; i++) {
        char current_char = b->getchar();
        ASSERT_EQ(expected[i%len], current_char) << "At i: " << i;
//        cout << current_char << endl;
    }
    //cout << endl;
}
