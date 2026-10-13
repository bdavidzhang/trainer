#include <bits/stdc++.h>
using namespace std;
const long long M=998244353;
long long pw(long long b,long long e){long long r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int main(){long long n,k,p;scanf("%lld %lld %lld",&n,&k,&p);
if(k*p>n){puts("1");return 0;}
long long a=n-k*p,b=n-p;long long f=1,fa=1,fb=1,fn=1;
for(long long i=1;i<=n;i++){f=f*i%M;if(i==a)fa=f;if(i==b)fb=f;}
fn=f;
// P(all disjoint)= n! * ((n-p)!)^k / ((n-kp)! * (n!)^k)
long long num=fn*pw(fb,k)%M;long long den=fa*pw(fn,k)%M;
long long q=num*pw(den,M-2)%M;printf("%lld\n",((1-q)%M+M)%M);}
