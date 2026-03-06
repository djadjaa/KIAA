/*
gruba sila: racunanje nzda i u ojlerovoj za svaki elem provera
da li je nzd == 1

kako znamo da je:
- ojlerova fja multiplikativna
- fi(p) = p-1 za prost br p
- fi(p^k) = p^k - p^(k-1) = p^k((p-1)/p) je broj brojeva uzajamno prostih
sa brojem p^k 
(jedini koji nisu uzajamno prosti su p,2p,3p...p^(k-1)*p... i njih ima p^(k-1))

rastavimo broj n takav da bude fi(p^k)*...*fi(p^km) pri cemu su ovi p^ki prosti cinioci broja n

dakle broj trazenih bice upravo  n * proizvod(1 - 1/p) za sve proste brojeve p koji dele broj n
*/

#include <iostream>

using namespace std;

int main(){
    
    int n;
    cin >> n;
    int d=2; //delilac(2 je prvi prost br)
    int proizvod = n; 
    while(d*d<=n){
        if(n%d==0){ //d je prost delilac
            proizvod = (proizvod/d)*(d-1);
            while(n%d==0) //uklanjamo sve d-ojke, odn sva pojavljvianja prostog faktora
                n/=d;
        }
        d++; //sledeci kandidat
    }
    if(n>1)
        proizvod = (proizvod/n)*(n-1);
    cout << proizvod << endl;
    return 0;
}