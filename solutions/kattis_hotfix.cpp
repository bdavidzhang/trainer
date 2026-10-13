#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){
    static char buf[1000005];
    if(scanf("%1000001s",buf)!=1) return 0;
    int n=strlen(buf);
    vector<int> sa(n), x(n), y(n), c(max(n,128)+1);
    {
        int m=128;
        for(int i=0;i<m;i++) c[i]=0;
        for(int i=0;i<n;i++) c[x[i]=buf[i]]++;
        for(int i=1;i<m;i++) c[i]+=c[i-1];
        for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
        for(int k=1;;k<<=1){
            int p=0;
            for(int i=n-k;i<n;i++) y[p++]=i;
            for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
            for(int i=0;i<m;i++) c[i]=0;
            for(int i=0;i<n;i++) c[x[i]]++;
            for(int i=1;i<m;i++) c[i]+=c[i-1];
            for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
            swap(x,y);
            p=1; x[sa[0]]=0;
            for(int i=1;i<n;i++){
                int a=sa[i-1], b=sa[i];
                bool same = y[a]==y[b] && ((a+k<n?y[a+k]:-1)==(b+k<n?y[b+k]:-1));
                x[b]= same? p-1 : p++;
            }
            if(p>=n) break;
            m=p;
        }
    }
    // x = rank
    vector<int>& rk=x;
    for(int i=0;i<n;i++) rk[sa[i]]=i;
    vector<int> h(n+1,0); // h[r]=lcp(sa[r-1],sa[r]), h[0]=h[n]=0
    {
        int k=0;
        for(int i=0;i<n;i++){
            if(rk[i]==0){k=0;continue;}
            int j=sa[rk[i]-1];
            while(i+k<n&&j+k<n&&buf[i+k]==buf[j+k]) k++;
            h[rk[i]]=k;
            if(k) k--;
        }
    }
    // letters
    vector<long long> diff(n+2,0), cnt(n+2,0);
    for(int i=0;i<n;i++){
        int l=h[rk[i]];
        long long w=n-i-l;
        diff[i]+=w; diff[i+l]-=w; cnt[i+l]++;
    }
    ull res[128]; memset(res,0,sizeof res);
    {
        long long d=0, cc=0;
        for(int p=0;p<n;p++){
            d+=diff[p]; cc+=cnt[p];
            res[(int)buf[p]] += (ull)d + (ull)cc*(ull)(n-p);
        }
    }
    // histogram of occurrence counts
    vector<long long> H(n+2,0);
    for(int r=0;r<n;r++){
        int len=n-sa[r];
        int mxl=max(h[r],h[r+1]);
        H[1]+=len-mxl;
    }
    {
        vector<pair<int,int>> st; // (lcp, left)
        for(int r=1;r<=n;r++){
            int left=r-1;
            while(!st.empty()&&st.back().first>h[r]){
                int hv=st.back().first, lb=st.back().second; st.pop_back();
                int par=max(h[r], st.empty()?0:st.back().first);
                H[r-lb]+=hv-par;
                left=lb;
            }
            if(h[r]>0 && (st.empty()||st.back().first<h[r])) st.push_back({h[r],left});
        }
    }
    for(int k=1;k<=n;k++) if(H[k]){
        int t=k; while(t){ res['0'+t%10]+=H[k]; t/=10; }
    }
    for(int ch=33;ch<127;ch++) if(res[ch]) printf("%c %llu\n",ch,res[ch]);
}
