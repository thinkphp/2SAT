#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#define FIN "2sat.in"
#define FOUT "2sat.out"

using namespace std;

class SAT2 {

public:
      SAT2(const int n = 0): N( n ), t( 0 ), 
                             G(vector<vector<int> >(2*n+1)), 
                             GT(vector<vector<int> >(2*n+1)),
                             visited(vector<bool>(2*n+1, false)),
                             postorder(vector<int>(2*n+1, 0)), 
                             solution(vector<bool>(2*n+1, false)){}

void addEdge(int x, int y) {

     if(x < 0) x = -x + N; 
     if(y < 0) y = -y + N;

     G[Not(x)].push_back(y); 
     GT[y].push_back(Not(x)); 

     G[Not(y)].push_back(x);  
     GT[x].push_back(Not(y));
}

int Not(int x) const {
 
    if(x > N) return  x - N;
        else  return  x + N;
}
    void DFS(int nod)
    {
        visited[nod] = true;
 
        for (auto it: G[nod])
            if (!visited[it])
                DFS(it);
 
        postorder[ ++t ] = nod;
    }


void DFSR(int node) {

     visited[ node ] = false;

     solution[ Not(node) ] = true;

     for(auto it : GT[ node ]) {
    
         if(visited[ it ]) {

            DFSR( it ); 
         }
     }      
};

void Kosaraju() {

     for(int i = 1; i <= 2 * N; ++i ) {

         if(!visited[ i ]) {

            DFS( i );
         }
     }

     for(int i = 2 * N; i >= 1; --i ) {     

         int node = postorder[ i ];

         if( visited[ node ] && visited[ Not(node) ]) {

             DFSR( node );
         } 
     }

};

bool isSolution() const {

     for(int i = 1; i <= N; i++) {
  
         if(solution[ i ] && solution[ Not(i) ])  return false;
     }

    return true; 
}

public:
      int N, t;
      vector<vector<int> > G,GT;
      vector<bool> solution;
      vector<int> postorder;
      vector<bool> visited;
};

int main() {

    ifstream fin( FIN );
    ofstream fout( FOUT );

    int n, 
        m, 
        x, 
        y;

    fin >> n >> m;
 
    SAT2 S(n);
 
    for ( ;m--; ) {

        fin >> x >> y;
 
        S.addEdge(x, y);
    }
 
    S.Kosaraju();
 
    if (S.isSolution()) {

        for (int i = 1; i <= S.N; ++i)

            fout << S.solution[i] << " ";
    }
    else

        fout << "-1\n";

 return (0);

};
