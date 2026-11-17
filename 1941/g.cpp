#include <bits/stdc++.h>
using namespace std;
#define NMAX 200100
#define INF INT_MAX
#define MOD 1000000007
#define pii pair<int,int>

#define STDIN 1
#if STDIN
    #define fein cin
    #define fout cout
#else
    ifstream fein("date.in");
    ofstream fout("date.out");
#endif

int n, m, t;
vector<int> l[NMAX*2];


void reset() {
    for(int i=0;i<=n+m+10;i++) {
        l[i].clear();
    }
}

int bfs(int start, int end) {
    if(start==end) return 0;
    deque<int> q;
    q.push_back(start);
    vector<int> v(m+n+10, 0);
    v[start]=1;
    while(!q.empty()) {
        int nc=q.front();
        q.pop_front();
        if(nc==end) {
            return v[nc]-1;
        }

        for(int vc : l[nc]) {
            if(!v[vc]) {
                v[vc]=v[nc];
                if(vc>n) {
                    v[vc]++;
                    q.push_front(vc);
                }
                else {
                    q.push_back(vc);
                }
            }
        }
    }
    return -1;
}

void solve_queries() {
    int x, y, c, start, end;
    for(int i=1;i<=t;i++) {
        reset();
        fein>>n>>m;
        unordered_map<int, int> mp;
        int cnt=0;
        for(int j=1;j<=m;j++) {
            fein>>x>>y>>c;

            if(mp.find(c)==mp.end()) {
                cnt++;
                mp[c]=cnt;
            }
            c=mp[c];

            l[n+c].push_back(x);
            l[n+c].push_back(y);
            l[x].push_back(n+c);
            l[y].push_back(n+c);
        }
        fein>>start>>end;
        fout<<bfs(start, end)<<'\n';
    }
}

void read_data() {
    fein>>t;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    read_data();
    solve_queries();
    return 0;
}
