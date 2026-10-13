#include <bits/stdc++.h>
using namespace std;
int main(){
    int P; scanf("%d",&P);
    while(P--){
        int K,n; scanf("%d %d",&K,&n);
        vector<int> a(n); for(auto&x:a) scanf("%d",&x);
        vector<int> s=a; sort(s.begin(),s.end());
        int j=0;
        for(int i=0;i<n;i++) if(a[i]==s[j]) j++;
        printf("%d %d\n",K,n-j);
    }
}
