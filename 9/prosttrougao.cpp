//Eratostenovo sito
#include <iostream>
#include <vector>

using namespace std;

vector<bool>EratostenovoSito(int n){
    vector<bool> prost(n+1,true);
    prost[0]=false; //2
    prost[1]=false; //3
    //korena slozenost
    for(int i=2; i*i<=n; i++){
        if(prost[i]){
            //kvadrat delioca:
            for(int j=i*i; j<=n; j+=i) //za sve kvadrate delioca znamo da nisu prosti
                prost[j] = false;
        }
    }
    return prost;
}
//cuvamo red i kolonu 
vector<pair<int,int>>trougao(const vector<bool>&prost, const int n){
    vector<pair<int,int>>res(n+1);
    long row=1, col=1;
    for(int i=2;i<=n; i++){
        //formiranje trougla, jasno nam je ako je kolona veca od reda da se resetuje na narednu kolonu i da idemo na naredni red
        if(row<col) {
            row++;
            col=1;
        }
        if(prost[i])
            res[i] = make_pair(row,col++);
    }
    return res;
}

int main(){

    int n,q;
    cin >> n >> q;
    auto prost = EratostenovoSito(n);
    auto rezultati = trougao(prost,n);

    while(q--){
        int num;
        cin >> num;
        if(!prost[num])
            cout << -1 << endl;
        else{
            auto [row,col] = rezultati[num];
            cout << row << ' ' << col << endl;
        }
    }

    return 0;
}