#include "LargeNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include "DataIO.h"
#include "OtherDefinition.h"
using namespace std;

LargeNumber::LargeNumber()
{

}

LargeNumber::LargeNumber(char *phlNumber, unsigned long long size, bool sign)
{
	m_phLargeNumber = phlNumber;
	m_ullsize = size;
	bsign = sign;
}
LargeNumber::~LargeNumber()
{

}

void LargeNumber::CreateLargeNumber(int i)
{
	if (i == 1)
	{
		cout << "Input Large Number:" << endl;
		char* s=new char[100000000];
		cin >> s;
		this->m_ullsize = strlen(s);
		this->m_phLargeNumber = new char[this->m_ullsize];
		if (s[0] == '-')
		{
			for (unsigned long long j = 1; j < this->m_ullsize; j++)
			{
				this->m_phLargeNumber[j-1] = s[this->m_ullsize-j] - '0';
			}
			bsign = 1;
			this->m_ullsize--;
		}
		else
		{
			for (unsigned long long j = 0; j < this->m_ullsize; j++)
			{
				this->m_phLargeNumber[j] = s[this->m_ullsize-1 - j] - '0';
			}
			bsign = 0;
		}
	}
	else
	{
		cout << "1:positive,2:negative :";
		char c;
		cin >> c;
		if (c == '1')
		{
			bsign = 0;
		}
		else
		{
			bsign = 1;
		}
		cout << "enter #digits:";
		unsigned long long N;
		cin >> N;
		if (!CreateandWriteLargeNumbertoFile(N)){
			cout << "Error writing data to file!" << endl;
			exit(1);
		}

		DataNode *pHeader = new DataNode;
		m_ullsize = 0;
		if (!ReadLargeNumberfromFile(pHeader, m_ullsize)){
			cout << "Error reading data from file!" << endl;
			exit(1);
		}
		m_phLargeNumber = new char[m_ullsize];
		Convert2Array(pHeader, m_ullsize, m_phLargeNumber);
	}



}

void LargeNumber::ShowLargeNumber()
{
	if (this->m_phLargeNumber == NULL)
	{
		cout << "NULL Number!" << endl;
	}
	else
	{
		if (bsign)
			cout << '-';
		if (m_ullsize > 1)
		{
			if (m_phLargeNumber[m_ullsize - 1] != 0)
				cout << (char)(m_phLargeNumber[m_ullsize - 1] + '0');
			for (unsigned long long i = m_ullsize - 1; i > 0; i--)
				cout << (char)(m_phLargeNumber[i - 1] + '0');
		}
		else
			cout << (char)(m_phLargeNumber[0] + '0');
	}
}

LargeNumber LargeNumber::operator+ (const LargeNumber &LargeNumber1)const
{
	unsigned long long size,size1;
	bool sign;
	char *phLagNumber;
	if (this->bsign == LargeNumber1.bsign)
	{
		sign = this->bsign;
		size1 = this->m_ullsize <=  LargeNumber1.m_ullsize ? this->m_ullsize : LargeNumber1.m_ullsize ;
		if (size1 == this->m_ullsize && size1 > 0 )
		{
			phLagNumber = new char[LargeNumber1.m_ullsize+1];
			phLagNumber[0] = this->m_phLargeNumber[0] + LargeNumber1.m_phLargeNumber[0];
			for (unsigned long long i = 1; i < size1; i++)
			{
				phLagNumber[i] = this->m_phLargeNumber[i] + LargeNumber1.m_phLargeNumber[i] + phLagNumber[i - 1] / 10;
				phLagNumber[i - 1] %= 10;
			}
			if (phLagNumber[size1 - 1]>9)
			{
				if (size1 == LargeNumber1.m_ullsize)
				{
					phLagNumber[size1] = 1;
					phLagNumber[size1 - 1] %= 10;
				}
				else
				{
					phLagNumber[size1] = 1 + LargeNumber1.m_phLargeNumber[size1];
					phLagNumber[size1 - 1] %= 10;
					for (unsigned long long i = size1+1; i < LargeNumber1.m_ullsize; i++)
					{
						phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] + phLagNumber[i - 1] / 10;
						phLagNumber[i - 1] %= 10;
					}
					if (phLagNumber[LargeNumber1.m_ullsize - 1]>9)
					{
						phLagNumber[LargeNumber1.m_ullsize] = 1;
						phLagNumber[LargeNumber1.m_ullsize - 1] %= 10;
						size = LargeNumber1.m_ullsize + 1;
					}
					else
					{
						size = LargeNumber1.m_ullsize;
					}
				}
		
			}
			else 
			{
				for (unsigned long long i = size1 ; i < LargeNumber1.m_ullsize; i++)
				{
					phLagNumber[i] = LargeNumber1.m_phLargeNumber[i];
				}
				size = LargeNumber1.m_ullsize;
			}
		}
		else if (size1 == LargeNumber1.m_ullsize && size1 > 0)
		{
			phLagNumber = new char[this->m_ullsize + 1];
			phLagNumber[0] = LargeNumber1.m_phLargeNumber[0] + this->m_phLargeNumber[0];
			for (unsigned long long i = 1; i < size1; i++)
			{
				phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] + this->m_phLargeNumber[i] + phLagNumber[i - 1] / 10;
				phLagNumber[i - 1] %= 10;
			}
			if (phLagNumber[size1 - 1]>9)
			{
				if (size1 == this->m_ullsize)
				{
					phLagNumber[size1] = 1;
					phLagNumber[size1 - 1] %= 10;
				}
				else
				{
					phLagNumber[size1] = 1 + this->m_phLargeNumber[size1];
					phLagNumber[size1 - 1] %= 10;
					for (unsigned long long i = size1 + 1; i < this->m_ullsize; i++)
					{
						phLagNumber[i] = this->m_phLargeNumber[i] + phLagNumber[i - 1] / 10;
						phLagNumber[i - 1] %= 10;
					}
					if (phLagNumber[this->m_ullsize - 1]>9)
					{
						phLagNumber[this->m_ullsize] = 1;
						phLagNumber[this->m_ullsize - 1] %= 10;
						size = this->m_ullsize + 1;
					}
					else
					{
						size = this->m_ullsize;
					}
				}

			}
			else
			{
				for (unsigned long long i = size1; i < this->m_ullsize; i++)
				{
					phLagNumber[i] = this->m_phLargeNumber[i];
				}
				size = this->m_ullsize;
			}
		}
		else if (size1 == 0 && size1 == this->m_ullsize)
		{
			phLagNumber = new char[LargeNumber1.m_ullsize];
			for (unsigned long long i = size1; i < LargeNumber1.m_ullsize; i++)
			{
				phLagNumber[i] = LargeNumber1.m_phLargeNumber[i];
			}
			size = LargeNumber1.m_ullsize;
		}
		else 
		{
			phLagNumber = new char[this->m_ullsize];
			for (unsigned long long i = size1; i < this->m_ullsize; i++)
			{
				phLagNumber[i] = this->m_phLargeNumber[i];
			}
			size = this->m_ullsize;
		}

	}
	else 
	{
		bool borrow = 0;
		if (this->m_ullsize > LargeNumber1.m_ullsize)
		{
			borrow = 0;
			sign = this->bsign;
			size = this->m_ullsize;
			size1 = LargeNumber1.m_ullsize;
			phLagNumber = new char[size];
			if (size1 > 0)
			{
				if (this->m_phLargeNumber[0] >= LargeNumber1.m_phLargeNumber[0])
				{
					phLagNumber[0] = this->m_phLargeNumber[0] - LargeNumber1.m_phLargeNumber[0];
					borrow = 0;
				}
				else
				{
					phLagNumber[0] = this->m_phLargeNumber[0] - LargeNumber1.m_phLargeNumber[0] + 10;
					borrow = 1;
				}

				if (size1 > 1)
				{
					for (unsigned long long i = 1; i < size1 ; i++)
					{
						if (this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow) >= 0)
						{
							phLagNumber[i] = this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow);
							borrow = 0;
						}
						else
						{
							phLagNumber[i] = this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow)+10;
							borrow = 1;
						}
					}
				}
			}
			
			
			if (this->m_phLargeNumber[size1] - (int)(borrow) > 0)
			{
				phLagNumber[size1] = this->m_phLargeNumber[size1] - (int)(borrow);
				for (unsigned long long i = size1+1; i < size; i++)
				{
					phLagNumber[i] = this->m_phLargeNumber[i];
				}
			}
			else
			{
				phLagNumber[size1] = 0;
				if (size==size1 + 1)
				{
					size--;
				}
				else
				{
					for (unsigned long long i = size1 + 1; i < size; i++)
					{
						phLagNumber[i] = this->m_phLargeNumber[i];
					}
				}
			}

		}
		else if (this->m_ullsize < LargeNumber1.m_ullsize)
		{
			borrow = 0;
			sign = LargeNumber1.bsign;
			size = LargeNumber1.m_ullsize;
			size1 = this->m_ullsize;
			phLagNumber = new char[size];
			if (size1 > 0)
			{
				if (LargeNumber1.m_phLargeNumber[0] >= this->m_phLargeNumber[0])
				{
					phLagNumber[0] = LargeNumber1.m_phLargeNumber[0] - this->m_phLargeNumber[0];
					borrow = 0;
				}
				else
				{
					phLagNumber[0] = LargeNumber1.m_phLargeNumber[0] - this->m_phLargeNumber[0] + 10;
					borrow = 1;
				}

				if (size1 > 1)
				{
					for (unsigned long long i = 1; i < size1; i++)
					{
						if (LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow) >= 0)
						{
							phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow);
							borrow = 0;
						}
						else
						{
							phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow)+10;
							borrow = 1;
						}
					}
				}
			}


			if (LargeNumber1.m_phLargeNumber[size1] - (int)(borrow) > 0)
			{
				phLagNumber[size1] = LargeNumber1.m_phLargeNumber[size1] - (int)(borrow);
				for (unsigned long long i = size1 + 1; i < size; i++)
				{
					phLagNumber[i] = LargeNumber1.m_phLargeNumber[i];
				}
			}
			else
			{
				phLagNumber[size1] = 0;
				if (size == size1 + 1)
				{
					size--;
				}
				else
				{
					for (unsigned long long i = size1 + 1; i < size; i++)
					{
						phLagNumber[i] = LargeNumber1.m_phLargeNumber[i];
					}
				}
			}
		}
		else
		{
			sign = this->bsign;
			size = this->m_ullsize;
			for (unsigned long long i = m_ullsize; i > 0; i--)
			{
				if (this->m_phLargeNumber[i-1] == LargeNumber1.m_phLargeNumber[i-1])
				{
					size--;
				}
				else
				{
					if (this->m_phLargeNumber[i - 1] < LargeNumber1.m_phLargeNumber[i - 1])
					{
						sign = LargeNumber1.bsign;
					}
					break;
				}
			}
			
			if (sign == this->bsign && size > 0 )
			{
				phLagNumber = new char[size];
				if (this->m_phLargeNumber[0] >= LargeNumber1.m_phLargeNumber[0])
				{
					phLagNumber[0] = this->m_phLargeNumber[0] - LargeNumber1.m_phLargeNumber[0];
					borrow = 0;
				}
				else
				{
					phLagNumber[0] = this->m_phLargeNumber[0] - LargeNumber1.m_phLargeNumber[0] + 10;
					borrow = 1;
				}

				for (unsigned long long i = 1; i < size - 1; i++)
				{
					if (this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow) >= 0)
					{
						phLagNumber[i] = this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow);
						borrow = 0;
					}
					else
					{
						phLagNumber[i] = this->m_phLargeNumber[i] - LargeNumber1.m_phLargeNumber[i] - (int)(borrow)+10;
						borrow = 1;
					}
				}
				if (this->m_phLargeNumber[size - 1] - (int)(borrow) - LargeNumber1.m_phLargeNumber[size-1] > 0)
				{
					phLagNumber[size - 1] = this->m_phLargeNumber[size - 1] - (int)(borrow)-LargeNumber1.m_phLargeNumber[size - 1];
				}
				else
				{
					size--;
				}
			}
			else if (sign == LargeNumber1.bsign && size > 0)
			{
				phLagNumber = new char[size];
				if (LargeNumber1.m_phLargeNumber[0] >= this->m_phLargeNumber[0])
				{
					phLagNumber[0] = LargeNumber1.m_phLargeNumber[0] - this->m_phLargeNumber[0];
					borrow = 0;
				}
				else
				{
					phLagNumber[0] = LargeNumber1.m_phLargeNumber[0] - this->m_phLargeNumber[0] + 10;
					borrow = 1;
				}

				for (unsigned long long i = 1; i < size - 1; i++)
				{
					if (LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow) >= 0)
					{
						phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow);
						borrow = 0;
					}
					else
					{
						phLagNumber[i] = LargeNumber1.m_phLargeNumber[i] - this->m_phLargeNumber[i] - (int)(borrow)+10;
						borrow = 1;
					}
				}
				if (LargeNumber1.m_phLargeNumber[size - 1] - (int)(borrow)-this->m_phLargeNumber[size - 1] > 0)
				{
					phLagNumber[size - 1] = LargeNumber1.m_phLargeNumber[size - 1] - (int)(borrow)-this->m_phLargeNumber[size - 1];
				}
				else
				{
					size--;
				}
			}
			else
			{
				if (this->m_ullsize > 0)
				{
					phLagNumber=new char[1];
					size = 1;
					phLagNumber[0] = 0;
					sign = 0;
				}
				else
				{
					phLagNumber = NULL;
					size = 0;
					sign = 0;
				}
			}
		}
	}
	return LargeNumber(phLagNumber, size, sign);
}

LargeNumber LargeNumber::operator- (LargeNumber &LargeNumber1)const
{
	LargeNumber1.bsign = 1 - int(LargeNumber1.bsign);
	LargeNumber temp;
	temp=*this + LargeNumber1;
	LargeNumber1.bsign = 1 - int(LargeNumber1.bsign);
	return temp;
}

LargeNumber LargeNumber::operator * (const LargeNumber &LargeNumber1)const
{

	unsigned long long len, i,l1,l2;
	
	l1 = 2 * this->m_ullsize;
	l2 = 2 * LargeNumber1.m_ullsize;
	len = 1;
	while (len<l1 || len<l2) len <<= 1;
	
	complex *C1 = new complex[len];
	complex *C2 = new complex[len];
	int *S = new int[len];
	for (i = 0; i < len; i++)
	{
		C1[i].re = C1[i].im = 0.0;
		C2[i].re = C2[i].im = 0.0;
		S[i] = 0;
	}
	
	//convert to complex
	for (i = 0; i<this->m_ullsize; i++)
	{
		C1[i].re = this->m_phLargeNumber[i]; C1[i].im = 0.0;
	}
	for (; i<this->m_ullsize; i++)  
	{
		C1[i].re = C1[i].im = 0.0;
	}
	for (i = 0; i<LargeNumber1.m_ullsize; i++)
	{
		C2[i].re = LargeNumber1.m_phLargeNumber[i]; C2[i].im = 0.0;
	}
	for (; i<LargeNumber1.m_ullsize; i++)  
	{
		C2[i].re = C2[i].im = 0.0;
	}
	
	//FFT
	FFT(C1, len, 1);
	FFT(C2, len, 1);
	
	//dot product
	for (i = 0; i<len; i++)
		C1[i] = C1[i] * C2[i];
	
	//IFFT
	FFT(C1, len, -1);
	
	
	for (i = 0; i<len; i++)
		S[i] = int(C1[i].re + 0.5);
	free(C1);
	free(C2);
	
	for (i = 0; i<len; i++)     
	{
		S[i + 1] += S[i] / 10;
		S[i] %= 10;
	}
	
	len = this->m_ullsize + LargeNumber1.m_ullsize - 1;
	while (S[len] <= 0 && len>0)len--;

	char *phLN = new char[len+1];
	
	for (i = 0; i < len+1; i++)   
		phLN[i] = char(S[i]);

	free(S);

	unsigned long long size = len+1;
	
	bool sign = this->bsign^LargeNumber1.bsign;
	
	return LargeNumber(phLN, size, sign);
}

LargeNumber LargeNumber::operator/ (const LargeNumber &LargeNumber1)const
{
	unsigned long long i, len1, len2, nTimes,sizeTemp,size;
	long long Temp;
	bool sign;
	char *phQuotient,*phRemainder;
	len1 = this->m_ullsize;
	len2 = LargeNumber1.m_ullsize;
	if (len1 < len2)
	{
		size = 1;
		phQuotient = new char[size];
		phQuotient[0] = 0;
		sign = 0;
	}
	else
	{
		nTimes = len1 - len2;
		phQuotient = new char[len1 - len2 + 2];
		char *S = new char[len1];
		for (i = 0; i<len1 - len2 + 2; i++)
		{
			phQuotient[i] = 0;
		}
		for (i = 0; i<len1; i++)
		{
			S[i] = this->m_phLargeNumber[i];
		}
		char *phTemp = new char[len1];
		if (nTimes>0)
		{
			for (i = len1 - 1; i >= nTimes; --i)
				phTemp[i] = LargeNumber1.m_phLargeNumber[i - nTimes];
			for (i = nTimes; i >= 1; --i)
				phTemp[i-1] = 0;   
			sizeTemp = len1;
			for (i = 0; i < nTimes+1; i++)
			{
				Temp = Substract(S, phTemp + i, len1, sizeTemp - i);
				while (Temp >= 0)
				{
					len1 = Temp;
					++phQuotient[nTimes - i];
					Temp = Substract(S, phTemp + i, len1, sizeTemp - i);
				}
			}
			if (phQuotient[nTimes] == 0) size = nTimes ;
			else
				size = nTimes+1;
			sign = 0;
#if 1-MYSTYLE
			cout << "qoutient:" << endl;
			Show(phQuotient,size);
			cout << endl;
			cout << "remainder:" << endl;
			Show(S, len1);
#endif
		}
		else
		{
			for (i = len1 ; i >= 1; i--)
			{
				if (this->m_phLargeNumber[i-1] > LargeNumber1.m_phLargeNumber[i-1])
				{
					phQuotient[0] = 1;
					size = 1;
#if 1-MYSTYLE
					for (unsigned long long j = 0; j < i; j++)
					{
						S[j] -= LargeNumber1.m_phLargeNumber[j];
							if (S[j] < 0)
							{
								S[j] += 10;
								S[j + 1]--;
							}
					}
					cout << "qoutient:" << endl;
					Show(phQuotient, size);
					cout << endl;
					cout << "remainder:" << endl;
					Show(S, i);
#endif
					break;
				}
				if (this->m_phLargeNumber[i-1] < LargeNumber1.m_phLargeNumber[i-1])
				{
					phQuotient[0] = 0;
					size = 1;
#if 1-MYSTYLE
					cout << "qoutient:" << endl;
					Show(phQuotient, size);
					cout << endl;
					cout << "remainder:" << endl;
					Show(m_phLargeNumber, this->m_ullsize);
#endif
					break;
				}
			}
			if (i == 0)
			{
				phQuotient[0] = 1;
				size = 1;
			}
		}
		if (!this->bsign)
		{
			sign = LargeNumber1.bsign;
		}
		else
		{
			sign = 1-LargeNumber1.bsign;
			phQuotient[0]++;
			for (i = 0; i < size-1; i++)
			{
				if (phQuotient[i]>9)
				{
					phQuotient[i] -= 10;
					phQuotient[i + 1]++;
				}
			}
			if (phQuotient[size - 1] > 9)
			{
				phQuotient[size-1] -= 10;
				phQuotient[size] = 1;
				size++;
			}
		}
	}
	if (sign == 1 && !phQuotient[0])
	{
		sign = 0;
	}
	return LargeNumber(phQuotient, size, sign);
}