#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "gensha.h"
#include "hdr_for_gen.h"
#define PORT 4464
string torrent;
string shahash;
long long int file_size;
map<string,struct file_info> clients_info;
string seeders;
struct file_info
{
	string file_name;
	string file_path;
	string client_ip;
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


int main(int argc,char*argv[]){
	
	setbuf(stdout,NULL);
	string cmp,name,temp,functionality,torrent;
	int k,pos,pos1,i,l,j;
	char info[1024];
	string ip_client,server,tracker2,client_ip,client_port,server_ip,server_port,tracker2_ip,tracker2_port;
	ip_client=argv[1];
	server=argv[2];
	tracker2=argv[3];
	l=ip_client.size();
	k=ip_client.find(':');
	client_ip=ip_client.substr(0,k);
	client_port=ip_client.substr(k+1,l-k);
	l=server.size();
	k=server.find(':');
	server_ip=server.substr(0,k);
	server_port=server.substr(k+1,l-k);
	l=tracker2.size();
	k=tracker2.find(':');
	tracker2_ip=tracker2.substr(0,k);
	tracker2_port=tracker2.substr(k+1,l);
	//cout<<client_ip<<endl<<client_port<<server_ip<<endl<<server_port<<endl<<tracker2_ip<<endl<<tracker2_port<<endl;
	l=server_port.size();
	k=0;
	for(i=0;i<l;i++)
	{	
		k=k*10+(server_port[i]-'0');	
	}
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[9999];
	 
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(k);
	serverAddr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Tracker 1.\n");

	while(1)
		{
		printf("Client: \t");
		fgets(buffer,9999,stdin);
		l=strlen(buffer);
		for(i=0;i<l;i++)
		{
			if(buffer[i]==32)
			break;
			functionality+=buffer[i];
		}
		//cout<<functionality<<endl;
		if(functionality=="share")
		{	
			i++;
			for(i;i<l;i++)
			{	
				if(buffer[i]==32)
				break;
				torrent+=buffer[i];
			}
		/*i++;
		for(i;i<l;i++)
		{
			if(buffer[i]=='\n')
			break;
			torrent+=buffer[i];
		}
		l=torrent.size();
		k=torrent.find('.');
		for(i=k+1;i<l;i++)
		{
		if(torrent[i]=='.')
   		break;
   		}
  		torrent=torrent.substr(0,i);
		}*/
		//cout<<torrent<<endl;
				
		mtorrent(torrent,server_ip,server_port,tracker2_ip,tracker2_port);
		string_cal(buffer,client_ip);
		
		//cout<<buffer;		
		send(clientSocket, buffer, strlen(buffer), 0);
		}
		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 9999, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buffer);
		}}
	
	
return 0;
}
