#include <bits/stdc++.h>

using namespace std;

int main(){

    string haystack, needle;
    cin >> needle >> haystack;
    int n = haystack.size();
    int m = needle.size();
    vector<int> kmp(m,0);
    kmp[0]=0;
    
    /*DRUGI NACIN
    int i=0, j=0;
    while(i<m){
        if(needle[i]==needle[j]){
            kmp[i]=j+1;
            i++;
            j++;
        }
        else{
            if(j!=0)
                j = kmp[j-1];
            else{
                kmp[i]=0;
                i++;
            }
        }
    }*/
   int j = 0;

   for (int i = 1; i < m; i++) {
       while (j > 0 && needle[i] != needle[j])
           j = kmp[j - 1];
       if (needle[i] == needle[j])
           j++;
       kmp[i] = j;
   }

   int brPonavljanja = 0;
    j=0;
    for(int i=0; i<n; i++){
        while(j>0 && haystack[i]!=needle[j])
            j = kmp[j-1];
        if(haystack[i]==needle[j])
            j++;
        if(j==m){
            brPonavljanja++;
            j = kmp[j-1];
        }
    }
    cout << brPonavljanja << endl;
    return 0;
}