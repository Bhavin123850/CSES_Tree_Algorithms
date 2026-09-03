#include<bits/stdc++.h>
using namespace std;
int dfs(int node,vector<int>adj[],vector<int>&dp)
{
    int count = 0;
    for(auto neighbors : adj[node])
    {
        count += dfs(neighbors,adj,dp);
    }
    dp[node] = count;
    return count+1;
}
int main()
{
    int n;
    cin>>n;
    vector<int>v(n-1);
    vector<int>adj[n+1];
    for(int i = 0;i<n-1;i++)
    {
        cin>>v[i];
        adj[v[i]].push_back(i+2);
    }
    vector<int>dp(n+1,-1);
    dfs(1,adj,dp);
    for(int i = 1;i<=n;i++)
    {
        cout<<dp[i]<<" ";
    }
    cout<<"\n";
    return 0;
}