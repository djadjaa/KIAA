//Belman Ford

/*
radi sa negativnim tezinama te je sporiji od dajkstre
takodje, detektuje negativne cikluse (one cija je ukupna suma tezina grana u ciklusu negativna)

dajkstra je efikasnija za mape,mreze,rute,a belman za finansije
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

/*
posto belman ford sabira tezine grana,a mi imamo mnozenje tezina,
logaritmovacemo celu jnu da bismo dobili sabirke
log(5*8*9) = log5+log8+log9 ...

celu jnu cemo zatim pomnoziti sa -1 da bismo detektovali negativne grane
*/

void logarithm(vector<vector<double>> &R){
    const int n = R.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            R[i][j] = -log(R[i][j]);
        }
    }
}

void otpustanjeGrane(int u, int v, const vector<vector<double>> &R,vector<double> &dist, vector<int> &parent){
    if(dist[v]>dist[u]+R[u][v]) {
        dist[v] = dist[u]+R[u][v];
        parent[v] = u;
        //parent niz omogućava da se rekonstruiše ciklus kada se detektuje negativna suma
    }
    //kraći put → negativni ciklus → profitabilni valutni ciklus
}

/*
Kada Bellman-Ford detektuje negativni ciklus, 
pratimo parent niz da rekonstruiramo koje valute čine ciklus.
*/
string formirajCiklus(int u, int v, const vector<int> &roditelj, const vector<string>&valute){
    vector<int> putanja;
    putanja.push_back(v);
    putanja.push_back(u);

    while(find(putanja.begin(),putanja.end(),roditelj[u])==putanja.end()){
        putanja.push_back(roditelj[u]);
        u = roditelj[u];
    }
    putanja.push_back(roditelj[u]);

    int prviUCiklusu = putanja.back();
    putanja.pop_back();

    //inicijalizacija stringa
    string ciklus = valute[prviUCiklusu]+" ";
    //formiranje stringa
    while(!putanja.empty() && putanja.back() != prviUCiklusu){
        ciklus += valute[putanja.back()]+" ";
        putanja.pop_back();
    }
    ciklus += valute[prviUCiklusu]; //terminirajuca nula
    return ciklus;
}

void belmanford(vector<vector<double>> &R, const vector<string> &valute){
    const int n = R.size();
    logarithm(R);
    //prethodni cvorovi
    vector<int> roditelj(n,-1);
    //trenutno poznata udaljenost od izvornog čvora.
    vector<double> rastojanja(n,numeric_limits<double>::max());
    rastojanja[0] = 0.0;
    for(int i=0; i<n-1; i++){
        for(int u=0; u<n; u++){//pocetni cvor
            for(int v=0; v<n; v++){
                otpustanjeGrane(u,v,R,rastojanja,roditelj);
            }
            //Na kraju ovoga imamo minimalne udaljenosti ako nema negativnih ciklusa.
        }
    }
    set<string> rezultat;
    //belman ford:
    for(int u=0; u<n; u++){
        for(int v=0; v<n; v++){
            //Ako se još neka relaksacija može izvršiti → postoji negativan ciklus.
            if(rastojanja[v]>rastojanja[u]+R[u][v])
            //i rekonstruise se ciklus -> primenjujemo skup jer ne zelimo duplikate
                rezultat.insert(formirajCiklus(u,v,roditelj,valute));
        }
    }
    for(auto str : rezultat)    
        cout << str << endl;
}

int main(){
    int n; cin >> n;

    vector<string> currencies(n);
    for (int i = 0; i < n; i++) {
        cin >> currencies[i];
    }

    vector<vector<double>> R(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> R[i][j];
        }
    }

    belmanford(R, currencies);
    return 0;
}