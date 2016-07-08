#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
	ifstream in("D:\\raw.txt");
	ofstream out("D:\\processed.txt");
	if(!in || !out)
	{
		printf("Error: cannot read or write the file.\n");
		return false;
	}
	while(!in.eof())
	{
		char info[20][30];
		in>>info[0]>>info[1]>>info[2]>>info[3]>>info[4]>>info[5]>>info[6]>>info[7];
		int tem;
		tem = (info[0][0] - '0') * 10 + info[0][1] - '0'; 
		if(tem < 38)
		{
			tem = 1;
		}
		else
			tem = 2;
		out<<tem<<' ';
		for(int i = 1; i < 8; i++)
		{
			int temp;
			if(strcmp(info[i],"yes") == 0)
			{
				temp = i + 2;
				out<<temp<<' ';
			}
			else
			{
				out<<0<<' ';
			}
		}
		out<<endl;
	}
	return 0;
}