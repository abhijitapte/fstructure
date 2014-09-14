#include<iostream>
using namespace std;

BufferFile::BufferFile(IOBuffer & from):Buffer(from){}

int BufferFile::Open(char * filename, int mode){
    if(mode & ios::noreplace || mode & ios::trunc) return 0;
    File.open(filename, mode|ios::in|ios::nocreate|ios::binary);
    if(!File.good()) return 0;
    File.seekg(0, ios::beg);
    File.seekp(0, ios::beg);
    HeaderSize = ReadHeader();
    if(!HeaderSize) return 0;
    File.seekp(HeaderSize, ios::beg)
    File.seekg(HeaderSize, ios::beg)
    return File.good();
}

int BufferFile::Create(char * filename, int mode){
    if(!(mode & ios::out) ) return 0;
    File.open(filename, mode|ios::out|ios::noreplace|ios::binary);
    if(!File.good()) {
        File.close();
        return 0;
    }
    HeaderSize = WriteHeader();
    return HeaderSize!=0;
}

int BufferFile::Close(){
    File.close()
    return 1;
}

int BufferFile::Rewind(){
    File.seekp(HeaderSize, ios::beg)
    File.seekg(HeaderSize, ios::beg)
    return 1;
}

int BufferFile::Read(int recaddr){
    if(recaddr==-1) return Buffer.Read(File);
    else return Buffer.DRead(File, recaddr);
}

int BufferFile::Write(int recaddr){
    if(recaddr==-1) return Buffer.Write(File);
    else return Buffer.DWrite(File, recaddr);
}

int BufferFile::Append(){
    File.seekp(0, ios::beg);
    return Buffer.Write(File);
}

IOBuffer & BufferFile::GetBuffer(){
    return Buffer;
}

IOBuffer & BufferFile::GetBuffer(){
    return Buffer;
}

int BufferFile::ReadHeader(){
    return Buffer.ReadHeader(File);
}

int BufferFile::WriteHeader(){
    return Buffer.WriteHeader(File);
}

