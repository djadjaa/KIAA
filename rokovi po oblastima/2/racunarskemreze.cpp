#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int brKompjutera;
    int brKablova;
    long long cenaServer;
    long long cenaKabl;
    vector<vector<int>> susedi;

    public:
    Graph(int brKompjutera, int brKablova, long long cenaServer, long long cenaKabl){
        this->brKompjutera = brKompjutera;
        this->brKablova = brKablova;
        this->cenaServer = cenaServer;
        this->cenaKabl = cenaKabl;
        susedi.resize(brKompjutera);
    }

    //dodavanje veza izmedju kompjutera
    void dodajGranu(int kompjuter1, int kompjuter2){
        susedi[kompjuter1].push_back(kompjuter2);
        susedi[kompjuter2].push_back(kompjuter1);
    }

    //koliko mreza imamo
    int pronadjiBrojKomponenti(){
        vector<int> komponente(brKompjutera,0);
        int brojKomponenti=0;
        for(int kompjuter=0; kompjuter<brKompjutera; kompjuter++){
            if(komponente[kompjuter]==0)
                komponentePovezanosti(kompjuter,komponente,++brojKomponenti);
        }
        return brojKomponenti;
    }

    //dodajemo kompjutere u jednu komponentu
    void komponentePovezanosti(int kompjuter, vector<int>&komponente, int komponentaID){
        komponente[kompjuter] = komponentaID;
        for(int susednikomp:susedi[kompjuter]){
            if(komponente[susednikomp]==0)
                komponentePovezanosti(susednikomp,komponente,komponentaID);
        }
    }

    int minCena(){
        if(cenaServer<=cenaKabl)
            return brKompjutera*cenaServer;
        else{
            int brojGrupaKompjutera = pronadjiBrojKomponenti();
            int brojServera = brojGrupaKompjutera;
            int brojOstalih = brKompjutera-brojServera;
            return brojServera*cenaServer + brojOstalih*cenaKabl;
        }
    }
};

int main(){


    return 0;
}