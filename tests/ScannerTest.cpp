#include "../scan/Scanner.hpp"
#include "../scan/Token.hpp"
#include <gtest/gtest.h>
#include <string.h>

using namespace std;

class ScannerTest : public testing::Test {

protected:
    void TokenColumnsTester(Scanner* s, int expectedTokenColumns[], int array_size) {
        int line = 1;
        for (int i=0; i < array_size; i++) {
            int expected = expectedTokenColumns[i];
            if (expected == -1) {
                line++;
                continue;
            }
            Token* t = s->nextToken();
            ASSERT_EQ(line, t->getLine());
            ASSERT_EQ(expected, t->getColumn()) << "This error is at line " << line << endl;
        }
    }
};

TEST_F(ScannerTest, TokensFileOne) {
    char scannertestfile[] = "scannertestfile";
    Scanner *s = new Scanner(scannertestfile);
    int expectedTokenColumns[] = {
        1, 8, 13, 15, 18, 19, 20, -1,
        1, 5, 6, -1,
        1, 5, 6, -1,
        1, 3, 5, 7
    };
    TokenColumnsTester(s, expectedTokenColumns, sizeof(expectedTokenColumns)/(sizeof(int)));
}

TEST_F(ScannerTest, TokensFileTwo) {
    char scannertestfile[] = "scannertestfile2";
    Scanner *s = new Scanner(scannertestfile);
    int expectedTokenColumns[] = {
        -1,
        -1,
        1, 5, 6, -1,
        1, 5, 6, -1,
        1, 5, 6, -1,
        -1,
        1, 5, 6, -1,
        1, 5, 6, -1,
        -1,
        1, 5, 8, -1,
        1, 5, 8

    };
    TokenColumnsTester(s, expectedTokenColumns, sizeof(expectedTokenColumns)/(sizeof(int)));
}
