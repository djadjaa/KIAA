#include <bits/stdc++.h>

using namespace std;

int main(){

    string s;
    cin >> s;
    string tmpreverse = s;
    string tmp = tmpreverse;
    reverse(tmpreverse.begin(), tmpreverse.end());
    tmp += "#";
    tmp += tmpreverse;
    int n = tmp.size();

    vector<int> kmp(n);

    kmp[0] = 0;
    int i=1, j=0;
    for(int i=1; i<n; i++){
        while(j>0 && tmp[i]!=tmp[j])
            j = kmp[j-1];
        if(tmp[i]==tmp[j])
            j++;
        kmp[i]=j;
    }

    string sufiks = s.substr(kmp[n-1]);
    reverse(sufiks.begin(),sufiks.end());

    sufiks+= s;
    cout << sufiks.size() << endl;
    return 0;
}