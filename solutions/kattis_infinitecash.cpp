#include <bits/stdc++.h>
using namespace std;
typedef vector<int> B; // bits, LSB first, no leading zeros
B rd(){ string s; cin>>s; B b; for(int i=s.size()-1;i>=0;i--) b.push_back(s[i]-'0'); while(!b.empty()&&b.back()==0) b.pop_back(); return b; }
int main(){
    B s=rd(), d=rd(), m=rd();
    long long dv;
    if(d.size()>20) dv=LLONG_MAX/4; else { dv=0; for(int i=d.size()-1;i>=0;i--) dv=dv*2+d[i]; }
    B x=m; long long base=0;
    while(true){
        long long bl=x.size();
        if(bl<=dv-1){
            long long ans=base+bl;
            string o; if(ans==0) o="0"; while(ans){ o.push_back('0'+(ans&1)); ans>>=1; }
            reverse(o.begin(),o.end()); cout<<o<<endl; return 0;
        }
        if((long long)s.size()>=dv){ cout<<"Infinite money!"<<endl; return 0; }
        // x = (x>>dv)+s
        B y(x.begin()+dv,x.end());
        B z; int c=0;
        for(size_t i=0;i<max(y.size(),s.size())||c;i++){
            int t=c; if(i<y.size()) t+=y[i]; if(i<s.size()) t+=s[i];
            z.push_back(t&1); c=t>>1;
        }
        x=z; base+=dv;
    }
}
