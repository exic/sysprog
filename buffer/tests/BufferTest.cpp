
#include "../Buffer.hpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class BufferTest : public testing::Test {
protected:

    virtual void SetUp() {
        char buffertestfile[] = "/tmp/buffertestfile";
        char buffertestfile2[] = "/tmp/buffertestfile2";
        read_buffer = new Buffer(buffertestfile, true);
        write_buffer = new Buffer(buffertestfile2, false);
    }

    virtual void TearDown() {
        delete read_buffer;
    }

    Buffer *read_buffer;
    Buffer *write_buffer;
};

TEST_F(BufferTest, Write) {
    cout << "hmm." << endl;
//    char result[256];
    string line;
    char text[] = "mal gucken, was das tut.\" und so weiter.. babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";
//    cout << "doing it soon" << endl;
    write_buffer->addchars(text);
//    cout << "done" << endl;
    delete write_buffer;
//    cout << "it is over" << endl;

    ifstream inFile("/tmp/buffertestfile2");

    int count = 0, i;
    if (inFile.is_open()) {
        while (inFile.good()) {
            getline(inFile, line);
            for (i=0; i < line.size(); i++) {
                if (text[i+count] == '\0') {
                    break;
                }
                ASSERT_EQ(text[i+count], line[i]) << "At count: " << count;
//                cout << "checked char: " << text[i+count] << endl;
            }
            count += i + 1; // +1 because of newline
        }
        inFile.close();
    } else {
        cout << "file not open!" << endl;
    }

    /*
    int i=0;
    if (inFile.is_open()) {
        cout << " starting reading " << endl;
        while (inFile >> x) {
            cout << " got char " << x << endl;
            ASSERT_EQ(text[i], x) << "At i: " << i;
            i++;
        }
        cout << " done " << endl;
        inFile.close();
    } else {
        cerr << "file not open!" << endl;
    }
    */

    ASSERT_EQ(strlen(text), count);

//    for (int i=0; i < 20; i++) {
//        cout << result[i] << endl;
//    }
}


TEST_F(BufferTest, Read) {
    cout << "hmm2." << endl;
    char expected[] = "babaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddd\nZ =?= ((3 +++ 4 - 6));\nÄy=X / (X - 4);\nprinto read a <=>*b;\n(* eine einfache Aufgabe !! *)\nm = n <=/ o;\n";
//    cout << sizeof(expected) << endl;

    int len = strlen(expected);
    for (int i=0; i < len * 8; i++) {
        char current_char = read_buffer->getchar();
        ASSERT_EQ(expected[i%len], current_char) << "At i: " << i;
//        cout << current_char << endl;
    }
    //cout << endl;
}
