#include <iostream>
#include <fstream>
#include <string>
#include "math.h"
//#typedef long long Large
using namespace std;
#define MAX_LENGTH1 4
#define true 1
#define false 0

struct DataNode
{
	char *phData;
	unsigned long ulsize;
	DataNode *pDataNode;
};



bool CreateandWriteLargeNumbertoFile(unsigned long long N)
{
	ofstream fout("data.txt");
	fout.clear();
	char c;
	if (fout.is_open())
	{

		for (long long i = 0; i < N; i++)
		{
			c = rand() % 10 + '0';
			fout << c;
		}
		fout << '$';
		fout.close();
		return true;
	}
	else
	{
		return false;
	}

}

bool ReadLargeNumberfromFile(DataNode *&pDatNode,unsigned long long &ullsize)
{
	ifstream fin("data.txt");
	if (!fin.is_open())
	{
		cout << "Error opening file";
		return false;
	}
	else
	{
		long l=-1;
		char c;
		DataNode *pDNode1, *pDNode;
		pDNode1= pDatNode;
		pDatNode -> ulsize = 0;
		while (!fin.eof())
		{
			fin >> c;
			l++;
			if (c != '$')
			{
				pDNode1->ulsize = 2 << l;
				pDNode1->phData = new char[pDNode1->ulsize];
				pDNode1->phData[0] = c;
				ullsize++;
			}
			else
			{
				pDNode1->pDataNode = NULL;
				fin.close();
				return true;
			}
			for (unsigned long lg = 1; lg < pDNode1->ulsize; lg++)
			{
				if (!fin.eof())
				{
					fin >> c;
					if (c != '$')
					{
						pDNode1->phData[lg] = c;
						ullsize++;
					}
					else
					{
						pDNode1->pDataNode = NULL;
						fin.close();
						return true;
					}
				}
				else
				{
					pDNode1->pDataNode = NULL;
					fin.close();
					return true;
				}

			}
			pDNode = pDNode1;
			pDNode1 = new DataNode;
			pDNode->pDataNode = pDNode1;
		}
		pDNode1->pDataNode = NULL;
		fin.close();
		return true;
	}
}

void Convert2Array(DataNode *pDatNode, unsigned long long &ullsize, char *&phLargeNumber)
{
	DataNode *pDNode1 , *pDNode ;
	unsigned long long i = ullsize,k=0;
	pDNode = pDatNode;
	pDNode1 = pDatNode->pDataNode;
	while (pDNode1)
	{
		for (unsigned long j = 0; j < pDNode->ulsize; j++)
		{
			phLargeNumber[(i--)-1] = pDNode->phData[j]-'0';
			k++;
		}
		free(pDNode);
		pDNode = pDNode1;
		pDNode1 = pDNode->pDataNode;
	}
	for (unsigned long j = 0; k < ullsize ; j++)
	{
		phLargeNumber[(i--)-1] = pDNode->phData[j]-'0';
		k++;
	}
	if (phLargeNumber[ullsize - 1] == 0) ullsize--;
}