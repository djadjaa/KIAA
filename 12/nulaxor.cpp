//Z algoritam  - on omogucava da brzo pronadjemo sve pozicije gde se string javlja kao prefiks
//Ako se nađe celo poklapanje (z[i] == m), znači da postoji rotacija
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
z[i] meri koliko se string s poklapa sa sobom, ali počevši od i.
l i r čuvaju najdesniji segment poklapanja koji smo otkrili, da bismo preskakali nepotrebna poređenja.

*/
vector<int> izracunajZ(const string &s){
    int n = s.size();
    vector<int> z(n);
    //cuvamo segment u kojem znamo da se string poklapa sa prefiksom - to je prozor koji se pomera kroz string
    int l=0, r=0;
    for(int i=1; i<n; i++){
        //ako je pozicija unutar segmenta:
        if(i<=r)
        /*biramo da li je vrednost:
        -maksimalno sto mozemo garantovati da se uklapa
        -koliko se poklapa ako krenemo od i
        */
            z[i] = min(r-i+1,z[i-l]);
        /*
        preskacemo proveru karaktera od pozicije i do pozicije z[i]
        dokle god se karakteri poklapaju, povecavamo vrednost z[i]
        */
        while(i+z[i]<n && s[z[i]]==s[i+z[i]])
            z[i]++;
        //Ako je novo poklapanje duže nego trenutni segment [l, r], proširujemo segment
        if(i+z[i]-1>r){
            l=i;
            r = i+z[i]-1;
        }
    }
    return z;
}

int main(){

    string s,t; //s uzorak t tekst
    cin >> s >> t;
    //svaka rotacija od t podstaje podniz od t1
    //dakle dovoljno je proveriti gde se s pojavljuje u t1 kao podstring duzine s
    string t1 = t+t.substr(0,t.size()-1);
    //svaka pozicija u t1 gde se s poklapa bice vidljiva u Z nizu
    string s1 = s+"#"+t1;

    vector<int> z = izracunajZ(s1);
    int counter = 0;

   for (int x : z) {
      if (x == s.size()) {
         counter++;
      }
   }

    cout << counter << "\n";

    return 0;
}