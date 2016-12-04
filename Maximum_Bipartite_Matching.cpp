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

vector<ll> prime;
bool mark[100000] = {0};

void sieve() {
	ll N = sqrt( 1e9 ) + 1;
	FOR(i,2,N)
	 if( !mark[i] ) {
		prime.pb( i );
		for( ll k = i*i; k <= N; k += i )
			mark[k] = 1;
	 }
}

ll a[105] = {0}, c = 0;
ll node[3205] = {0};
vector<ll> grp[105];
vector<ll> v[3205];

int flow[3200][3200] = {0};
ll parent[3205] = {0};
bool seen[3205] = {0};

ll match[3205] = {0};

bool dfs( ll start ) {
	
	for( ll p : v[start] )
	  if( !seen[p] ) {
		seen[p] = 1;
		if( match[p] == -1 || dfs( match[p] ) ) {
			match[p] = start;
			return 1;
		}
	  }
	return 0;
}

ll max_match() {
	memset( match, -1, sizeof match );
	ll ans = 0;
	FOR(i,1,c) {
	 memset( seen, 0, sizeof seen );
	 ans += dfs( i );
	}
	return ans;
}



int main() {
	sieve();
	
	ll n, m;
	cin >> n >> m;
	
	FOR(i,1,n) {
		cin >> a[i];
		ll num = a[i];
		
		for( ll p : prime )
			while( num%p == 0 ) {
				num /= p;
				grp[i].pb(++c);
				node[c] = p;
			}
		if( num > 1 ) {
			grp[i].pb(++c);
			node[c] = num;
		}
	}
	
	FOR(i,1,m) {
		ll x, y;
		cin >> x >> y;
		
		if(x%2) swap(x,y);
		
		for( ll q : grp[x] )
		 for( ll p : grp[y] )
			if( node[q] == node[p] )
				v[q].pb(p);
	}
	
	cout << max_match();
	
}
