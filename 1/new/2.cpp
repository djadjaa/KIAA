/*
na ulazu imamo broj elemenata niza a i br upita sledeceg tipa:
u/s br1 br2
u slucaju da imamo u -> na poziciju br1 postavimo broj br2 u niz

npr 3 1 4 1 5 9 2 6
u 2 5: 3 1 5 1 ....

inace -> sabiramo elemente od pozicije br1 do br2

npr 3 1 4 1 5 9 2 6
s 0 4: 3+1+4+1+5=14
*/

#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n,q;
    cin >> n >> q;
    vector <int> a(n);
    for(int i=0; i<n; i++) //O(n)
        cin >> a[i];
    for(int i=0; i<q; i++){//O(q)
        string upit;
        cin >> upit;
        if(upit == "u"){ //i ovako mozemo proveriti za prvi karakter
            int poz, num;
            cin >> poz >> num;
            a[poz] = num;
        }else if(upit == "s"){
            int l,r;
            cin >> l >> r;
            int sum = 0;
            for(int i=l; i<=r; i++){ //u najgorem slucaju O(n) jer postoji mogucnost da saberemo sve elem niza
                sum += a[i];
            }
            cout << sum << endl;
        }
    }
}

//kompletna slozenost O(n+q), u najgorem slucaju O(n+nq)