
#include <iostream>
#include<time.h> 
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
 
/* 构造完成标志 */
bool sign = false;
int cycle;
time_t t = time(NULL);
/* 创建数独矩阵 */
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
 
/* 函数声明 */
bool isNum(string str);
void initdata();
void Output();
bool Check(int n, int key);
int Recursion(int n);
 
/* 主函数 */
int main(int argc,char *argv[])
{   
	string N;int n,m;bool input=true;
	if(argc!=3)
		cout<<"参数个数错误:"<<endl;
	else
	{
		if(strcmp(argv[1],"-c")==0)
		{
			if(isNum(argv[2]))
			   {m=atoi(argv[2]);
			   if(m>0)
                     {     input=false;
			               cout<<"成功输出到sudoku.txt文件中"<<endl;
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
				   cout<<"请输入大于0的数字:";
			         }
			    }
			else
			{cout<<"请输入数字，不要包含别的字符:"<<endl;input=true;}
		}
		else
		{   input=true;
			cout<<"第二个参数应该是-c:"<<endl;

		}

	}
	
	while(input)
	{
    cout << "请输入N:" ;
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
	cout<<"运行成功:"<<endl;
    system("pause");
	}
	else
	{
		cout<<"请输入数字！,请重新输入:"<<endl;
		input=true;
		system("pause");
	}

	}
}
 
/* 读入数独矩阵 */
void initdata()
{    
    srand(t);
	t++;//生成随机数的种子  
    int a[9]={NULL};//初始化数组  
    int n=0;  
    while(n<9){  
        int m=rand()%9+1;  
        bool flag=0;  
        for(int j=0;j<n+1;j++){  
            if(a[j]==m){  
                flag=1;//如果之前保存的数中出现了和m相同的数，就把flag标记为1并跳出循环，表示需要重新生成随机数m  
                break;  
            }  
        }  
        if(flag==0){  
            a[n]=m;//如果flag是0，表示前n个数中没有和m相同的数，因此可以把第n+1个元素赋值为m  
            n++;  
        }  
    }

        for (int j = 0; j < 9; j++)
        {
            num[0][j]=a[j];
          
        }
		
    
}
 
/* 输出数独矩阵 */
void Output()
{

	ofstream ofile;               //定义输出文件
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
 
/* 判断key填入n时是否满足条件 */
bool Check(int n, int key)
{
    /* 判断n所在横列是否合法 */
    for (int i = 0; i < 9; i++)
    {
        /* j为n竖坐标 */
        int j = n / 9;
        if (num[j][i] == key) return false;
    }
    
    /* 判断n所在竖列是否合法 */
    for (int i = 0; i < 9; i++)
    {
        /* j为n横坐标 */
        int j = n % 9;
        if (num[i][j] == key) return false;
    }
    
    /* x为n所在的小九宫格左顶点竖坐标 */
    int x = n / 9 / 3 * 3;
    
    /* y为n所在的小九宫格左顶点横坐标 */
    int y = n % 9 / 3 * 3;
    
    /* 判断n所在的小九宫格是否合法 */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (num[i][j] == key) return false;
        }
    }
    
    /* 全部合法，返回正确 */
    return true;
}
 
/* 深搜构造数独 */
int Recursion(int n)
{
    /* 所有的都符合，退出递归 */
    if (n > 80)
    {
        sign = true;
        return 0;
    }
    /* 当前位不为空时跳过 */
    if (num[n/9][n%9] != 0)
    {
        Recursion(n+1);
    }
    else
    {
        /* 否则对当前位进行枚举测试 */
        for (int i = 1; i <= 9; i++)
        {
            /* 满足条件时填入数字 */
            if (Check(n, i) == true)
            {
                num[n/9][n%9] = i;
                /* 继续搜索 */
                Recursion(n+1);
                /* 返回时如果构造成功，则直接退出 */
                if (sign == true) return 0;
                /* 如果构造不成功，还原当前位 */
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