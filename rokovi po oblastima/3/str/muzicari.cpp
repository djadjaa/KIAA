#include<bits/stdc++.h>
using namespace std;

void izracunajLPS(string &pattern, vector<int>&lps){
    int m = pattern.size();
    lps[0] = 0;
    int j=0;
    for(int i=1; i<m; i++){
        while(j>0 && pattern[i]!=pattern[j])
            j = lps[j-1];
        if(pattern[i]==pattern[j])
            j++;
        lps[i] = j;
    }
}

int kmp(string &pattern,string &text){
    int cntr=0;
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);
    izracunajLPS(pattern,lps);
    int j=0;
    for(int i=0; i<n; i++){
        while(j>0 && text[i]!=pattern[j])
            j=lps[j-1];
        if(text[i]==pattern[j])
            j++;
        if(j==m){
            cntr++;
            j = lps[j-1];
        }
    }
    return cntr;
}

int main() {
    string riff1,riff2,pesma;
    cin >> riff1 >> riff2 >> pesma;
    int res1 = kmp(riff1,pesma);
    int res2 = kmp(riff2,pesma);

    if(res1 > res2)
        cout << 1 << endl;
    else if(res1 < res2)
        cout << 2 << endl;
    else
        cout << 0 << endl;

    return 0;
}