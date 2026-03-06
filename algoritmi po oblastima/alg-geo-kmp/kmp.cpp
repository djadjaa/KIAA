#include <bits/stdc++.h>

using namespace std;

void izracunajLPS(string &sifra, vector<int>&lps){
    int m = sifra.size();
    lps[0] = 0;
    int j=0;
    for(int i=1; i<m; i++){
        while(j>0 && sifra[i]!=sifra[j])
            j = lps[j-1];
        if(sifra[i]==sifra[j])
            j++;
        lps[i] = j;
    }
}

int kmp(string &tekst, string &sifra){
    int cntr=0;
    int n = tekst.size();
    int m = sifra.size();
    int j=0;
    vector<int> lps(m);
    izracunajLPS(sifra,lps);
    for(int i=0; i<n; i++){
        while(j>0 && tekst[i]!=sifra[j])
            j = lps[j-1];
        if(tekst[i]==sifra[j])
            j++;
        if(j==m){
            cntr++;
            j = lps[j-1];
        }
    }
    return cntr;
}

int main(){
    string tekst, sifra;
    cin >> tekst >> sifra;
    cout << kmp(tekst,sifra) << endl;

    return 0;
}