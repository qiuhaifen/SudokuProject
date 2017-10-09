
#include <iostream>
#include<time.h> 
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
 
/* ������ɱ�־ */
bool sign = false;
int cycle;
time_t t = time(NULL);
/* ������������ */
int num[9][9] = {    
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
};
 
/* �������� */
bool isNum(string str);
void initdata();
void Output();
bool Check(int n, int key);
int Recursion(int n);
 
/* ������ */
int main(int argc,char *argv[])
{   
	string N;int n,m;bool input=true;
	if(argc!=3)
		cout<<"������������:"<<endl;
	else
	{
		if(strcmp(argv[1],"-c")==0)
		{
			if(isNum(argv[2]))
			   {m=atoi(argv[2]);
			   if(m>0)
                     {     input=false;
			               cout<<"�ɹ������sudoku.txt�ļ���"<<endl;
			               for(int i=0;i<m;i++)
	                             {
                                    initdata();
                                    Recursion(0);
                                    Output();
                               	}
			         }
			   else
			        {
				   input=true;
				   cout<<"���������0������:";
			         }
			    }
			else
			{cout<<"���������֣���Ҫ��������ַ�:"<<endl;input=true;}
		}
		else
		{   input=true;
			cout<<"�ڶ�������Ӧ����-c:"<<endl;

		}

	}
	
	while(input)
	{
    cout << "������N:" ;
	cin>>N;
	if(isNum(N))
	{
    n=atoi(N.c_str());
	for(int i=0;i<n;i++)
	{
    initdata();
    Recursion(0);
    Output();
	}
	input=false;
	cout<<"���гɹ�:"<<endl;
    system("pause");
	}
	else
	{
		cout<<"���������֣�,����������:"<<endl;
		input=true;
		system("pause");
	}

	}
}
 
/* ������������ */
void initdata()
{    
    srand(t);
	t++;//���������������  
    int a[9]={NULL};//��ʼ������  
    int n=0;  
    while(n<9){  
        int m=rand()%9+1;  
        bool flag=0;  
        for(int j=0;j<n+1;j++){  
            if(a[j]==m){  
                flag=1;//���֮ǰ��������г����˺�m��ͬ�������Ͱ�flag���Ϊ1������ѭ������ʾ��Ҫ�������������m  
                break;  
            }  
        }  
        if(flag==0){  
            a[n]=m;//���flag��0����ʾǰn������û�к�m��ͬ��������˿��԰ѵ�n+1��Ԫ�ظ�ֵΪm  
            n++;  
        }  
    }

        for (int j = 0; j < 9; j++)
        {
            num[0][j]=a[j];
          
        }
		
    
}
 
/* ����������� */
void Output()
{

	ofstream ofile;               //��������ļ�
    ofile.open("\sudoku.txt",ios::app); 
    ofile<< endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
           ofile << num[i][j]<<' ';
           
        }
       ofile << endl;
       
    }
	ofile.close();
}
 
/* �ж�key����nʱ�Ƿ��������� */
bool Check(int n, int key)
{
    /* �ж�n���ں����Ƿ�Ϸ� */
    for (int i = 0; i < 9; i++)
    {
        /* jΪn������ */
        int j = n / 9;
        if (num[j][i] == key) return false;
    }
    
    /* �ж�n���������Ƿ�Ϸ� */
    for (int i = 0; i < 9; i++)
    {
        /* jΪn������ */
        int j = n % 9;
        if (num[i][j] == key) return false;
    }
    
    /* xΪn���ڵ�С�Ź����󶥵������� */
    int x = n / 9 / 3 * 3;
    
    /* yΪn���ڵ�С�Ź����󶥵������ */
    int y = n % 9 / 3 * 3;
    
    /* �ж�n���ڵ�С�Ź����Ƿ�Ϸ� */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (num[i][j] == key) return false;
        }
    }
    
    /* ȫ���Ϸ���������ȷ */
    return true;
}
 
/* ���ѹ������� */
int Recursion(int n)
{
    /* ���еĶ����ϣ��˳��ݹ� */
    if (n > 80)
    {
        sign = true;
        return 0;
    }
    /* ��ǰλ��Ϊ��ʱ���� */
    if (num[n/9][n%9] != 0)
    {
        Recursion(n+1);
    }
    else
    {
        /* ����Ե�ǰλ����ö�ٲ��� */
        for (int i = 1; i <= 9; i++)
        {
            /* ��������ʱ�������� */
            if (Check(n, i) == true)
            {
                num[n/9][n%9] = i;
                /* �������� */
                Recursion(n+1);
                /* ����ʱ�������ɹ�����ֱ���˳� */
                if (sign == true) return 0;
                /* ������첻�ɹ�����ԭ��ǰλ */
                num[n/9][n%9] = 0;
            }
        }
    }
}


bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}