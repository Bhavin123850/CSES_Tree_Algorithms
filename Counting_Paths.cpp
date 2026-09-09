#include<bits/stdc++.h>
using namespace std;
const int LOG = 18;
void dfs(int node,int parent,vector<int>adj[],vector<vector<int>>&up,vector<int>&depth)
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
        dfs(neighbors,node,adj,up,depth);
    }
}
int LCA(int u,int v,vector<vector<int>>&up,vector<int>&depth)
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
void dfs2(int node,int parent,vector<int>adj[],vector<int>&count)
{
    for(auto neighbors : adj[node])
    {
        if(neighbors == parent) continue;
        dfs2(neighbors,node,adj,count);
        count[node] += count[neighbors];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin>>n>>k;
    vector<int>adj[n+1];
    for(int i = 1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>>up(n+1,vector<int>(LOG+1));
    vector<int>depth(n+1);
    depth[1] = 1;
    dfs(1,-1,adj,up,depth);
    vector<int>count(n+1,0);
    for(int i = 0;i<k;i++)
    {
        int a,b;
        cin>>a>>b;
        count[a]++;
        count[b]++;
        int lca = LCA(a,b,up,depth);
        count[lca]--;
        if(up[lca][0] != -1)
        {
            count[up[lca][0]]--;
        }
    }
    dfs2(1,-1,adj,count);
    for(int i = 1;i<=n;i++)
    {
        cout<<count[i]<<" ";
    }
    cout<<"\n";
    return 0;
}