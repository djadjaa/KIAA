#include <bits/stdc++.h>

using namespace std;

int main(){
    int k,m,n;
    cin >> k >> m >> n;

    const int N = 1e6;
    vector<int> delitelji(N + 1, 0);

    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i)
            delitelji[j]++;

    vector<long long> prefixSum(N+1,0);
    for(int i=1; i<=N; i++){
        prefixSum[i] = prefixSum[i-1];
        if(delitelji[i]>=k && i<=m)
            prefixSum[i] +=i;
    }


    while(n--){
        int a,b;
        cin >> a >> b;
        //nijedan br veci od m ne ulazi u zbir
        if(a>m)
            a = m;
        if(b>m)
            b = m;
        if(a>b)
            cout << 0 << endl;
        else
            cout << prefixSum[b] - prefixSum[a-1] << endl;
    }

    return 0;
}