#include<iostream>
using namespace std;

class LengthTextBuffer{
    public:
        LengthTextBuffer(int maxBytes=1000);
        void Clear();
        int Read(istream &);
        int Write(ostream &);
        //int Write(ostream &) const;
        int Pack(const char *, short int size=-1);
        int Unpack(char *);
        void Print(ostream &) const;
        void Init(int maxBytes=1000);
    private:
        char * Buffer;
        int BufferSize;
        int MaxBytes;
        int NextBytes;
};

