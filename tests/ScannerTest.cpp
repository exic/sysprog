#include "../scan/Scanner.hpp"
#include "../scan/Token.hpp"
#include "../scan/TType.hpp"
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
    char scannertestfile[] = "/tmp/scannertestfile";
    Scanner *s = new Scanner(scannertestfile);
    int expectedTokenColumns[] = {
        1, 8, 13, 15, 18, 19, 20, -1,
        1, 5, 6, -1,
        1, 5, 6, -1,
        1, 3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 17, 19, 20, 21, 22, -1,
        1, 2, 3, 5, 7, 8, 10, 12, 13, 14, -1,
        1, -1,
        -1,
        -1,
        1, 3, 5, 7, 8, 9, 11, 12
    };
    TokenColumnsTester(s, expectedTokenColumns, sizeof(expectedTokenColumns)/(sizeof(int)));
}

TEST_F(ScannerTest, TokensFileTwo) {
    char scannertestfile[] = "/tmp/scannertestfile2";
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
        1, 5, 8, -1,
        -1,
        1, 5, 6, 7, 8, -1,
        1, 5, 6, 7, 8, -1,
        1, 5, 6, 7, 8, -1,
        -1,
        1, 2, 3, 4, -1,
        1, 2, 3, 4, -1,
        1, 6, 7, 9, 11, 12, 13, -1,
        -1,
        3, 7, 9, 10, 11, 12, -1,
        3, 7, 9, 11, 13, 14, 18
    };
    TokenColumnsTester(s, expectedTokenColumns, sizeof(expectedTokenColumns)/(sizeof(int)));
}

TEST_F(ScannerTest, TokenTest) {
    char scannertestfile[] = "/tmp/scannertestfile";
    Scanner *s = new Scanner(scannertestfile);
    Token* t;
    bool sawLastPoint = false;
    for (int i = 1; (t = s->nextToken()) != 0; i++) {
//         EXPECT_FALSE(t) << "Hi! " << i << ", t: " << t << endl;
         switch (i) {
             case 4:
                 ASSERT_EQ(SIGN_NE, t->getType());
                 break;
             case 5:
                 ASSERT_EQ(SIGN_MULTIPLICATION, t->getType());
                 break;
             case 15:
                 ASSERT_EQ(SIGN_ASSIGN, t->getType());
                 break;
             case 16:
                 // Test if error token is created
                 ASSERT_EQ(NO_TYPE, t->getType());
                 break;
             case 32:
                 ASSERT_EQ(IDENTIFIER, t->getType());
                 ASSERT_STREQ("X", t->getEntry()->getLexem());
                 break;
             case 40:
                 ASSERT_EQ(IDENTIFIER, t->getType());
                 ASSERT_STREQ("hiho", t->getEntry()->getLexem());
                 break;
             case 43:
                 ASSERT_EQ(IDENTIFIER, t->getType());
                 ASSERT_STREQ("n", t->getEntry()->getLexem());
                 break;
             case 44:
                 ASSERT_EQ(SIGN_LT, t->getType());
                 break;
             case 45:
                 ASSERT_EQ(SIGN_ASSIGN, t->getType());
                 break;
             case 46:
                 ASSERT_EQ(SIGN_DIVISION, t->getType());
                 break;
             case 47:
                 ASSERT_EQ(IDENTIFIER, t->getType());
                 ASSERT_STREQ("o", t->getEntry()->getLexem());
                 break;
             case 48:
                 ASSERT_EQ(SIGN_SEMICOLON, t->getType());
                 break;
             case 49:
                 // If int is out of range, failure should be reported but
                 // token should not be passed on. Hence the next token after
                 // out-of-range-int is wanted here.
                 ASSERT_EQ(IDENTIFIER, t->getType());
                 ASSERT_STREQ("didntgettoolongvalue", t->getEntry()->getLexem());
                 sawLastPoint = true;
                 break;
         }
    }
    ASSERT_TRUE(sawLastPoint);

}

