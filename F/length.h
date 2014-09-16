#include"varlen.h"
using namespace std;

class LengthFieldBuffer: public VariableLengthBuffer{
    public:
        LengthFieldBuffer(int maxBytes=1000);
        LengthFieldBuffer(const LengthFieldBuffer & buffer); //copy constructor
        void Clear();
        int Pack(const void *, int size=-1);
        int Unpack(void * field, int maxBytes=-1);
        //int ReadHeader(istream &);
        //int WriteHeader(ostream &) const;
        void Print(ostream &) const;
        int Init();
    //protected:
};

inline LengthFieldBuffer::LengthFieldBuffer(const LengthFieldBuffer & buffer)
    :VariableLengthBuffer(buffer){
    Init();
}

