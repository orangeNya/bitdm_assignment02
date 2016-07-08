#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void freComputer(int database[][10], int count, int rule[][15], int frequ[], int rcount, int length)
{
	for(int i = 0; i < rcount; i++)
	{
		for(int j = 0; j < count; j++)
		{
			int flag = 1;
			for(int k = 0; k < length; k++)
			{
				if(!database[j][rule[i][k]])
				{
					flag = 0;
					break;
				}
			}
			if(flag)
			{
				frequ[i] = frequ[i] + 1;
			}
		}
	}
}
void link1(int a[], int b[], int length,int cc[])
{
	int i, j, k = 0;
	for( i = 0, j = 0;  i < length && j < length;)
	{
		if(a[i] < b[j])
		{
			cc[k] = a[i];
			i = i + 1;
			k = k + 1;
		}
		else
		{
			if(a[i] > b[j])
			{
				cc[k] = b[j];
				j = j + 1;
				k = k + 1;
			}
			else
			{
				cc[k] = a[i];
				i = i + 1;
				j = j + 1;
				k = k + 1;
			}
		}
	}
	if(i == length && j < length)
	{
		cc[k] = b[j];
	}
	if(i < length && j == length)
	{
		cc[k] = a[i];
	}
}
int joint(int rule[200][15], int rcount, int length, int res[200][15])
{
	int count = 0; 
	for(int i = 0; i < rcount - 1; i++)
	{
		for(int j = i + 1; j < rcount; j++)
		{
			int flag = 0;
			for(int k = 0; k < length; k++)
			{
				for(int t = 0; t < length; t++)
				{
					if(rule[i][k] == rule[j][t])
					{
						flag = flag + 1;
						break;
					}
				}
			}
			if(flag == length - 1)
			{
				int temp[15];
				link1(rule[i], rule[j], length, temp);
				if(count == 0)
				{
					for(int k = 0; k <= length; k++)
					{
						res[count][k] = temp[k];
					}
					count = count + 1;
				}
				else
				{
					int flagN = 1;
					for(int k =0; k < count; k++)
					{
						int t;
						for(t = 0; t <= length; t++)
						{
							if(temp[t] != res[k][t])
								break;
						}
						if(t > length)
						{
							flagN = 0;
							break;
						}
					}
					if(flagN)
					{
						for(int k = 0; k <= length; k++)
						{
							res[count][k] = temp[k];
						}
						count = count + 1;
					}
				}
			}
		}
	}
	return count;
}
int main()
{
	int database[200][10] = {0}, count, freq[15][200] = {0}, freItem[15][200][15], freCount[15], minS;
	float minSupport = 0.2;
	ifstream in("D:\\processed.txt");
	int i = 0;
	while (!in.eof())
	{
		int tem[8];
		for(int j = 0; j < 8;j++)
		{
			in>>tem[j];
		}
		for(int j = 0; j < 8;j++)
		{
			if(tem[j])
			{
				database[i][tem[j]] = 1;
			}
		}
		i = i + 1;
	}
	count = i - 1;
	minS = count * minSupport;

	int rule1[200][15], freq1[200] = {0};
	for(int t = 0; t < 9; t++)
	{
		rule1[t][0] = t + 1;
	}
	freComputer(database, count, rule1, freq1, 9, 1);
	int count1 = 0;
	for(int i = 0; i < 9; i++)
	{
		if(freq1[i] >= minS)
		{
			freItem[1][count1][0] = rule1[i][0];
			freq[1][count1] = freq1[i];
			count1++;
		}
	}
	freCount[1] = count1;

	int rule2[200][15], freq2[200] = {0}, temp2;
	temp2 = joint(freItem[1], freCount[1], 1, rule2);
	freComputer(database, count, rule2, freq2, temp2, 2);
	int count2 = 0;
	for(int i = 0; i < temp2; i++)
	{
		if(freq2[i] >= minS)
		{
			for(int j = 0; j < 2; j++)
			{
				freItem[2][count2][j] = rule2[i][j];
			}
			freq[2][count2] = freq2[i];
			count2++;
		}
	}
	freCount[2] = count2; 
	int itemNum = 3;
	while(1)
	{
		int ruleTemp[200][15], freqTemp[200] = {0}, count_temp;
		count_temp = joint(freItem[itemNum - 1], freCount[itemNum - 1], itemNum - 1, ruleTemp);
		freComputer(database, count, ruleTemp, freqTemp, count_temp, itemNum);
		int countI = 0;
		for(int i = 0; i < count_temp; i++)
		{
			if(freqTemp[i] >= minS)
			{
				for(int j = 0; j < itemNum; j++)
				{
					freItem[itemNum][countI][j] = ruleTemp[i][j];
				}
				freq[itemNum][countI] = freqTemp[i];
				countI++;
			}
		}
		freCount[itemNum] = countI; 
		if(freCount[itemNum] <= 1)
		{
			break;
		}
		else
			itemNum++;
	}
	
	//for(int i = 1; i < itemNum; i++)
	//{
	//	for(int j = 0; j < freCount[i];j++)
	//	{
	//		printf("The set of most frequent term: ");
	//		for(int k = 0; k < i; k++)
	//		{
	//			printf("%d ",freItem[i][j][k]);
	//		}
	//		printf("  frequency: %d\n", freq[i][j]);
	//	}
	//}

	for(int i = 2; i < itemNum; i++)
	{
		for(int j = 0; j < freCount[i];j++)
		{
			if(freItem[i][j][i-1] == 8 ||freItem[i][j][i-1] == 9){
				float supp, conf, countTemp[2];
				int tem[15], k;
				countTemp[0] = freq[i][j];
				for(k = 0; k < i - 1; k++)
				{
					tem[k] = freItem[i][j][k];
				}
				for(int k1 = 0; k1 < freCount[i-1];k1++)
				{
					int k2, flag = 1;
					for(k2 = 0; k2 < i - 1; k2++)
					{
						if(tem[k2] != freItem[i-1][k1][k2])
						{
							flag = 0;
							break;
						}
					}
					if(flag)
					{
						countTemp[1] = freq[i-1][k1];
						break;
					}
				}
				supp = countTemp[0] / 120;
				conf = countTemp[0] / countTemp[1];
				if(conf>=0.8){
					for(k = 0; k < i - 1; k++)
					{
						if(k == 0)
						{
							printf("%d", freItem[i][j][k]);
						}
						else
						{
							printf("¡Ä%d", freItem[i][j][k]);
						}
					}
					printf("->%d",freItem[i][j][k]);
					printf(":   ");
					printf("%.f¡Â120 = %.3f;   ",countTemp[0], supp);
					printf("%.f¡Â%.f = %.3f",countTemp[0], countTemp[1], conf);
					if(freItem[i][j][i - 1]== 8)
					{
						printf(";   %.3f¡Â0.492=%.3f", conf, conf/0.492);
					}
					if(freItem[i][j][i - 1]== 9)
					{
						printf(";   %.3f¡Â0.417=%.3f", conf, conf/0.417);
					}
					printf("\n");
				}
			}
		}
	}
	system("pause");
	return 0;
}