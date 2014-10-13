#include"iobuffer.h"
#include"tindbuff.h"
#include"buffile.h"
using namespace std;

template <class RecType>
class TextIndexedFile{
    public:
        int Read(RecType & record); //read next record
        int Read(char * key, RecType & record); //read by key
        int Append(const RecType & record);
        int Update(char * oldKey, const RecType & record);
        int Create(char * name, int mode=ios::in|ios::out);
        int Open(char * name, int mode=ios::in|ios::out);
        int Close();
        TextIndexedFile(IOBuffer &buffer, int keySize, int maxKeys=100);
        ~TextIndexedFile();
    protected:
        TextIndex Index;
        BufferFile IndexFile;
        TextIndexBuffer IndexBuffer;
        RecordFile<RecType> DataFile;
        char *FileName;
        int SetFileName(char *fileName,
            char *& dataFileName, char *& indexFileName);
};
