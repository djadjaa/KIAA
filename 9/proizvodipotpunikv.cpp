/*
Da bi broj bio potpun kvadrat, svaki prost činilac treba da se javlja paran broj puta
Umesto da racunamo sve proste cinioce cuvacemo samo informaciju koliko puta se prost cinilac pojavljuje

ako cinilac nije u skupu , ubacimo ga jer se pojavljuje jednom
ako jeste izbacimo ga, sto znaci da se pojavio jos jednom i to paran br puta

-> za prazan skup imamo da je broj potpun kvadrat inace nije

pritom, primenicemo eratostenovo sito radi efiakasnije provere parnosti
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

vector<int> prosti;
unordered_set<long long> cinioci;

void prost(int n){
    vector<bool>prost(n+1,true);
    int i=2;
    while(i*i<=(n+1)){
        if(prost[i]){
            prosti.push_back(i);
            for(int j=i*i; j<=n; j+=i)
                prost[j] = false;
        }
        i++;
    }
    for(int j=i; j<=n; j++){
        if(prost[j])
            prosti.push_back(j);
    }
}

void azurirajSkup(long long c){
    auto it = cinioci.find(c);
    if(it!=cinioci.end()) //ako se vec nalazi cinilac u skupu
        cinioci.erase(it);
    else //inace ga dodajemo
        cinioci.insert(c);
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    int K = 1e9;
    prost((int)ceil(sqrt(K)));//dobijemo info o svim prostim brojevima
    for(int i=0; i<n; i++){
        long long x;
        cin >> x;
        for(auto p:prosti){
            while(x%p==0){//dokle god nije prost broj
                x/=p;
                azurirajSkup(p);//ubacujemo prosti cinilac
            }
            if(x<p*p)//ako smo dosli do korena
                break;
        }
        if(x>1)
            azurirajSkup(x);
        cout << (cinioci.empty() ? "da" : "ne") << '\n';
    }

    return 0;
}