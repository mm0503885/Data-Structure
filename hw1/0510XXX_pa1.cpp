#include <fstream>

int main(int argc,char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);
	
	//start your program here
	
	fin.close();
	fout.close();
	return 0;
}
	