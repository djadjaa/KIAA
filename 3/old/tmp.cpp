#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool isPrime(int x){
    if(x<=1)
        return false;
    for(int i=2; i*i<=x; i++){
        if(x%i==0)
            return false;
    }
    return true;
}

int main(){
    int x;
    cin >> x;
    cout << isPrime(x) << endl;
}