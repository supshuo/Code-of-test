#if !defined(CPP9_H)                    
#define  CPP9_H               
#include <fstream> using namespace std;                     //���ļ����� �ļ��������
#include <stdlib.h>                      //��׼��ͷ�ļ� ������������ڴ���亯��
#include <stdio.h>                       //���������������
#include <string.h>                      //�ַ�������
#include <iostream> using namespace std;                      //�����������

#define ASK(p) { do {p = new Student;     if (p == NULL)  	{cout << "memory fail!" << endl; exit(-1);}}while(0);};                   //�궨��

static struct shorts {                        //��̬�ṹ������ �������
	char name[16];
	double ave;
}sm[10]={{" ",0}};                           //����̬�ṹ���������ֵ
static struct bads  {                        // ��̬�ṹ������  �������
	char no[10];                           //����ѧ������
	char name[16];                         //����ѧ������
	int math;                               //������ѧ�ɼ�
	int chi;                                 //�������ĳɼ�
	double ave;                             //����ƽ���ɼ�
}bad[10]={{" "," ",0,0}};                        //����̬�ṹ���������ֵ

class Student                               //����һ��ѧ����
{
  private:                                  //����˽�г�Ա
    char no[10];                            
	char name[16];
	int math;
	int chi;
	double ave;
	Student *next;                          //�������ָ��
	int menu_select(void);                   //�����˵�ѡ����
  public:                                   //���幫�г�Ա
    static int count;                         //������һ����̬����

    Student();                              //���캯��������
	~Student();                           //��������������
	Student *input(Student *);                  //������Ϣ����������
	void display(Student *);                     //��ʾ������Ϣ����������
	void save(Student *);                      //�ļ��洢��������������
	Student *load(Student *);                   //�ļ���ȡ��������������
	void handle_menu(Student *);                //�˵�������������
	Student *delete_record(Student *);           //ɾ��ѧ����Ϣ����������
	void short_record(Student *);                //���������ļ�������
	 Student *bad_record(Student *top);         //�����������ļ�������
	 void Student::find_record(Student *);       //��ѯѧ����Ϣ�ļ�������

	 friend ostream &operator <<( ostream &os, Student &ob); //����"<<"�������������
     friend istream &operator >>( istream &is, Student &ob);//����">>"�������������
};

#endif
Source Files
Cpp9.cpp
#include "cpp9.h"
int Student::count=0;						//������̬��Ա��¼��������
/***************************************
*���캯��
***************************************/
Student::Student()                       //���幹�캯��
{
	next=NULL;
	name[0]='0';
	no[0]=' ';
math=0;
chi=0;
ave=0.0;
}
/***************************************
*��������
***************************************/
Student::~Student()                        //������������
{
	if (next !=NULL)
			delete next;                  
}                                       //ȱʡ����������Ϊ��
void main()                               //����������
{
	Student   *top;                      //�������ָ��
    ASK(top);
    top->handle_menu(top);
}
/***********************************
*�˵�������
***********************************/
void Student::handle_menu(Student *top)     //����˵�������
{
	for ( ; ; )                               //�൱��while��1����䣨��ѭ����
	{
      switch(menu_select())
	  {
	     case 1:
			top = input(top);                  //����������Ϣ����
			break;
       	 case 2:
			display(top);                   //������ʾ������Ϣ����
			break;
	     case 3:
			save(top);                    //�����ļ��洢��������
			break;
	     case 4:
			top=load(top);               //�����ļ���ȡ��������
			break;
	     case 5:	
			top=delete_record(top);         //����ɾ��ѧ����Ϣ���ݺ���
			break;
	     case 6:
			short_record(top);             //�������ɼ����ļ�����
			break;
	     case 7:
			top=bad_record(top);             //���ò�ѯѧ����Ϣ����
			break;
	     case 8:
			find_record(top);
			break;
	     case 9:
			cout<<"\t�˳��������ټ���"<<endl;
			delete top;
			return;                        //�˳�����
	  }
	}
}
/***********************************
*�˵�ѡ����
***********************************/
int Student::menu_select()          //����˵�ѡ����
{
	char s[2];
	int cn=0;
	cout<<'\n'
		<<"\t1,����ԭʼ��¼\n"
		<<"\t2,��ʾ�����ļ�\n"
		<<"\t3,����ԭʼ�ļ�\n"
		<<"\t4,��ȡԭʼ�ļ�\n"	
		<<"\t5,ɾ��ԭʼ��¼\n"
		<<"\t6,���������ļ�\n"
		<<"\t7,���������ļ�\n"	
		<<"\t8,Ѱ��ԭʼ��¼\n"	
		<<"\t9,������������\n"
		<<"\n\t������ֶ�Ӧ����ѡ����ѡ��1~9:"<<flush;
    for( ; ; )
	{
      gets(s);             //�Ӽ��̽����ַ���������������s��
      cn=atoi(s);
      if(cn<1||cn>9) cout<<"\n\t���������ѡ1- 9��"<<flush;
      else  break;
	}
    return cn;            //�˳�����
}	
Save_load.cpp

#include "cpp9.h"

/*******************

* �ļ��洢��������

*******************/
void Student::save(Student *top)               //�����ļ��洢��������
{
  if(top->name[0]=='0')          //���ָ��ָ������name����0����ô��ֱ���˳�����
  {
       cout<<"\tû�м�¼�ɴ�!"<<endl;
       return;                        //�˳�����
  }
  ofstream out;                       //�������������
  out.open("stud.dat",ios::out);   //��stud.dat�������ƶ��������ʽ��
  if (!out)                       //����ļ����ܴ�
  {
       cout<<"\t���ܴ��ļ�!"<<endl;
       exit(1);                    //�������˳�
  }

  cout<<"\n\t���ļ�"<<endl;
  out<<top->count<<'\n';         //����"<<"�����
  Student *p=top;               //�������ָ��
  while(p!=NULL)                //��p��Ϊ��ʱ
  {
     out<< *p;                 //����"<<"�����
     p=p->next;               //������ʳ�Ա
  }
  out.close();                  //�ر��ļ�
  cout<<'\t'<<top->count<<"����¼�Ѿ������ļ��������������"<<endl;
}

/*******************

* �ļ���ȡ��������

*******************/

Student *Student::load(Student *top)            //�����ļ���ȡ��������
{
   ifstream in;                               //��������������
   in.open("stud.dat",ios::in|ios::nocreate);//��stud.dat�������ƶ������뷽ʽ��/����ļ������ڣ�����ļ�ʧ��

   if(!in)   //������ļ�ʧ��
   {
        cout<<"\t�ļ�������!"<<endl;
        return top;
   }
   cout<<"\n\tȡ�ļ�..."<<endl;
 
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
    in.close();                                  //�ر��ļ�
    cout<<"\tȡ��"<<top->count<<"����¼."<<endl;
    return(top);                                //�˳�����
}
/*******************

* ����>>���������

*******************/

istream & operator >>(istream &is,Student &ob) //����">>"�������������
{
   is.getline(ob.no,10,'\n');    //ʹ���ܹ������ַ����еĿո�
   is.getline(ob.name,16,'\n');  //ʹ���ܹ������ַ����еĿո�
   is>>ob.math;
   is>>ob.chi;
   is>>ob.ave;
   return is;                             //�˳�����
}
/*******************

* ����<<���������

*******************/

ostream & operator<<(ostream &os,Student &ob)  //����"<<"�������������
{
  os<<ob.no<<'\n';
  os<<ob.name<<'\n';
  os<<ob.math<<'\n';
  os<<ob.chi<<'\n';
  os<<ob.ave<<'\n';
  return os;                               //�˳�����
}
Input_disp.cpp
#include"cpp9.h"

/******************

 * ������Ϣ����

 ******************/

Student *Student::input(Student *top)            //����������Ϣ����
{
	ifstream in;                               //��������������
	in.open("sname",ios::in|ios::nocreate); //��sname�������ƶ������뷽ʽ��/����ļ������ڣ�����ļ�ʧ��

	if(!in)                     //�ж��Ƿ������ļ�
	{
		cout<<"\t��û�н��ļ����˳�ʱ�����Ǵ��ļ���"<<endl;
	}
	else
	{
		in.close();                                  //�ر��ļ�
		if(top->count==0)  //���ָ��ָ������count����0����ô��ֱ���˳�����     
		{
		        
			cout<<"\t���Ժ�ȡ�����ļ�..."<<endl;
			top=load(top);                         //��������
		}
	}

    Student *old,*star;                              //�������ָ��
	ASK(star);                                     //���³�ʼ��
	old=top;                                       //����ָ����ʶ���


	while(old->next!=NULL)
	{
		old=old->next;
	}
	cout<<"\t�������ݣ�����0ʱ������"<<endl;


	--top->count;
	do
	{
	      ++top->count;
          cout<<"\tѧ��:"<<flush;
	      gets(star->no);                            //�Ӽ��̽���ѧ��
	      if(strcmp(star->no,"0")==0)                  //�Ƚ��ַ���
		  break;
	      cout<<"\t����:"<<flush;
	      gets(star->name);                         //�Ӽ��̽�������
              cout<<"\t��ѧ:"<<flush;
	      cin>>star->math;                          //������ѧ�ɼ�
              cout<<"\t����:"<<flush;
	      cin>>star->chi;                             //�������ĳɼ�
     
		  star->ave=(star->chi+star->math)/2;           //����ƽ���ɼ�
	      if(top->count==0) top=star;
	      old->next=star;
	      old=star;
          ASK(star);
	}while(1);

    old->next=NULL;
	return(top);                                       //�˳�����
}

/**********************

 * ��ʾ������Ϣ�ĺ���

 **********************/

void Student::display(Student *top)                       //������ʾ������Ϣ����
{
	char choose[2];//,input[30];
    int cn=0;
	cout<<"\tѡ��Ҫ�������ļ�����"<<endl;
	cout<<"\t1.ԭ�ļ�"<<endl;
	cout<<"\t2.�����ļ�"<<endl;
    cout<<"\t3.���������ļ�"<<endl;
    cout<<"\t4.������ڻ����ƽ���ɼ���ѧ������"<<flush;
    cout<<"\t��ѡ��1-4:"<<flush;
	
	gets(choose) ;                      //�Ӽ��̽����ַ���
	while(1)
	{
		cn=atoi(choose);
		if(cn<1||cn>4)
		{
                    cout<<"\t���������ѡ1-4��"<<flush;
                    gets(choose);             //�Ӽ��̽����ַ���
		}
		else break;
	}
	switch(cn)
	{  
	   case 1:                          //��ʾԭʼ����
		{
		    if(top->count==0)
		    {
			cout<<"\n\t����û�м�¼!"<<endl;
			return;
		    }
		    Student*p=top;
		    cout<<"\n\t���ڹ�������"<<count<<"����¼:\n";
            cout<<"\tѧ��\t����\t��ѧ\t����\tƽ��\n";
		    while(p!=NULL)               //��pΪ�ǿ�ʱ
		    {
			cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'
                         <<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n'; //���ԭʼ����
			p=p->next;
		    }
		    cout<<endl;
		    break;
		}
	   case 2:                         //��ʾ�����ļ�                         
       {
		    ifstream in;                 //��������������
            in.open("stud_mean.dat",ios::in|ios::nocreate);//��stud_mean.dat�������ƶ������뷽ʽ��/����ļ������ڣ�����ļ�ʧ��
            		     
	         if(!in)                         //�ж��Ƿ������ļ�
		    {
			cout<<"\t�ļ�������!"<<endl;
			return;                             //�˳�����                   
		    }
		    cout<<"\n\tȡ�ļ�..."<<endl;
		    in.read((char*)sm,sizeof sm);
		    in.close();                     //�ر��ļ�
		    cout<<"\t����\tƽ���ɼ�\n";
		    for(int i=0;i<10;i++)//,p=p->next)
		    {
			if(sm[i].ave==0) break;
			cout<<'\t'<<sm[i].name<<'\t'<<sm[i].ave<<endl;
		    }
		    break;
		}
	   case 3:                            //��ʾ���������ļ�
		{
		    ifstream in;                      //��������������   
		    in.open("bad.dat",ios::in|ios::nocreate);//��bad.dat�������ƶ������뷽ʽ��/����ļ������ڣ�����ļ�ʧ��

            if(!in)                           //�ж��Ƿ������ļ�
		    {
			cout<<"\t�ļ������ڣ�"<<endl;
			return;                           //�˳�����
		    }
		    cout<<"\n\tȡ�ļ�..."<<endl;
		    in.read((char*)bad,sizeof bad);	   
            in.close();                         //�ر��ļ�

            cout<<"\tѧ��\t����\t��ѧ\t����\tƽ��\n";

		    for(int i=0;i<10;i++)
			{
		     if(bad[i].ave==0) break;
		     cout<<'\t'<<bad[i].no<<'\t'<<bad[i].name
                        <<'\t'<<bad[i].math<<'\t'<<bad[i].chi
                        <<'\t'<<bad[i].ave<<endl;            //��������ļ�
			}
		    break;
		}
       case 4:                  //��ʾ���ڻ����ƽ���ֵ�ѧ����Ϣ
		{
	      if(top->count==0)
		  {
		    cout<<"\n\t����û�м�¼!"<<endl;
		    return;                              //�˳�����
		  }
	      Student *p=top;                          //�������ָ����ʶ���
	      cout<<"\n\t���ڹ�������"<<count<<"����¼:\n";    //����ƽ���ɼ�
	      int num=0;
	      double mean=0;
	      while(p!=NULL)                         //��pΪ�ǿ�ʱ
		  {
		     ++num;             //���ط���������ѧ������
		     mean+=p->ave;   //����ƽ����֮��
		     p=p->next;
		  }
                mean=mean/num;       //����ȫ��ѧ����ƽ����
		  cout<<"\tƽ���ɼ�Ϊ:"<<mean<<"��"<<endl;
          cout<<"\t���и��ڻ����ƽ���ɼ���ѧ����Ϣ����:\n";
          cout<<"\tѧ��\t����\t��ѧ\t����\tƽ��\n";
		  p=top;
          while(p!=NULL)                  //��pΪ�ǿ�ʱ
		  {
			  if(p->ave>=mean)
			  {
                  cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'
                  <<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n';//������ڻ����ƽ���ֵ�ѧ����Ϣ

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

* ���ɼ��������ļ�

********************/

void Student::short_record(Student *top)         //��������ļ�����
{
	Student *p;
	p=top;
	if(p->count==0)
	{
		cout<<"\t�ڴ���û�п��ü�¼"<<endl;
		return;
	}
	for(int i=0;i<p->count;i++,p=p->next)
	{
		strcpy(sm[i].name,p->name);
		sm[i].ave=p->ave;
	}
	ofstream out;                              //�������������
	out.open("stud_mean.dat",ios::out);
	if(!out)                                    //����ļ����ܴ�
	{
		cout<<"\t���ܴ��ļ���"<<endl;
		return;
	}
	cout<<"\n\t���ļ�"<<endl;
	out.write((char *)sm,sizeof  sm);
	out.close();                               // ���ļ�
	cout<<'\t'<<top->count<<"����¼�Ѿ������ļ����������£�"<<endl;
	cout<<"\t����\tƽ���ɼ�\n";
	for(i=0;i<p->count;i++)
			cout<<"\t"<<sm[i].name<<"\t"<<sm[i].ave<<endl;
}
Bad.cpp
#include"cpp9.h"   
/*********************************

* ���ɾ��������ѧ���ļ��Ĵ�����

**********************************/
Student *Student::bad_record(Student *top)   //������������ѧ���ļ�������
{
     int cb=0;
     Student *old,*star;
     old=star=top;
     if(top->count==0)
     {
	  cout<<"\t�ڴ���û�п��ü�¼"<<endl;
	  return  top;
     }
     for (int i=0;star!=NULL;i++)
     {
	                                   //ȡ����������ѧ������Ϣ
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

	cout<<"\n\t���ƾ��������ѧ����Ϣ���£�"<<endl;
	cout<<"\tѧ��\t����\t��ѧ\t����\tƽ��\n";           //������ƾ��������ѧ����Ϣ

	for( i=0;i<cb;i++)
	{
		if(bad[i].ave==0) break;
		   cout<<'\t'<<bad[i].no<<'\t'<<bad[i].name<<'\t'
                       <<bad[i].math<<'\t'<<bad[i].chi<<'\t'<<bad[i].ave<<endl;
	}

	                                   //�����ļ�
    ofstream out;                           //�������������
	out.open("bad.dat",ios::out);
	if(!out)                            //����ļ����ܴ�
	{
		cout<<"\t���ܴ��ļ���"<<endl;
		return top;
	}

    out.write((char *)bad,sizeof bad);
	out.close();                               //���ļ�
	cout<<"\n\t�ļ��洢�ɹ�"<<endl;

	if(count==0)                    //˵�������ѿգ���Ҫ���³�ʼ��
	{
		ASK(top);            //���³�ʼ��
		cout<<"\tԭ�ļ����ڴ��еļ�¼�Ѿ�ɾ��"<<endl;
	}
	return top;
}
Find.cpp
#include "cpp9.h"
/********************** 
����ѧ����Ϣ����
***********************/
void  Student::find_record(Student  *top)  //�������ѧ����Ϣ����
{
	char  choose[2],input[30];
	int  cn=0;
	cout<<"\t1.ͨ��ѧ��Ѱ��"<<endl;             
	cout<<"\t2.ͨ������Ѱ��"<<endl;
	cout<<"\t��ѡ��1-2��"<<flush;
	gets(choose);                          //�Ӽ��̽����ַ���
	while(1)
	{
		cn=atoi(choose);
			if(cn!=1&&cn!=2)
			{
				cout<<"\t���������ѡ1-2:"<<flush;
				gets(choose);               //�Ӽ��̽����ַ���
			}
			else  break;
	}
	switch(cn)
	{
	 case  1:
			cout<<"\t������ѧ�ţ�"<<flush;           //����ѧ��
			break;
	 case  2:
		cout<<"\t���������֣�"<<flush;              //��������
	}
	gets(input);


	Student  *p;
	p=top;
	while(p!=NULL)                                //��PΪ�ǿ�ʱ
	{
		if((cn==1&&strcmp(input,p->no)==0)||(cn==2&&strcmp(input,p->name)==0))
		{
			cout<<"\t�ҵ�����Ϣ���£�"<<endl;

			cout<<"\tѧ��\t����\t��ѧ\t����\tƽ��\n";
			cout<<'\t'<<p->no<<'\t'<<p->name<<'\t'<<p->math<<'\t'<<p->chi<<'\t'<<p->ave<<'\n';
			return;
		}
		else 
		{
			p=p->next;
		}
	}
	cout<<"\tû���ҵ���Ӧ�ļ�¼��"<<endl;
	return;
}
Delete_record.cpp
#include "cpp9.h"
/**************************
ɾ��ѧ����Ϣ������
***************************/
Student *Student::delete_record(Student  *top)  //����ɾ��ѧ����Ϣ��������
{
	char  choose[2],input[30];
	int cn  =0;
	cout<<"1.ͨ��ѧ��"<<endl;
	cout<<"2.ͨ������"<<endl;
	cout<<"������ѧ��:"<<flush;

	gets(choose);                          //�Ӽ��̽����ַ���
	while(1)
	{
		cn=atoi(choose);
		if(cn!=1&&cn!=2)
		{
			cout<<"�����������ѡ1-2��"<<flush;
			gets(choose);
		}
		else break;
	}
	switch(cn)
	{
	 case  1:
		cout<<"������ѧ��:"<<flush;                     //����ѧ��
		break;
	 case  2:
		cout<<"����������:"<<flush;                     //��������
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
			cout<<"��ɾ����¼����Ϣ���£�"<<endl;
			cout<<"ѧ��\t����\t��ѧ\t����\tƽ��\n";
			cout<<star->no<<'\t'<<star->name<<'\t'<<star->math<<'\t'<<star->chi<<'\t'<<star->ave<<'\n';

			--count;
			cout<<"��ѡ�񱣴��¼֮�󣬲���ȷ��ɾ����"<<endl;
			if(cout==0)
				{
				ASK(top);                              //���³�ʼ��
			cout<<"��¼�Ѿ�ɾ��"<<endl;
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
cout<<"û���ҵ���Ӧ�ļ�¼��"<<endl;
return top;
}


