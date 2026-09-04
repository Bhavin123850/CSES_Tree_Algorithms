#include<bits/stdc++.h>
using namespace std;
const int LOG = 20;
void dfs(int node,int parent,vector<int>adj[],vector<int>&depth,vector<vector<int>>&up)
{
    up[node][0] = parent;
    for(int i = 1;i<=LOG;i++)
    {
        if(up[node][i-1] == -1)
        {
            up[node][i] = -1;
        }
        else
        {
            up[node][i] = up[up[node][i-1]][i-1];
        }
    }
    for(auto neighbors : adj[node])
    {
        depth[neighbors] = depth[node] + 1;
        dfs(neighbors,node,adj,depth,up);
    }
}
int LCA(int u,int v,vector<int>&depth,vector<vector<int>>&up)
{
    if(depth[u] < depth[v])
    {
        swap(u,v);
    }
    int diff = depth[u] - depth[v];
    for(int i = 0;i<=LOG;i++)
    {
        if(diff & (1<<i))
        {
            u = up[u][i];
        }
    }
    if(u == v) return u;
    for(int j = LOG;j>=0;j--)
    {
        if(up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}
int main()
{
    int n,q;
    cin>>n>>q;
    vector<int>adj[n+1];
    vector<vector<int>>up(n+1,vector<int>(LOG+1));
    vector<int>depth(n+1,0);
    for(int i = 0;i<n-1;i++)
    {
        int a;
        cin>>a;
        adj[a].push_back(i+2);
    }
    dfs(1,-1,adj,depth,up);
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        cout<<LCA(a,b,depth,up)<<"\n";
    }
    return 0;
}