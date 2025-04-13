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
 
#define sz(x) (int)(x).size()
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
 
#define DEBUG 0
#define RANDOM 1

using namespace std::chrono;

const int MAXN = 55; 
int n = 20, m = 30, k = 10; 
bool adj[MAXN][MAXN];
vi part, other; 

void broder() {
    vector<bool> visited(n,0); 
    int start = rand()%n; 
    visited[start] = 1; 
    int num_visited = 1; 

    int cur = start; 
    while (num_visited != n) {
        // randomly choose 1 node to go to 
        int to = rand()%n; 
        if (!visited[to]) {
            adj[cur][to] = 1; 
            adj[to][cur] = 1; 
            visited[to] = 1;
            num_visited++;
        }
        cur = to; 
    }
}

void wilson() {
    int start = rand()%n; 

    // pick arbitrary node not in mst
    vector<bool> visited(n,0); 
    visited[start] = 1; 

    int sz_remaining = n-1; 
    while (sz_remaining) {
        int v = rand()%sz_remaining; 
        int i = 0, cnt = 0; 
        for (; i < n; i++) {
            if (cnt == v && !visited[i]) break;
            else if (!visited[i]) cnt++;
        }

        // start random walk from i to mst
        vi pending; 
        int cur = i; 
        while (!visited[cur]) {
            int to = rand()%n; 
            pending.pb(cur);
            cur = to; 
        }
        
        // loop erasure
        vi last_occurance(n,-1); 
        F0Rd(j, pending.size()-1) {
            int x = pending[j];
            if (last_occurance[x] == -1) last_occurance[x] = j;
        }

        vi path; 
        for (int j = 0; j < pending.size(); j++) {
            path.pb(pending[j]);
            visited[pending[j]] = 1;
            if (last_occurance[pending[j]] > j) {
                j = last_occurance[pending[j]]; 
            }
            // else j++;
        }

        sz_remaining -= path.size(); 
        path.pb(cur); 

        F0R(j,path.size()-1) {
            int a = path[j], b = path[j+1];
            adj[a][b] = 1; 
            adj[b][a] = 1; 
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

bool solve() {
    memset(adj,0,sizeof adj); 
    part.clear(); 
    other.clear(); 

    #if !RANDOM
    cin >> n >> m >> k; 
    #endif

    #if RANDOM
    broder(); 
    // wilson(); 

    // add additional edges

    // int num_edges = n-1; 
    // m = rand()%(n*(n-1)/2-n+2) + n-1; 
    // while (num_edges < m) {
    //     int v = rand()%n; 
    //     int u = rand()%n;
    //     if (v == u) continue; 
    //     if (!adj[v][u]) {
    //         adj[v][u] = 1; 
    //         adj[u][v] = 1; 
    //         num_edges++;
    //     }
    // }
    double p_edge = 0.3; 
    F0R(i,n) FOR(j,i+1,n) if (i != j && !adj[i][j]) {
        double r = ((double) rand() / (RAND_MAX)); 
        if (r < p_edge) {
            adj[i][j] = 1; 
            adj[j][i] = 1; 
        }
    }
    #else
    F0R(i,m) {
        int a, b; cin >> a >> b; 
        a--, b--;
        adj[a][b] = 1; 
        adj[b][a] = 1; 
    }
    #endif

    #if DEBUG
    F0R(i,n) {
        trav(x,adj[i]) cout << x << ' '; 
        cout << '\n';
    }
    #endif

    #if RANDOM
    // generate bipartition 
    // vi A(k); 
    // F0R(i,k) A[i] = i; 
    // FOR(i,k,n) {
    //     int j = rand()%i; 
    //     if (j < k) A[j] = i; 
    // }

    vi v(n); 
    F0R(i,n) v[i] = i; 
    random_shuffle(all(v));
    // F0R(i,n) cout << v[i] << ' '; 
    // cout << endl;
    
    F0R(i,k) part.pb(v[i]);
    FOR(i,k,n) other.pb(v[i]);
    #else
    F0R(i,k) {
        int a; cin >> a; 
        a--; 
        part.pb(a); 
    }
    F0R(i,n) {
        if (!in_vec(part, i)) {
            other.pb(i);
        }
    }
    #endif

    #if DEBUG
    trav(x,part) cout << x << ' ' ; 
    cout << endl; 
    trav(x,other) cout << x << ' '; 
    cout << endl;
    #endif

    int r = k, c = n+1; 
    const int MAXN = 1e5; 
    vector<bitset<MAXN>> a(r);

    F0R(i,r) {
        F0R(j,n) if (adj[part[i]][j]) {
            if (in_vec(other, j)) {
                a[i][j] = 1;
            }
        }
        if (subgraph_deg(part[i])%2 == 0) {
            a[i][n] = 1; 
        }
        #if DEBUG
        F0R(j,n+1) cout << a[i][j]; 
        cout << endl;
        #endif
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

    #if DEBUG
    if (sol) cout << "solution"; 
    else cout << "no solution";
    #endif
    return sol;
}

double simulate() {
    int sol = 0; 
	double prev_percentage = 0; 
    int cnt = 0; 
    int i = 0; 
	while(cnt != 5 || prev_percentage == 0) {
        if (i != 0 && i%5000 == 0) {
            double tmp = (double)sol/i; 
            // cout << tmp << endl; 
            if (abs(tmp-prev_percentage) < 1e-4) {
                cnt++;
                prev_percentage = (cnt == 1) ? tmp : (tmp + cnt*prev_percentage)/(cnt+1);
                // cout << "prev_percentage: " << prev_percentage << endl;
            }
            else {
                prev_percentage = tmp;
            }
        }
        bool x = solve(); 
        if (x) sol++; 
        i++;
    }
    return prev_percentage;
}

int main() {
    #if DEBUG
    setIn("test.in");
    #else
    // setOut("input_data.txt");
    #endif

    auto start = high_resolution_clock::now();

    srand(time(NULL)); 

    FOR(i,19,20) {
        FOR(j,2,i-1) {
            n = i; k = j; 
            cout << j << endl;
            double res = simulate(); 
            printf("n=%d, k=%d, percentage solvable = %.4f\n", n,k,res);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << endl << duration.count() << endl;

    return 0;
}
