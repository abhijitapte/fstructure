#include"fixlen.h"
using namespace std;

class FixedFieldBuffer: public FixedLengthBuffer{
    public:
        FixedFieldBuffer(int maxFields, int recordSize=1000);
        FixedFieldBuffer(int maxFields, int *fieldSize);
        FixedFieldBuffer(const FixedFieldBuffer &); //copy constructor
        FixedFieldBuffer & operator = (const FixedFieldBuffer &);
        void Clear();
        int AddField(int fieldSize); //define nxt field.
        int ReadHeader(istream &);
        int WriteHeader(ostream &) const;
        int Pack(const void *, int size=-1);
        int Unpack(void * field, int maxBytes=-1);
        void Print(ostream &) const;
        int NumberOfFields() const; //return no. of defined fields.
        int Init(int maxFields);
        int Init(int numFields, int *fieldSize);
    protected:
        int *FieldSize;//array to hold field sizes
        int MaxFields; //maximum no. of fields
        int NumFields; //actual number of defined fields
        int NextField; //index of next fields to be packed/unpacked
};

inline FixedFieldBuffer::FixedFieldBuffer(const FixedFieldBuffer & buffer)
    :FixedLengthBuffer(buffer){
    Init(buffer.NumFields, buffer.FieldSize);
}

