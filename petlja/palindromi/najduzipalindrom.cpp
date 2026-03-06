/*
primena dinamickog programiranja:

ako smo dosli izvan granice vracamo 0
ako su nam indeksi jednaki, imamo jedan karakter
ako su nam karakteri jednaki, onda nam je rezultat za 2 veci + rek poziv
 jer imamo 2 karaktera koje smo razmatrali
inace posmatramo levi ili desni podniz preko max fje
*/
#include <bits/stdc++.h>

using namespace std;

int najduziPalindrom(string &s, int l, int d,vector<vector<int>>&memo){
    if(memo[l][d]!=-1)
        return memo[l][d];
    if(l>d)
        return memo[l][d]= 0;
    if(l==d)
        return memo[l][d] = 1;
    if(s[l]==s[d])
        return memo[l][d] = 2+najduziPalindrom(s,l+1,d-1,memo);
    //inace
    return memo[l][d] = max(najduziPalindrom(s,l,d-1,memo),najduziPalindrom(s,l+1,d,memo));
}

int main(){
    string s;
    cin >> s;
    vector<vector<int>> memo(s.length(),vector<int>(s.length(),-1));
    cout << najduziPalindrom(s,0,s.length()-1,memo) << endl;

    return 0;
}