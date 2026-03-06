/*uklanjanje artikulacionih tacaka*/

#include <iostream>
#include <vector>

using namespace std;

int discoveryTime=0; //Promenljiva koja predstavlja vreme koje se dodeljuje svakom od cvorova
vector<bool> posecen;
// Vektor koji cuva vremena posecivanja cvorova u DFS obilasku
vector<int> times; //(dolazna)
// Vektor koji cuva lower times za sve cvorove. Lower time je zapravo minamlna vrednost time-a za sve susedne cvorove cvora u
vector<int> lower_times; //(lowlink)
vector<int> roditelj;
vector<bool> artikulacioneTacke; //cuvamo da li su cvorovi artikulacione tacke
vector<vector<int>> listaSuseda;

//efikasnije su nam globalne promenljive nego da ih prosledjujemo kroz argumente fje
void dfsArtikTacke(int cvor){
    posecen[cvor] = true; //tekucem cvoru koji je posecen dodeljujemo vreme obilaska
    times[cvor] = discoveryTime++;
    int numChilds = 0; //broj dece trenutnog cvora
    lower_times[cvor] = times[cvor]; //i trenutno je on najmanji od svih njegovih vremena obilaska

    for(auto sused : listaSuseda[cvor]){
        if(posecen[sused]){
            if(sused!=roditelj[cvor])
                lower_times[cvor] = min(lower_times[cvor],times[sused]);
        }else{
            numChilds++;
            roditelj[sused] = cvor;
            dfsArtikTacke(sused);
            lower_times[cvor] = min(lower_times[cvor],lower_times[sused]);

            //ako cvor nije koren dfs drveta
            if(roditelj[cvor] !=-1 && lower_times[sused] >= times[cvor])
                artikulacioneTacke[cvor] = true;
        }
    }
    if(roditelj[cvor]==-1 && numChilds>1)
        artikulacioneTacke[cvor] = true;
}

int main(){

    int n, m; //br cvorova i br grana
    cin >> n >> m;

   listaSuseda.resize(n);
   posecen.resize(n, false);
   times.resize(n);
   lower_times.resize(n);
   roditelj.resize(n, -1); //za sad nemamo nijedan koren DFS drveta
   
   artikulacioneTacke.resize(n, false); //i nemamo nijednu artikulacionu tacku

   int u, v;
   for(int i = 0; i < m; i++){
      cin >> u >> v; //dodavanje cvorova i grana
      listaSuseda[u].push_back(v);
      listaSuseda[v].push_back(u);
   }

   for(int i = 0; i < n; i++)
      if(!posecen[i])
         dfsArtikTacke(i);

   int q, ind; //upiti 
   cin >> q;
   while(q--){
      cin >> ind;
      if(artikulacioneTacke[ind]){
        //koliko se grana brise uklanjanjem cvora
         cout << "Da " << listaSuseda[ind].size() << endl;
      } else {
         cout << "Ne" << endl;
      }
   }

    return 0;
}

/*
razlika izmedju mostova i artikulacionih tacaka je sto
se razmatra broj dece i da li je tekuci cvor koren dfs drveta (mora da bude potomak!!)
pritom najmanji discovery time suseda moze biti jednak discovery timeu tekuceg cvora
*/