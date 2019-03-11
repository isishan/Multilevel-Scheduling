#include<bits/stdc++.h>
#include<queue>
using namespace std;
struct process
	{	
		int pid, priority, burst;
	};

struct process pro[100];
bool cmp(process p1, process p2)
	{
		if(p1.priority!=p2.priority)
		return p1.priority>p2.priority;
	}
struct process find (int pid,int p)
{
	for(int i=1; i<=p; i++)
	{
		if(pro[i].pid==pid)
		{
			return pro[i];
		}
	}
}
int main()
{
	
	
	queue <int> q1;
	queue <int> q2;
	queue <int> q3;
	cout<<"\nHow many processes do you want to enter ?\t";
	int p;
	cin>>p;
	
	for(int i=1; i<=p; i++)
	{
		pro[i].pid=100+i;
//		cout<<"\n  \tPRIORITY  \tBURST TIME";
		cout<<"\nP"<<i<<"\t";
		cin>>pro[i].priority;
		cout<<"\t";
		cin>>pro[i].burst;
//		if(pro[i].priority>0 && pro[i].priority<=3)
//			q1.push(pro[i].pid);
//		else if(pro[i].priority>4 && pro[i].priority<=6)
//			q2.push(pro[i].pid);
//		else if(pro[i].priority>7 && pro[i].priority<=9)
//			q3.push(pro[i].pid);
	}
	
	
	sort(pro+1, pro+p+1,cmp);
	for(int i=0; i<p; i++)
	{
		if(pro[i].priority>0 && pro[i].priority<=3)
			q1.push(pro[i].pid);
		else if(pro[i].priority>4 && pro[i].priority<=6)
			q2.push(pro[i].pid);
		else if(pro[i].priority>7 && pro[i].priority<=9)
			q3.push(pro[i].pid);
	}
	cout<<"\nPRESS ANY BUTTON TO START PROCESS EXECUTION AND E TO EXIT\t";
//	system("stty raw"); 
//	char input=getchar();
//	system("stty cooked");
//	//sleep(2);
//	cout<<endl<<input;
	int ch;
	cin>>ch;
	if(ch=='E'||ch=='e')
	exit(0);
	int t=10, present=1, t1=4,curr;
	while(t>0)
	{
		t=10;
		if(present==1)
		{
			t1=4;
			curr=q1.top();
			currpro=find(curr,p);
			while(t1<0 && t<10)
			{
				currpro.burst--;
				t1--;
				t--;
			}
		}
		else if(present==2)
		{
			curr=q2.top();
			currpro=find(curr,p);
			while(flag)
		}
	}
}
