#include <bits/stdc++.h>

using namespace std;

int mod(int a, int m){
    return (m+a%m)%m;
}

int add(int a, int b, int m){
    return mod(mod(a,m)+mod(b,m),m);
}

int mul(int a, int b, int m){
    return mod(mod(a,b)*mod(b,m),m);
}

int pmp(int a, int b, int c){
    return c*(a%b);
}

long long prosireniNZD(long long a, long long b, long long &s, long long &t){
    long long r0 = a, r1 = b, s0 = 1, s1 = 0, t0 = 0, t1 = 1;
    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp = r0;
        r0 = r1;
        r1 = tmp-q*r1;

        tmp = s0;
        s0 = s1;
        s1 = tmp-q*s1;

        tmp = t0;
        t0 = t1;
        t1 = tmp-q*t1;
    }
    s = s0, t = t0;
    return r0;
}

bool kineskaTeorema(long long a1, long long n1, long long a2, long long n2, long long &r){
    long long m1, m2;
    long long d = prosireniNZD(n1,n2,m1,m2);
    if(a1%d!=a2%d)
        return false;
    // resenje je (a1*m2*(n2/d) + a2*m1*(n1/d)) % (n1*n2/d)
    /*
     лопта упада у рупу ако и само ако бројеви rx и ry 
     имају исти остатак при дељењу са d.
    */
    //kod realnih vrednosti (n1*n2/d) nece imati konzistentan rezultat
    long long n = (n1/d)*n2; //stoga moramo ovako
    long long proizvod1 = mul(a1,m2,n);
    long long proizvod2 = mul(a2,m1,n);
    long long proizvodfinal1 = pmp(proizvod1,n1,n2/d);
    long long proizvodfinal2 = pmp(proizvod2,n2,n1/d);
    long long sum = add(proizvodfinal1,proizvodfinal2,n);
    if(sum<0)
        sum+=n;
    return true;
}

int main(){
    int m,n,x0,y0,vx,vy;
    cin >> m >> n >> x0 >> y0 >> vx >> vy;
    if(vx==0 && vy==0)
        //loptica se ne krece
        cout << -1 << endl;
    //loptica se krece vertikalno
    else if(vx==0){
        //nemoguce kretanje
        if(x0!=0 && x0!=m)
            cout << -1 << endl;
        //ide vertikalno ka gornjoj ivici stola gde je y koordinata n
        else if(vy>0)
            cout << x0 << ' ' << n << endl;
        //ide horizontalno ka donjoj ivici stola
        else
            cout << x0 << ' ' << 0 << endl;
    }
    //loptica se krece horizontalno
    else if(vy==0){
        //analogno kao i za vx==0
        if(y0!=0 && y0!=n)
            cout << -1 << endl;
        else if(vx>0)
            cout << m << ' ' << y0 << endl;
        else
            cout << 0 << ' ' << y0 << endl;
    }else{ //dijagonalno kretanje
        //kretanje do ivice; kako su kretanja periodicna stavljamo mod
        //rx i ry su nam pocetne udaljenosti do najblize ivice

        //ako se ispaljuje nadesno, bice m-x, inace samo x
        int rx = (vx>0 ? (m-x0) : x0) % m;
        //analogno ako se ispaljuje nadole bice n-y inace samo y
        int ry = (vy>0 ? (n-y0) : y0) % n;

        //kretanje do rupe -> do (0,0), (x,0), (0,y), (x,y)

        //r nam je ukupno rastojanje do same rupe
        long long r;
        if(!kineskaTeorema(rx,m,ry,n,r))
            cout << -1 << endl;
        else{
            //horizontalni polozaj rupe
            int ivica_hor; //indikator da li je leva(0) ili desna(1)
            if(x0==0)
                ivica_hor = 0;
            else if(x0 == m)
                ivica_hor = 1;
            else
                ivica_hor = vx < 0 ? 0 : 1;
            
            //vertikalni polozaj rupe
            int ivica_ver;
            if(y0==0)
                ivica_ver = 0;
            else if(y0==n)
                ivica_ver = 1;
            else
                ivica_ver = vy < 0 ? 0 : 1;

            //broj prelaza
            //r-rx je rastojanje koje loptica predje nakon prve ivice,
            //kada podelimo sa sirinom dobijamo koliko je loptica presla celu sirinu

            long long broj_prelaza_x = (r - rx) / m;
            long long broj_prelaza_y = (r - ry) / n;

            //koordinate; parnost odredjuje da li je levo desno gore ili dole
            int rupax = (ivica_hor + broj_prelaza_x) % 2 == 0 ? 0 : m;
            int rupay = (ivica_ver + broj_prelaza_y) % 2 == 0 ? 0 : n;
            cout << rupax << ' ' << rupay << endl;
        }

    }
    return 0;
}