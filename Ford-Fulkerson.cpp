#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001;

int n, m, s, t;
vector <int> adj[MAXN];    //đồ thị lưu kiểu danh sách kề
int c[MAXN][MAXN], f[MAXN][MAXN], trace[MAXN], maxFlow;

//BFS để tìm đường tăng luồng
void bfs()
{
    fill(trace, trace + n + 1, 0);
    trace[s] = -1;

    queue <int> bfsQueue;
    bfsQueue.push(s);

    while (!bfsQueue.empty())
    {
        int u = bfsQueue.front();
        bfsQueue.pop();
        for (auto v : adj[u])
        {
            //Không dẫm lại đường cũ theo đúng luật BFS
            if (trace[v]) continue;

	    //Không đi qua cạnh có r(u, v) = c(u, v) - f(u, v) = 0
            if (f[u][v] - c[u][v] == 0) continue;

            //Các công việc còn lại của BFS
            trace[v] = u;
            bfsQueue.push(v);
        }
    }
}

//Hàm tăng luồng
void incFlow()
{
    //Đi ngược theo đường tăng luồng để tìm giá trị delta = c - f tốt nhất
    int delta = INT_MAX;
    int v = t;
    while (v != s)
    {
        int u = trace[v];
        delta = min(delta, c[u][v] - f[u][v]);
        v = u;
    }

    maxFlow += delta;

    //Đi ngược theo đường tăng luồng một lần nữa để cập nhật giá trị f
    v = t;
    while (v != s)
    {
        int u = trace[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
}

int main()
{
    cin >> n >> m >> s >> t;
    for (int u, v, i = 1; i <= m; i ++)
    {
        cin >> u >> v;
        cin >> c[u][v];
        adj[u].push_back(v);
        adj[v].push_back(u);	//lưu thêm cạnh ngược để có thể chạy qua nó khi tăng luồng
    }

    maxFlow = 0;

    //Tăng luồng đến khi không tăng được nữa
    do
    {
        bfs();
        if (trace[t]) incFlow();
    } while (trace[t]);

    cout << maxFlow;
}