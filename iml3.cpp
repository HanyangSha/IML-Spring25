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

const int num[11] = {-1,-1,1,2,6,21,112,853,11117,261080,11716571}; 

const int MXN = 10; 
vector<string> v; 
bool adj[MXN][MXN]; 

int n; 
vi part, other; 

void parse_input(int x) {
    memset(adj,0,sizeof adj);
    string s = v[x];
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
    int x = rand()%num[n]; 
    parse_input(x); 

    vi tmp(n); 
    F0R(i,n) tmp[i] = i; 
    random_shuffle(all(tmp));

    part.clear(), other.clear(); 
    F0R(i,k) part.pb(tmp[i]);
    FOR(i,k,n) other.pb(tmp[i]);

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

double simulate(int k) {
    int sol = 0; 
	double prev_percentage = 0; 
    ll cnt = 0; 
    ll i = 0; 
	while(cnt != 5 || prev_percentage == 0) {
        if (i != 0 && i%5000 == 0) {
            double tmp = (double)sol/i; 
            // cout << tmp << endl; 
            if (abs(tmp-prev_percentage) < 1e-4) {
                cnt++;
                prev_percentage = (cnt == 1) ? tmp : (tmp + cnt*prev_percentage)/(cnt+1);
            }
            else {
                prev_percentage = tmp;
            }
        }
        bool x = solve(k); 
        if (x) sol++; 
        i++;
    }
    return prev_percentage;
}

int main() {

    cin.clear();  
    v.clear();

    n = 10; // only indices [1,n-1] are used

    string input_filename = "connected/graph10c.g6"; 
    setIn(input_filename); 
    srand(time(NULL)); 

    auto start = high_resolution_clock::now();

    F0R(k,num[n]) {
        string s; cin >> s; 
        v.pb(s); 
    }

    FOR(k,1,n) {
        double res = simulate(k); 
        printf("n=%d, k=%d, percentage solvable = %.4f\n", n, k, res); 
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << endl << duration.count() << endl;


    return 0;
}
