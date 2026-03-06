/*
Covek tuce bubnjeve levom rukom svakih a sekundi a desnom rukom svakih b sekundi. Naci trenutak za koji ce se najmanje razlikovati udaljenost udaraca levom i desnom. Ispisati koja je to razlika i trenutak prvog i drugog udarca. Dato je n ovakvih upita. Slozenost O(nlog(ab)) a prostorna O(1).
Npr za 2 i 5 treba ispisati 1 4 5 tj najmanja razlika je 1 i desava se kada levom lupi u trenutku 4 a desnom u trenutku 5 (a moglo je da se ispise i 1 5 6)

Primer:
4
2 5
7 4
6 3
9 9

Ispis:
1 4 5
1 7 8
3 3 6
9 0 9
*/


#include <bits/stdc++.h>

using namespace std;

long long prosireniEuklid(long long a, long long b, long long &s, long long &t){
    long long r0=a, r1=b, s0=1, s1=0, t0=0, t1=1;

    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp = r0;
        r0 = r1;
        r1 = tmp-q*r1;

        tmp = s0;
        s0 =s1;
        s1 = tmp-q*s1;

        tmp = t0;
        t0 = t1;
        t1 = tmp-q*t1;
    }
    s=s0;
    t=t0;
    return r0;
}

int main(){

    int n;
    cin >> n;
    while(n--){
        long long a,b;
        cin >> a >> b;
        long long x,y;
        long long minimalnaRazlika = prosireniEuklid(a,b,x,y);
        //left je i*a a right je j*b
        //radi ispisa na standardnom izlazu uzimamo min i max
        long long prviUdaracTrenutak = min(abs(x*a),abs(y*b));
        long long drugiUdaracTrenutak = max(abs(x*a),abs(y*b));
        cout << minimalnaRazlika << ' ' << prviUdaracTrenutak << ' ' << drugiUdaracTrenutak << endl;
    }

    return 0;
}