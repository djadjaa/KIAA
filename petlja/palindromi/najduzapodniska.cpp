#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    cin >> s;
    string tmp = "$#";
    int n = s.size();
    for(int i=0; i<n; i++){
        tmp+=s[i];
        tmp+= "#";
    }
    tmp+="@";

    int c = 1, r = 1;
    vector<int> tmpvector (tmp.size());
    int mirror;
    n = tmp.size();
    for(int i=1; i<tmp.size()-1; i++){
        mirror = 2*c-i;
        if(i<r)
            tmpvector[i] = min(r-i, tmpvector[mirror]);
        while(tmp[i+(tmpvector[i]+1)]==tmp[i-(tmpvector[i]+1)])
            tmpvector[i]++;
        if(i+tmpvector[i]>r){
            c = i;
            r = i+tmpvector[i];
        }
    }
    int maxlen = 0, centerindex = 0;
    for(int i=1; i<tmp.size()-1; i++){
        if(tmpvector[i]>maxlen){
            maxlen = tmpvector[i];
            centerindex = i;
        }
    }
    int start = (centerindex-maxlen-1)/2;
    cout << s.substr(start,maxlen) << endl;
    return 0;
}