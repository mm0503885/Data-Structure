#include <fstream>
#include <iostream>
using namespace std;


class node{

public:

node* Lchild;
node* Rchild;
int id;
char direction;
int change_condition;
int frequency;
node(int a =0,char b ='L',int c=0);

};

node::node(int a,char b,int c):id(a),direction(b),change_condition(c),frequency(0),Lchild(NULL),Rchild(NULL){}  //constructor


int main(int argc,char* argv[]){

    ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

    char a;
    node* root=NULL;
    node* current;
    node* pre_node;
    char  pre_node_dir;
    node* swap_current;
    node* pre_swap_current;
    bool is_root=true;

    while(fin.get(a))
    {
       if(a=='a')
       {
         for(int i=0;i<4;i++)
           fin.get(a);
         int ID=0;
         while(a!=' ')
         {
           ID=ID*10+(a-'0');
           fin.get(a);
         }
         fin.get(a);
         char DIRECTION=a;
         fin.get(a);
         fin.get(a);
         int CHANGE_CONDITION=0;
         while(a!='\n')
         {
           CHANGE_CONDITION=CHANGE_CONDITION*10+(a-'0');
           fin.get(a);
         }

         node* t=new node(ID,DIRECTION,CHANGE_CONDITION);

         if(is_root)
         {
             root=t;
             is_root=false;
         }
         else
         {
             current=root;
             while(1)
             {
                if(t->id==current->id)
                {
                   current->direction=t->direction;
                   current->change_condition=t->change_condition;
                   current->frequency=t->frequency;
                   delete t;
                   break;
                }
                else if(t->id<current->id)
                {
                  if(current->Lchild==NULL)
                  {
                    current->Lchild=t;
                    break;
                  }
                  else
                    current=current->Lchild;
                }
                else //t->id>current->id
                {
                  if(current->Rchild==NULL)
                  {
                    current->Rchild=t;
                    break;
                  }
                  else
                    current=current->Rchild;
                }
             }
         }
        }
        else if(a=='d')
        {
            fin.get(a);
            if(a=='e')
            {

              for(int i=0;i<5;i++)
              fin.get(a);
              char del_dir=a;
              fin.get(a);
              fin.get(a);
              int del_id=0;
              while(a!='\n')
              {
                del_id=del_id*10+(a-'0');
                fin.get(a);
              }
              current=root;
              while(1)
              {
                if(root==NULL)
                {
                   fout<<"Deletion failed."<<endl;
                   break;
                }
                if(current->id==del_id)
                {
                  if((current->Lchild==NULL) && (current->Rchild==NULL))
                  {
                    if(current==root)
                    {
                      root=NULL;
                      is_root=true;
                    }
                    else
                    {
                      if(pre_node_dir=='L')
                        pre_node->Lchild=NULL;
                      else
                        pre_node->Rchild=NULL;
                    }
                    delete current;
                  }
                  else  if((current->Lchild!=NULL) && (current->Rchild==NULL))
                  {
                    if(current==root)
                    {
                      root=current->Lchild;
                      delete current;
                    }
                    else
                    {
                      if(pre_node_dir=='L')
                      { pre_node->Lchild=current->Lchild; delete current;}
                      else
                      { pre_node->Rchild=current->Lchild; delete current;}
                    }
                  }
                  else  if((current->Lchild==NULL) && (current->Rchild!=NULL))
                  {
                    if(current==root)
                    {
                      root=current->Rchild;
                      delete current;
                    }
                    else
                    {
                      if(pre_node_dir=='L')
                      { pre_node->Lchild=current->Rchild; delete current;}
                      else
                      { pre_node->Rchild=current->Rchild; delete current;}
                    }
                  }
                  else //  ((current->Lchild!=NULL) && (current->Rchild!=NULL))
                  {
                     swap_current=current;
                     pre_swap_current=current;
                     if(del_dir=='L')
                     {
                       swap_current=swap_current->Lchild;
                       while(swap_current->Rchild!=NULL)
                       {
                         pre_swap_current=swap_current;
                         swap_current=swap_current->Rchild;
                       }
                       current->id=swap_current->id;
                       current->direction=swap_current->direction;
                       current->change_condition=swap_current->change_condition;
                       current->frequency=swap_current->frequency;
                       if(swap_current->Lchild==NULL)
                       {
                         pre_swap_current->Rchild=NULL;
                         delete swap_current;
                       }
                       else //(swap_current->Lchild!=NULL)
                       {

                         if(pre_swap_current==current)
                         {
                           pre_swap_current->Lchild=swap_current->Lchild;
                           delete swap_current;
                         }
                         else
                         {
                           pre_swap_current->Rchild=swap_current->Lchild;
                           delete swap_current;
                         }
                       }
                     }
                     else //del_dir=='R'
                     {
                       swap_current=swap_current->Rchild;
                       while(swap_current->Lchild!=NULL)
                       {
                         pre_swap_current=swap_current;
                         swap_current=swap_current->Lchild;
                       }
                       current->id=swap_current->id;
                       current->direction=swap_current->direction;
                       current->change_condition=swap_current->change_condition;
                       current->frequency=swap_current->frequency;
                       if(swap_current->Rchild==NULL)
                       {
                         pre_swap_current->Lchild=NULL;
                         delete swap_current;
                       }
                       else //(swap_current->Rchild!=NULL)
                       {

                         if(pre_swap_current==current)
                         {
                           pre_swap_current->Rchild=swap_current->Rchild;
                           delete swap_current;
                         }
                         else
                         {
                           pre_swap_current->Lchild=swap_current->Rchild;
                           delete swap_current;
                         }
                       }
                     }
                  }
                  break;
                }
                else if(current->id>del_id)
                  if(current->Lchild==NULL)
                  {
                    fout<<"Deletion failed."<<endl;
                    break;
                  }
                  else
                  {
                    pre_node=current;
                    pre_node_dir='L';
                    current=current->Lchild;
                  }
                else //current->id<del_id
                  if(current->Rchild==NULL)
                  {
                    fout<<"Deletion failed."<<endl;
                    break;
                  }
                  else
                  {
                    pre_node=current;
                    pre_node_dir='R';
                    current=current->Rchild;
                  }
              }
            }
            else // drop
            {
              for(int i=0;i<4;i++)
              fin.get(a);
              int counter=0;
              while(a!='\n')
              {
                counter=counter*10+(a-'0');
                fin.get(a);
              }
              for(int i=0;i<counter;i++)
              {
                 if(root==NULL)
                 {
                    fout<<"Tree is empty.";
                    break;
                 }
                 current=root;
                 while(1)
                 {
                   current->frequency+=1;
                   if(i==counter-1)
                     fout<<current->id<<' ';
                   if(current->direction=='L')
                   {
                      if(current->frequency==current->change_condition)
                      {
                         current->direction='R';
                         current->frequency=0;
                      }
                      if(current->Lchild==NULL)
                        break;
                      else
                        current=current->Lchild;
                   }
                   else //current->direction=='R'
                   {
                      if(current->frequency==current->change_condition)
                      {
                         current->direction='L';
                         current->frequency=0;
                      }
                      if(current->Rchild==NULL)
                        break;
                      else
                        current=current->Rchild;
                   }
                 }
              }
              fout<<endl;

            }


        }
    }

    fin.close();
	fout.close();

    return 0;

}
