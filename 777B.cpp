#include<bits/stdc++.h>

using namespace std;
char srr[1001];
char mrr[1001];
int dp[10];
int dp2[10];
int main()
	{
		int n;
		cin>>n;
		int count1=0;
		int count2=0;
		for(int i=0;i<n;i++)
			cin>>srr[i];
		for(int i=0;i<n;i++)
			{cin>>mrr[i];dp[mrr[i]-'0']++;dp2[mrr[i]-'0']++;}
		for(int i=0;i<n;i++)
			{int j=0;
				while(srr[i]-'0'+j<10 && dp[srr[i]-'0'+j]==0)
					{j++;}
				if(srr[i]-'0'+j==10)
					count1++;
				else
					{
					dp[srr[i]-'0'+j]--;	
					}

			}
		for(int i=0;i<n;i++)
			{int j=0;
				while((srr[i]-'0'+j)<9 && dp2[srr[i]-'0'+1+j]==0)
					{j++;}
				if((srr[i]-'0'+j)==9)
					;
				else
					{count2++;

					dp2[srr[i]-'0'+j+1]--;
					
					}

			}	

		cout<<count1<<endl;
		cout<<count2<<endl;


	}