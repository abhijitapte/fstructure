#include<string>
#include<cstring>
#include<iostream>
#include"deltext.h"
using namespace std;

DelimTextBuffer::DelimTextBuffer(char delim, int maxBytes){
    Init(delim, maxBytes);
}

void DelimTextBuffer::Clear(){
    NextBytes=0;
    BufferSize=0;
}

void DelimTextBuffer::Init(char delim, int maxBytes){
    Delim=delim;
    Delim='|';
    DelimStr[0] = Delim;
    DelimStr[1] = 0;
    if(maxBytes<0) maxBytes=0;
    MaxBytes = maxBytes;
    Buffer = new char[MaxBytes];
    Clear();
}

int DelimTextBuffer::Read(istream & stream){
    Clear();
    stream.read((char *)&BufferSize, sizeof(BufferSize));
    if(stream.fail()) return 0;
    if(BufferSize > MaxBytes) return 0;
    stream.read(Buffer, BufferSize);
    return stream.good();
}

int DelimTextBuffer::Write(ostream & stream) const{
    stream.write((char*)(&BufferSize), sizeof(BufferSize));
    stream.write(Buffer, BufferSize);
    return stream.good();
}

int DelimTextBuffer::Pack(const char *str, int size){
    short len;

    if(size>=0) len=size;
    else len=strlen(str);

    if(len > strlen(str)) return 0;

    int start = NextBytes;
    NextBytes += (len + 1);
    if(NextBytes > MaxBytes) return 0;
    memcpy(&Buffer[start], str, len);
    Buffer[start+len] = Delim;
    BufferSize = NextBytes;
    //strcat(&Buffer[start+len], DelimStr);
    return 1;
}

int DelimTextBuffer::Unpack(char *str){
    int len=-1;
    if(NextBytes >= BufferSize) return 0;

    int start = NextBytes;
    for(int i=start; i<BufferSize; i++){
        if(Buffer[i]==Delim){
            len = i - start;
            break;
        }
    }
    if(len==-1) return 0;
    NextBytes += len + 1;
    if(NextBytes > BufferSize) return 0;
    strncpy(str, &Buffer[start], len);
    str[len]=0;
    return 1;
}

void DelimTextBuffer::Print(ostream & stream) const{
    stream << "Buffer has max characters :" << MaxBytes
        << "\nand Buffer size :" << BufferSize << endl;
}

