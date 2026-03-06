#include <bits/stdc++.h>

using namespace std;

int main(){

    string haystack, needle;
    cin >> haystack >> needle;
    int n = haystack.size();
    int m = needle.size();
    vector<int> kmp(m,0);
    kmp[0] = 0;
    int i=1, j=0;
    while(i<m){
        if(needle[i]==needle[j]){
            kmp[i]=j+1;
            i++;
            j++;
        }else{
            if(j!=0)
                j = kmp[j-1];
            else{
                kmp[i]=0;
                i++;
            }
        }
    }

    j=0; //pozicija u podstringu
    int res = -1;
    for(i=0; i<n; i++){
        while(j>0 && haystack[i]!=needle[j])
            j = kmp[j-1];
        if(haystack[i]==needle[j])
            j++;
        if(j==m){
            res = i-m+1;
            j = kmp[j-1];
            break;
        }
    }
    cout << res << endl;
    return 0;
}