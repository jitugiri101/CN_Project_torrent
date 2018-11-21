#include<stdio.h>
#include<iostream>
#include<stdlib>
#include<fstream>
#include<string>
#include<string.h>

void seeder_update(string ssh,string filename,string filesize,string client_ip)
{
fstream seeder;
seeder.open("seeder.txt");
seeder<<ssh;
seeder<";";
seeder<<filename;
seeder<<";"
seeder<<filepath;
seeder<<";";
seeder<<filesize;
seeder<<";";
seeder<<client_ip;
seeder<<";";
seeder<<"\n";
}

