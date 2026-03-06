/*isti zadatak samo preko prefiksnih suma

za upit u cim se azurira vrednost na nekoj poziciji, azurirace se 
i prefiksna suma
za upit s racunamo zbir segmenta tako sto oduzmemo prefiksne sume na odredjenim
intervalima:
suma = (suma_od_0_do_r) - (suma_od_0_do_l-1) (ako je l>0)
     = suma_od_0_do_r (ako je l=0 (jer onda je to elem na nultoj poziciji))
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){

    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i=0; i<n; i++) //O(n)
        cin >> a[i];
    vector<int> p(n); //niz sa parcijalnim sumama
    partial_sum(a.cbegin(),a.cend(),p.begin()); //O(n)
    /*
    begin()
    -Vraća mutable (promenljiv) iterator na prvi element vektora.
    -Omogućava čitanje i modifikaciju elemenata na koje iterator pokazuje.

    cbegin()
    -Vraća constant (read-only) iterator.
    -Omogućava samo čitanje elemenata – ne može se koristiti za modifikaciju
    */
    for(int i=0; i<q; i++){ //O(q)
        string upit;
        cin >> upit;
        if(upit == "u"){
            int poz,vr;
            a[poz] = vr;
            //azuriranje parcijalne sume
            partial_sum(a.cbegin(),a.cend(),p.begin()); //O(n)
        }else if(upit == "s"){
            int l, r;
            cin >> l >> r;
            cout << (l==0 ? p[r] : p[r]-p[l-1]) << endl; //O(1)
        }
    }

    return 0;
}
//optimizovanije za nijansu, i dalje je slozenost u najgorem slucaju O(nq)