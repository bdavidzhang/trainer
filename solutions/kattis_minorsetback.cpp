#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);bool used[12]={0};
for(int i=0;i<n;i++){double f;scanf("%lf",&f);long long k=llround(12*log2(f/440.0));a[i]=((k%12)+12)%12;used[a[i]]=1;}
// index from A: A0 A#1 B2 C3 C#4 D5 D#6 E7 F8 F#9 G10 G#11
struct K{const char*name;vector<pair<int,const char*>> p;};
vector<K> ks={
{"G major",{{10,"G"},{0,"A"},{2,"B"},{3,"C"},{5,"D"},{7,"E"},{9,"F#"}}},
{"C major",{{3,"C"},{5,"D"},{7,"E"},{8,"F"},{10,"G"},{0,"A"},{2,"B"}}},
{"Eb major",{{6,"Eb"},{8,"F"},{10,"G"},{11,"Ab"},{1,"Bb"},{3,"C"},{5,"D"}}},
{"F# minor",{{9,"F#"},{11,"G#"},{0,"A"},{2,"B"},{4,"C#"},{5,"D"},{7,"E"}}},
{"G minor",{{10,"G"},{0,"A"},{1,"Bb"},{3,"C"},{5,"D"},{6,"Eb"},{8,"F"}}}};
int cnt=0,which=-1;
for(int k=0;k<5;k++){bool in[12]={0};for(auto&p:ks[k].p)in[p.first]=1;bool ok=1;for(int i=0;i<12;i++)if(used[i]&&!in[i])ok=0;if(ok){cnt++;which=k;}}
if(cnt!=1){puts("cannot determine key");return 0;}
const char* nm[12];for(auto&p:ks[which].p)nm[p.first]=p.second;
puts(ks[which].name);string out;for(int i=0;i<n;i++){out+=nm[a[i]];out+='\n';}fputs(out.c_str(),stdout);}
