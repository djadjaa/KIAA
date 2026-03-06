/*
ideja je da idemo po svakom pomeraju i da poredimo sve karaktere
efikasnija implementacija bi bila preskakanje za br karaktera u sablonu
jer ako se poklapa prvi
*/

#include <iostream>
#include <string>
using namespace std;

int main(){
    string tekst,sablon;
    cin >> tekst >> sablon;
    const int n = tekst.size();
    const int m = sablon.size();
    /*
    naivna implementacija:
    for (int s = 0; s < n - m + 1; s++) {
        // pattern[0..m-1] == text[s..s+m-1]?
        for (int i = 0; i < m; i++) {
            if (pattern[i] != text[s + i]) {
                break;
            } else if (i == m - 1){
                cout << s << ' ';
            }
        }
    }

    zato sto se s pomera iskljucivo u spoljasnjoj petlji,ali ne u unutrasnjoj

    */

    int s = 0; //trenutni pomeraj
    while(s<n-m+1){ //proveravamo sve pomeraje gde sablon moze stati u tekst (s<=n-m)
        for(int i=0; i<m; i++){ //ide kroz sve karaktere sablona
            cout << sablon[i] << ' ' << tekst[s] << endl;
            if(sablon[i]!=tekst[s]){ //ako se karakter ne poklapa
                if(i==0) //neslaganje odmah na prvom karakteru
                    s++;
                break;
            }else if(i==m-1){ //ako smo stigli do poslednjeg karaktera obrasca i sve se poklapa
                cout << s-m+1 << ' ';//tada smo pronasli validan pomeraj
            }
            s++;
            cout << '(' << i << ',' << s << ')' << endl;
        }
    }

    return 0;
}