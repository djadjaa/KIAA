//Potrebno je dodati maksimalan broj grana u ovaj graf tako da on i dalje ostane aciklički.
/*
primenicemo ovog puta kanov alg na dfs pretrazi jer je graf aciklican i usmeren

dodavacemo grane ka svim kasnijim cvorovima kojima ne postoji veza/grana medju njima
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool> posecen;
    vector<int> pozicijaUTopSort;
    vector<pair<int,int>> dodateGrane;
    stack<int> s; //DFS je u pitanju

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
    }

    void addEdge(int u, int v){
        susedi[u].push_back(v);
    }

    void DFS(int cvor){
        posecen[cvor] = true;
        for(int sused : susedi[cvor]){
            if(!posecen[sused])
                DFS(sused);
        }
        
        /*
        Kod obične DFS pretrage, element može da se stavi na stek (ili u listu obilaska) čim ga otkrijemo, 
        jer nam je bitan samo redosled posećivanja.
        Kod topološkog sortiranja, bitno je da svaki čvor dođe posle svih svojih prethodnika.
        Zato čvor stavljamo na stek tek kad završimo obilazak svih njegovih suseda 
        – znači kad smo sigurni da su svi čvorovi koji zavise od njega već ubačeni pre njega.
        */  

        s.push(cvor);
    }

    void kanovAlg(){
        for(int i=0; i<V; i++){
            if(!posecen[i])
                DFS(i);
        }
        int tekucicvor;
        while(!s.empty()){
            tekucicvor = s.top();
            s.pop();

            pozicijaUTopSort.push_back(tekucicvor);
        }
    }

    void dodajGrane(){
        kanovAlg();

        int tekucicvor;
        for(int i=0; i<V; i++){
            tekucicvor = pozicijaUTopSort[i];
            cout << tekucicvor << '\n';
            //svi čvorovi se resetuju na „neposećen“ status u jednom potezu.
            fill(posecen.begin(), posecen.end(), false);
            for(int sused : susedi[tekucicvor])
                posecen[sused] = true;
            for(int j = i+1; j<V; j++){
                int sledeci = pozicijaUTopSort[j];
                if(!posecen[sledeci])
                    dodateGrane.push_back({tekucicvor,sledeci});
            }
        }
        sort(dodateGrane.begin(),dodateGrane.end());
        for(auto &[u,v] : dodateGrane)
            cout << u << ' ' << v << '\n';
    }
};

int main(){

    int n, m;

    cin >> n >> m;
 
    Graph *G = new Graph(n);
 
    int u, v;
    for (int i = 0; i < m; i++) {
       cin >> u >> v;
       G->addEdge(u, v);
    }
 
    G->dodajGrane();

    return 0;
}