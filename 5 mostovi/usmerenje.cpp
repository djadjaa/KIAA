/*
usmerenje je moguce akko ne postoji most izmedju dva cvora:

most - grana koja kada se ukloni inkrementiraju se komponente grafova
artikulaciona tacka - tacka koja -||-
*/

#include <iostream>
#include <vector>

using namespace std;

//ovog puta necemo koristiti klase:

void dfsMostovi(int cvor, int &discoveryTime,vector<bool> &posecen, vector<int>&dolazna, vector<int>&lowlink, vector<int>&roditelj, vector<pair<int,int>> &mostovi, vector<vector<int>>&listaSuseda){
    posecen[cvor] = true;
    dolazna[cvor] = discoveryTime++;
    lowlink[cvor] = dolazna[cvor];

    for(auto sused:listaSuseda[cvor]){
        if(posecen[sused]){
            //ako grana ne vodi ka roditelju datog cvora
            if(sused!=roditelj[cvor]){
                
                //tada postoji veza unazad ka ranijem cvoru

                /*
                if(dolazna[sused]<lowlink[cvor])
                    lowlink[cvor] = dolazna[sused];*/
                //ako je manji discoverytime suseda od najmanjeg discoveryTimea
                lowlink[cvor] = min(lowlink[cvor],dolazna[sused]);
            }
        }else{
            roditelj[sused] = cvor;
            //pokrecemo iz suseda dfs
            dfsMostovi(sused, discoveryTime, posecen, dolazna, 
                lowlink, roditelj, mostovi, listaSuseda);

            //ako je manji discoverytime suseda od discoverytime cvora:
            /*if(lowlink[sused] < lowlink[cvor])
                lowlink[cvor] = lowlink[sused];*/
            lowlink[cvor] = min(lowlink[cvor],lowlink[sused]);

            //ako je discovery time tekuceg cvora manji od najmanjeg discoveryTimea za sused
            //da li je grana most
            if(lowlink[sused]>dolazna[cvor])
                mostovi.emplace_back(cvor,sused);
        }
    }
}

int main(){

    int n,m;
    cin >> n >> m;
    vector<vector<int>> listaSuseda(n);

    int u, v;
    for(int i=0; i<m; i++){
        cin >> u >> v;
        listaSuseda[u-1].push_back(v-1);
        listaSuseda[v-1].push_back(u-1);
    }

    int discoveryTime =0; //brojac vremena posete cvorova
    vector<bool> posecen(n);
    vector<int> roditelj(n); //cuva cvor iz kojeg smo u dfsu prvi put dosli do cvora u
    vector<int>lowlink(n); //cuva najmanji discoveryTime cvora kojem se moze doci iz cvora u
    vector<int>dolazna(n); //niz discoveryTimeova

    vector<pair<int,int>> mostovi;
    dfsMostovi(0, discoveryTime, posecen, dolazna, 
        lowlink, roditelj, mostovi, listaSuseda);

    if(mostovi.size() > 0)
        cout << 0 << endl;
    else{
        for(int cvor=0; cvor<n; cvor++){
            for(int sused:listaSuseda[cvor]){
                if(cvor > sused)
                    continue;
                int u = cvor, v = sused;
                //grana mora biti usmerena od pretka ka potomku, predak ima manji discoveryTime
                if(dolazna[u]>dolazna[v])
                    swap(u,v);
                //usmeravanje grane:
                if(roditelj[v]==u)
                    cout << u+1 << ' ' << v+1 << endl;
                else
                    cout << v+1 << ' ' << u+1 << endl;
            }
        }
    }
    return 0;
}