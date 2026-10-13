#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> v(n+1),p(n+1);
    for(int i=1;i<=n;i++) scanf("%d %d",&v[i],&p[i]);
    vector<multiset<int>*> s(n+1,nullptr);
    size_t ans=0;
    for(int i=n;i>=1;i--){
        if(!s[i]) s[i]=new multiset<int>();
        auto it=s[i]->lower_bound(v[i]);
        if(it!=s[i]->end()) s[i]->erase(it);
        s[i]->insert(v[i]);
        if(i==1){ans=s[i]->size();break;}
        int q=p[i];
        if(!s[q]) s[q]=s[i];
        else{
            if(s[q]->size()<s[i]->size()) swap(s[q],s[i]);
            for(int t:*s[i]) s[q]->insert(t);
            delete s[i];
        }
    }
    printf("%zu\n",ans);
}
