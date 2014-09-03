#include<stdio.h>

int main(){
char ch;
FILE *file;
char filename[20];
printf("Enter the name of the file: ");
gets(filename);
file = fopen(filename, "r");
while ( fread(&ch,1, 1, file) != 0)
	fwrite(&ch, 1, 1, stdout);
fclose(file);
return(0);
}
