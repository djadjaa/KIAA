/*
na ulazu imamo najpre n reči a zatim q upita za
koje moramo proveriti koje sve reči počinju pod tim prefiksom

čuvaćemo listu koja će sadržati sve reči koja ima kao prefiks
svoj ključ -> mapa gde je ključ prefiks, a vrednost lista reči koje se poklapaju
sa prefiksom
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(){

    int n,q; //br reci i br upita
    cin >> n >> q;

    map<string, vector<string>> autocomplete; //mapa gde je ključ prefiks, a vrednost lista reči koje se poklapaju sa prefiksom

    //unosimo reci
    for(int i=0; i<n; i++){ //(O(n))
        string wrd;
        cin >> wrd;

        //ubacujemo prefiks u mapu i njegovu vrednost odnosno rec koja se poklapa sa prefiksom
        for(int i=0; i<=wrd.size(); i++){//O(duzina_najvece_reci := M)
            autocomplete[wrd.substr(0,i)].push_back(wrd); //O(log(br_prefiksa_recnika := N)
        }
    }
    //ispitujemo:
    for(int i=0; i<q; i++){//O(q)
        string upit;
        cin >> upit;
        for(auto wrd:autocomplete[upit]){
            cout << wrd << ' ';
        }
        cout << endl;
    }
    return 0;
}

//kompletna vremenska slozenost O(nMlogN + q)