#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int len=s.size();
    if(len%2==0){puts("-1");return 0;}
    int m=(len-1)/2;
    vector<int> c(len); for(int i=0;i<len;i++) c[i]=s[len-1-i]-'0';
    // mod 2: a_i = c_{2i} mod 2
    vector<int> p(m+1); for(int i=0;i<=m;i++) p[i]=c[2*i]%2;
    // mod 5 square roots
    vector<vector<int>> qs;
    int low=-1; for(int i=0;i<len;i++) if(c[i]%5){low=i;break;}
    if(low<0) qs.push_back(vector<int>(m+1,0));
    else if(low%2==0){
        int j=low/2, cv=c[low]%5;
        for(int sq=1;sq<5;sq++) if(sq*sq%5==cv){
            vector<int> q(m+1,0); q[j]=sq;
            int inv=1; while((2*sq*inv)%5!=1) inv++;
            for(int k=1;j+k<=m;k++){
                int sum=0; for(int i=1;i<k;i++) sum+=q[j+i]*q[j+k-i];
                q[j+k]=(((c[2*j+k]-sum)%5+5)%5)*inv%5;
            }
            qs.push_back(q);
        }
    }
    string best="";
    for(auto&q:qs){
        vector<int> a(m+1);
        for(int i=0;i<=m;i++){ for(int d=0;d<10;d++) if(d%2==p[i]&&d%5==q[i]) a[i]=d; }
        if(a[m]==0) continue;
        bool ok=true;
        for(int k=0;k<len&&ok;k++){int sum=0; for(int i=0;i<=m;i++){int j=k-i; if(j>=0&&j<=m) sum+=a[i]*a[j];} if(sum%10!=c[k]) ok=false;}
        if(!ok) continue;
        string t; for(int i=m;i>=0;i--) t+=char('0'+a[i]);
        if(best.empty()||t<best) best=t;
    }
    puts(best.empty()?"-1":best.c_str());
}
