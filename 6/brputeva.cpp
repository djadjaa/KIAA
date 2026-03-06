/*
prosti put je put koji ne posećuje nijedan čvor više od jednom
cvorovi su medjusobno razliciti

kada imamo aciklican graf po prirodi je svaki put prost jer nema ciklusa te se ne mozemo vratiti u isti cvor

ovde brojimo takve puteve
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;
    vector<int>pozUTopSort;
    vector<pair<int,int>> dodateGrane;
    stack<int> s; //DFS

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
    }

    void DFS(int cvor){
        posecen[cvor] = true;
        for(int sused : susedi[cvor]){
            if(!posecen[sused])
                DFS(sused);
        }
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

            pozUTopSort.push_back(tekucicvor);
        }
    }

    /*
    funkcija vraca 1 ako prosti put formira iskljucivo jedan cvor
    funkcija vraca 0 ako u putu postoje dva čvora gde je pozicija prethodnog u topološkom sortiranju veća od pozicije sledeceg
    inace formiraju sumu tih cvorova
    */

    //inace upotreba dinamickog programiranja; rezultat cuvamo u nizu:
   int brojProstihPuteva(const int tekucicvor, const int krajnji, const vector<int> &pozUTopSort, vector<int> &memo){
        if(memo[tekucicvor]!=-1)
            return memo[tekucicvor];
        if(pozUTopSort[tekucicvor] == pozUTopSort[krajnji])
            return memo[tekucicvor] = 1;
        if(pozUTopSort[tekucicvor]>pozUTopSort[krajnji])
            return memo[tekucicvor] = 0;
        
        //inace formiramo sumu cvorova koji cine prosti put
        memo[tekucicvor]=0;
        for(int sused : susedi[tekucicvor]){
            if(pozUTopSort[tekucicvor]<=pozUTopSort[sused])
                memo[tekucicvor]+=brojProstihPuteva(sused,krajnji,pozUTopSort,memo);
        }
        return memo[tekucicvor];
   }

   int brojProstihPutevaFinal(int s, int t){
        kanovAlg();
        vector<int> pozicije(V);
        for(int i=0; i<pozUTopSort.size(); i++)
            pozicije[pozUTopSort[i]] = i;
        vector<int> memo(V,-1); //vektor dinamickog programiranja
        return brojProstihPuteva(s,t,pozicije,memo);
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

   int s, t;

   cin >> s >> t;

   cout << G->brojProstihPutevaFinal(s, t) << endl;

    return 0;
}