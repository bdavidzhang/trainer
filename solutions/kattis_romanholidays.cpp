#include <bits/stdc++.h>
using namespace std;
int main(){const char*o[]={"","I","II","III","IV","V","VI","VII","VIII","IX"};const char*t[]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};const char*h[]={"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
vector<string> R(1000);vector<string> small,large;
for(int i=1;i<1000;i++){R[i]=string(h[i/100])+t[i/10%10]+o[i%10];if(R[i]<"M")small.push_back(R[i]);else large.push_back(R[i]);}
sort(small.begin(),small.end());sort(large.begin(),large.end());long long A=small.size(),B=large.size();
int n;scanf("%d",&n);while(n--){long long x;scanf("%lld",&x);long long k=x/1000;int r=x%1000;
 if(r==0)printf("%lld\n",k*(A+1));
 else if(R[r]<"M"){long long rk=lower_bound(small.begin(),small.end(),R[r])-small.begin()+1;printf("%lld\n",k*(A+1)+rk);}
 else{long long gt=large.end()-upper_bound(large.begin(),large.end(),R[r]);printf("%lld\n",-(k*B+gt+1));}}}
