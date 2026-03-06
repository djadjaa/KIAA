#include <bits/stdc++.h>
using  namespace std;

int main(){

    string s;
    cin >> s;
    int n = s.size();
    string novi = s+s;
    vector<int> kmp(n,0);
    int brPonavljanja =0;
    for(int i=1; i<n; i++){
        int j = kmp[i-1];
        while(j>0 && s[i]!=s[j])
            j = kmp[j-1];
        if(s[i]==s[j])
            j++;
        kmp[i]=j;
    }
    int j=0;
    //kako smo duplirali nisku, idemo do 2*n-1
    for(int i=0; i<2*n-1; i++){
        while(j>0 && novi[i]!=s[j])
            j = kmp[j-1];
        if(novi[i]==s[j])
            j++;
        if(j==n){
            int start = i-n+1;
            if(start < n)
                brPonavljanja++;
            j = kmp[j-1];
        }
    }
    cout << brPonavljanja << endl;
    return 0;
}