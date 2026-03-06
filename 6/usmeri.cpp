//topolosko sortiranje

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> ulaznistepeni;
    vector<int> pozicijaUTopSort;
    vector<pair<int,int>> neusmereneGrane;
    vector<pair<int,int>> dodateGrane;

    public:
    //konstruktor
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        ulaznistepeni.resize(V,0);
        pozicijaUTopSort.resize(V,-1);
    }

    void dodajUsmerenuGranu(int u, int v){
        susedi[u].push_back(v);
        ulaznistepeni[v]++;
    }

    void dodajNeusmerenuGranu(int u, int v){
        neusmereneGrane.push_back({u,v});
    }

    //BFS
    //za DFS ne bismo imali ulazne stepene ali cvorove bismo smestali u tom slucaju na stek
    void KanovAlg(){
        queue<int> cvorovi;
        //priority_queue<int, vector<int>, greater<int>> cvorovi;


        for(int i=0; i<V; i++){
            if(!ulaznistepeni[i]) //u red ubacujemo ulazne stepene cvorova razlicitih od 0
                cvorovi.push(i);
        }

        int cvor;
        int pozUTopSort=0; //prva pozicija tekuceg cvora

        while(!cvorovi.empty()){
            cvor = cvorovi.front();
            cvorovi.pop();
            
            //koju dodeljujemo tekucem cvoru
            pozicijaUTopSort[cvor] = pozUTopSort++;

            /*Prolazimo kroz sve cvorove koji su susedni cvoru cvor, smanjujemo im ulazni stepen, 
            i onda ako je neki dosao do ulaznog stepena 0
            znaci da smo zavrsili sve aktivnosti od kojih on zavisi, tako da se i on moze dodati na kraj reda*/
            for(int sused : susedi[cvor]){
                ulaznistepeni[sused]--;

                if(ulaznistepeni[sused]==0)
                    cvorovi.push(sused);
            }

        }
    }
    void usmeriGrane(){
        KanovAlg();

        for(auto & [u,v] : neusmereneGrane){
            // Ako je u pre v u topoloskom redosledu dodajemo granu u -> v inace granu v->u
            if(pozicijaUTopSort[u] < pozicijaUTopSort[v]){
                dodajUsmerenuGranu(u,v);
                dodateGrane.push_back({u,v});
            }else{
                dodajUsmerenuGranu(v,u);
                dodateGrane.push_back({v,u});
            }
        }
        for(auto &[u,v]:dodateGrane)
            cout << u << ' ' << v << endl;
    }
};

int main ()
{
   int n, m, p;
   cin >> n >> m >> p;

   Graph *G = new Graph(n);

   int u, v;
   for (int i = 0; i < m; i++) {
      cin >> u >> v;
      G->dodajUsmerenuGranu(u, v);
   }

   for (int i = 0; i < p; i++) {
      cin >> u >> v;
      G->dodajNeusmerenuGranu(u, v);
   }

   G->usmeriGrane();
   return 0;
}