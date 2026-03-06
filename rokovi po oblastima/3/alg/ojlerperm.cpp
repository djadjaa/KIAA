#include <bits/stdc++.h>

using namespace std;

//umesto int ll

int ojler(int x){
    int pr=x;
    for(int d=2; d*d<=x; d++){
        if(x%d==0){
            pr = (pr/d)*(d-1);
            while(x%d==0)
                x/=d;
        }
    }
    if(x>1)
        pr = (pr/x)*(x-1);
    return pr;
}

bool permutacija(int x, int y){
    string s1 = to_string(x);
    string s2 = to_string(y);
    sort(begin(s1),end(s1));
    sort(begin(s2),end(s2));
    return s1 == s2;
}

int main(){
    int n;
    cin >> n;
    int cnt=0;
    while(n--){
        int x;
        cin >> x;
        //cout << ojler(x) << endl;
        if(permutacija(ojler(x),x))
            cnt++;
    }
    cout << cnt << endl;
    return 0;
}