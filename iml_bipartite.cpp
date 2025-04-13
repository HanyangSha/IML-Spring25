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

const int MXN = 10; 
bool adj[MXN][MXN]; 

int n; 

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

bool bipartite_check() {
    vi color(n,-1);
    color[0] = 0; 
    queue<int> q; 
    q.push(0); 
    while (!q.empty()) {
        int v = q.front(); 
        q.pop(); 
        F0R(x,n) if (adj[v][x]) {
            if (color[x] == -1) {
                color[x] = 1-color[v];
                q.push(x);
            }
            else if (color[x] == color[v]) return 0; 
        }
    }
    return 1; 
}

int main() {

    for (int i = 4; i <= 10; i++) {
        cin.clear(); 
        n = i; 
        string input_filename = (i <= 9) ? "connected/c"+to_string(n)+".txt" : "connected/graph10c.g6"; 
        setIn(input_filename);
        string output_filename = "connected/b" + to_string(n) + ".txt"; 
        setOut(output_filename);

        auto start = high_resolution_clock::now();

        int bipartite_cnt = 0; 

        F0R(j,num[n]) {
            if (j%5000==0) cerr << j << '\n';
            string s; cin >> s; 
            parse_input(s); 
            bool bipartite = bipartite_check(); 
            if (bipartite) {
                cout << s << '\n';
                bipartite_cnt ++; 
            }
        } 

        cerr << "number of bipartite graphs with n=" << n << "vertices: " << bipartite_cnt << '\n';

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cerr << endl << duration.count() << endl;
    }

    return 0;
}
