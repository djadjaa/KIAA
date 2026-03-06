/*
w = x s = t x
w - najduzi prefiks sufiks
x - string sa svim periodama osim poslednjeg perioda
s - ostatak poslednje periode (druga polovina)
t - perioda

w = "abacabacabacab"
p = "abac"
n = 3
p1 = "ab" - poslednji nepotpuni deo
p2 = "ac" - ostatak poslednjeg perioda

x = p^(n-1)p1 = "abac" + "abac" + "ab" = "abacabacab"
s = p2p1 = "ac" + "ab" = "acab"
t = p = "abac"

znamo da je w = p^n + p1
važi: |x| ≥ |s|  jer x sadrzi sve pune periode osim poslednjeg dela
kako je w = x s
sledi |w| = |x| + |s|
iz  |x| ≥ |s| imamo |x| ≥ |w| - |x|   =>   2*|x| ≥ |w|
*/

#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    cin >> s;
    int n = s.size();
    vector<int> kmp(n,0);
    for(int i=1; i<n; i++){
        int j = kmp[i-1];
        while(j>0 && s[i]!=s[j])
            j = kmp[j-1];
        if(s[i]==s[j])
            j++;
        kmp[i]=j;
    }

    int perioda = kmp[n-1]; //duzina najduzeg prefiks sufiksa
    if(perioda > 0 && 2*perioda>=n) //2*|x| ≥ |w|
        cout << "da\n";
    else
        cout << "ne\n";

    return 0;
}