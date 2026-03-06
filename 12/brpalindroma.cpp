//Manacerov alg - daje najveću dužinu palindroma sa centrom u svakoj poziciji.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){

    string s;

    cin >> s;
    //$ start, # za odvajanje karaktera, @ za kraj
    string tmp = "$";
    //cuvamo duzinu originalnog stringa
    int n = s.size();

    for(int i=0; i<n; i++){
        tmp+="#";
        tmp+=s[i];
    }

    tmp+="@";

    int c = 1, r=1; //C predstavlja centar (sredinu) trenutog palindroma koji razmatramo, a R njegov desni kraj
    vector<int> tmpvector(tmp.size());
    int mirror;
    //dimenzija novog stringa sa granicama
    n=tmp.size();
    for(int i=1; i<tmp.size()-1; i++){
        mirror = 2*c-i;  //ovo je indeks simetricne tacke i u odnosu na c
        /*
        podniz [C - d, C + d] je palindrom za neki d
        svaka pozicija unutar tog palindroma ima simetričnu poziciju oko centra

        tmpvector nam sluzi da izracunamo duzinu palindroma oko pozicije mirror
        
        ako smo unutar trenutno poznatog palindroma, onda palindrom oko i
        ima bar onoliko duzine koliko mu je simetricna tacka dopusta
        ali ne sme preci desnu granicu
        */
       if(i<r)
            tmpvector[i] = min(r-i,tmpvector[mirror]);
        /*
        tmp vector trenutno sadrzi poluprecnik palindroma oko pozicije i
        karakterdesno == karakterlevo od trenutnog palindroma
        */
        while (tmp[i + (tmpvector[i] + 1)] == tmp[i - (tmpvector[i] + 1)]) {
            tmpvector[i]++; //povecavamo radijus dokle imamo palindrom
        }
        if (i + tmpvector[i] > r) {
            c = i;
            r = i + tmpvector[i];
        }
    }
    int size=0;
    for(int x : tmpvector)
        size += x/2; //delimo sa dva zbog umetnutih karaktera
    cout << size << endl;
    return 0;
}