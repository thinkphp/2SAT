#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 200010

vector<int> G[MAXN], Gt[MAXN];
int Fix[MAXN];
bool Ok[MAXN];
int x, y, i;
int N, Q, M;
int V[MAXN];

inline int non(const int &x)
{
	return (x > N ? x - N : x + N);
}

inline void Muchie(const int &x, const int &y)
{
	G[x].push_back(y);
	Gt[y].push_back(x);
}

void df1(const int &nod)
{
	vector<int>::iterator it;
	int nod2;
	
	Ok[nod] = true;
	for (it = G[nod].begin(); it != G[nod].end(); ++it){
		nod2 = *it;
		if (!Ok[nod2])
			df1(nod2);
	}
	
	V[++Q] = nod;
}

void df2(const int &nod)
{
	if (Fix[nod]){
		printf("-1\n");
		exit(0);
	}
	
	Fix[non(nod)] = 1;
	Ok[nod] = true;
	
	int nod2;
	vector<int>::iterator it;
	for (it = Gt[nod].begin(); it != Gt[nod].end(); ++it){
		nod2 = *it;
		if (!Ok[nod2])
			df2(nod2);
	}
}

int main()
{
	freopen("2sat.in","r",stdin);
	freopen("2sat.out","w",stdout);
	
	scanf("%d %d",&N,&M);
	
	for (i = 1; i <= M; ++i){
		scanf("%d %d",&x,&y);
		x = x > 0 ? x : N - x;
		y = y > 0 ? y : N - y;
		Muchie(non(x), y); Muchie(non(y), x);
	}
	
	Q = 0;
	for (i = 1; i <= 2 * N; ++i)
		if (!Ok[i])
			df1(i);

	for (i = 1; i <= 2 * N; ++i)
		Ok[i] = false;
	
	for (i = Q; i >= 1; --i)
		if (!Ok[V[i]] && !Ok[non(V[i])])
			df2(V[i]);
		
	for (i = 1; i <= N; ++i)
		printf("%d ", Fix[i]);

	return 0;
	
}
