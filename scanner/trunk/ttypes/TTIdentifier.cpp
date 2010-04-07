#include "../TType.hpp"

class TTInteger : public TType {
    public:
        char* getName() {
            return const_cast<char*>("identifier");
        }
    private:
        char* lexem;
};
