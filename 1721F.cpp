#include <bits/stdc++.h>

using namespace std;

#define N 500010
#define ll long long
#define fs first
#define sc second
#define ii pair<int,int>
#define pb push_back
#define iii pair<int,ii>
#define cong 1000001
#define ld long double

int check[N][2],times,ktr[N],n1,n2,m,q,assigned[N];
vector<int>g[N],nguoc[N];
vector<ii>canh;
ll sum=0;
map<ii,int>mp;

bool visit(int u)
{
    if(ktr[u]==times)
        return 0;
    ktr[u]=times;
    for(auto v:g[u])
    {
        if(!assigned[v]||visit(assigned[v]))
        {
            assigned[v]=u;
            return 1;
        }
    }
    return 0;
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
    cin>>n1>>n2>>m>>q;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        nguoc[v].pb(u);
        mp[{u,v}]=i;
    }
    int ans=0;
    for(int i=1;i<=n1;i++)
    {
        times++;
        ans+=visit(i);
    }
   // cout<<ans<<endl;
    queue<int>s;
    memset(ktr,0,sizeof(ktr));
    for(int i=1;i<=n2;i++)
        if(assigned[i])
        {
            ktr[assigned[i]]=1;
        }else
            s.push(i+n1);
    for(int i=1;i<=n1;i++)
        if(!ktr[i])
            s.push(i);//,cout<<i<<endl;
    while(!s.empty())
    {
        int u=s.front();
        s.pop();
        if(u<=n1)
        {
           // cout<<u<<endl;
            if(check[u][0])
                continue;
            for(auto v:g[u])
                if(check[v][1]==0)
                {
                    check[v][1]=1;
                    for(auto x:nguoc[v])
                        if(assigned[v]==x)
                            s.push(x);
                }
        }else
        {
            u-=n1;
         //   cout<<u<<endl;
            if(check[u][1])
                continue;
            for(auto v:nguoc[u])
                if(check[v][0]==0)
                {
               //     cout<<v<<"cc\n";
                    check[v][0]=1;
                    for(auto x:g[v])
                        if(assigned[x]==v)
                            s.push(x+n1);
                }
        }
    }
    for(int i=1;i<=n2;i++)
        if(assigned[i]&&!check[i][1]&&!check[assigned[i]][0])
        {
          //  cout<<i<<endl;
            check[i][1]=1;
        }
    for(int i=1;i<=n2;i++)
        if(assigned[i])
        {
            int vt=mp[{assigned[i],i}];
            sum=sum+1ll*vt;
            if(check[i][1])
                canh.pb({vt,-i});
                    else canh.pb({vt,assigned[i]});
        }
    for(int i=1;i<=q;i++)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            cout<<1<<endl;
            cout<<canh.back().sc<<endl;
            sum=sum-1ll*canh.back().fs;
            canh.pop_back();
            cout<<sum<<endl;
            cout<<endl;
        }else
        {
            cout<<canh.size()<<"\n";
            for(int j=0;j<canh.size();j++)
                cout<<canh[j].fs<<" ";
            cout<<endl<<endl;
        }
    }
    return 0;
}