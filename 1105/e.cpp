#include <bits/stdc++.h>
using namespace std;
#define NMAX 40
#define INF 1000000001
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

int graph[NMAX][NMAX], mx=0, n, m;
long long int max_mask[1<<(NMAX/2)], half, g[NMAX];
vector<int> q;
map<string, int> h;

void rec(long long int mask, int bit) {

    if(bit==m/2) {
        max_mask[mask]= __builtin_popcountll(mask);
        return;
    }

    rec(mask, bit+1);
    if((g[bit]&mask)==0) {
        rec((mask | (1ULL<<bit)), bit+1);
    }
}

void compute_submasks() {
    int limit=(1<<(m/2));
    for(int mask=0;mask<limit;mask++) {
        if(!max_mask[mask]) {
            for(int bit=0;bit<(m/2);bit++) {
                if(mask & (1ULL<<bit)) {
                    max_mask[mask]=max(max_mask[mask],
                        max_mask[mask^(1ULL<<bit)]);
                }
            }
        }
    }
}

void rec_2(long long mask, int bit, long long unallowed) {
    if(bit==m) {
        int allowed = ((1<<(m/2))-1)^unallowed;
        int cnt=__builtin_popcountll(mask) + max_mask[allowed];
        mx=max(cnt, mx);
        return;
    }

    rec_2(mask, bit+1, unallowed);
    if((g[bit]&mask)==0) {
        unallowed |= g[bit] & ((1<<(m/2))-1);
        rec_2(mask | (1ULL<<bit), bit+1, unallowed);
    }
}

void print_graph() {
    for(int i=0;i<m;i++) {
        for(int j=0;j<m;j++) {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

void read_data() {
    fein>>n>>m;
    int x, cnt=0;
    string s;
    for(int i=1;i<=n;i++) {
        fein>>x;
        if(x==2) {
            fein>>s;
            if(h.find(s)==h.end()) {
                h[s]=cnt++;
            }
            q.push_back(h[s]);
        }
        else {
            for(int i=0;i<q.size();i++) {
                for(int j=0;j<q.size();j++) {
                    if(q[i]!=q[j]) {
                        graph[q[i]][q[j]]=1;
                        graph[q[j]][q[i]]=1;

                        g[q[i]] |= (1ULL<<q[j]);
                        g[q[j]] |= (1ULL<<q[i]);
                    }
                }
            }
            q.clear();
        }
    }
    for(int i=0;i<q.size();i++) {
        for(int j=0;j<q.size();j++) {
            if(q[i]!=q[j]) {
                graph[q[i]][q[j]]=1;
                graph[q[j]][q[i]]=1;
                g[q[i]] |= (1ULL<<q[j]);
                g[q[j]] |= (1ULL<<q[i]);
            }
        }
    }
    // print_graph();
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    read_data();
    rec(0, 0);
    compute_submasks();
    rec_2(0, m/2, 0);
    fout<<mx;
    return 0;
}
