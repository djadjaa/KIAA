#include <bits/stdc++.h>
using namespace std;

int ojler(int n){
    int pr = n;
    for(int d=2; d*d<=n; d++){
        if(n%d==0){
            pr = (pr/d)*(d-1);
            while(n%d==0)
                n/=d;
        }
    }
    if(n>1)
        pr = (pr/n)*(n-1);
    return pr;
}

int main(){

    int n;
    cin >> n;
    cout << ojler(n) << endl;
    return 0;
}