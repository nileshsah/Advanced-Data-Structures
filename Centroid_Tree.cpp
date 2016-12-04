#include <bits/stdc++.h>
typedef int ll;
#define all(c) (c).begin(), (c).end()
#define pb push_back
#define FOR(i,a,b) for( ll i = (ll)(a); i <= (ll)(b); i++ )
#define ROF(i,a,b) for( ll i = (ll)(a); i >= (ll)(b); i-- )
#define debug(x) cerr << "[DEBUG] " << #x << " = " << x << endl;
#define F first
#define S second
#define INPFILE freopen("input.in","r",stdin)
#define BOOST ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

// Centroid Tree

const int MAXN = 100005;
const int LOGN = 21, INF = INT_MAX/50;

vector<ll> v[MAXN];
ll depth[MAXN], n;
ll parent[MAXN], p[MAXN], size[MAXN], sz[MAXN];
ll dp[MAXN][LOGN];
bool used[MAXN], color[MAXN];
multiset<ll> ans[MAXN];


/*.......... LCA STARTS ................*/

void dfs( ll x, ll p, ll lvl = 0 ) {
	depth[x] = lvl;
	parent[x] = p;
	size[x] = 1;
	
	for( ll q : v[x] )
	 if( q != p ) {
		dfs( q, x, lvl+1 );
		size[x] += size[q];
	 }	
}

void preprocess() {
	memset( dp, -1, sizeof dp );
	
	FOR(i,1,n)
	 dp[i][0] = parent[i];
	
	for( ll j = 1; (1LL<<j) <= n; j++ )
	 for( ll i = 1; i <= n; i++ )
	  if( dp[i][j-1] != -1 )
	   dp[i][j] = dp[ dp[i][j-1] ][j-1];
}

ll LCA( ll p, ll q ) {
	
	if( depth[p] < depth[q] )
	 swap(p,q);
	
	for( ll i = log2(n)+1; i >= 0; i-- )
	 if( depth[p] - (1LL<<i) >= depth[q] )
	  p = dp[p][i];
	
	if( p == q ) return p;
	
	for( ll i = log2(n)+1; i >= 0; i-- )
	 if( dp[p][i] != dp[q][i] && dp[p][i] != -1 )
	   p = dp[p][i], q = dp[q][i];
	
	return parent[p];	
}

ll dist( ll a, ll b ) {
	return depth[a] + depth[b] - 2*depth[LCA(a,b)];
}

ll go_up( ll x, ll up ) {
	for( ll i = log2(n)+1; i >= 0; i-- )
	 if( (1LL<<i) <= up ) {
		up -= (1LL<<i);
		x = dp[x][i];
	 }
	return x;
}

/*................ LCA ENDS ................. */

/*........... Decomposition Starts ...........*/

void dfsTree( ll x, ll p = -1 ) {
  sz[x] = 1;
  for( ll q : v[x] )
    if( q != p && !used[q] ) {
      dfsTree( q, x );
      sz[x] += sz[q];
    }
}


ll centroid( ll x, ll p, ll _size ) {
  for( ll q : v[x] )
    if( q != p && !used[q] && sz[q] > _size/2 )
      return centroid( q, x, _size );
  return x;
}

void decompose( ll r, ll par ) {
  dfsTree(r);
  ll c = centroid( r, -1, sz[r] );
  p[c] = par;
  used[c] = 1;
  for( ll x : v[c] )
    if( !used[x] )
      decompose( x, c );
}


/*........... Decomposition Ends............*/

void update( ll x ) {
  ll idx = x;
  while( idx != -1 ) {
    if( color[x] )
      ans[idx].erase( ans[idx].find( dist(x,idx) ) );
    else
      ans[idx].insert( dist(x,idx) );
    idx = p[idx];
  }
  color[x] = !color[x];
}

ll query( ll x ) {
  ll idx = x, val = INF;
  while( idx != -1 ) {
    if( !ans[idx].empty() )
      val = min( val, *ans[idx].begin() + dist(idx,x) );
    idx = p[idx];
  }
  if( val == INF ) return -1;
  return val;
}


int main() {
  BOOST;
  cin >> n;
  FOR(i,1,n-1) {
    ll x, y;
    cin >> x >> y;
    v[x].pb(y);
    v[y].pb(x);
  }
  
  dfs(1,-1,0);
  preprocess();
  decompose(1,-1);
  
  ll q; cin >> q;
  
  while(q--) {
    ll o, v;
    cin >> o >> v;
    
    if( o == 0 )
      update(v);
    else if( o == 1 )
      cout << query(v) << '\n';
  }  
}
