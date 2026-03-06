/*
ispiti - unosi se broj ispita i espb vrednost svakog, zatim uslovljenost ispita, ispisi raspored polaganja tako da u svakom trenutku 
student osvoji max espb (u sustini samo biras trenutno neuslovljen predmet sa max espb)

-> topolosko sortiranje

oni ciji je ulazni stepen 0 su ispiti koji nisu uslovljeni te njih prvo obradjujemo
*/

#include <bits/stdc++.h>
using namespace std;
/*
struct comparator
{
  bool operator()(const int &p1, const int &p2)
  {
    return p1 > p2;
  }
};
*/

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> espb;
    vector<int> inDeg;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        espb.resize(V);
        inDeg.resize(V,0);
    }

    void dodajEspb(int e){
        espb.push_back(e);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        inDeg[v]++;
    }
/*
(first  = ESPB)
(second = indeks ispita)

pair se poredi leksikografski:
prvo po first
ako su first jednaki, onda po second

Max-heap znači: najveći first je na vrhu
Ako first jednaki, veći second ide na vrh
*/
    void kanov(){
        //automatski sortira rastuce po espb
        priority_queue<pair<int,int>> q;
        for(int i=0; i<V; i++){
            if(inDeg[i]==0)
                q.push({espb[i],i});
        }
        while(!q.empty()){
            auto [tmpespb, tmp] =  q.top();
            q.pop();

            cout << tmp << ' ';

            for(int sused : susedi[tmp]){
                inDeg[sused]--;
                if(inDeg[sused]==0){
                    q.push({espb[sused],sused});
                }
            }
        }
    }
};

int main(){

    int n;
    cin >> n;
    
    Graph *G = new Graph(n);
    
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        G->dodajEspb(x);
    }

    int m;
    cin >> m;

    for(int i=0;i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    G->kanov();

    return 0;
}