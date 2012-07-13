
#include "../Buffer.hpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class BufferTest : public testing::Test {

};

TEST_F(BufferTest, Write) {
    char buffertestfile2[] = "/tmp/buffertestfile2";
    Buffer* write_buffer = new Buffer(buffertestfile2, false);
//    char result[256];
    string line;
    char text[] = "mal gucken, was das tut.\" und so weiter.. babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";
    write_buffer->addchars(text);
    delete write_buffer;

    ifstream inFile("/tmp/buffertestfile2");

    unsigned int count = 0, i;
    int done_with_text = 0;
    int empty_chars = 0;

    if (inFile.is_open()) {
        while (inFile.good()) {
            getline(inFile, line);
            for (i=0; i < line.size(); i++) {
                if (text[count+i] == '\0') {
                    done_with_text = 1;
                }
                if (!done_with_text) {
                    ASSERT_EQ(text[count+i], line[i]) << "At count, i: " << count << ", " << i;
                } else {
                    ASSERT_EQ(' ', line[i]) << "At count, i: " << count << ", " << i;
                    empty_chars++;
                }
            }
            if (text[count+i] == '\n') {
                count += 1; // "line" doesn't have newline character
            }
            count += i;
        }
        inFile.close();
    } else {
        cout << "file not open!" << endl;
    }

    ASSERT_EQ(strlen(text) + empty_chars, count) << "Checking if file was checked at all";
}


TEST_F(BufferTest, Read) {
    char buffertestfile[] = "/tmp/buffertestfile";
    Buffer* read_buffer = new Buffer(buffertestfile, true);

    char expected[] = "babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";

    int i;
    int len = strlen(expected);
    for (i=0; i < len * 8; i++) {
        char current_char = read_buffer->getchar();
        ASSERT_EQ(expected[i%len], current_char) << "At i: " << i;
    }

    ASSERT_EQ(len*8, i) << "Number of checked characters needs to be length of text";
    delete read_buffer;
}
