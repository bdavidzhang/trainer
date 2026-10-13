#include <bits/stdc++.h>
using namespace std;
const long long M=1001113;
long long A[101][101];
int main(){A[1][0]=1;for(int n=2;n<=100;n++)for(int k=0;k<n;k++)A[n][k]=((k+1)*A[n-1][k]+(k?(n-k)*A[n-1][k-1]:0))%M;
    int P;scanf("%d",&P);while(P--){int K,n,v;scanf("%d %d %d",&K,&n,&v);printf("%d %lld\n",K,A[n][v]);}}
