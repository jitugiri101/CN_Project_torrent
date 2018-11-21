#include<iostream>
#include<fstream>
#include<map>
#include<openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
void generate_sha(string s);
void mtorrent(string s,string server,string port1,string tracker2,string port2);
void string_cal(char buffer[9999],string ip_temp);
void seeder_update(string ssh,string filename,string filepath,string client_ip,string filesize);
void store_client_info();
void change_seed_ds(string ssh,string filename,string filepath,string client_ip,string filesize);


