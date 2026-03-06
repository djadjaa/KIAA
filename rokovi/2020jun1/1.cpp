//najduzi palindrom

#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    int x;
    cin >> s >> x;
    int n = s.size();
    string tmp = "$#";
    for(int i=0; i<n; i++){
        tmp += s[i];
        tmp+="#";
    }
    tmp+="@";
    int c=1, r=1;
    int mirror;
    vector<int> tmpvector(tmp.size());
    n = tmp.size();
    for(int i=1; i<tmp.size()-1; i++){
        mirror = 2*c-i;
        if(i<r)
            tmpvector[i] = min(r-i,tmpvector[mirror]);
        while(tmp[i+(tmpvector[i]+1)]==tmp[i-(tmpvector[i]+1)])
            tmpvector[i]++;
        if(i+tmpvector[i]>r){
            c=i;
            r=i+tmpvector[i];
        }
    }
    int maxlastlen =-1, centerindex = -1;
    for(int i=1; i<tmp.size()-1; i++){
        int len = tmpvector[i];
        //Beleži sve palindromske podstringove sa dužinom ≥ x, ali ne traži maksimum, već poslednji koji zadovoljava uslov.
        
        if(len>=x){
            maxlastlen = len;
            centerindex = (i-len)/2;
        }
    }
    if(maxlastlen==-1)
        cout << -1 << endl;
    else
        cout << maxlastlen << ' ' << s.substr(centerindex,maxlastlen) << endl;
    return 0;
}