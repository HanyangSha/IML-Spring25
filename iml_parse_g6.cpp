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

const int MXN = 10; 
bool adj[MXN][MXN]; 

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

int main() {

    // int n = 4; 
    // string s = "CF";
    int n; 
    string s;
    cin >> n >> s; 
    
    parse_input(s); 
    F0R(i,n) {
        F0R(j,n) cout << adj[i][j] << ' '; 
        cout << endl;
    }

    return 0;
}
