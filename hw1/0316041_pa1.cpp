#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <stack>
#include <queue>
using namespace std;

int main(int argc,char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

	//start your program here

	char a;
	string s;
	deque<string> d;

	stack<deque<string> >stk;
	queue<deque<string> >q;

	while(fin.get(a))
    {
        if(a=='#')
            break;
        else if(a=='\n')
        {
            stk.push(d);
            d.clear();

        }
        else if(a==' ') continue;
        else
        {
            s=s+a;
            if(fin.peek()==' ' || fin.peek()=='\n' || fin.peek()=='\r')
            {
                d.push_front(s);
                s.clear();
            }

        }

    }
    int num1,num2;
    deque<string> d1;
    deque<string> d2;
    deque<string> d_temp;
    while(fin.get(a))
    {
       if(a=='\n') continue;
       else if(a==' ')
       {
          fin.get(a);
          num2=a-'0';
          if(num1<num2)
          {
            for(int i=1;i<num1;i++)
            {
                d_temp=stk.top();
                q.push(d_temp);
                stk.pop();
            }
            d1=stk.top();
            stk.pop();
            for(int i=num1+1;i<num2;i++)
            {
                d_temp=stk.top();
                q.push(d_temp);
                stk.pop();
            }
            d2=stk.top();
            stk.pop();
          }
          else
          {
            for(int i=1;i<num2;i++)
            {
                d_temp=stk.top();
                q.push(d_temp);
                stk.pop();
            }
            d2=stk.top();
            stk.pop();
            for(int i=num2+1;i<num1;i++)
            {
                d_temp=stk.top();
                q.push(d_temp);
                stk.pop();
            }
            d1=stk.top();
            stk.pop();
          }
          int last_flag=0;
          string s1_temp;
          string s2_temp;
          while(!d2.empty())
          {
            s1_temp=d1.front();
            s2_temp=d2.front();
            if((s1_temp[0]==s2_temp[0]) || (s1_temp[1]==s2_temp[1]))
            {
                d1.push_front(s2_temp);
                last_flag=0;

            }
            else
            {
                d1.push_back(s2_temp);
                last_flag=1;
            }
            d2.pop_front();
          }
          if(last_flag==0)
          {
             stk.push(d1);
             while(!q.empty())
             {
                 stk.push(q.front());
                 q.pop();
             }
          }
          else
          {
             while(!q.empty())
             {
                 stk.push(q.front());
                 q.pop();
             }
             stk.push(d1);
          }




       }
       else  num1=a-'0';
    }

    deque<string> d_ans;
    string s_ans;
    d_ans=stk.top();
    while(!d_ans.empty())
    {
       s_ans=d_ans.front();
       fout<<s_ans<<" ";
       d_ans.pop_front();
    }



	fin.close();
	fout.close();
	return 0;
}
