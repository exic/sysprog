#include "../TType.hpp"

class TTInteger : public TType {
    public:
        char* getName() {
            return const_cast<char*>("integer");
        }
    private:
        long value;
};
