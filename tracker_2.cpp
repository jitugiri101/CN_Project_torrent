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
#define PORT 7777

string shahash;
long long int file_size;
map<string,struct file_info> clients_info;
string seeders="seeder1.txt";
struct file_info
{
	string file_name;
	string file_path;
	string client_ip;
	string file_size;
	
};
int main(int argc, char*argv[]){
	int l;
	string sha_server,filename_server,filepath_server,client_server,filesize_server;
	//seeders=argv[3];
	
	int sockfd, ret,i,j;	struct sockaddr_in serverAddr;
struct sockaddr_in newAddr;
	int newSocket;
	
	string ip=argv[1];
	string tracker_ip,tracker_port;
	l=ip.size();
	int k=ip.find(':');
	tracker_ip=ip.substr(0,k);
	tracker_port=ip.substr(k+1,l-k);
	k=0;	
	for(i=0;i<tracker_port.size();i++)
	{
	k=k*10+(tracker_port[i]-'0');
	}
	cout<<tracker_ip<<endl<<k<<endl;
	socklen_t addr_size;
	
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
	serverAddr.sin_addr.s_addr = inet_addr(tracker_ip.c_str());

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	//printf("[+]Bind to port %d\n", 4444);

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
					//printf("Data saved in seeder\n");
					//cout<<"Enter next command";
					//send(newSocket, buffer, strlen(buffer), 0);
	//				bzero(buffer, sizeof(buffer));
				}
		}
			}
		}

	

	close(newSocket);


	return 0;
}
