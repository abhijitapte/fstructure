#ifndef DELIMFIELDBUFFER
#define DELIMFIELDBUFFER
#include"varlen.h"
using namespace std;

class DelimFieldBuffer: public VariableLengthBuffer{
    public:
        DelimFieldBuffer(char delim = -1, int maxBytes=1000);
        DelimFieldBuffer(const DelimFieldBuffer & buffer); //copy constructor
        void Clear();
        int Pack(const void *, int size=-1);
        int Unpack(void * field, int maxBytes=-1);
        int ReadHeader(istream &);
        int WriteHeader(ostream &) const;
        void Print(ostream &) const;
        void Init(char delim=0);
        static void SetDefaultDelim(char delim);
    protected:
        char Delim;
        static char DefaultDelim;
};

inline DelimFieldBuffer::DelimFieldBuffer(const DelimFieldBuffer & buffer)
    :VariableLengthBuffer(buffer){
    Init(buffer.Delim);
}

#endif
