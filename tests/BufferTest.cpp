#include "BufferTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

void BufferTest :: setUp() {
    char buffertestfile[] = "buffertestfile";
    b = new Buffer(buffertestfile);
}

void BufferTest :: tearDown() {
    delete b;
}

void BufferTest::testOpen() {
    CPPUNIT_ASSERT(b->isOpen());
}

void BufferTest::testRead() {
    cout << endl << endl << endl << endl;
    for (int i=0; i<500; i++) {
        char c = b->getchar();
        cout << c;
    }
}
