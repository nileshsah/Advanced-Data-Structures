#include <bits/stdc++.h>
typedef int ll;
#define get(a) scanf("%lld", &a)
#define repVector(v)  for( auto it = v.begin(); it != v.end(); it++ )
#define all(c) (c).begin(), (c).end()
#define pb push_back
#define FOR(i,a,b) for( ll i = a; i <= b; i++ )
#define ROF(i,a,b) for( ll i = a; i >= b; i-- )
#define debug(x) cerr << "[DEBUG] " << #x << " = " << x << endl
#define matrix vector< vector<ll> >
#define F first
#define S second
#define mp make_pair
#define L 2*r
#define R 2*r+1
#define INPFILE freopen("input.in","r",stdin)
#define BOOST ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

struct pairhash {
public:
  template <typename T, typename U>
  size_t operator()(const pair<T, U> &x) const
  {
    return hash<T>()(x.first) ^ hash<U>()(x.second);
  }
};

ll MaxVal = 100000;
unordered_map< pair<ll,ll>, ll, pairhash > tree;

void update( ll x, ll y ) {
	while( x <= MaxVal ) {
		ll p = y;
		while( p <= MaxVal ) {
			tree[mp(x,p)]++;
			p += (p&-p);
		}
		x += (x&-x);
	}
}

ll read( ll x, ll y ) {
	ll sum = 0;
	while(x>0) {
		ll p = y;
		while(p>0) {
		 sum += tree[mp(x,p)];
		 p -= (p&-p);
		}
		x -= (x&-x);
	}
	return sum;
}

unordered_map< ll, set< pair<ll,ll> > > m;

int main() {
	BOOST;
	ll n; cin >> n;
	vector<ll> w;
	vector< pair<ll,ll> > v;
	
	
	FOR(i,1,n) {
		ll x, y;
		cin >> x >> y;
		m[y-x].insert( mp(x+1,y+1) );
	}
	
	
	FOR(i,1,n) {
		ll x; cin >> x;
		w.pb(x); 
		if( m[x].empty() ) {
			cout << "NO"; return 0;
		}
		auto p = *m[x].begin();
		m[x].erase( m[x].begin() );
		
		v.pb(p);
	}
	
	for( auto p : v ) {
		update( p.F, p.S );
		if( read(p.F,p.S) < p.F*p.S ) {
			cout << "NO";
			return 0;
		}
	}
		
	cout << "YES\n";
	for( auto p : v )
	 cout << p.F-1 << " " << p.S-1 << '\n';
}
