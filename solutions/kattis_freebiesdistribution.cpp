#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static char buf[1<<25];
int main(){
    size_t len=0; string data; 
    { size_t r; while((r=fread(buf,1,sizeof(buf),stdin))>0) data.append(buf,r); }
    const char*p=data.c_str();
    auto rd=[&]()->ll{while(*p&&(*p<'0'||*p>'9'))p++;ll x=0;while(*p>='0'&&*p<='9'){x=x*10+(*p-'0');p++;}return x;};
    (void)len;
    int m=rd(); vector<ll> b(m); for(auto&x:b)x=rd();
    sort(b.begin(),b.end());
    ll X=rd(),Y=rd(); int n=rd();
    vector<int> cnt(m,0);
    for(int i=0;i<n;i++){
        ll r=rd(),c=rd();
        int j=lower_bound(b.begin(),b.end(),c)-b.begin(); // first booth >= c
        int best;
        if(j==m) best=m-1;
        else if(j==0) best=0;
        else best=(c-b[j-1]<=b[j]-c)?j-1:j; // tie -> leftmost
        ll t=r+llabs(c-b[best]);
        if(t<=X+llabs(Y-b[best])) cnt[best]++;
    }
    printf("%d\n",*min_element(cnt.begin(),cnt.end()));
}
