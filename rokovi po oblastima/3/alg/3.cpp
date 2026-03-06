#include <bits/stdc++.h>

using namespace std;

long long nzd(long long a, long long b){
    while(b!=0){
        long long tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

long long stepen(long long a, long long n, long long mod){
    long long s=1;
    while(n>0){
        if((n&1)==0){
            a = ((long long)a * (long long)a)%mod;
            n = n>>1;
        }
        else{
            s = ((long long)s*(long long)a)%mod;
            n--;
        }
    }
    return s;
}

long long ojler(long long n){
    long long pr = n;
    for(long long d=2; d*d<=n; d++){
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
    long long a, n;
    long long k;
    cin >> a >> n >> k;
    if(nzd(a,n)!=1){
        cout << -1 << endl;
    }else{
        //tada redukujemo stepen k mod phi(n)
        long long phi = ojler(n);
        k %= phi;
        if(k==0)
            k = phi;
        long long res = stepen(a%n,k,n);
        cout << res << endl;
    }

    return 0;
}