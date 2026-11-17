#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define NMAX 10001
#define INF 2000000001
#define MOD 998244353

#define STDIN 1
#if STDIN
    #define fein cin
    #define fout cout
#else
    ifstream fein("date.in");
    ofstream fout("date.out");
#endif

int n, m;
vector<int> l, r, mob, spf;

void read_data() {
    fein>>n>>m;
    r.assign(n+1, 0);
    l.assign(n+1, 0);
    mob.assign(m+1, 0);
    spf.assign(m+1, 0);
    for(int i=1;i<=n;i++) {
        fein>>l[i]>>r[i];
    }
}

void compute_smallest_prime_factors() {
    spf[1]=1;
    for(int i=2;i<=m;i++) {
        if(!spf[i]) {
            for(int j=i;j<=m;j+=i) {
                if(!spf[j]) {
                    spf[j]=i;
                }
            }
        }
    }
}

void compute_mobius() {
    mob[1]=1;
    for(int i=2;i<=m;i++) {
        if(spf[i]==spf[i/spf[i]]) {
            mob[i]=0;
        }
        else {
            mob[i] = mob[i/spf[i]] * -1;
        }
    }
}

int count_sums(int d) {
    int ans=0;
    int M = m/d;
    vector<int> dp(M+1, 0), pref(M+1, 0);
    dp[0]=1;
    for(int i=1;i<=n;i++) {
        int L = (l[i]+d-1)/d;
        int R = r[i]/d;

        pref[0]=dp[0];
        for(int j=1;j<=M;j++) {
            pref[j]=(dp[j]+pref[j-1]) % MOD;
        }

        for(int j=0;j<=M;j++) {
            int left=0;
            if(j-L>=0) left=pref[j-L];

            int right=0;
            if(j-R-1>=0) right=pref[j-R-1];
            dp[j]=(left-right+MOD) % MOD;
        }
    }
    for(int i=1;i<=M;i++) ans=(ans+dp[i])%MOD;
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    read_data();
    compute_smallest_prime_factors();
    compute_mobius();
    int64_t res=0;
    for(int d=1;d<=m;d++) {
        res=(res+1LL*mob[d]*count_sums(d)+MOD)%MOD;
    }
    fout<<res;

}
