#include <bits/stdc++.h>

using namespace std;

long long stepen(long long a, long long n, long long mod){
    long long s = 1;
    while(n>0){
        if((n&1)==0){
            a = ((long long)(a*a))%mod;
            n = n>>1;
        }else{
            s = ((long long)(s*a))%mod;
            n--;
        }
    }
    return s;
}

int main(){
    long long a,n,mod;
    cin >> a >> n >> mod;
    cout << stepen(a%mod,n,mod) << endl;

    return 0;
}