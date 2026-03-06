//ojler fermaova formula

#include <bits/stdc++.h>
using namespace std;

//nzd==1;
int nzd(int a, int b){
    while(b!=0){
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

//stepen po modulu:
int stepen(int a, int n, int mod){
    int rez=1;
    while(n>0){
        //ako je paran
        if((n&1)==0){
            a = ((long long)a*(long long)a)%mod;
            n = n>>1; //delimo sa 2
        }
        else{
            rez = ((long long)rez*(long long)a)%mod;
            n--;
        }
    }
    return rez;
}

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

    int a,n;
    cin >> a >> n;
    //radimo ojler od n
    //a^ojler(n)
    if(nzd(a,n)!=1)
        cout << -1 << endl;
    else
        cout << stepen(a%n, ojler(n), n) << endl;

    return 0;
}