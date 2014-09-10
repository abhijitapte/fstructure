#include<iostream>
using namespace std;

class DelimTextBuffer{
    public:
        DelimTextBuffer(char delim='|', int maxBytes=1000);
        void Clear();
        int Read(istream &);
        int Write(ostream &);
        //int Write(ostream &) const;
        int Pack(const char *, int size=-1);
        int Unpack(char *);
        void Print(ostream &) const;
        void Init(char delim, int maxBytes=1000);
    private:
        char Delim;
        char DelimStr[2];
        char *Buffer;
        int BufferSize;
        int MaxBytes;
        int NextBytes;
};

