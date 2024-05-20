#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define ll long long
#define fs first
#define sc second
#define ii pair<int,int>
#define pb push_back
#define iii pair<ii,int>
#define cong 1000001
#define ld long double

int d[N],f[N][N],ans,n,m,S,T,u,v,L,c[N][N];
vector<int>g[N];

queue<int>s;

bool findpath(int S,int T)
{
    fill(d+1,d+1+n,0);
    d[S]=-1;
    while(!s.empty())
        s.pop();
     s.push(S);
    while(!s.empty())
    {
        int u=s.front();
        s.pop();
        if(u==T)
            return 1;
        for(auto v:g[u])
            if(d[v]==0&&c[u][v]>f[u][v])
            {
                d[v]=u;
                s.push(v);
            }
    }
    return 0;
}

void update()
{
    int u,v,val=1e9;
    for(v=T;v!=S;v=d[v])
        val=min(val,c[d[v]][v]-f[d[v]][v]);
    for(v=T;v!=S;v=d[v])
    {
        u=d[v];
        f[u][v]+=val;
        f[v][u]-=val;
    }
}

int get(int u)
{
    ll ans=0;
    for(auto v:g[u])
        ans+=f[u][v];
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m>>S>>T;
    if(S==T)
    {
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>L;
        g[u].pb(v);
        g[v].pb(u);
        c[u][v]=L;
    }
    while(findpath(S,T))
        update();
    cout<<get(S);
   // cout<<0;
    return 0;
}
