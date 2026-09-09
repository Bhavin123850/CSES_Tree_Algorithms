#include<bits/stdc++.h>
using namespace std;
const int LOG = 20;
void dfs(int node,int parent,vector<int>&depth,vector<int>adj[],vector<vector<int>>&up)
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
        if(neighbors == parent) continue;
        depth[neighbors] = depth[node] + 1;
        dfs(neighbors,node,depth,adj,up);
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
    for(int i = LOG;i>=0;i--)
    {
        if(up[u][i] != -1 && up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    vector<int>adj[n+1];
    vector<int>depth(n+1,0);
    vector<vector<int>>up(n+1,vector<int>(LOG+1));
    for(int i = 0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1,depth,adj,up);
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        int distance = depth[a] + depth[b];
        int lca = LCA(a,b,depth,up);
        distance -= 2*depth[lca];
        cout<<distance<<"\n";
    }
    return 0;
}