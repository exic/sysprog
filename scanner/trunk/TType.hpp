#ifndef TTYPE
#define TTYPE

class TType {
    public:
        virtual char* getName() {
            return const_cast<char*>("makemeabstract");
        };
};

#endif
