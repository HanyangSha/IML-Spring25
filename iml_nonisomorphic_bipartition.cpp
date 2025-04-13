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
// part = B, other = A
vi B, A, pB, pA, cB, cA;

struct Comp {
    template<std::size_t N>
    bool operator()(const std::bitset<N>& x, const std::bitset<N>& y) const
    {
        for (int i = N-1; i >= 0; i--) {
            if (x[i] ^ y[i]) return y[i];
        }
        return false;
    }
};

typedef bitset<243> code; 
vector<set<code, Comp>> isomorphic_bipartitions; 

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

code encode_bipartition() {
    // lowest 81 bits is adj of a 
    // middle 81 bits is adj of b
    // highest 81 bits is adj of ab
    code res = 0; 
    int base = 0; 

    int szA = sz(A), szB = sz(B); 

    F0R(i,szA) FOR(j,i+1,szA) {
        int a = pA[cA[A[i]]], b = pA[cA[A[j]]];
        if (adj[A[i]][A[j]]) {
            res[base+a*szA+b] = 1; 
            res[base+b*szA+a] = 1; 
        }
    }
    base = 81; 
    F0R(i,szB) FOR(j,i+1,szB) {
        int a = pB[cB[B[i]]], b = pB[cB[B[j]]];
        if (adj[B[i]][B[j]]) {
            res[base+a*szB+b] = 1; 
            res[base+b*szB+a] = 1; 
        }
    }
    base = 81*2; 
    F0R(i,szA) F0R(j,szB) {
        int a = pA[cA[A[i]]], b = pB[cB[B[j]]];
        if (adj[A[i]][B[j]]) {
            res[base+a*szB+b] = 1; 
        }
    }
    return res; 
}

bool check_isomorphic() {
    int szA = sz(A), szB = sz(B); 
    pA.resize(szA); 
    pB.resize(szB);
    cA.resize(n); 
    cB.resize(n); 
    F0R(i,szA) cA[A[i]]=i, pA[i]=i; 
    F0R(i,szB) cB[B[i]]=i, pB[i]=i;

    int k = sz(B); 
    code res; 
    do {
        do {
            res = encode_bipartition(); 
            if(isomorphic_bipartitions[k].count(res)) return 0; 
        } while(next_permutation(all(pB)));
    } while (next_permutation(all(pA))); 

    isomorphic_bipartitions[k].insert(res);
    return 1; 
}

void enumerate(string s) {

    parse_input(s); 

    // obs: all partitions between 2 nonisomorphic graphs must be nonisomorphic
    isomorphic_bipartitions.clear(); 
    isomorphic_bipartitions.resize((n+1)/2+1); 

    vector<vi> isomorphic_masks((n+1)/2+1); 

    FOR(msk,1,(1<<n)-1) {
        B.clear(); A.clear(); 
        int k = __builtin_popcount(msk); 
        if (k > (n+1)/2) continue; // abuse symmetry :)
        F0R(x,n) {
            if (msk&(1<<x)) B.pb(x); 
            else A.pb(x); 
        }

        bool iso = check_isomorphic(); 
        if (iso) isomorphic_masks[k].pb(msk); 
    }

    // write out all isomorphic graphs 
    cout << s << '\n'; 
    FOR(i,1,(n+1)/2+1) {
        cout << i << ' ' << sz(isomorphic_bipartitions[i]) << '\n';
        trav(x,isomorphic_masks[i]) cout << x << ' ' ;
        cout <<'\n';
    }
    
}

#define BIPARTITE 1 

int main() {

    for (int i = 4; i <= 10; i++) {
        cin.clear();  

        n = i; 
        string tmp = BIPARTITE ? "b" : "c"; 
        string input_filename = "connected/" + tmp + to_string(n) + ".txt"; 
        setIn(input_filename); 
        tmp = BIPARTITE ? "b" : "";
        string output_filename = "connected/i" + tmp + to_string(n) + ".txt"; 
        setOut(output_filename);

        auto start = high_resolution_clock::now();

        int mx = BIPARTITE ? bipartnum[n] : num[n];
        F0R(k,mx) {
            if (i > 8 && k%10==0) cerr << k << endl;
            string s; cin >> s; 
            enumerate(s);
        }      
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cerr << endl << duration.count() << endl; 

        if (!BIPARTITE && i == 8) break; 
    }

    return 0;
}
