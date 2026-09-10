#include<bits/stdc++.h>
using namespace std;
#define int long long
class SegmentTree{
    private:
    vector<int>seg;
    public:
    SegmentTree(int n)
    {
        seg.resize(4*n+1);
    }
    void build(int index,int low,int high,vector<int>&arr,vector<int>&flat)
    {
        if(low == high)
        {
            seg[index] = 1ll*arr[flat[low]];
            return;
        }
        int mid = (low+high)/2;
        build(index*2+1,low,mid,arr,flat);
        build(index*2+2,mid+1,high,arr,flat);
        seg[index] = seg[index*2+1] + seg[index*2+2];
    }
    int query(int index,int low,int high,int l,int r)
    {
        if(r < low|| l > high) return 0ll;
        else if(low >= l && high <= r) return seg[index];
        else
        {
            int mid = (low+high)/2;
            return query(index*2+1,low,mid,l,r) + query(index*2+2,mid+1,high,l,r);
        }
    }
    void update(int index,int low,int high,int updateIndex,int updateValue)
    {
        if(low == high)
        {
            seg[index] = 1ll*updateValue;
            return;
        }
        int mid = (low+high)/2;
        if(updateIndex <= mid)
        {
            update(index*2+1,low,mid,updateIndex,updateValue);
        }
        else
        {
            update(index*2+2,mid+1,high,updateIndex,updateValue);
        }
        seg[index] = seg[index*2+1] + seg[index*2+2];
    }
};
int timer = 0;
void flattenTree(int node,int parent,vector<int>adj[],vector<int>&tin,vector<int>&tout,vector<int>&flat)
{
    tin[node] = timer;
    flat[timer] = node;
    timer++;
    for(auto neighbors : adj[node])
    {
        if(neighbors == parent) continue;
        flattenTree(neighbors,node,adj,tin,tout,flat);
    }
    tout[node] = timer-1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    vector<int>values(n+1);
    for(int i = 1;i<=n;i++)
    {
        cin>>values[i];
    }
    vector<int>adj[n+1];
    for(int i = 1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>tin(n+1),tout(n+1),flat(n);
    flattenTree(1,-1,adj,tin,tout,flat);
    SegmentTree sg(n);
    sg.build(0,0,n-1,values,flat);
    while(q--)
    {
        int t;
        cin>>t;
        if(t == 1)
        {
            int s,x;
            cin>>s>>x;
            int time = tin[s];
            sg.update(0,0,n-1,time,x);
        }
        else
        {
            int s;
            cin>>s;
            int l = tin[s];
            int r = tout[s];
            cout<<sg.query(0,0,n-1,l,r)<<"\n";
        }
    }
    return 0;
}