/*
kondenzovani graf “sažima” sve cikluse/komponente jake povezanosti u jedan čvor i pretvara graf u aciklican

Odredjujemo komponente jake povezanosti
zatim formiramo kondenzovani graf gde su komponente jake povezanosti čvorovi, a grane postoje ako postoji veza između komponenti.
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
    vector<vector<int>> susediReverse;
    vector<bool> posecen;
    //redosled čvorova po završetku DFS-a (finish time) u prvom prolazu DFS-a
    //koji određuje redosled obrade čvorova u obrnutom grafu
    stack<int> odlaznaEnumeracija; //radimo sa komponentama jake povezanosti
    vector<int> komponente;
    int brojKomponente = 0;

    void dfsDirect(int cvor){
        posecen[cvor] = true;
        for(int sused: susedi[cvor]){
            if(!posecen[sused])
                dfsDirect(sused);
        }
        //svrha ovog DFSA je odrediti reodsled zavrsetka cvorova
        //ovaj stek ce kasnije odrediti redosled obrade cvorova u obratnom grafu
        odlaznaEnumeracija.push(cvor);
    }

    void dfsReverse(int cvor, vector<bool>&posecen){
        posecen[cvor] = true;
        komponente[cvor] = brojKomponente;
        for(int sused:susediReverse[cvor]){
            if(!posecen[sused])
                dfsReverse(sused,posecen);
        }
        //svrha ovog dfsa je pronaci jednu komponentu jake povezanosti
    }

    void nadjiKomponente(){
        fill(posecen.begin(),posecen.end(),false);
        for(int i=0; i<V; i++){
            if(!posecen[i]){
                dfsDirect(i);
            }
        }
        fill(posecen.begin(),posecen.end(),false);
        while(!odlaznaEnumeracija.empty()){
            int cvor = odlaznaEnumeracija.top();
            odlaznaEnumeracija.pop();
            if(!posecen[cvor]){
                dfsReverse(cvor,posecen);
                brojKomponente++;
            }
        }
    }

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        susediReverse.resize(V);
        posecen.resize(V,false);
        komponente.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susediReverse[v].push_back(u);
    }

    //formiranje kondenzovanog grafa:
    int brojPrekidaca(){
        nadjiKomponente();

        vector<int> kondenzovani(brojKomponente,0);

        for(int i=0; i<V; i++){
            for(auto j:susedi[i]){
                if(komponente[i]!=komponente[j])
                    kondenzovani[komponente[j]]++;
            }
        }

        int res=0;
        /*dovoljno je upaliti sve svetiljke sa ulaznim stepenom 0
        jer će se kroz grane aktivirati sve ostale svetiljke.
        ukoliko za proizvoljan čvor koji ima bar jedan senzor pratimo grane u nazad,
        u nekom trenutku ćemo naići na neki čvor koji ima ulazni stepen 0,*/
        for(int i=0; i<brojKomponente; i++)
            if(kondenzovani[i]==0)
                res++;
        return res;
    }
};

int main(){
    int N, M, u, v;

    cin >> N >> M;
    Graph *G = new Graph(N);
    for(int i = 0; i < M; i++) {
       cin >> u >> v;
       G->dodajGranu(u-1, v-1); 
    }
 
    cout << G->brojPrekidaca() << endl;
 
    delete G;

    return 0;
}