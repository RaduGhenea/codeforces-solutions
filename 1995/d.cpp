#include <bits/stdc++.h>
using namespace std;
ifstream fein("date.in");
ofstream g("date.out");
#define NMAX 10000
#define INF 100010

// #define cin fein
// #define cout g

int c, n, k, t, fullmask, windows[(1<<18)+1];
bitset<((1<<18)+1)> useless;
string s;

int nr_bits(int mask) {
    return (__builtin_popcount(mask));
}

void mark_useless_submasks(int mask) {
    for (unsigned s = mask; s; s = (s - 1) & mask) {
        useless[s]=1;
    }
}

void process_windows(string charset) {
    int window=0;
    vector<int> f(c+1, 0);

    for(int i=0;i<min(n, k);i++) {
        int id=charset[i]-'A';
        f[id]++;
        window |= (1<<id);
    }
    windows[window]=1;
    for(int i=k;i<n;i++) {
        int old_id=charset[i-k]-'A';
        f[old_id]--;
        if(f[old_id]==0) {
            window ^= (1<<old_id);
        }
        int new_id=charset[i]-'A';
        f[new_id]++;
        window |= (1<<new_id);
        windows[window]=1;
    }
    int last_id=charset[n-1]-'A';
    windows[(1<<last_id)]=1;
}

void solve_string() {
    int res=INF;
    fullmask=(1<<c)-1;
    fill(windows, windows+fullmask+1, 0);
    useless=0;

    process_windows(s);
    for(int mask=1;mask<=fullmask;mask++) {
        if(windows[mask]) {
            mark_useless_submasks(mask^fullmask);
        }
    }
    for(int mask=1;mask<=fullmask;mask++) {
        int last_id=s[n-1]-'A';
        if(!useless[mask]) {
            res=min(res, nr_bits(mask));
        }
    }
    cout<<res<<'\n';
}

void solve_querries() {
    for(int i=1;i<=t;i++) {
        cin>>n>>c>>k>>s;
        solve_string();
    }
}
void read_data() {
    cin>>t;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    read_data();
    solve_querries();

    return 0;
}
