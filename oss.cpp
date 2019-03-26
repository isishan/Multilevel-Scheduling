#include<iostream>
#include<iomanip>
#include<algorithm>
#include<queue>
using namespace std;
struct process
	{	
		int pid, priority, burst, burst2, at, start, end, wt, tat;
	};
int ttime=0;
int p;
struct process pro[100];

struct process find (int pid)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==pid)
		{
			return pro[i];
		}
	}
}

void enterprocess(int p)
{
	for(int i=0; i<p; i++)
	{
		cout<<"\nFor process P"<<i+1;
		pro[i].pid=100+(i+1);
		re_at:
		cout<<"\nAT: ";
		cin>>pro[i].at;
		if(pro[i].at<0)
		{
			cout<<"\nArrival time cannot be negative. Please enter again";
			goto re_at;
		}
		re_pri:
		cout<<"\nPriority (1-9): ";
		cin>>pro[i].priority;
		if(pro[i].priority<1 || pro[i].priority>9)
		{
			cout<<"\nPriority has to be an integer between 1 and 9. Please enter again";
			goto re_pri;
		}
		re_burst:
		cout<<"\nBurst: ";
		cin>>pro[i].burst;
		if(pro[i].burst<1)
		{
			cout<<"\nBurst time cannot be 0 or negative. Please enter again";
			goto re_burst;
		}
		pro[i].burst2=pro[i].burst;
		pro[i].start=-1;
		pro[i].end=-1;
	}
}

queue <int> q1;
queue <int> q2;
queue <int> q3;

void showall()
{
	int avgwt=0, avgtat=0;
	cout<<endl<<setw(7)<<"    Process"<<setw(15)<<"Arrival Time"<<setw(10)<<"Priority"<<setw(15)<<"Burst Time"<<setw(10)<<"Start Time"<<setw(20)<<"Completition Time"<<setw(15)<<"Waiting Time"<<setw(20)<<"Turnaround Time";	
	for(int i=0; i<p; i++)
	{
		pro[i].wt=(pro[i].start-pro[i].at)+((pro[i].end-pro[i].start)-pro[i].burst2);
		pro[i].tat=pro[i].wt+pro[i].burst2;
		avgwt+=pro[i].wt;
		avgtat+=pro[i].tat;
		cout<<endl<<setw(7)<<"P"<<pro[i].pid-100<<setw(15)<<pro[i].at<<setw(10)<<pro[i].priority<<setw(15)<<pro[i].burst2<<setw(10)<<pro[i].start<<setw(20)<<pro[i].end<<setw(15)<<pro[i].wt<<setw(20)<<pro[i].tat;	
	}
	
	cout<<"\n\n\n\tAverage Waiting Time -->"<<(float)avgwt/p<<"\n\tAverage Turnaround Time -->"<<(float)avgtat/p;
	
}
void qload(int ttime)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].at==ttime)
		{
			if(pro[i].priority>0 && pro[i].priority<=3)
			{
				q1.push(pro[i].pid);
			}
			else if(pro[i].priority>=7 && pro[i].priority<=9)
				q3.push(pro[i].pid);
		}
	}
}



bool cmp2(int a, int b)
{
	if(find(a).priority!=find(b).priority)
	return find(a).priority<find(b).priority;
}

void qload2 (int ttime)
{
	vector <int> a;
	int flag=0;
	for(int i=0; i<p; i++)
	{
		if(pro[i].at==ttime)
		{
			if(pro[i].priority>=4 and pro[i].priority<=6)
			{
				a.push_back(pro[i].pid);
				flag=1;
			}
		}
	}
	int cnt=1;
	if(flag==1)
	{
		int x=q2.size();
		for(int j=0; j<x; j++)
		{
			a.push_back(q2.front());
			q2.pop();
			cnt++;
		}
		sort(a.begin(),a.end(), cmp2);
		for(int j=0; j<a.size(); j++)
		{
			q2.push(a[j]);
		}
	}
}


void proupdate(int b, int id)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==id)
		{
			pro[i].burst=b;
		}
	}
}

struct process currpro;

bool procheck()
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].burst!=0)
			return false;
	}
	return true;

}

void prostart(int ttime, int id)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==id)
		{
			if(pro[i].start==-1)
			pro[i].start=ttime;
			else
			pro[i].start=min(pro[i].start,ttime);
		}
	}
}

void proend(int ttime, int id)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==id)
		{
			if(pro[i].end==-1)
			pro[i].end=ttime;
			else
			pro[i].end=max(pro[i].end,ttime);
		}
	}
}

int main()
{
	int prev=0;
	re_pr:
	cout<<"\nNo of processes: ";
	cin>>p;
	if(p<1)
	{
		cout<<"No. of processes must be greater than 0. Enter again.";
		goto re_pr;
	}
	enterprocess(p);
	int flagclose=0;
	qload(ttime);
	qload2(ttime);
	int t=0;
	cout<<"\n";
	while( flagclose==0)
	{
		int t1=0;
		int curr, b;
		t=0;
		if(!q1.empty())
		{
			curr=q1.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		while(t1<4 && t<10 && q1.size()!=0)
		{
			if(q1.front()!=prev)
			{
				cout<<" <"<<ttime<<"> -P"<<q1.front()-100<<"-";
				prostart(ttime, q1.front());
			}
			prev=q1.front();
			b--;
			t++;
			t1++;
			ttime++;
			proupdate(b,q1.front());
			qload(ttime);
			qload2(ttime);
			if(t==10)
			{
				proupdate(b,q1.front());
			}
			if(t1==4 || b==0)
			{
				if(b==0)
				{
					proend(ttime, q1.front());
					q1.pop();
				}
				if(b!=0)
				{
					proupdate(b,q1.front());
					int x=q1.front();
					q1.pop();
					q1.push(x);
				}
				if(q1.size()!=0)
				{
					curr=q1.front();
					currpro=find(curr);
					b=currpro.burst;
					t1=0;
				}
				else
				t=10;
			}		
		}
		
		
		t=0;
		
		if(q2.size()!=0)
		{
			curr=q2.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		
		while(t<10 && q2.size()!=0)
		{
			curr=q2.front();
			currpro=find(curr);
			b=currpro.burst;
			if(q2.front()!=prev)
			{
				cout<<" <"<<ttime<<"> -P"<<q2.front()-100<<"-";
				prostart(ttime, q2.front());
			}
			prev=q2.front();
			b--;
			t++;
			ttime++;
			proupdate(b,q2.front());
			
			if(t==10 && b>0)
			{
				proupdate(b,q2.front());	
			}
			if(b==0)
			{
				proend(ttime, q2.front());
				q2.pop();
				qload(ttime);
				qload2(ttime);
				if(q2.size()!=0)
				{
					curr=q2.front();
					currpro=find(curr);
					b=currpro.burst;
				}
				else
					t=10;
			}
			else
			{
				qload(ttime);
				qload2(ttime);
			}
		}
		
		
		
		t=0;
		
		if(q3.size()!=0)
		{
			curr=q3.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		while(t<10 && q3.size()!=0)
		{
			if(q3.front()!=prev)
			{
				cout<<" <"<<ttime<<"> -P"<<q3.front()-100<<"-";
				prostart(ttime, q3.front());
			}
			prev=q3.front();
			b--;
			t++;
			ttime++;
			proupdate(b,q3.front());
			qload(ttime);
			qload2(ttime);
			if(t==10)
			{
				proupdate(b,q3.front());
				int x=q3.front();
			}
				if(b==0)
				{
					proend(ttime, q3.front());
					q3.pop();
					if(q3.size()!=0)
					{
						curr=q3.front();
						currpro=find(curr);
						b=currpro.burst;
						
					}
					else
					t=10;
				}
		}
		
		if(q2.size()==0 && q1.size()==0 && q3.size()==0)
		{
			if(procheck())
			{
				cout<<" <"<<ttime<<"> \n";
				flagclose=1;
			}
			else
			{
				cout<<" <"<<ttime<<">"<<" -X-";
				ttime++;
				qload(ttime);
				qload2(ttime);
			}
			
		}
	}	
	showall();
}
