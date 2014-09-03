
int ReadVariablePerson(istream & stream, Person &p){
    short length;
    stream.read(&length, sizeof(length));
    if(stream.fail()){
        p.LastName[0] = 0;
        return 0;
    }
    char * buffer = new char[length + 1];
    stream.read(buffer, length);
    buffer[length] = 0;
    istrstream strbuff(buffer);
    strbuff >> p;
    return 1;
}

