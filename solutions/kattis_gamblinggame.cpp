#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull C[40][40];
int main(){
    for(int i=0;i<40;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+(j<=i-1?C[i-1][j]:0);}
    int m,n,p;cin>>m>>n>>p;
    if(n==0){ puts(p==0?"1/1":"0/1"); return 0; }
    if(p<n){puts("0/1");return 0;}
    // first p-1 balls (as a set) from the other m-2 numbers must cover the other n-1 squares
    ull cnt=0;
    for(int j=0;j<=n-1;j++){
        int rest=p-1-(n-1)-j; // from m-2n free numbers
        if(rest<0||rest>m-2*n) continue;
        cnt+=C[n-1][j]*(1ULL<<(n-1-j))*C[m-2*n][rest];
    }
    ull num=2ULL*n*cnt, den=(ull)m*C[m-1][p-1];
    if(num==0){puts("0/1");return 0;}
    ull g=std::gcd(num,den);
    printf("%llu/%llu\n",num/g,den/g);
}
