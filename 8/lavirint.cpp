//ojlerov put i hierholzerov alg
/*ojlerov put je takav put gde se grana izmedju dva cvora obilazi tacno jednom
dakle svi cvorovi imaju jednak broj ulaznih i izlaznih grana

kod neusmerenih grafova tacno 0 ili 2 cvora imaju neparan stepen
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> ulazniStepeni;
    vector<int> izlazniStepeni;
    int pocetnicvor;
    int krajnjicvor;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        ulazniStepeni.resize(V,0);
        izlazniStepeni.resize(V,0);
        pocetnicvor = -1;
        krajnjicvor  =-1;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        izlazniStepeni[u]++;
        ulazniStepeni[v]++;
    }

    /*
    outdeg(u) = indeg(u) + 1
    indeg(v) = outdeg(v) + 1
    ovo mora da ispunjava Ojlerov put !!!
    */
    bool ojlerovPut(){
        for(int i=0; i<V; i++){
            //uslov koji ispunjava pocetni cvor
            if(izlazniStepeni[i] == ulazniStepeni[i]+1){
                //ako smo vec nasli pocetni cvor; ovaj uslov osigurava da ne postoje 2 ili vise pocetnih cvorova
                if(pocetnicvor!=-1)
                    return false;
                pocetnicvor = i;
            //uslov koji ispunjava krajnji cvor
            }else if(ulazniStepeni[i]==izlazniStepeni[i]+1){
                //medjutim ako smo ga pronasli u medjuvremenu
                if(krajnjicvor!=-1)
                    return false;
                krajnjicvor = i;
            }else if(ulazniStepeni[i]!=izlazniStepeni[i])
                return false;
        }
        return true;
    }

    void hierholzer(int cvor, vector<int>&ojlerovPut){
        while(izlazniStepeni[cvor]>0){
            int sused = susedi[cvor][0];
            susedi[cvor].erase(susedi[cvor].begin());
            izlazniStepeni[cvor]--;
            hierholzer(sused,ojlerovPut);
        }
        ojlerovPut.insert(ojlerovPut.begin(),cvor);
    }

    void pronadjiPut(int cvor){
        if(!ojlerovPut()){
            cout << "nemoguce\n";
            return;
        }
        vector<int> ojlerovPut;
        hierholzer(cvor,ojlerovPut);

        for(int cvor: ojlerovPut)
            cout << cvor << ' ';
        cout << '\n';
    }

    int pronadjiPocetak(){
        return pocetnicvor;
    }
};

int main(){

    int n, m;

   cin >> n >> m;

   Graph *G = new Graph(n);

   int u, v;
   for (int i = 0; i < m; i++) {
      cin >> u >> v;
      G->dodajGranu(u, v);
   }
//moramo ovako jer je pocetak pod private
   G->pronadjiPut(G->pronadjiPocetak());

   delete G;

    return 0;
}