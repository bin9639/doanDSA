#include <bits/stdc++.h>

using namespace std;

#define N 1000010
#define ll long long
#define fs first
#define sc second
#define ii pair<int,int>
#define pb push_back
#define iii pair<int,ii>
#define cong 1000001
#define ld long double

int tmp[N],cnt[N],cs[N][2],a[N],tt[N],dist[N],cur[N],adj[N],head[N],u,n,m,S,T,dem,numEdge=0,canh[N];
queue<int>s;
ii edge[N];

struct canh
{
    int from,to;
    ll c,f;
}g[N];

void themcanh(int u,int v,ll c)
{
   // cout<<u<<" "<<v<<" "<<c<<endl;
    g[numEdge++]={u,v,c,0};
    g[numEdge++]={v,u,0,0};
    head[u]++;
    head[v]++;
}

bool find_path(int S,int T)
{
    fill(dist+1,dist+1+dem,-2);
    dist[S]=0;
    while(!s.empty())
        s.pop();
    s.push(S);
    int u;
    while(!s.empty())
    {
        u=s.front();
      //  cout<<u<<" "<<dist[u]<<endl;
        s.pop();
        if(u==T)
            return 1;
        for(int i=head[u];i<head[u+1];i++)
            if(g[adj[i]].c>g[adj[i]].f&&dist[g[adj[i]].to]==-2)
            {
                dist[g[adj[i]].to]=dist[u]+1;
                s.push(g[adj[i]].to);
            }
    }
    return 0;
}

ll update(int u,int T,ll flowin)
{
    //cout<<u<<" "<<flowin<<endl;
    if(u==T)
        return flowin;
    ll val,flowout=0;
    int i;
    for(;cur[u]<head[u+1];cur[u]++)
    {
        i=adj[cur[u]];
        if(g[i].c>g[i].f&&dist[g[i].to]==dist[u]+1)
        {
            val=update(g[i].to,T,min(flowin,g[i].c-g[i].f));
            flowout+=val;
            flowin-=val;
            g[i].f+=val;
            g[(i^1)].f-=val;
            if(flowin==0)
                return flowout;
        }
    }
    return flowout;
}

int main()
{
    #ifdef TTCC
    freopen("A.inp","r",stdin);
    freopen("A.out","w",stdout);
    #endif // TTCC
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>tt[i];
    for(int i=1;i<=n;i++)
        cin>>a[i];
    //0 tru 1 cong
    S=1;
    T=2;
    dem=2;
    for(int i=1;i<=n;i++)
    {
        cs[i][0]=++dem;
        cs[i][1]=++dem;
    }
   // cout<<S<<" "<<T<<" "<<dem<<endl;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        edge[i]={u,v};
        cnt[u]++;
        cnt[v]++;
    }
    for(int i=1;i<=n;i++)
        if(tt[i]==0)
        {
          //  themcanh(cs[i][1],T,1e9);
        }else
        {
            if(abs(a[i])>cnt[i]||abs(a[i])%2!=cnt[i]%2)
            {
                cout<<"NO";
                return 0;
            }
            themcanh(cs[i][1],T,(a[i]+cnt[i])/2);
        }
    for(int i=1;i<=m;i++)
    {
        int u,v;
        tie(u,v)=edge[i];
        dem++;
        themcanh(S,dem,1);
        canh[i]=numEdge;
        themcanh(dem,cs[v][1],1);
        themcanh(dem,cs[u][1],1);
    }
    for(int i=1;i<=dem;i++)
        tmp[i]=head[i];
    for(int i=1;i<=dem+1;i++)
        head[i]+=head[i-1];
    for(int i=0;i<numEdge;i++)
        adj[--head[g[i].from]]=i;
    ll ans=0;
    while(find_path(S,T))
    {
        for(int i=1;i<=dem;i++)
            cur[i]=head[i];
        ans+=update(S,T,1e15);
    }
    for(int i=1;i<=dem;i++)
        head[i]=tmp[i];
    for(int i=1;i<=n;i++)
        if(tt[i]==0)
        {
            themcanh(cs[i][1],T,1e9);
        }
    for(int i=1;i<=dem+1;i++)
        head[i]+=head[i-1];
    for(int i=0;i<numEdge;i++)
        adj[--head[g[i].from]]=i;
    while(find_path(S,T))
    {
        for(int i=1;i<=dem;i++)
            cur[i]=head[i];
        ans+=update(S,T,1e15);
    }
   // cout<<ans<<endl;
    for(int i=1;i<=n;i++)
        if(tt[i]==1)
        {
            for(int j=head[cs[i][1]];j<head[cs[i][1]+1];j++)
                if(g[adj[j]].to==T)
                {
                //    cout<<i<<" "<<g[adj[j]].c<<endl;
                    if(g[adj[j]].f!=g[adj[j]].c)
                    {
                        cout<<"NO\n";
                        return 0;
                    }
                }
        }
 for(int i=1;i<=m;i++)

        {
            if(g[canh[i]].f!=1) swap(edge[i].fs,edge[i].sc);
            a[edge[i].fs]++;
            a[edge[i].sc]--;
        }
    for(int i=1;i<=n;i++)
    if(tt[i]==1&&a[i]!=0)
    {//
     //   cout<<i<<" "<<a[i]<<endl;
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    for(int i=1;i<=m;i++)
        cout<<edge[i].fs<<" "<<edge[i].sc<<"\n";
    return 0;
}