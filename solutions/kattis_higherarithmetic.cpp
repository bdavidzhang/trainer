#include <bits/stdc++.h>
using namespace std;
// Optimal shape: product of groups; each number >=2 takes at most one 1, the k smallest take one;
// the remaining ones are split into groups of 3 (and 2s). Try every k.
int main(){
    int n;scanf("%d",&n);vector<int> b;int c1=0;
    for(int i=0;i<n;i++){int a;scanf("%d",&a);if(a==1)c1++;else b.push_back(a);}
    sort(b.begin(),b.end());int t=b.size();
    auto lf=[&](int r)->long double{
        if(r<=1)return 0;
        if(r%3==0)return (r/3)*logl(3.0L);
        if(r%3==1)return logl(4.0L)+((r-4)/3)*logl(3.0L);
        return logl(2.0L)+((r-2)/3)*logl(3.0L);
    };
    long double pre=0,best=-1;int bk=0;
    for(int k=0;k<=min(c1,t);k++){
        if(k>0)pre+=logl((long double)(b[k-1]+1)/b[k-1]);
        long double v=pre+lf(c1-k);
        if(v>best+1e-12L){best=v;bk=k;}
    }
    string out;
    auto add=[&](const string&s){if(!out.empty())out+='*';out+=s;};
    for(int i=0;i<t;i++){if(i<bk)add("("+to_string(b[i])+"+1)");else add(to_string(b[i]));}
    int r=c1-bk;
    if(r==1)add("1");
    else if(r>=2){
        int twos=0;if(r%3==1)twos=2;else if(r%3==2)twos=1;
        int threes=(r-2*twos)/3;
        for(int i=0;i<twos;i++)add("(1+1)");
        for(int i=0;i<threes;i++)add("(1+1+1)");
    }
    puts(out.c_str());
}
