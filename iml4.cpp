#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = a; i >= b; i--)
#define F0Rd(i,a) for (int i = a; i >= 0; i--)
#define FORit(it,a) for (auto it = a.begin(); it != a.end(); it++)
#define trav(a,x) for (auto& a: x)
 
#define sz(x) (ll)(x).size()
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define alla(arr, sz) arr, arr + sz
 
const int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 }; // for every grid problem!!
const char dir[4] = { 'D', 'R', 'U', 'L' };
const ll linf = 4*1e18;
const int inf = 1000000007;
 
namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
    }
}
 
using namespace io;

using namespace std::chrono;

const int num[11] = {-1,-1,1,2,6,21,112,853,11117,261080,11716571}; 
const int bipartnum[11] = {1, 1, 1, 1, 3, 5, 17, 44, 182, 730, 4032};

const int MXN = 10; 
bool adj[MXN][MXN]; 

int n; 
vi part, other, p;

void parse_input(string s) {
    memset(adj,0,sizeof adj);
    int r = 0, c = 1; 
    FOR(i,1,sz(s)) {
        char b = s[i]; b -= 63; 
        for (int j = 5; j >= 0; j--) {
            if (b&(1<<j)) {
                adj[r][c] = 1; 
                adj[c][r] = adj[r][c];  
            }
            r++; 
            if (r == c) {
                r = 0, c++; 
            }
        }
    } 
}

bool in_vec(vi& v, int x) {
    trav(t,v) if (t == x) return 1; 
    return 0; 
}

int subgraph_deg(int v) {
    int cnt = 0; 
    F0R(i,n) if (adj[v][i]) {
        if (in_vec(part,i)) cnt++;
    }
    return cnt; 
}

bool solve(int k) {
    int r = k, c = n+1; 
    vector<bitset<MXN>> a(r);
    
    F0R(i,r) {
        F0R(j,n) if (adj[part[i]][j]) {
            if (in_vec(other, j)) {
                a[i][j] = 1;
            }
        }
        if (subgraph_deg(part[i])%2 == 0) {
            a[i][n] = 1; 
        }
    }
   
    vector<int> where (c, -1);
    for (int col=0, row=0; col<c && row<r; ++col) {
        for (int i=row; i<r; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<r; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }

    bool sol = 1; 

    // look for row with all 0s in 0~n-1 and 1 in n 
    F0R(i,r) if (a[i][n] == 1) {
        bool found = 1; 
        F0R(j,n-1) {
            if (a[i][j]) {
                found = 0; break;
            } 
        }
        if (found) {
            sol = 0; break;
        }
    }

    return sol;
}

#define BIPARTITE 1

int main() {
    setIO();

    for (int i = 4; i <= 10; i++) {
        cin.clear();
        n = i; 

        string tmp = BIPARTITE ? "b" : "";
        string input_filename = "connected/i" + tmp + to_string(n) + ".txt"; 
        setIn(input_filename); 

        auto start = high_resolution_clock::now();

        vector<pll> ans(n,{0,0}); 
        
        int mx = BIPARTITE ? bipartnum[n] : num[n];
        F0R(j,mx) {
            if (j%5000==0) cout << j << endl;
            string s; cin >> s; 

            parse_input(s); 
            FOR(k,1,(n+1)/2+1) {
                int kdup, cnt; cin >> kdup >> cnt; 
                assert(kdup == k); 
                F0R(t, cnt) {
                    int msk; cin >> msk; 

                    part.clear(); other.clear(); 
                    F0R(x,n) {
                        if (msk&(1<<x)) part.pb(x); 
                        else other.pb(x); 
                    }
                    if (solve(k)) ans[k].ff++;

                    swap(part,other); 
                    if (solve(n-k)) ans[n-k].ff++;
                    ans[k].ss ++; 
                    ans[n-k].ss ++; 
                }
            }
        }

        FOR(k,1,n) {
            printf("n=%d, k=%d, percentage solvable = %.4f\n", n, k, (double)ans[k].ff/ans[k].ss); 
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << endl << duration.count() << endl;

        if (!BIPARTITE && i == 8) break; 
    }

    return 0;
}
