#include"iobuffer.h"
using namespace std;

class Recording{
    public:
        Recording();
        Recording(char *label, char *idNum, char *title, char * composer, char * artist);
        char IdNum[7]; char Title[30]; char Label[7];
        char Composer[30]; char Artist[30];
        char *Key() const;
        int Unpack(IOBuffer &);
        int Pack(IOBuffer &) const;
        void Print(ostream &, char *label=0) const;
        friend ostream & operator << (ostream &stream, Recording &rec);
};

ostream & operator << (ostream &, Recording &);

inline ostream & operator << (ostream &stream, Recording &rec){
    rec.Print(stream);
    return stream;
}
