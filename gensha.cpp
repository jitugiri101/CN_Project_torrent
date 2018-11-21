#include "gensha.h"
#include "hdr_for_gen.h"
#include<stdio.h>
#include<openssl/sha.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<string.h>
#include<unistd.h>
#include<map>
using namespace std;
extern string ip_temp;
extern string shahash;
extern long long int file_size;
extern map<string,struct file_info> clients_info;
extern string seeders;
struct file_info
{
	string file_name;
	string file_path;
	string client_ip;
	string file_size;
};
/*void generate_sha(string s)
{	
	int i,k=0;
	ifstream myReadFile;
	char out[61];
	shahash.clear();
	FILE*pfile; 	
	myReadFile.open(s.c_str());
 	char output[512*1024];
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
			shahash=shahash+out;
			memset(out,'\0',512);
			
		}
	}

	myReadFile.close();
	
}*/
void mtorrent(string s,string server,string port1,string tracker2,string port2)
{
	string name,temp,fullname,fs,file_name,size,sha;
	int l,i,pos,pos1,k,r,u;
	//cin>>s;
	
	ifstream f_read;
	ofstream f_write;
	f_read.open(s.c_str());
	l=s.size();
	for(i=0;i<l;i++)
	{
		if(s[i]=='/')
			pos=i;
		if(s[i]=='.')
			pos1=i;
	}
	for(i=pos+1;i<l;i++)
	fullname+=s[i];
	for(i=pos+1;i<pos1;i++)
	{
		name=name+s[i];
	}
	FILE *f = fopen(s.c_str(), "r");
  	fseek(f, 0, SEEK_END);
	file_size=ftell(f);  
	name.assign(fullname);	
	fullname=fullname+".mtorrent";
	f_write.open(fullname.c_str());
	temp="Tracker URL1:";
	temp+=server;
	temp+=":";
	temp+=port1;
	f_write<<temp.c_str();
	f_write<<"\n";
	temp="Tracker URL2";
	temp+=tracker2;
	temp+=":";
	temp+=port2;
	f_write<<temp.c_str();
	f_write<<"\n";
	f_write<<"Filename:";
	temp=temp+name;
	f_write<<name.c_str();
	f_write<<"\n";
	generate_sha(s);		
	temp="Filesize:";
	f_write<<temp;
	k=file_size;
	u=k;
	k=0;
	while(u>0)
	{
		r=u%10;
		k=k*10+r;
		u=u/10;
	}	
	
	while(k>0)
	{
		r=k%10;
		fs+=(char)(r+'0');	
		k=k/10;
	}
	//std::reverse(fs.begin(),fs.end());
	f_write<<fs.c_str();
	f_write<<"\n";
	temp="SHA:";
	f_write<<temp;
	f_write<<shahash;

}

void string_cal(char buffer[9999],string ip_temp)
{
		//string ip_temp="127.0.0.1";
		int l,k,i,j,pos,pos1,file_size,fl,u,r;
		    string cmp,name,fs;
		l=strlen(buffer);
		for(i=0;i<l;i++)
		{
		
			if(buffer[i]==32)
			break;
			cmp+=buffer[i];
		}
		//cout<<cmp.c_str()<<"1st"<<endl;
		if(cmp=="share")
		{
		cmp.clear();
		i++;
		for(i;i<l;i++)
		{
			if(buffer[i]==32)
			break;
			cmp+=buffer[i];					
		}
		k=0;
		FILE *f = fopen(cmp.c_str(), "r");
  		fseek(f, 0, SEEK_END);
		file_size=ftell(f);  
	
		generate_sha(cmp.c_str());
		
		for(i=0;i<shahash.size();i++)
		{
			buffer[k]=shahash[i];
			k++;
		}		
		buffer[k]=';';
		k++;
		//cout<<buffer<<endl;
		for(i=0;i<cmp.size();i++)
		{
			buffer[k]=cmp[i];
			k++;
		}
		buffer[k]=';';
		k++;
		for(i=0;i<cmp.size();i++)
		{
		if(cmp[i]=='/')
			pos=i;
		if(cmp[i]=='.')
			pos1=i;
		}
		for(i=pos+1;i<cmp.size();i++)
		{
		name=name+cmp[i];
		}
		for(i=0;i<name.size();i++)
		{
			buffer[k]=name[i];
			k++;
		}
		buffer[k]=';';
		k++;
		for(i=0;i<ip_temp.size();i++)
		{
			buffer[k]=ip_temp[i];
			k++;
		}
		buffer[k]=';';
		k++;
		fl=file_size;
		u=fl;
		fl=0;
		while(u>0)
		{
			r=u%10;
			fl=fl*10+r;
			u=u/10;
		}	
	
		while(fl>0)
		{
			r=fl%10;
			fs+=(char)(r+'0');	
			fl=fl/10;
		}
		for(i=0;i<fs.size();i++)
		{
			buffer[k]=fs[i];
			k++;
		}
		buffer[k]=';';
		
		
}
}


void seeder_update(string ssh,string filename,string filepath,string client_ip,string filesize)
{
fstream seeder;

seeder.open(seeders.c_str(), std::ofstream::out | std::ofstream::app);
seeder<<ssh;
seeder<<";";
seeder<<filename;
seeder<<";";
seeder<<filepath;
seeder<<";";
//seeder<<filesize;
//seeder<<";";
seeder<<client_ip;
seeder<<";";
seeder<<filesize;
seeder<<";";
seeder<<"\n";
}


void store_client_info()
{
	struct file_info info;
	string filename,filepath,clientip,ssh,filesize;
	filename.clear();
	filepath.clear();
	clientip.clear();
	ssh.clear();	
	filesize.clear();	
	ifstream read_from_seeder;
	string line;
	int l,i;
	read_from_seeder.open(seeders.c_str());
	if(read_from_seeder.is_open())
	{
		while(getline(read_from_seeder,line))
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
			if((line[i]==';')||(line[i]=='\n'))
			break;
			clientip+=line[i];
			i++;						
			}
			i++;
			while(i<l)
			{
			if((line[i]==';')||(line[i]=='\n'))
			break;
			filesize+=line[i];
			i++;		
			}
		info.file_name.assign(filename);
		info.file_path.assign(filepath);
		info.client_ip.assign(clientip);
		info.file_size.assign(filesize);
		clients_info.insert(pair<string,struct file_info>(ssh,info));

		
		}
	}		
	
			
}


void change_seed_ds(string ssh,string filename,string filepath,string client_ip,string filesize)
{
	seeder_update(ssh,filename,filepath,client_ip,filesize);	
	store_client_info();
	map<string,struct file_info>::iterator itr;
	itr=clients_info.begin();	
	
}


