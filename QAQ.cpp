#include <bits/stdc++.h>

using namespace std;

long getWays(long n, vector < long > c){
  
    long  dp[c.size()+1][n+1];
    for(int j=0;j<=c.size();j++)   
        fill_n(dp[j],n+1,0);
  
    sort(c.begin(),c.end());
     for(int j=1;j<=c.size();j++)  
     {   
         for(int i=1;i<=n;i++)
            {
                if(i<c[j-1])
                    dp[j][i]=dp[j-1][i];
                else if(i==c[j-1])
                    {
                     dp[j][i]=dp[j-1][i]+1;
                     
                    }
                else 
                    {
                     dp[j][i]=dp[j-1][i]+dp[j][i-c[j-1]];
                    	
                    }
         
            }
     }
    return dp[c.size()][n];
    // Complete this function
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++)
    {
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    long ways = getWays(n, c);
    cout<<ways<<endl;
    return 0;
}