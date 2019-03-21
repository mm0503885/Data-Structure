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
    int first=0; //�}�l���H���s��
    int tag=0;  //�C�ӤH���s��
    node *head;
    node *last;
    bool node1=true;  //�O�_���Ĥ@��node

    while(fin.get(a))  //�p��}�l���H���s��
    {
      if(a=='\n') break;
      else first=first*10+(a-'0');
    }

    while(fin.get(a))
    {
       if(a=='-') //��̫�@�ӤH����Ĥ@�ӤH �Φ�circular
       {
          last->Rlink=head;
          head->Llink=last;
          break;
       }
       else if(a==' ') //���ͷs��node
       {
         if(node1)  //�Ĥ@�ӤH
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
       else  //�p��s��
       {
         int i=a-'0';
         tag=10*tag+i;;
       }

    }

    node *start=head;
    while(start->number!=first) //��start���V�}�l���H
    {
        start=start->Rlink;
    }


    while(fin.get(a)) //���L�t��
    {
      if(a!='\n') continue;
      else break;
    }

    node *current=start;
    bool direction=0;  //0�����ɰw 1���f�ɰw
    while(fin.get(a))
    {
        if(a=='\n') continue;

        else
        {  if(!direction)
             current->word.push_back(a);
           else
             current->word.push_front(a);
           if(fin.peek()=='\n') //�@�ӦrŪ�� �L�X�骺�H ��Ldelete��
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
    //�̫�Ѩ�ӤH�Acurrent���쪺�OĹ�a�A�ҥH���L���䨺�ӤH
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
