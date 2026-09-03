#include<bits/stdc++.h>
using namespace std;
pair<int,int> dfs(int node,int parent,vector<int>adj[])
{
    pair<int,int>ans = {0,node};
    for(auto neighbors : adj[node])
    {
        if(neighbors == parent) continue;
        auto temp = dfs(neighbors,node,adj);
        temp.first++;
        if(temp.first > ans.first)
        {
            ans = temp;
        }
    }
    return ans;
}
int main()
{
    int n;
    cin>>n;
    vector<int>adj[n+1];
    for(int i = 1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto it = dfs(1,-1,adj);
    int node = it.second;
    it = dfs(node,-1,adj);
    cout<<it.first<<"\n";
    return 0;
}