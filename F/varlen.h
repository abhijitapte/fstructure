using namespace std;

class VariableLengthBuffer: public IOBuffer{
    public:
        VariableLengthBuffer(int MaxBytes=1000);
        VariableLengthBuffer(const VariableLengthBuffe & buffer)
            :IOBuffer(buffer);//copy constructor.
        void Clear();
        int Read(istream &);
        int Write(ostream &) const;
        int ReadHeader(istream &);
        int WriteHeader(ostream &) const;
        int PachFixLen(void *, int);
        int PackDelimeted(void *, int);
        int PackLength(void *, int);
        void Print(ostream &) const;
        int SizeOfBuffer() const;
        int Init();
};
