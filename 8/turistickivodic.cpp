//flojd varsal
/*
ideja je baziran na maksimalnom uskom grlu puta:
to je put koji omoguca da se najvise ljudi odjednom preveze
odredjujemo kapacitet putnika odnosno najmanju tezinu grane izmedju dva cvora odn dva grada
zatim trazimo maksimum od tih minimuma i ture dobijamo podelom broja turista sa dobijenim kapacitetom puta
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <math.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V=V;
        susedi.resize(V);
        for(int i=0; i<V; i++)
            susedi[i].resize(V,0);
    }

    void dodajGranu(int u,int v, int w){
        susedi[u][v] = w;
        susedi[v][u] = w;
    }

    void flojdVarsal(){
        for(int k=0; k<V; k++){
            for(int i=0; i<V; i++){
                for(int j=0; j<V; j++){
                    //odredjujemo kapacitet putnika odnosno najmanju tezinu grane izmedju dva cvora odn dva grada
                    //zatim trazimo maksimum od tih minimuma
                    susedi[i][j] = max(susedi[i][j],min(susedi[i][k],susedi[k][j]));
                }
            }
        }
    }
    //ture dobijamo podelom broja turista sa dobijenim kapacitetom puta
    int brRuta(int p, int k, int t){
        return ceil((float)t/susedi[p][k]);
    }
};

int main(){
    int n, m;
    cin >> n >> m;

   Graph *G = new Graph(n);

   int u, v, t;
    for(int i=0;i<m;i++){
         cin >> u >> v >> t;
         G->dodajGranu(u-1, v-1, t);

    }

   G->flojdVarsal();

   int q;
   cin >> q;
   while(q--){
      int p, k, t;
      cin >> p >> k >> t;

      cout << G->brRuta(p-1, k-1, t) << endl;

   }

   

    delete G;

    return 0;
}