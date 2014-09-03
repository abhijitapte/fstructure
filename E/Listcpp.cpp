#include <fstream>
#include <iostream>
using namespace std;

int main(){
	char ch;
	char filename[20];
	fstream file;
	cout << "Enter the name of the file: "
		 << flush;
	cin >> filename;
	file.open(filename, ios::in);
	file.unsetf(ios::skipws);
	while (1){
		file >> ch;
		if(file.fail()) break;
		cout << ch;
	}
	file.close();
	return(0);
}
