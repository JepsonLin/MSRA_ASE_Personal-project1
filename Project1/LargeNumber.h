#define MYSTYLE 0
class LargeNumber{
private:
	char *m_phLargeNumber;
	unsigned long long m_ullsize;
	bool bsign;
public:
	LargeNumber(char *phlNumber, unsigned long long size, bool sign);
	LargeNumber();
	~LargeNumber();
	void CreateLargeNumber(int i);
	void ShowLargeNumber();
	LargeNumber operator+ (const LargeNumber &LargeNumber1)const;
	LargeNumber operator- (LargeNumber &LargeNumber1)const;
	LargeNumber operator* (const LargeNumber &LargeNumber1)const;
	LargeNumber operator/ (const LargeNumber &LargeNumber1)const;
	void Destroy()
	{
		delete []m_phLargeNumber;
		m_ullsize = 0;
		bsign = 0;
	}
	//void LargeNumberSubstract(long long *& pllLargeNumber1, long long *& pllLargeNumber2, long long *pllLargeNumberResult);
	//void LargeNumberMutiply(long long *& pllLargeNumber1, long long *& pllLargeNumber2, long long *pllLargeNumberProduct);
	//void LargeNumberDivide(long long *& pllLargeNumber1, long long *& pllLargeNumber2, long long *pllLargeNumberQuotient, long long *pllLargeNumberRemainder);
};