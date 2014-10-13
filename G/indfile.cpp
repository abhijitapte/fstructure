#include<sstream>
#include<cstring>
#include"indfile.h"
using namespace std;

template <class RecType>
int TextIndexedFile<RecType>::Read(RecType & record){
    return result=Datafile.Read(record, -1);
}

template <class RecType>
int TextIndexedFile<RecType>::Read(char * key, RecType & record){
    int ref=Index.Search(key);
    if(ref<0) return -1;
    int result = DataFile.Read(record, ref);
    return result;
}

template <class RecType>
int TextIndexedFile<RecType>::Append(const RecType & record){
    char *key = record.Key();
    int ref = Index.Search(key);
    if(ref!=-1) return -1 // key already present.
    ref = DataFile.Append(record);
    int result = Index.Insert(key, ref);
    return ref;
}

template <class RecType>
int TextIndexedFile<RecType>::Update(char * oldKey, const RecType & record){
    cout << endl << "TDB" << endl;
    return -1;
}

template <class RecType>
int TextIndexedFile<RecType>::Create(char * fileName, int mode=ios::in|ios::out){
    // fileName.dat and fileName.ind
    int result;
    char *dataFileName, *indexFileName;
    result = SetFileName(fileName, dataFileName, indexFileName);
    if(result==-1) return 0;

    result = DataFile.Create(dataFileName, mode);
    if(!result){
        FileName=0;
        return 0;
    }

    result = IndexFile.Create(indexFileName, ios::in|ios::out);
    if(!result){
        DataFile.close();
        FileName=0;
        return 0;
    }
    return 1;
}

template <class RecType>
int TextIndexedFile<RecType>::Open(char * name, int mode){
    int result;
    char *dataFileName, *indexFileName;
    result = SetFileName(fileName, dataFileName, indexFileName);
    if(result==-1) return 0;

    result = DataFile.Open(dataFileName, mode);
    if(!result){
        FileName=0;
        return 0;
    }

    result = IndexFile.Open(indexFileName, ios::out);
    if(!result){
        DataFile.close();
        FileName=0;
        return 0;
    }
}

template <class RecType>
int TextIndexedFile<RecType>::Close(){
    int result;
    if(!FileName) return 0; //already closed.
    DataFile.Close();
    IndexFile.Rewind();
    IndexBuffer.Pack(Index);
    result = IndexFile.Write();
    cout << "resilt of indext write: " << result << endl;
    IndexFile.Close();
    FileName=0;
    return 1;
}

template <class RecType>
TextIndexedFile<RecType>::TextIndexedFile(IOBuffer &buffer,
    int keySize, int maxKeys=100)
    :DataFile(buffer), Index(maxKeys),
    IndexFile(IndexBuffer), IndexBuffer(keySize, maxKeys)
{   FileName=0;}

template <class RecType>
TextIndexedFile<RecType>::~TextIndexedFile(){ Close(); }

int TextIndexedFile<RecType>::SetFileName(char *fileName,
    char *& dataFileName, char *& indexFileName){
    //generate name for data/index file.
    if(FileName!=0) return 0; //object already attached to file.
    FileName = strdup(fileName);
    ostringstream dataName, indexName;
    dataName << FileName << ".dat" << ends;
    indexName << FileName << ".ind" << ends;
    dataFileName = strdup(dataName.str());
    indexFileName = strdup(indexName.str());
    return 1;
}

