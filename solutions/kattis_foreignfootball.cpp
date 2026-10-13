#include <bits/stdc++.h>
using namespace std;
static char buf[1000005];
int main(){
    int n; scanf("%d",&n);
    vector<vector<string>> T(n,vector<string>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ scanf("%s",buf); T[i][j]=buf; }
    if(n==2){
        const string &A=T[0][1],&B=T[1][0];
        if(A.size()!=B.size()){ puts("NONE"); return 0; }
        int L=A.size();
        string S=B+"#"+A+A;
        int N=S.size(); vector<int> z(N,0);
        for(int i=1,l=0,r=0;i<N;i++){
            if(i<r) z[i]=min(r-i,z[i-l]);
            while(i+z[i]<N&&S[z[i]]==S[i+z[i]]) z[i]++;
            if(i+z[i]>r){l=i;r=i+z[i];}
        }
        int c=0,kk=-1;
        for(int k=1;k<L;k++) if(z[L+1+k]>=L){c++;kk=k;}
        if(c==0) puts("NONE");
        else if(c>1) puts("MANY");
        else { puts("UNIQUE"); printf("%s\n%s\n",A.substr(0,kk).c_str(),A.substr(kk).c_str()); }
        return 0;
    }
    long long a=T[0][1].size(), b=T[0][2].size(), c=T[1][2].size();
    long long l1x2=a+b-c;
    if(l1x2<=0||l1x2%2){ puts("NONE"); return 0; }
    long long l1=l1x2/2;
    vector<string> s(n);
    if((long long)T[0][1].size()<=l1){ puts("NONE"); return 0; }
    s[0]=T[0][1].substr(0,l1);
    for(int j=1;j<n;j++){
        if((long long)T[0][j].size()<=l1){ puts("NONE"); return 0; }
        s[j]=T[0][j].substr(l1);
    }
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(i!=j){
        const string&t=T[i][j];
        if(t.size()!=s[i].size()+s[j].size()){ puts("NONE"); return 0; }
        if(t.compare(0,s[i].size(),s[i])!=0||t.compare(s[i].size(),s[j].size(),s[j])!=0){ puts("NONE"); return 0; }
    }
    puts("UNIQUE");
    for(int i=0;i<n;i++) printf("%s\n",s[i].c_str());
}
