#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){
    vector<int> a;
    {
        string s((istreambuf_iterator<char>(cin)),istreambuf_iterator<char>());
        size_t i=0;
        while(i<s.size()){
            if(isdigit((unsigned char)s[i])){
                int v=0;
                while(i<s.size()&&isdigit((unsigned char)s[i])){v=v*10+(s[i]-'0');i++;}
                a.push_back(v);
            }else i++;
        }
    }
    int n=a.size();
    mt19937_64 rng(712367123ULL);
    ull r[256];
    for(auto&x:r)x=rng();
    vector<pair<ull,int>> v;
    for(int L=min(256,n/2);L>=64;L--){
        int w=n-L+1;
        vector<ull> h(w);
        ull cur=0;
        for(int i=0;i<L;i++)cur+=r[a[i]];
        h[0]=cur;
        for(int i=1;i<w;i++){cur+=r[a[i+L-1]]-r[a[i-1]];h[i]=cur;}
        v.clear();
        for(int i=0;i<w;i++)v.push_back({h[i],i});
        sort(v.begin(),v.end());
        for(int i=0;i+L<w;i++){
            auto it=lower_bound(v.begin(),v.end(),make_pair(h[i],i+L));
            if(it!=v.end()&&it->first==h[i]){
                printf("%d\n%d\n%d\n",L,i,it->second);
                return 0;
            }
        }
    }
    puts("no key");
}
