#include <bits/stdc++.h>
using namespace std;
static char buf[1<<25];
int main(){
    size_t len=0; vector<char> in; { size_t r; while((r=fread(buf,1,sizeof(buf),stdin))>0) in.insert(in.end(),buf,buf+r);} in.push_back(0);
    const char*p=in.data();
    auto rd=[&]()->long long{while(*p&&(*p<'0'||*p>'9'))p++;long long v=0;while(*p>='0'&&*p<='9')v=v*10+(*p++-'0');return v;};
    (void)len;
    int m=rd(),n=rd(); vector<int>a(m); long long S=0; for(auto&x:a){x=rd();S+=x;}
    string out; out.reserve((size_t)n*4);
    unordered_map<long long,bool> memo;
    for(int i=0;i<n;i++){long long q=rd(); bool ok=false;
        if(q<=S){ long long T=S-q; // need a contiguous block (possibly empty) of sum T to leave behind
            if(T==0)ok=true; else {
                auto it=memo.find(T);
                if(it!=memo.end())ok=it->second; else {
                    long long cur=0;int l=0;
                    for(int r=0;r<m&&!ok;r++){cur+=a[r];while(cur>T)cur-=a[l++];if(cur==T)ok=true;}
                    memo[T]=ok;
                }
            }
        }
        out+= ok?"Yes\n":"No\n";
    }
    fwrite(out.data(),1,out.size(),stdout);
}
