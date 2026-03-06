/*
data su dva riff-a i pesma u kojoj se sadrže, 
odrediti koji je frekventniji unutar pesme.

pesma = "ABCDABCDAB"
riff1 = "AB"
riff2 = "CD"
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> LPS(const string &s){
    int m  = s.size();
    vector<int> kmp(m,0);
    //kmp[0] = 0;
    int j=0;
    for(int i=1; i<m; i++){
        while(j>0 && s[i]!=s[j])
            j = kmp[j-1];
        if(s[i]==s[j])
            j++;
        kmp[i]=j;
    }
    return kmp;
}

int KMP(const string &s, const string &sifra){
    int n = s.size();
    int m = sifra.size();
    if(m==0)
        return 0;
    vector<int> kmp = LPS(sifra);
    int j=0;
    int res=0;
    for(int i=0; i<n; i++){
        while(j>0 && s[i]!=sifra[j])
            j = kmp[j-1];
        if(s[i]==sifra[j])
            j++;
        if(j==m){
            res++;
            j = kmp[j-1];
        }
    }
    return res;
}

int main(){

    string pesma,riff1, riff2;
    cin >> pesma >> riff1 >> riff2;
    
    int res1 = KMP(pesma,riff1);
    int res2 = KMP(pesma,riff2);

    cout << (res1 > res2 ? "prvi" : "drugi") << endl;

    return 0;
}