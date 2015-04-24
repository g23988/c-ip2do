#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
#define SIZE 1024

map<string,string> iptodo;

void map_insert(map<string,string> *ID2DO,string ip,string domain){
	ID2DO->insert(map<string,string>::value_type(ip,domain));
}
void readDir(char* dirFile ){
	char line[SIZE] = {0};
	string strDomain = "";
	string strIP = "";
	fstream fin;
	fin.open(dirFile,ios::in);
	while(fin.getline(line,sizeof(line),'\n')){
 		
		strDomain = strtok(line, ":");
		if(strDomain != ""){
			strIP = strtok(NULL, ":");
		}
		map_insert(&iptodo,strIP,strDomain);	
		
	}
	fin.close();
}
int main(int argc, char **argv){
	char line[SIZE] = {0};
	string buffer;
	//read argv
	if((argc == 1) || (argc == 2) || (argc == 3)){
		printf("Please tell me how to do it...\nEx: ./ip2do [domain list] [source config] [new config]\n");
		return 1;
	}
	readDir(argv[1]);
	//start main
	fstream fin;
	fstream fp;
	fin.open(argv[2],ios::in);
	fp.open(argv[3],ios::out);
	int found = -1;
	while(fin.getline(line,sizeof(line),'\n')){
		//char a[1024];
		string buffer = line;	
		buffer = line;
		map<string,string>::iterator iter;	
		for(iter= iptodo.begin();iter!=iptodo.end();iter++){
			string ip = iter->first;
			string domain = iter->second;
			found = buffer.find(ip);
			if(found != -1){
				buffer.replace(found,ip.size(),domain);
			}
		}
		fp<<buffer<<endl;	
	}
	fin.close();
	fp.close();
	fin.close();
	return 0;	
}


