#include<iostream>
using namespace std;

class FixedTextBuffer{
    public:
        FixedTextBuffer(int maxFields, int maxChars=1000);
        FixedTextBuffer(int numFields, int *FieldSize);
        int NumberOfFields() const;
        void Clear();
        int AddField(int fieldSize);
        int Read(istream &);
        int Write(ostream &);
        int Pack(const char *);
        int Unpack(char *);
        void Print(ostream &) const;
        void Init(int numFields, int maxChars=1000);
        void Init(int numFields, int maxChars=1000);
    private:
        char * Buffer;      // character array to hold field values.
        int BufferSize;     // sum of sizes of declared fields.
        int * FieldSize;    // array to hold field sizes.
        int MaxFields;      // maximum number of fields.
        int MaxChars;       // maximum number of characters in buffer.
        int NumFields;      // actual number of defined fields.
        int NextField;      // index of next field to be packed/unpacked.
        int NumFieldValues; // number of fields which are packed.
        int Packing;        // TRUE if packing phase.
        int NextCharacter;  //[un]pack position in buffer.
};
