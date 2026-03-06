/*
komponente jake povezanosti - komponente grafa ciji su lowlinkovi cvorova
odnosno minimalna vremena obilaska grafa medjusobno jednaki
vazno je da je graf usmeren i da mogu postojati oba pravca iz jednog u drugi cvor
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<vector<int>> susediReverse;
    vector<bool>posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        susediReverse.resize(V);
        posecen.resize(V,false);
    }

    void dodajGranu(bool usmeren,int u,int v){
        susedi[u].push_back(v);
        susediReverse[v].push_back(u);
        if(!usmeren){
            susedi[v].push_back(u);
            susediReverse[u].push_back(v);
        }
    }

    void dfsDirect(int korenicvor){
        stack<int> s;
        s.push(korenicvor);
        posecen[korenicvor] = true;

        int tekucicvor;
        while(!s.empty()){
            tekucicvor = s.top();
            s.pop();

            for(int sused : susedi[tekucicvor]){
                if(!posecen[sused]){
                    s.push(sused);
                    posecen[sused] = true;
                }
            }
        }
    }
    void dfsReverse(int korenicvor){
        stack<int> s;
        s.push(korenicvor);
        posecen[korenicvor] = true;

        int tekucicvor;
        while(!s.empty()){
            tekucicvor = s.top();
            s.pop();

            for(int sused : susediReverse[tekucicvor]){
                if(!posecen[sused]){
                    s.push(sused);
                    posecen[sused] =true;
                }
            }
        }
    }

    bool KosarajuAlg(int korenicvor){
        dfsDirect(korenicvor);

        for(int i=0; i<V; i++)
            if(posecen[i]==false)
                return false;
        //svi čvorovi se resetuju na „neposećen“ status u jednom potezu.
        fill(posecen.begin(), posecen.end(), false);

        dfsReverse(korenicvor);

        for(int i=0; i<V; i++)
            if(posecen[i]==false)
                return false;
        
        return true;
    }
};

int main(){

    //br upita
    int q;
   cin >> q;

   while(q--){

      int broj_cvorova, number_of_edges;
      cin >> broj_cvorova >> number_of_edges;

      Graph *G = new Graph(broj_cvorova);

      int u, v, je_usmeren;
      for (int i = 0; i < number_of_edges; i++) {
        //1 - jednosmerna, 2 - dvosmerna
         cin >> je_usmeren >> u >> v;
         if(je_usmeren == 1)
            G->dodajGranu(true, u-1, v-1);
         else
            G->dodajGranu(false, u-1, v-1);   
      }

      if(G->KosarajuAlg(0))
         cout << "Da" << endl;
      else
         cout << "Ne" << endl;

      delete G;
   }

    return 0;
}