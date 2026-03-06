#include <bits/stdc++.h>

using namespace std;

int main(){

    /*
    ako bismo brojali decu u beskonacnost to je onda
    p+(s-1)
    inace ako ih stavimo u krug on mora da ima ogranicen br dece
    i kako ih brojimo od onog deteta od kog smo poceli imamo
    p+(s-1)%brdeceukrugu
    */
   int s,d,p;
   cin >> s >> d >> p;
   //p mod d+(s−1)mod d)mod d, тј. (p+(s−1)mod d)mod d, 
   cout << ((p+s-1)%d)%d << endl;

    return 0;
}