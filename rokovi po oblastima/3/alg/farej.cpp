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

    int N;
    cin >> N;
    int sum=1;
    for(int d=1; d<=N; d++)
        sum+=ojler(d);
    cout << sum << endl;

    return 0;
}