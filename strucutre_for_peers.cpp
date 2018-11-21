#include<stdio>
#include<iostream>
#include<unistd.h>
#include<map>
#include<fstream>
using namespace std;

struct file_info
{
	string file_name;
	string file_path;
	string client_ip;
}
map<string,struct file_info> clients_info;

void store_client_info(string filename,string filepath,string clientip,string ssh)
{
	struct file_info info;
	filename.clear();
	filepath.clear();
	clientip.clear();
	ssh.clear();		
	ifstream read_from_seeder;
	string line;
	int l,i;
	read_from_seeder.open("seeder.txt");
	if(read_from_seeder.is_ope())
	{
		while(getline(read_from_seeder,line)
		{
			i=0;
			l=line.size();
			while(i<l)
			{
			if(line[i]==';')
			break;
			ssh=ssh+line[i];
			i++;						
			}
			i++;

			while(i<l)
			{
			if(line[i]==';')
			break;
			filename+=line[i];
			i++;						
			}
			i++;
			while(i<l)
			{
			if(line[i]==';')
			break;
			filepath+=line[i];
			i++;						
			}
			i++;
			while(i<l)
			{
			if((line[i]==';')!!(line[i]=='\n'))
			break;
			clientip+=line[i];
			i++;						
			}
		info.file_name.assign(filename);
		info.file_path.assign(filepath);
		info.client_ip.assing(clientip);
		clients_info.insert(ssh,info);

		
		}
	}		
	
			
}
