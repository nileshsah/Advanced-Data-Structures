#include <bits/stdc++.h>
typedef long long ll;
#define get(a) scanf("%lld", &a)
#define repVector(v)  for( auto it = v.begin(); it != v.end(); it++ )
#define all(c) (c).begin(), (c).end()
#define pb push_back
#define FOR(i,a,b) for( ll i = (ll)(a); i <= (ll)(b); i++ )
#define ROF(i,a,b) for( ll i = (ll)(a); i >= (ll)(b); i-- )
#define debug(x) cerr << "[DEBUG] " << #x << " = " << x << endl
#define matrix vector< vector<ll> >
#define F first
#define S second
#define mp make_pair
#define INPFILE freopen("input.in","r",stdin)
#define BOOST ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

const int MAXN = 100005;
const int LOGN = 21;

vector<ll> v[MAXN];
ll depth[MAXN] = {0};
ll parent[MAXN] = {0};
ll size[MAXN] = {0};
ll dp[MAXN][LOGN];
ll n;

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
	
	ll m; cin >> m;
	while(m--) {
		ll x, y;
		cin >> x >> y;
		
		ll lca = LCA(x,y);
		
		if( dist(x,y)%2 ) {
			cout<< "0\n";
			continue;
		}
		
		if( dist(x,lca) == dist(y,lca) ) {
			ll ans = n, d = dist(x,lca);
			
			if( x != y )
			 ans -= size[go_up(x,d-1)] + size[go_up(y,d-1)];

			cout << ans << '\n';
		}
		else {
			if( depth[x] < depth[y] )
			 swap(x,y);
			ll mid = dist(x,y)/2;
			
			ll node = go_up(x,mid);
			ll ans = size[node] - size[go_up(x,mid-1)];
				
			cout << ans << '\n';
		}
		
		
		
	}
}
