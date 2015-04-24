#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
#define SIZE 1024
char line[SIZE];
char *sourceFile;
char *dirFile;
char *disFile;
//map<string,string> *IP2DO;
map<string,string> iptodo;

void map_insert(map<string,string> *ID2DO,string ip,string domain){
	ID2DO->insert(map<string,string>::value_type(ip,domain));
}

void readDir(){
	fstream fin;
	fin.open(dirFile,ios::in);
	while(fin.getline(line,sizeof(line),'\n')){
 		char buffer[1024];
		strcpy(buffer,line);
		char *domain = strstr(buffer,":");
		int point = domain - buffer;
		string ip = buffer;
		ip = ip.substr(0,point);
		*domain++;
		map_insert(&iptodo,ip,domain);	
		
	}
}
int main(int argc, char **argv){
	//read argv
	if(argc == 1 || argc == 2 || argc == 3){
		printf("Please tell me how to do it...\nEx: ./ip2do [domain list] [source config] [new config]\n");
		return 1;
	}
	dirFile = argv[1];
	sourceFile = argv[2];
	disFile = argv[3];
	readDir();
	//start main
	fstream fin;
	fstream fp;
	fin.open(sourceFile,ios::in);
	fp.open(disFile,ios::out);
	while(fin.getline(line,sizeof(line),'\n')){
		char a[1024];
		string buffer = strcpy(a,line);	
		map<string,string>::iterator iter;	
		for(iter= iptodo.begin();iter!=iptodo.end();iter++){
			string ip = iter->first;
			string domain = iter->second;
			int found;
			found = buffer.find(ip);
			if(found != -1){
				buffer.replace(found,ip.size(),domain);
			}
		}
		fp<<buffer<<endl;	
	}
	fp.close();
	return 0;	
}


