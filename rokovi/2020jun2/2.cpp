#include <bits/stdc++.h>
using namespace std;

/*
int gcd(int a, int b) {
    if (b == 0) return a;  // baza rekurzije
    return gcd(b, a % b);  // rekurzivni poziv
}
*/
int gcd3(int a, int b, int c){
    return gcd(a,gcd(b,c));
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    const int M = 1e6;

    vector<int> brDelilaca(M+1,0);
    for(int i=1; i<=M; i++){
        for(int j=i; j<=M; j+=i)
            brDelilaca[j]++;
    }

    while(q--){
        int a,b,c;
        cin >> a >> b >> c;
        int res = gcd3(a,b,c);
        cout << brDelilaca[res] << endl;
    }

    return 0;
}