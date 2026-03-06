//Koliko ima različitih razlomaka oblika a/b < 1, 1 ≤ b ≤ n, gcd(a,b)=1.

#include <bits/stdc++.h>
using namespace std;

int ojler(int n){
    int pr=n;
    for(int d=2; d*d<=n;d++){
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
    int res=0;
    for(int i=1; i<=n; i++){
        res += ojler(i);
    }
    cout << res << endl;

    return 0;
}