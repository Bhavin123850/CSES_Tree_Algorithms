#include<bits/stdc++.h>
using namespace std;
#define LOG 20
void dfs(int node,int parent,vector<int>adj[],vector<vector<int>>&up)
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
        dfs(neighbors,node,adj,up);
    }
}
int main()
{
    int n,q;
    cin>>n>>q;
    vector<int>v(n-1);
    vector<int>adj[n+1];
    for(int i = 0;i<n-1;i++)
    {
        cin>>v[i];
        adj[v[i]].push_back(i+2);
    }
    vector<vector<int>>up(n+1,vector<int>(LOG+1));
    dfs(1,-1,adj,up);
    while(q--)
    {
        int x,k;
        cin>>x>>k;
        for(int i = 0;i<=LOG;i++)
        {
            if(k & (1<<i))
            {
                x = up[x][i];
                if(x == -1) break;
            }
        }
        cout<<x<<"\n";
    }
    return 0;
}
