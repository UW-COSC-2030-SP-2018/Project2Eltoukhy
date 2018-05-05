//Ahmed Eltoukhy
//Project 2 

#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <ColorDlg.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>

using namespace std;
float cc=0;
float total = 0;

unsigned long long myrandom()
{
	int arr[24];
	for (int i = 0; i < 24; i++)
	{
		arr[i] = rand() % 2;
	}
	int p = 0;
	unsigned long long ans = 0;
	for (int i = 23; i >=0; i--,p++)
	{
		ans += arr[i] * pow(2, p);
	}
	return ans;
}
unsigned long long mypower(unsigned long long var, int power, int prime)
{
	unsigned long long ans = var;
	if (power == 0)
	{
		return 1;
	}
	else if (power == 1)
	{
		return var;
	}
	else 
	{
		for (int i = 2; i <= power; i++)
		{
			ans = (ans*var) % prime;
			//cout << ans << " ";
		}
		return ans;
	}
	
}
class BitVector
{
	unsigned char *Bits;
	int n;
public:
	BitVector(double s = 728000)
	{
		int a = ceil(s / 8);
		Bits = new unsigned char[a];
		n = s;
	}
	void Set()
	{
		int a = ceil(n / 8);
		for (int i = 0; i < a; i++)
		{
			Bits[i] = 255;
		}
	}
	void NotSet()
	{
		int a = ceil(n / 8);
		for (int i = 0; i < a; i++)
		{
			Bits[i] = 0;
		}
	}
	void Set(int BitNumber, bool value)
	{
		int ByteNum = BitNumber / 8;
		int BitOffSet = BitNumber % 8;
		if (value == true)
		{
			unsigned char Mask = (128 >> BitOffSet);
			Bits[ByteNum] = Bits[ByteNum] | Mask;
		}
		else
		{
			unsigned char Mask = ~(128 >> BitOffSet);
			Bits[ByteNum] = Bits[ByteNum] & Mask;
		}
	}
	bool Get(int BitNumber)
	{
		int ByteNum = BitNumber / 8;
		int BitOffSet = BitNumber % 8;
		unsigned char Mask = (128 >> BitOffSet);
		Mask = Mask & Bits[ByteNum];
		return (Mask != 0);
	}
};
template <class t>
class Vector
{
	t*arr;
	int cap;
	int size;
public:
	Vector()
	{
		arr = nullptr;
		cap = 0; size = 0;
	}
	void push_back(const t & obj)
	{
		if (arr == nullptr)
		{
			arr = new t[256];
			cap = 256;
			size = 0;
		}
		if (size<cap)
		{
			
			arr[size] = obj;  
			size++;
		}
		else
		{
			t*temp = new t[cap * 2];
			for (int i = 0; i < cap; i++)
			{
				temp[i] = arr[i];
			}
			temp[cap] = obj;
			cap *= 2;
			size++;
			delete[]arr;
			arr = temp;
		}
	}
	void pop_back()
	{
		if (arr != NULL && size != 0)
		{
			size--;
		}
		if (size < cap / 2)
		{
			t*temp = new t[size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			cap = cap / 2;
		}
	}
	Vector(int s)
	{
		cap = s; arr = new t[cap];
		size = 0;
	}
	int getsize()
	{
		return size;
	}
	t& operator[](int index)
	{
		return arr[index];
	}
	void realloc(int s)
	{
		// delete[]arr;
		arr = new t[s];
		cap = s;
		size = 0;
	}
	Vector(const Vector <t> & obj)
	{
		delete[]arr;
		cap = 2 * obj.getsize();
		size = cap / 2;
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj.arr[i];
		}
	}
	void updatesize()
	{
		size++;
	}
	const Vector <t>& operator=(Vector<t> & obj)
	{
		for (int i = 0; i < obj.size; i++)
		{
			arr[i] = obj.arr[i];
		}
		size = obj.size;
		cap = obj.cap;
		return (*this);
	}
	~Vector()
	{
		delete[]arr; size = 0; cap = 0;
	}
	void printvector()
	{
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};
class bloomfilter
{
private:
	BitVector arr;
	int prime;
	int m;
	int b;
	unsigned long long a[6];
public:
	bloomfilter()
	{
		srand(time(0));
		m = 91000 * 8;
		b = 8;
		prime = 16777213;
		for (int i = 0; i < 6; i++)
		{
			a[i] = myrandom();
		}
		arr.NotSet();
	}
	void movestringbackwards(char arrr[], int index)
	{
	
		for (int i = index; arrr[i] != 0; i++)
		{
			arrr[i] = arrr[i + 1];
		}
		arrr[strlen(arrr)] = 0;


	}
	unsigned long long pax(char arrr[], unsigned long long aw)
	{
		int l = strlen(arrr);
		int power = l - 1;
		unsigned long long res = 0;
		for (int i = 0; arrr[i] != 0; i++,power--)
		{
			int a = arrr[i];
			res += a*mypower(aw, power, prime);
			res = res%prime;
		}
		return res;
	}
	unsigned long long modifiedpax(char arrr[], unsigned long long aw)
	{
		int count=0;
		for (int i = 0; arrr[i] != 0; i++)
		{
			if (arrr[i] >= 97 && arrr[i]<=122)
			{
				count++;
			}
		}
	//	cout << "  count " << count << endl;
	//	int l = strlen(arrr);
		int power = count - 1;
		unsigned long long res = 0;
		for (int i = 0; arrr[i] != 0; i++, power--)
		{
			int a = arrr[i];
			if (arrr[i] >= 65 && arrr[i] <= 96)
			{
				a = a + 32;
			}
			if (a >= 97 && a <= 122)
			{
				
		//	cout << "                           " << a <<"   "<<power <<endl;
				res += a*mypower(aw, power, prime);
				res = res%prime;
			}
			else
			{
				power++;
			}
		}
		return res;
	}
	int hx(unsigned long long pax)
	{
		int hx = (pax%prime) % m;
		return hx;
	}
	void readfile_fillfilter(ifstream &fin )
	{
		char c[30];
		ofstream fout;
		float count = 0;
		fin.getline(c, 30, '\n');
		c[strlen(c)] = 0;
		arr.Set(hx(pax(c, a[0])), 1);
		arr.Set(hx(pax(c, a[1])), 1);
		arr.Set(hx(pax(c, a[2])), 1);
		arr.Set(hx(pax(c, a[3])), 1);
		arr.Set(hx(pax(c, a[4])), 1);
		arr.Set(hx(pax(c, a[5])), 1);
		float x = ((count / 91000) * 100);
		int y = x;
		count++;
		while (!fin.eof())
		{
			arr.Set(hx(pax(c, a[0])), 1);
			arr.Set(hx(pax(c, a[1])), 1);
			arr.Set(hx(pax(c, a[2])), 1);
			arr.Set(hx(pax(c, a[3])), 1);
			arr.Set(hx(pax(c, a[4])), 1);
			arr.Set(hx(pax(c, a[5])), 1);
			 x = ( (count / 91000) * 100);
		//	 cout << "percentage loaded " << x;
			 y = x;
			fin.getline(c, 30, '\n');
			c[strlen(c)] = 0;
			count++;
		}
	}
	bool searchword(char arr[])
	{
		ifstream fin;
		fin.open("dict.txt");
		char read[40];
		fin.getline(read, 40, '\n');
		read[strlen(read)] = 0;
		if (strcmp(read, arr) == 0)
		{
			return 1;
		}
		bool res = 0;
		while (!fin.eof())
		{
			fin.getline(read, 40, '\n');
			read[strlen(read)] = 0;
			if (strcmp(read, arr) == 0)
			{
				res =1;
				break;
			}
		}
		return res;
	}
	void comparefile(char filename[],int line)
	{
		char c[30];
		ofstream fout;
		ifstream finn;
		finn.open(filename);
		if (finn.is_open())
		{ 
			cout << " Matching with dictionary & displaying \n";
			while (!finn.eof())
			{
				if (line == 0)
				{
					finn.getline(c, 30, ' ');
				}
				else if (line == 1)
				{
					finn.getline(c, 30, '\n');
				}
				c[strlen(c)] = 0;
				for (int i = 0; c[i] != 0; i++)
				{
					if (c[i] >= 65 && c[i] <= 96)
					{
						c[i] = c[i] + 32;
					}
				}
				for (int i = 0; c[i] != 0; i++)
				{
					if (c[i] < 97 || c[i] > 122)
					{
						movestringbackwards(c, i);
					}
				}
				if (arr.Get(hx(modifiedpax(c, a[0]))) == 1 && arr.Get(hx(modifiedpax(c, a[1]))) == 1 && arr.Get(hx(modifiedpax(c, a[2]))) == 1 && arr.Get(hx(modifiedpax(c, a[3]))) == 1 && arr.Get(hx(modifiedpax(c, a[4]))) == 1 && arr.Get(hx(modifiedpax(c, a[5]))) == 1)
				{
					//system("COLOR F");

					total++;
					bool check = 1;
					for (int k = 0; c[k] != 0; k++)
					{
						if (c[k] < 97 || c[k]>122)
						{
							check = 0;
							break;
						}
					}
						if (searchword(c) != 1)
						{
							if (check == 0)
							{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
							}
							else
							{
								cc++;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
							}
							fout << c << " ";
							cout << c << " ";
						}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
						cout << c << " ";
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
					cout << c<<" ";
					
					total++;
				}
			}
		}
		else
		{
			cout << " File doesn't exist in the directory \n";
		}
	}
};
//------------------test case for bloom filter----------------------------
int main()

{
	srand(time(0));
	ifstream fin;
	bloomfilter bf;
	cout<<"Loading Dictionary"<<endl;
	fin.open("dict.txt");
	if (fin.is_open())
	{
	      bf.readfile_fillfilter(fin);
	}

	
	cout << "\n WHITE WORDS ARE CORRECT SPELLED RED ARE MISSPELLED GREEN ARE FALSE POSITIVES  \n \n";
	int choice,line;	
	cout << "Enter 1 to compare a file with dictionary \n";
	cout << "\nEnter 2 to EXIT \n"; cin >> choice;
	char filename[15];
	while (choice != 2)
	{
		cout << "Enter 1 for a file containing 1 word per line \n 0 for file of space separated words  \n "; cin >> line;
		cout << "\n Enter filename \n";
		cin >> filename;
		
		bf.comparefile(filename,line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		float perce = (cc / total) * 100; cout << " Error percentage = " << perce << endl<<endl;
		cc = 0; total = 0;
		cout << "WHITE WORDS ARE CORRECT SPELLED RED ARE MISSPELLED GREEN ARE FALSE POSITIVES  \n";
		cout << "Enter 1 to compare a file with dictionary \n";
		cout << "Enter 2 to EXIT \n";
		cin >> choice;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

	


}
