#include <fstream>
#include <iostream>
#include <list>
using namespace std;

class node{

public:

int number;
list <char> word;
node *Llink;
node *Rlink;
node(int value =0);

};

node::node(int value):number(value),Rlink(0),Llink(0){}  //constructor

int main(int argc,char* argv[]){

    ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

    char a;
    int first=0; //開始的人的編號
    int tag=0;  //每個人的編號
    node *head;
    node *last;
    bool node1=true;  //是否為第一個node

    while(fin.get(a))  //計算開始的人的編號
    {
      if(a=='\n') break;
      else first=first*10+(a-'0');
    }

    while(fin.get(a))
    {
       if(a=='-') //把最後一個人接到第一個人 形成circular
       {
          last->Rlink=head;
          head->Llink=last;
          break;
       }
       else if(a==' ') //產生新的node
       {
         if(node1)  //第一個人
         {
            last=new node(tag);
            head=last;
            node1=false;
         }
         else
         {
            node* t=new node(tag);
            last->Rlink=t;
            t->Llink=last;
            last=last->Rlink;
         }
          tag=0;
       }
       else  //計算編號
       {
         int i=a-'0';
         tag=10*tag+i;;
       }

    }

    node *start=head;
    while(start->number!=first) //把start指向開始的人
    {
        start=start->Rlink;
    }


    while(fin.get(a)) //跳過負數
    {
      if(a!='\n') continue;
      else break;
    }

    node *current=start;
    bool direction=0;  //0為順時針 1為逆時針
    while(fin.get(a))
    {
        if(a=='\n') continue;

        else
        {  if(!direction)
             current->word.push_back(a);
           else
             current->word.push_front(a);
           if(fin.peek()=='\n') //一個字讀完 印出輸的人 把他delete掉
           {
              fout<<current->number<<' ';
              for (list<char>::iterator it=current->word.begin() ; it != current->word.end(); ++it)
                fout<< *it;
              fout<<endl;
              (current->Llink)->Rlink=current->Rlink;
              (current->Rlink)->Llink=current->Llink;

               if(a!='a' && a!='e' && a!='i' && a!='o' && a!='u')
                direction=!direction;

              if(!direction)
              {
                node *x=current;
                current=current->Rlink;
                delete x;
              }
              else
              {
                node *x=current;
                current=current->Llink;
                delete x;
              }
           }
           else
           {
             if(!direction)
               current=current->Rlink;
             else
               current=current->Llink;
           }
        }
    }
    //最後剩兩個人，current指到的是贏家，所以先印旁邊那個人
    fout<<current->Llink->number<<' ';
    for (list<char>::iterator it=current->Llink->word.begin() ; it != current->Llink->word.end(); ++it)
      fout<< *it;
    fout<<endl;
    delete current->Llink;

    fout<<current->number<<' ';
    for (list<char>::iterator it=current->word.begin() ; it != current->word.end(); ++it)
      fout<< *it;
    fout<<endl;
    delete current;

    fin.close();
	fout.close();

    return 0;
}
