using namespace std;

class BufferFile{
    public:
        BufferFile(IOBuffer &);
        int Open(char *fname, int MODE);
        int Create(char *fname, int MODE);
        int Close();
        int Rewind();
        int Read(int recaddr=-1);
        int Write(int recaddr=-1);
        int Append();
        IOBuffer & GetBuffer();
    protected:
        IOBuffer & Buffer;
        fstream File;
        int HeaderSize;
        int ReadHeader();
        int WriteHeader();
};
