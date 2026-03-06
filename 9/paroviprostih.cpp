/*gruba sila
bool prost(int n)
    {
        if (n < 2)
            return false;
        for (int d = 2; d*d <= n; d++)
            if (n % d == 0)
                return false;
        return true;
    }

drugi nacin eratostenovo sito i dupla petlja kroz brojeve

efikasniji: eratostenovo sito i posmatranje iskljucivo neparnog zbira
*/

#include <iostream>
#include <vector>

using namespace std;

vector<bool> eratostenovoSito(int n){
    vector<bool>prost(n+1,true);
    prost[0]=false;
    prost[1]=false;
    for(int i=2; i*i<=n; i++){
        if(prost[i]){
            for(int j=i*i; j<=n; j+=i){
                prost[j] = false;
            }
        }
    }
    return prost;
}

int main(){

    int n;
    cin >> n;
    vector<bool>prost = eratostenovoSito(n);
    int brParova=0;
    /*
    fiksiracemo p=2 zato sto zbir dva neparna broja daju paran zbir
    a to nam ne ide u prilog stoga cemo uzeti jedan jedini parni prost
    broj a to je 2 (jer svaki broj pomnozen sa 2 nije prost)
    */
    int p=2;
    //mora da vazi p<q i p+q<=n
    for(int q=p+1; p+q<=n; q++){
        if(prost[q] && prost[p+q])
            brParova++;
    }
    cout << brParova << endl;

    return 0;
}