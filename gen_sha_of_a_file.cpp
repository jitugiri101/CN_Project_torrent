#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<openssl/sha.h>
using namespace std;

int main() 
{	string s;
	cin>>s;
	
	//s="/home/jitu/Desktop/change.txt";
	//FILE *f = fopen(s.c_str(), "r");
  	//fseek(f, 0, SEEK_END);
  	//printf("%ld\n", ftell(f));
  	//fclose(f);
  
	int i,k=0;
	string str;
	ifstream myReadFile;
	char out[60];
	
	str.clear();
	FILE*pfile; 	
	myReadFile.open(s.c_str());
 	char output[512*1024];
	memset(output,'\0',512*1024);	
	unsigned char hash[20];
 	if (myReadFile.is_open()) 
	{
 		while (!myReadFile.eof()) 
		{
			myReadFile.read(output,512*1024);
			//cout<<output<<endl;
   			// myReadFile >> output;
    			//cout<<output<<endl;
			SHA1((unsigned char*) output,512*1024, hash);
			for(i=0;i<20;i++)
			{
			snprintf(out+i*2,4,"%02x",hash[i]);
			}
			str=str+out;
			memset(output,'\0',512*1024);
			
		}}

		/*ofstream new_file;
		pfile=fopen("/home/anant/Desktop/Torrent.txt","wb+");
		if(pfile!=NULL)
		{	fputs("address1",pfile);
			fputs(str.c_str(),pfile);
			fclose(pfile);

		}
					
			/*for(i=0;i<20;i++)
			printf("%02x",hash[i]);
			printf("\n");*/
		
			
			//for(i=0;i<str.size();i++)
			//{
			//	printf("%02x",str[i]);
			cout<<str;	
			
			//}*/
		cout<<str;
		
	
		
	myReadFile.close();
	return 0;
}



