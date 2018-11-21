#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string>
#include "gensha.h"
#include "hdr_for_gen.h"
#define PORT 4466
#define PORT2 7777
string shahash;
long long int file_size;
map<string,struct file_info> clients_info;
string seeders;
struct file_info
{
	string file_name;
	string file_path;
	string client_ip;
	string file_size;
	
};
void create_conn_to_2(char buffer[9999],string ip,int port2)
{

//setbuf(stdout,NULL);
	string cmp,name,temp,functionality,torrent;
	int k,pos,pos1,i,l,j;
	char info[1024];
	

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	//char buffer[9999];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	//printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port2);
	serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to tracker 2.\n");
	while(1)
		{
		printf("Tracker 1: \t");
		//fgets(buffer,9999,stdin);
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
		//mtorrent(torrent);
		string_cal(buffer,"127.0.0.1");
		
		//cout<<buffer;		
		send(clientSocket, buffer, strlen(buffer), 0);
		}
		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
			break;
		}

		if(recv(clientSocket, buffer, 9999, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buffer);
		}}





}
int main(int argc, char*argv[]){
	int l;
	string sha_server,filename_server,filepath_server,client_server,filesize_server;
	seeders=argv[3];
	
	int sockfd, ret;	struct sockaddr_in serverAddr;
struct sockaddr_in newAddr;
	int newSocket,k;
	

	socklen_t addr_size;
	string first,first_ip,first_port,second,second_ip,second_port;
	int i,j,port1,port2;
	first=argv[1];
	l=first.size();
	k=first.find(':');
	first_ip=first.substr(0,k);
	//cout<<first_ip<<endl;
	first_port=first.substr(k+1,l-k);
	second=argv[2];
	l=second.size();
	k=second.find(':');
	second_ip=second.substr(0,k);
	second_port=second.substr(k+1,l-k);
	//cout<<first_port<<endl;
	//cout<<second_ip<<endl<<second_port<<endl;	
	l=first_port.size();
	//reverse(first_port.begin(),first_port.end());
	k=0;
	for(i=0;i<l;i++)
	{	
		k=k*10+(first_port[i]-'0');		
	}	
	port1=k;
	
	//cout<<k<<endl;
	char buffer[9999];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(k);
	serverAddr.sin_addr.s_addr = inet_addr(first_ip.c_str());
	k=0;
	for(i=0;i<l;i++)
	{	
		k=k*10+(first_port[i]-'0');		
	}	
	port2=k;

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}


	while(1)
	{
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0)
		{
			exit(1);
		}
		//printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		
		if((childpid = fork()) == 0)
		{
			//close(sockfd);

			while(1)
			{
				recv(newSocket, buffer, 9999, 0);
				if(strcmp(buffer, ":exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}
				else
				{

				l=strlen(buffer);
				//cout<<buffer<<endl;
					for(i=0;i<l;i++)
			{
		
		if(buffer[i]==';')
		break;
		sha_server+=buffer[i];
		}	
		//cout<<sha_server.c_str()<<endl;
		i++;
		for(i;i<l;i++)
		{
		if(buffer[i]==';')
		break;
		else
		filepath_server+=buffer[i];
		}
		i++;
		//cout<<filepath_server.c_str()<<endl;
		for(i;i<l;i++)
		{
		if(buffer[i]==';')
		break;
		else
		filename_server+=buffer[i];
		}
		i++;
		//cout<<filename_server.c_str()<<endl;
		for(i;i<l;i++)
		{
		if(buffer[i]==';')
		break;
		else
		client_server+=buffer[i];
		}			
		//cout<<sha_server<<endl;
		//cout<<filename_server<<endl;
		//cout<<filepath_server<<endl;
		//cout<<client_server.c_str()<<endl;
		i++;	
		for(i;i<l;i++)
		{
		if(buffer[i]==';')
		break;
		else
		filesize_server+=buffer[i];
		//cout<<filesize_server.c_str()<<endl;
		}					
		//cout<<filesize_server.c_str()<<endl;			
															
		change_seed_ds(sha_server.c_str(),filename_server.c_str(),filepath_server.c_str(),client_server.c_str(),filesize_server.c_str());
					//printf("Client: %s\n", buffer);
create_conn_to_2(buffer,second_ip,port2);
					printf("Data saved in seeder\n");
					cout<<"Enter next command";
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
		}

		
			}
		}

	

	close(newSocket);


	return 0;
}
