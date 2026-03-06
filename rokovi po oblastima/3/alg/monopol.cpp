#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, presao1, presao2;
    cin >> n >> presao1 >> presao2;
    int src = presao1%n;
    int dest = presao2%n;
    cout << (dest >= src ? dest-src : dest-src+n) << endl;
    return 0;
}