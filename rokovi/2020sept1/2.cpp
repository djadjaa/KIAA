#include <bits/stdc++.h>
using namespace std;

int main(){

    string s;
    cin >> s;
    int x;
    cin >> x;

    string tmp = "$#";
    int n = s.size();
    for(int i=0; i<n; i++){
        tmp+= s[i];
        tmp+="#";
    }
    tmp+="@";

    int c=1,r=1;
    vector<int> tmpvector(tmp.size());
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
    int index=-1,minlen=INT_MAX;
    for(int i=0; i<n; i++){
        int len = tmpvector[i];
        int reallen;

        if(tmp[i]=='#')
            reallen = len/2*2; //paran
        else
            reallen = len/2*2+1;//neparan

        if(reallen >= x && reallen < minlen){
            minlen = reallen;
            index = (i-tmpvector[i])/2;
        }
    }
    cout << (index != -1 ? s.substr(index,minlen) : "nema")  << endl;
    return 0;
}