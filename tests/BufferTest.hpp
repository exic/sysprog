#ifndef BUFFERTEST
#define BUFFERTEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Buffer.hpp"

using namespace std;

class BufferTest : public CPPUNIT_NS :: TestFixture {

    CPPUNIT_TEST_SUITE(BufferTest);
    CPPUNIT_TEST(testOpen);
    CPPUNIT_TEST(testRead);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

    protected:
        void testOpen();
        void testRead();

    private:
        Buffer *b;
};

#endif

