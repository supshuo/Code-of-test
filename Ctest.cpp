#if !defined(CPP9_H)                    
#define  CPP9_H               
#include <fstream> using namespace std;                     //对文件操作 文件输入输出
#include <stdlib.h>                      //标准库头文件 定义杂项函数及内存分配函数
#include <stdio.h>                       //定义输入输出函数
#include <string.h>                      //字符串处理
#include <iostream> using namespace std;                      //数据输入输出

#define ASK(p) { do {p = new Student;     if (p == NULL)  	{cout << "memory fail!" << endl; exit(-1);}}while(0);};                   //宏定义

static struct shorts {                        //静态结构体声明 定义变量
	char name[16];
	double ave;
}sm[10]={{" ",0}};                           //给静态结构体变量赋初值
static struct bads  {                        // 静态结构体声明  定义变量
	char no[10];                           //定义学生总数
	char name[16];                         //定义学生姓名
	int math;                               //定义数学成绩
	int chi;                                 //定义语文成绩
	double ave;                             //定义平均成绩
}bad[10]={{" "," ",0,0}};                        //给静态结构体变量赋初值

class Student                               //定义一个学生类
{
  private:                                  //定义私有成员
    char no[10];                            
	char name[16];
	int math;
	int chi;
	double ave;
	Student *next;                          //定义对象指针
	int menu_select(void);                   //声明菜单选择函数
  public:                                   //定义公有成员
    static int count;                         //定义了一个静态对象

    Student();                              //构造函数的声明
	~Student();                           //析构函数的声明
	Student *input(Student *);                  //输入信息函数的声明
	void display(Student *);                     //显示数据信息函数的声明
	void save(Student *);                      //文件存储操作函数的声明
	Student *load(Student *);                   //文件读取操作函数的声明
	void handle_menu(Student *);                //菜单处理函数的声明
	Student *delete_record(Student *);           //删除学生信息函数的声明
	void short_record(Student *);                //建立简明文件的声明
	 Student *bad_record(Student *top);         //建立不及格文件的声明
	 void Student::find_record(Student *);       //查询学生信息文件的声明

	 friend ostream &operator <<( ostream &os, Student &ob); //重载"<<"运算符函数声明
     friend istream &operator >>( istream &is, Student &ob);//重载">>"运算符函数声明
};

#endif
Source Files
Cpp9.cpp
#include "cpp9.h"
int Student::count=0;						//声明静态成员记录计数变量
/***************************************
*构造函数
***************************************/
Student::Student()                       //定义构造函数
{
	next=NULL;
	name[0]='0';
	no[0]=' ';
math=0;
chi=0;
ave=0.0;
}
/***************************************
*析构函数
***************************************/
Student::~Student()                        //定义析构函数
{
	if (next !=NULL)
			delete next;                  
}                                       //缺省析构函数体为空
void main()                               //定义主函数
{
	Student   *top;                      //定义对象指针
    ASK(top);
    top->handle_menu(top);
}
/***********************************
*菜单处理函数
***********************************/
void Student::handle_menu(Student *top)     //定义菜单处理函数
{
	for ( ; ; )                               //相当于while（1）语句（死循环）
	{
      switch(menu_select())
	  {
	     case 1:
			top = input(top);                  //调用输入信息函数
			break;
       	 case 2:
			display(top);                   //调用显示数据信息函数
			break;
	     case 3:
			save(top);                    //调用文件存储操作函数
			break;
	     case 4:
			top=load(top);               //调用文件读取操作函数
			break;
	     case 5:	
			top=delete_record(top);         //调用删除学生信息数据函数
			break;
	     case 6:
			short_record(top);             //调用生成简明文件函数
			break;
	     case 7:
			top=bad_record(top);             //调用查询学生信息函数
			break;
	     case 8:
			find_record(top);
			break;
	     case 9:
			cout<<"\t退出操作，再见！"<<endl;
			delete top;
			return;                        //退出函数
	  }
	}
}
/***********************************
*菜单选择函数
***********************************/
int Student::menu_select()          //定义菜单选择函数
{
	char s[2];
	int cn=0;
	cout<<'\n'
		<<"\t1,增加原始记录\n"
		<<"\t2,显示各种文件\n"
		<<"\t3,保存原始文件\n"
		<<"\t4,读取原始文件\n"	
		<<"\t5,删除原始记录\n"
		<<"\t6,建立简明文件\n"
		<<"\t7,均不及格文件\n"	
		<<"\t8,寻找原始记录\n"	
		<<"\t9,结束程序运行\n"
		<<"\n\t左边数字对应功能选择，请选择1~9:"<<flush;
    for( ; ; )
	{
      gets(s);             //从键盘接受字符串，并放入数组s中
      cn=atoi(s);
      if(cn<1||cn>9) cout<<"\n\t输入错误，重选1- 9："<<flush;
      else  break;
	}
    return cn;            //退出函数
}	
Save_load.cpp

#include "cpp9.h"

/*******************

* 文件存储操作函数

*******************/
void Student::save(Student *top)               //定义文件存储操作函数
{
  if(top->name[0]=='0')          //如果指针指向对象的name等于0，那么就直接退出函数
  {
       cout<<"\t没有记录可存!"<<endl;
       return;                        //退出函数
  }
  ofstream out;                       //建立输出流对象
  out.open("stud.dat",ios::out);   //与stud.dat关联并制定以输出方式打开
  if (!out)                       //如果文件不能打开
  {
       cout<<"\t不能打开文件!"<<endl;
       exit(1);                    //非正常退出
  }

  cout<<"\n\t存文件"<<endl;
  out<<top->count<<'\n';         //重载"<<"运算符
  Student *p=top;               //定义对象指针
  while(p!=NULL)                //当p不为空时
  {
     out<< *p;                 //重载"<<"运算符
     p=p->next;               //对象访问成员
  }
  out.close();                  //关闭文件
  cout<<'\t'<<top->count<<"条记录已经存入文件，请继续操作。"<<endl;
}

/*******************

* 文件读取操作函数

*******************/

Student *Student::load(Student *top)            //定义文件读取操作函数
{
   ifstream in;                               //建立输入流对象
   in.open("stud.dat",ios::in|ios::nocreate);//与stud.dat关联并制定以输入方式打开/如果文件不存在，则打开文件失败

   if(!in)   //如果打开文件失败
   {
        cout<<"\t文件不存在!"<<endl;
        return top;
   }
   cout<<"\n\t取文件..."<<endl;
 
   in>>top->count;
   in.ignore();
   Student *p=top;
   Student *old;
   for(int i=0;i<top->count;i++)
   {
       in>>*p;
       ASK(p->next);
       old=p;
       p=p->next;
       in.ignore();
   }
    old->next=NULL;
    in.close();                                  //关闭文件
    cout<<"\t取入"<<top->count<<"条记录."<<endl;
    return(top);                                //退出函数
}
/*******************

* 重载>>运算符函数

*******************/

istream & operator >>(istream &is,Student &ob) //重载">>"运算符函数声明
{
   is.getline(ob.no,10,'\n');    //使其能够读入字符串中的空格
   is.getline(ob.name,16,'\n');  //使其能够读入字符串中的空格
   is>>ob.math;
   is>>ob.chi;
   is>>ob.ave;
   return is;                             //退出函数
}
/*******************

* 重载<<运算符函数

*******************/

ostream & operator<<(ostream &os,Student &ob)  //重载"<<"运算符函数声明
{
  os<<ob.no<<'\n';
  os<<ob.name<<'\n';
  os<<ob.math<<'\n';
  os<<ob.chi<<'\n';
  os<<ob.ave<<'\n';
  return os;                               //退出函数
}
Input_disp.cpp
#include"cpp9.h"

/******************

 * 输入信息函数

 ******************/

Student *Student::input(Student *top)            //定义输入信息函数
{
	ifstream in;                               //建立输入流对象
	in.open("sname",ios::in|ios::nocreate); //与sname关联并制定以输入方式打开/如果文件不存在，则打开文件失败

	if(!in)                     //判断是否已有文件
	{
		cout<<"\t还没有建文件，退出时别忘记存文件。"<<endl;
	}
	else
	{
		in.close();                                  //关闭文件
		if(top->count==0)  //如果指针指向对象的count等于0，那么就直接退出函数     
		{
		        
			cout<<"\t请稍候，取已有文件..."<<endl;
			top=load(top);                         //函数调用
		}
	}

    Student *old,*star;                              //定义对象指针
	ASK(star);                                     //重新初始化
	old=top;                                       //对象指针访问对象


	while(old->next!=NULL)
	{
		old=old->next;
	}
	cout<<"\t输入数据，输入0时结束。"<<endl;


	--top->count;
	do
	{
	      ++top->count;
          cout<<"\t学号:"<<flush;
	      gets(star->no);                            //从键盘接受学号
	      if(strcmp(star->no,"0")==0)                  //比较字符串
		  break;
	      cout<<"\t名字:"<<flush;
	      gets(star->name);                         //从键盘接受名字
              cout<<"\t数学:"<<flush;
	      cin>>star->math;                          //输入数学成绩
              cout<<"\t语文:"<<flush;
	      cin>>star->chi;                             //输入语文成绩
     
		  star->ave=(star->chi+star->math)/2;           //计算平均成绩
	      if(top->count==0) top=star;
	      old->next=star;
	      old=star;
          ASK(star);
	}while(1);

    old->next=NULL;
	return(top);                                       //退出函数
}

/**********************

 * 显示数据信息的函数

 **********************/

void Student::display(Student *top)                       //定义显示数据信息函数
{
	char choose[2];//,input[30];
    int cn=0;
	cout<<"\t选择要看到的文件类型"<<endl;
	cout<<"\t1.原文件"<<endl;
	cout<<"\t2.简明文件"<<endl;
    cout<<"\t3.均不及格文件"<<endl;
    cout<<"\t4.输出高于或等于平均成绩的学生名单"<<flush;
    cout<<"\t请选择1-4:"<<flush;
	
	gets(choose) ;                      //从键盘接受字符串
	while(1)
	{
		cn=atoi(choose);
		if(cn<1||cn>4)
		{
                    cout<<"\t输入错误，重选1-4："<<flush;
                    gets(choose);             //从键盘接受字符串
		}
		else break;
	}
	switch(cn)
	{  
	   case 1:                          //显示原始数据
		{
		    if(top->count==0)
		    {
			cout<<"\n\t现在没有记录!"<<endl;
			return;
		    }
		    Student*p=top;
		    cout<<"\n\t现在共有如下"<<count<<"条记录:\n";
            cout<<"\t学号\t名字\t数学\t语文\t平均\n";
		    while(p!=NULL)               //当p为非空时
		    {
			cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'
                         <<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n'; //输出原始数据
			p=p->next;
		    }
		    cout<<endl;
		    break;
		}
	   case 2:                         //显示简明文件                         
       {
		    ifstream in;                 //建立输入流对象
            in.open("stud_mean.dat",ios::in|ios::nocreate);//与stud_mean.dat关联并制定以输入方式打开/如果文件不存在，则打开文件失败
            		     
	         if(!in)                         //判断是否已有文件
		    {
			cout<<"\t文件不存在!"<<endl;
			return;                             //退出函数                   
		    }
		    cout<<"\n\t取文件..."<<endl;
		    in.read((char*)sm,sizeof sm);
		    in.close();                     //关闭文件
		    cout<<"\t名字\t平均成绩\n";
		    for(int i=0;i<10;i++)//,p=p->next)
		    {
			if(sm[i].ave==0) break;
			cout<<'\t'<<sm[i].name<<'\t'<<sm[i].ave<<endl;
		    }
		    break;
		}
	   case 3:                            //显示均不及格文件
		{
		    ifstream in;                      //建立输入流对象   
		    in.open("bad.dat",ios::in|ios::nocreate);//与bad.dat关联并制定以输入方式打开/如果文件不存在，则打开文件失败

            if(!in)                           //判断是否已有文件
		    {
			cout<<"\t文件不存在！"<<endl;
			return;                           //退出函数
		    }
		    cout<<"\n\t取文件..."<<endl;
		    in.read((char*)bad,sizeof bad);	   
            in.close();                         //关闭文件

            cout<<"\t学号\t名字\t数学\t语文\t平均\n";

		    for(int i=0;i<10;i++)
			{
		     if(bad[i].ave==0) break;
		     cout<<'\t'<<bad[i].no<<'\t'<<bad[i].name
                        <<'\t'<<bad[i].math<<'\t'<<bad[i].chi
                        <<'\t'<<bad[i].ave<<endl;            //输出简明文件
			}
		    break;
		}
       case 4:                  //显示高于或等于平均分的学生信息
		{
	      if(top->count==0)
		  {
		    cout<<"\n\t现在没有记录!"<<endl;
		    return;                              //退出函数
		  }
	      Student *p=top;                          //定义对象指针访问对象
	      cout<<"\n\t现在共有如下"<<count<<"条记录:\n";    //计算平均成绩
	      int num=0;
	      double mean=0;
	      while(p!=NULL)                         //当p为非空时
		  {
		     ++num;             //记载符合条件的学生人数
		     mean+=p->ave;   //计算平均分之和
		     p=p->next;
		  }
                mean=mean/num;       //计算全部学生的平均分
		  cout<<"\t平均成绩为:"<<mean<<"分"<<endl;
          cout<<"\t其中高于或等于平均成绩的学生信息如下:\n";
          cout<<"\t学号\t名字\t数学\t语文\t平均\n";
		  p=top;
          while(p!=NULL)                  //当p为非空时
		  {
			  if(p->ave>=mean)
			  {
                  cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'
                  <<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n';//输出高于或等于平均分的学生信息

			  }
              p=p->next;
		  }
	      cout<<endl;
			break;
		}
	}
}
Short_record.cpp
#include "cpp9.h"      
/*******************

* 生成简明函数文件

********************/

void Student::short_record(Student *top)         //定义简明文件函数
{
	Student *p;
	p=top;
	if(p->count==0)
	{
		cout<<"\t内存中没有可用记录"<<endl;
		return;
	}
	for(int i=0;i<p->count;i++,p=p->next)
	{
		strcpy(sm[i].name,p->name);
		sm[i].ave=p->ave;
	}
	ofstream out;                              //建立输出流对象
	out.open("stud_mean.dat",ios::out);
	if(!out)                                    //如果文件不能打开
	{
		cout<<"\t不能打开文件！"<<endl;
		return;
	}
	cout<<"\n\t存文件"<<endl;
	out.write((char *)sm,sizeof  sm);
	out.close();                               // 打开文件
	cout<<'\t'<<top->count<<"条记录已经存入文件，内容如下："<<endl;
	cout<<"\t名字\t平均成绩\n";
	for(i=0;i<p->count;i++)
			cout<<"\t"<<sm[i].name<<"\t"<<sm[i].ave<<endl;
}
Bad.cpp
#include"cpp9.h"   
/*********************************

* 生成均不及格的学生文件的处理函数

**********************************/
Student *Student::bad_record(Student *top)   //定义均不及格的学生文件处理函数
{
     int cb=0;
     Student *old,*star;
     old=star=top;
     if(top->count==0)
     {
	  cout<<"\t内存中没有可用记录"<<endl;
	  return  top;
     }
     for (int i=0;star!=NULL;i++)
     {
	                                   //取出均不及格学生的信息
	   if((star->math<60)&&(star->chi<60))
	   {
		strcpy(bad[cb].no,star->no);
		strcpy(bad[cb].name,star->name);
		bad[cb].math=star->math;
		bad[cb].chi=star->chi;
	    bad[cb].ave=star->ave;

	    if(top==star) top=star->next;
	    else old->next=star->next;
	    star=star->next;


	     ++cb;
	     --count;
	   }
	   else
	   {
	    old=star;
	    star=star->next;
	   }
	 }

	cout<<"\n\t两科均不及格的学生信息如下："<<endl;
	cout<<"\t学号\t名字\t数学\t语文\t平均\n";           //输出两科均不及格的学生信息

	for( i=0;i<cb;i++)
	{
		if(bad[i].ave==0) break;
		   cout<<'\t'<<bad[i].no<<'\t'<<bad[i].name<<'\t'
                       <<bad[i].math<<'\t'<<bad[i].chi<<'\t'<<bad[i].ave<<endl;
	}

	                                   //存入文件
    ofstream out;                           //建立输出流对象
	out.open("bad.dat",ios::out);
	if(!out)                            //如果文件不能打开
	{
		cout<<"\t不能打开文件！"<<endl;
		return top;
	}

    out.write((char *)bad,sizeof bad);
	out.close();                               //打开文件
	cout<<"\n\t文件存储成功"<<endl;

	if(count==0)                    //说明链表已空，需要重新初始化
	{
		ASK(top);            //重新初始化
		cout<<"\t原文件在内存中的记录已经删空"<<endl;
	}
	return top;
}
Find.cpp
#include "cpp9.h"
/********************** 
查找学生信息函数
***********************/
void  Student::find_record(Student  *top)  //定义查找学生信息函数
{
	char  choose[2],input[30];
	int  cn=0;
	cout<<"\t1.通过学号寻找"<<endl;             
	cout<<"\t2.通过名字寻找"<<endl;
	cout<<"\t请选择1-2："<<flush;
	gets(choose);                          //从键盘接受字符串
	while(1)
	{
		cn=atoi(choose);
			if(cn!=1&&cn!=2)
			{
				cout<<"\t输入错误，重选1-2:"<<flush;
				gets(choose);               //从键盘接受字符串
			}
			else  break;
	}
	switch(cn)
	{
	 case  1:
			cout<<"\t请输入学号："<<flush;           //输入学号
			break;
	 case  2:
		cout<<"\t请输入名字："<<flush;              //输入名字
	}
	gets(input);


	Student  *p;
	p=top;
	while(p!=NULL)                                //当P为非空时
	{
		if((cn==1&&strcmp(input,p->no)==0)||(cn==2&&strcmp(input,p->name)==0))
		{
			cout<<"\t找到的信息如下："<<endl;

			cout<<"\t学号\t名字\t数学\t语文\t平均\n";
			cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'<<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n';
			return;
		}
		else 
		{
			p=p->next;
		}
	}
	cout<<"\t没有找到相应的记录。"<<endl;
	return;
}
Delete_record.cpp
#include "cpp9.h"
/**************************
删除学生信息处理函数
***************************/
Student *Student::delete_record(Student  *top)  //定义删除学生信息处理声明
{
	char  choose[2],input[30];
	int cn  =0;
	cout<<"1.通过学号"<<endl;
	cout<<"2.通过名字"<<endl;
	cout<<"请输入学号:"<<flush;

	gets(choose);                          //从键盘接受字符串
	while(1)
	{
		cn=atoi(choose);
		if(cn!=1&&cn!=2)
		{
			cout<<"请输入错误，重选1-2："<<flush;
			gets(choose);
		}
		else break;
	}
	switch(cn)
	{
	 case  1:
		cout<<"请输入学号:"<<flush;                     //输入学号
		break;
	 case  2:
		cout<<"请输入名字:"<<flush;                     //输入名字
	}
	gets(input);
	Student  *old,*star;
	old=star=top;
	while(star!=NULL)
	{
		if((cn==1&&strcmp(input,star->no)==0)||(cn==2&&strcmp(input,star->no)==0))
		{
			if(star==top)
				top=star->next;
			else
				old->next=star->next;
			cout<<"被删除记录的信息如下："<<endl;
			cout<<"学号\t名字\t数学\t语文\t平均\n";
			cout<<star->no<<'\t'<<star->name<<'\t'<<star->math<<'\t'<<star->chi<<'\t'<<star->ave<<'\n';

			--count;
			cout<<"当选择保存记录之后，才能确认删除。"<<endl;
			if(cout==0)
				{
				ASK(top);                              //重新初始化
			cout<<"记录已经删空"<<endl;
			return  top;
		}
		return  top;
	}
	else
	{
		old=star;
		star=star->next;
	}
}
cout<<"没有找到相应的记录。"<<endl;
return top;
}


