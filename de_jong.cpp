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

typedef __int128_t lll;  

const int MXN = 130-5; 
lll fib[MXN+5], dp[MXN+5];

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    setIO();

    fib[1] = 1; 
    FOR(i,2,MXN+5) {
        fib[i] = fib[i-2]+fib[i-1];
    }

    dp[2] = 1; 
    dp[3] = 0; // 2 3 cannot be a 2 island 
    dp[4] = 0; // 3 4 cannot be a 2 island
    dp[5] = 1; 
    FOR(i,6,MXN+5) {
        dp[i] = 0; 
        for (int j = 3; i-j >= 2; j++) {
            if (j == 3 || j == 4) {
                dp[i] += dp[i-j]; continue; 
            }
            int multiplicand = fib[j-2]; 
            if (j%4 == 1) multiplicand --;
            dp[i] += multiplicand * dp[i-j];
        }
        // printf("i=%d: ", i); 
        // print(dp[i]); 
        // printf("; fib[i] = "); 
        // print(fib[i]);
        // printf("\n");
    }

    FOR(n,4,MXN) {
        lll no_GHZ = ((lll)1<<n) - fib[n+4] +n+1; 
        lll yes_mat = 0, yes_GHZ_yes_mat = 0; 
        for(int sum = 0; sum <= n-2; sum++) {
            for(int x = 0; x <= sum; x++) {
                int y = sum-x;
                lll xmultiplicand, ymultiplicand;  

                if (x == 0) xmultiplicand = 1; 
                else {
                    xmultiplicand = fib[x+1]; 
                    if (x%4 == 2) xmultiplicand --; 
                }

                if (y == 0) ymultiplicand = 1; 
                else {
                    ymultiplicand = fib[y+1]; 
                    if (y%4 == 2) ymultiplicand --; 
                }

                lll added = xmultiplicand * ymultiplicand * dp[n-x-y]; 
                // printf("at x=%d, y=%d, yes_mat increased by %d, ", x, y, added);
                yes_mat += added;

                lll two_x_two_both = 0; 
                if (n-x-y-5 >= 0) {
                    two_x_two_both += fib[n-x-y-4]; // n-x-y-4 -2 + 2, another -2 because cannot take both adjacent nodes of the 2-island
                    if ((n-x-y-4)%4 == 3) two_x_two_both--;
                }

                lll x_two = 0, two_y = 0; 
                if (n-x-y == 2) {
                    if (x-1 >= 0) {
                        x_two += fib[x+1]-1; // x-1+2 
                        if (x%4 == 2) x_two--;
                    }
                    if (y-1 >= 0) {
                        two_y += fib[y+1]-1; // y-1+2 
                        if (y%4 == 2) two_y--; 
                    }
                }

                // printf("yes_GHZ_yes_mat increased by: %d\n", two_x_two_both + x_two + two_y);
                yes_GHZ_yes_mat += two_x_two_both + x_two + two_y; 
                
            }
        }
        yes_GHZ_yes_mat += (n-1); // 2 islands

        lll no_GHZ_yes_mat = yes_mat - yes_GHZ_yes_mat; 
        // cout << no_GHZ << ' ' << yes_mat <<' ' << yes_GHZ_yes_mat << ' ' << no_GHZ_yes_mat << '\n';
        // print(yes_mat);
        // printf("\n");
        if (no_GHZ == 0) {
            printf("no_GHZ is 0, all configurations solvable\n"); 
        }
        else {
            // print(no_GHZ_yes_mat); 
            // printf(" "); 
            // print(no_GHZ); 
            // printf("\n");
            cout << fixed << setprecision(9) << (double)no_GHZ_yes_mat/(double)no_GHZ << '\n';
        }
    }

    return 0;
}
