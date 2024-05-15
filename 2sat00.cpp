#include <cstdio>
#include <vector>
using namespace std;
const int N = 200005;
int n, m, post[N], nr, v[N], ok, value[N];
vector<int> a[N], at[N];

inline int abs(int a) {
    if(a < 0)
        return -a;
    return a;
}
inline int neg(int a){
    if(a > n)
        return a -= n;
    return a + n;
}

inline void dfs(int k) {
    int i;
    v[k] = 1;
    for(i = 0 ; i < a[k].size(); ++i)
        if(!v[a[k][i]])
            dfs(a[k][i]);
    post[++nr] = k;
}

inline void dfst(int k) {
    int i;
    if(value[k])
        ok = 0;
    v[k] = 0;
    value[k] = 0;   value[neg(k)] = 1;
    for(i = 0 ;i < at[k].size(); ++i)
        if(v[at[k][i]])
            dfst(at[k][i]);
}

int main() {
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out" ,"w", stdout);
    int i, j, x, y;
    scanf("%d %d", &n, &m);
    for(i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        if(x < 0)
            x = n + abs(x);
        if(y < 0)
            y = n + abs(y);
        a[neg(x)].push_back(y);
        at[y].push_back(neg(x));
        a[neg(y)].push_back(x);
        at[x].push_back(neg(y));
    }

    for(i = 1; i <= 2 * n; ++i)
        if(v[i] == 0)
            dfs(i);
    ok = 1;
    for(i = nr; i >= 1; --i)
        if(v[post[i]] && v[neg(post[i])])
            dfst(post[i]);

    if(ok) {
        for(i = 1; i <= n; ++i)
            printf("%d ", value[i]);
        printf("\n");
    }
    else
        printf("%d\n", -1);
    return 0;
}
