#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#define INF 0x3fffffff
#define RE(x) (x)^1
#define S 1
#define MAXN 20
using namespace std;

int N, M, head[MAXN], lvl[MAXN], idx;

struct Edge
{
    int No, cap, next;
}e[1005];

void init()
{
    idx = -1;
    memset(head, 0xff, sizeof (head));
}

void insert(int x, int y, int z)
{
    ++idx;
    e[idx].No = y;
    e[idx].cap = z;
    e[idx].next = head[x];
    head[x] = idx;
    ++idx;
    e[idx].No = x;
    e[idx].cap = 0;
    e[idx].next = head[y];
    head[y] = idx;
}

bool bfs()
{
    int pos;
    queue<int>q;
    memset(lvl, 0xff, sizeof (lvl));
    lvl[S] = 0;
    q.push(S);
    while (!q.empty()) {
        pos = q.front();
        q.pop();
        for (int i = head[pos]; i!=-1; i = e[i].next) {
            if (e[i].cap > 0 && lvl[e[i].No]==-1) {
                lvl[e[i].No] = lvl[pos]+1;
                q.push(e[i].No);  // 注意不要直接把“i”push进去了 
            }
        }
    }
    return lvl[N] != -1;
}

int dfs(int u, int flow)
{
    if (u == N) {
        return flow;
        // 结束条件，把流推到了T节点（汇点） 
    }
    int tf = 0, f;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (lvl[u]+1 == lvl[e[i].No] && e[i].cap > 0 && (f = dfs(e[i].No, min(e[i].cap, flow - tf)))) {
            e[i].cap -= f;
            e[RE(i)].cap += f;
            tf += f;
        }
    }
    if (tf == 0) {
        lvl[u] = -1;
        // tf等于零表示该点没有进行增广的能力，应及时将其高度赋值为-1，防止第二次被搜索到 
    }
    return tf;
}

int main()
{
    int T, ans, ca = 0, a, b, c;
    scanf("%d", &T);
    while (T--) {
        init();
        ans = 0;
        scanf("%d %d", &N, &M);
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %d", &a, &b, &c);
            insert(a, b, c);
        }
        while (bfs()) {
            ans += dfs(S, INF);
        }
        printf("Case %d: %d\n", ++ca, ans);
    }
    return 0;    
}