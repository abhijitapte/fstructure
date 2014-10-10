#ifndef IOBUFFER
#define IOBUFFER
using namespace std;

class IOBuffer{
    public:
        IOBuffer(int maxBytes=1000);
        IOBuffer & operator = (const IOBuffer &);
        virtual void Clear();
        virtual int Pack(const void *field, int size=-1)=0;
        virtual int Unpack(void *field, int maxbytes=-1)=0;
        virtual void Print(ostream &) const;
        int Init(int maxBytes);
        virtual int Read(istream &)=0;
        virtual int Write(ostream &)const=0;
        virtual int DRead(istream &, int recref);
        virtual int DWrite(ostream &, int recref) const;
        virtual int ReadHeader(istream &);
        virtual int WriteHeader(ostream &) const;
    protected:
        int Initialized;
        char * Buffer;
        int BufferSize;
        int MaxBytes;
        int NextByte;
        int Packing;
}; 

#endif
