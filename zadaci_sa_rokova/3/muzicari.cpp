#include <bits/stdc++.h>

using namespace std;

void izracunajLPS(string &sifra, vector<int> &lps){
    int n = sifra.size();
    lps[0] = 0;
    int j=0;
    for(int i=1; i<n; i++){
        while(j>0 && sifra[i]!=sifra[j])
            j = lps[j-1];
        if(sifra[i]==sifra[j])
            j++;
        lps[i] = j;
    }
}

int kmp(string &sifra, string &str){
    int numOcc=0;
    int m = sifra.size();
    int n = str.size();
    vector<int> lps(m);
    izracunajLPS(sifra,lps);
    int j=0;
    //i prolazi kroz string !!! j prolazi kroz substring
    for(int i=0; i<n; i++){
        while(j>0 && sifra[j]!=str[i])
            j = lps[j-1];
        if(sifra[j]==str[i])
            j++;
        if(j==m){
            numOcc++;
            j = lps[j-1];
        }
    }
    return numOcc;
}

int main(){
    string riff1,riff2,pesma;
    cin >> riff1 >> riff2 >> pesma;
    int res1 = kmp(riff1,pesma);
    int res2 = kmp(riff2,pesma);
    cout << (res1 > res2 ? '1' : '2') << endl;
    return 0;
}