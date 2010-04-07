#include "../TType.hpp"

class TTest : public TType {
    public:
        char* getName() {
            return const_cast<char*>("Test");
        }
};
