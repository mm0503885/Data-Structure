#include <fstream>
#include <iostream>
using namespace std;


int main(int argc,char* argv[]){

    ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

   fout<<"Negative cycle"<<endl;



    fin.close();
	fout.close();

    return 0;

}

