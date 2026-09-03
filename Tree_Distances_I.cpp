#include<bits/stdc++.h>
using namespace std;
pair<int,int> dfs(int node,int parent,vector<int>adj[])
{
    pair<int,int>p = {0,node};
    for(auto neighbors : adj[node])
    {
        if(neighbors == parent) continue;
        auto temp = dfs(neighbors,node,adj);
        temp.first++;
        if(temp.first > p.first)
        {
            p = temp;
        }
    }
    return p;
}
vector<int> bfs(int node,vector<int>adj[],int n)
{
    vector<int>visited(n+1,0);
    queue<pair<int,int>>q;
    q.push({0,node});
    vector<int>dist(n+1,0);
    visited[node] = 1;
    while(!q.empty())
    {
        auto it = q.front();
        q.pop();
        dist[it.second] = it.first;
        for(auto neighbors : adj[it.second])
        {
            if(visited[neighbors]) continue;
            visited[neighbors] = 1;
            q.push({dist[it.second]+1,neighbors});
        }
    }
    return dist;
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
    auto it2 = dfs(it.second,-1,adj);
    int firstNode = it.second;
    int secondNode = it2.second;
    vector<int>distFromFirstNode,distFromSecondNode;
    distFromFirstNode = bfs(firstNode,adj,n);
    distFromSecondNode = bfs(secondNode,adj,n);
    for(int i = 1;i<=n;i++)
    {
        cout<<max(distFromFirstNode[i],distFromSecondNode[i])<<" ";
    }
    cout<<"\n";
    return 0;
}