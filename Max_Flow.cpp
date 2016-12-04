#include <bits/stdc++.h>
typedef int ll;
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

ll a[105] = {0};
ll b[105] = {0};
ll parent[205] = {0};
ll path_flow[205][205] = {{0}};
ll ans[105][105] = {{0}};

vector<ll> v[20005];

bool bfs( ll start, ll last ) {
	queue<ll> q;
	q.push( start );
	
	vector<bool> seen(last+1,0);
	seen[start] = 1;
	
	while( !q.empty() ) {
		ll ptr = q.front();
		q.pop();
				
		FOR(x,start,last)
		  if( !seen[x] && path_flow[ptr][x] > 0 ) {	
			parent[x] = ptr;
			seen[x] = 1;
			q.push(x);
		}
		
	}
	
	return seen[last];
}

int main() {
	ll n, m;
	cin >> n >> m;
	
	ll sumA = 0, sumB = 0;
	
	FOR(i,1,n) {
	  cin >> a[i];
	  sumA += a[i];
	}
	FOR(i,1,n) {
	  cin >> b[i];
	  sumB += b[i];
	}
	
	
	FOR(i,1,m) {
		ll x, y;
		cin >> x >> y;

		path_flow[x][y+n] = INT_MAX/10;	
		path_flow[y][x+n] = INT_MAX/10;	
	}
	
	FOR(i,1,n)
	    path_flow[i][i+n] = INT_MAX/10;
	
	FOR(i,1,n)
		path_flow[0][i] = a[i];
		
	FOR(i,1,n)
		path_flow[i+n][2*n+1] = b[i];
	
	ll max_flow = 0;
	
	while( bfs( 0, 2*n+1 ) ) {
			
		parent[0] = -1;
		
		ll p = 2*n+1, min_flow = INT_MAX;
		while( parent[p] != -1 ) {
			min_flow = min( min_flow, path_flow[ parent[p] ][p] );
			p = parent[p];
		}
				
		p = 2*n+1;
		while( parent[p] != -1 ) {
			path_flow[ parent[p] ][p] -= min_flow;
			path_flow[p][ parent[p] ] += min_flow;
			p = parent[p];
		}
		
		max_flow += min_flow;	
	}
	
	if( max_flow != sumA || sumA != sumB ) {
		cout << "NO";
		return 0;
	}	
	
	cout << "YES\n";
	FOR(i,1,n) {
	 FOR(j,1+n,2*n)
	  cout << path_flow[j][i] << ' ';
	 cout << '\n';
	}
}
