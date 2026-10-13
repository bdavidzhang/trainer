#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const u64 MOD=(1ULL<<61)-1;
u64 mul(u64 a,u64 b){return (u64)((unsigned __int128)a*b%MOD);}
u64 pw(u64 a,u64 e){u64 r=1;while(e){if(e&1)r=mul(r,a);a=mul(a,a);e>>=1;}return r;}
int main(){
    int n;string line;getline(cin,line);n=stoi(line);
    map<string,int>id;vector<vector<pair<int,int>>> rows;
    for(int i=0;i<n;i++){
        getline(cin,line);
        istringstream ss(line);string tok;int side=1,sign=1;
        vector<pair<int,int>> r;
        while(ss>>tok){
            if(tok=="="){side=-1;sign=1;}
            else if(tok=="*")sign=1;
            else if(tok=="/")sign=-1;
            else if(tok=="1"){}
            else{ if(!id.count(tok)){int k=id.size();id[tok]=k;} r.push_back({id[tok],side*sign}); }
        }
        rows.push_back(r);
    }
    int k=id.size();
    vector<vector<u64>> A(n,vector<u64>(k,0));
    for(int i=0;i<n;i++){vector<long long>e(k,0);for(auto&p:rows[i])e[p.first]+=p.second;
        for(int j=0;j<k;j++)A[i][j]=e[j]>=0?(u64)e[j]:MOD-(u64)(-e[j]);}
    int r=0;
    for(int c=0;c<k&&r<n;c++){
        int p=-1;for(int i=r;i<n;i++)if(A[i][c]){p=i;break;}
        if(p<0)continue;
        swap(A[p],A[r]);
        u64 inv=pw(A[r][c],MOD-2);
        for(int j=0;j<k;j++)A[r][j]=mul(A[r][j],inv);
        for(int i=0;i<n;i++)if(i!=r&&A[i][c]){u64 f=A[i][c];
            for(int j=0;j<k;j++){u64 t=mul(f,A[r][j]);A[i][j]=A[i][j]>=t?A[i][j]-t:A[i][j]+MOD-t;}}
        r++;
    }
    bool bad=false;
    for(int i=0;i<r;i++){int cnt=0;for(int j=0;j<k;j++)if(A[i][j])cnt++;if(cnt==1)bad=true;}
    puts(bad?"invalid":"valid");
}
