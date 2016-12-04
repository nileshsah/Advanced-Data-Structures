#include <bits/stdc++.h>
typedef long long ll;
#define get(a) scanf("%lld", &a)
#define repVector(v)  for( auto it = v.begin(); it != v.end(); it++ )
#define all(c) (c).begin(), (c).end()
#define pb push_back
#define FOR(i,a,b) for( ll i = a; i <= (ll)(b); i++ )
#define ROF(i,a,b) for( ll i = a; i >= (ll)(b); i-- )
#define debug(x) ; //cerr << "[DEBUG] " << #x << " = " << x << endl
#define matrix vector< vector<ll> >
#define F first
#define S second
#define mp make_pair
#define L 2*r
#define R 2*r+1
#define INPFILE freopen("input.in","r",stdin)
#define BOOST ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

struct node {
	ll val;
	ll l, r;
}tree[8*100005];

ll v[200005] = {0};

void construct( pair<ll,ll> p, ll r = 1 ) {
	node &ptr = tree[r];
	ptr.l = p.F; ptr.r = p.S;
	
	if( p.F == p.S )
	 ptr.val = v[p.F];
	else {
		ll mid = ( p.F + p.S )/2;
		construct( mp(p.F,mid), L );
		construct( mp(mid+1,p.S), R );
		
		ptr.val = min( tree[L].val, tree[R].val );
	}
}

bool dir = 0;

ll query( ll x, ll y, ll val, ll r = 1 ) {
	//~ cerr  << tree[r].l << ' ' << tree[r].r << " = " << tree[r].val << " -> " << val<<  "\n";
	ll mid = ( tree[r].l + tree[r].r )/2;
	
	if( tree[r].r < x || tree[r].l > y || x > y )
	 return 0;
	 
	 if( tree[r].l >= x && tree[r].r <= y ) {
		if( tree[r].val >= val )
		 return tree[r].r - tree[r].l + 1;
		else if( tree[r].r == tree[r].l )
		 return 0;
		if(dir) {
			if( tree[L].val >= val )
			 return tree[L].r - tree[L].l + 1 + query( x, y, val, R );
			else
			 return query( x, y, val, L );
		}
		else {
			if( tree[R].val >= val )
			 return tree[R].r - tree[R].l + 1 + query( x, y, val, L );
			else
			 return query( x, y, val, R );
		}
	}
	 
	if( x > mid )
	 return query( x, y, val, R );
	if( y <= mid )
	 return query( x, y, val, L );

	
	ll ql = query( x, y, val, L );
	if( dir && ql < mid-x+1 )
	 return ql;
	ll qr = query( x, y, val, R );
	//~ cerr << tree[r].l << ' ' << tree[r].r << '\n'; debug( y-mid+1);
	if( !dir && qr < y-mid )
	 return qr;
	debug(ql); debug(qr);
	
	return ql + qr;
	
}

ll ans[200005] = {0};


int main() {
	BOOST;
	ll n; cin >> n;
	
	FOR(i,1,n)
	 cin >> v[i];
	
	construct( mp(1,n) );
	
	FOR(i,1,n) {
		dir = 0;
		ll prefix = query( 1, i-1, v[i] );
		dir = 1;
		ll suffix = query( i+1, n, v[i] );
		
		ll val = prefix + suffix + 1;
		ans[val] = max( ans[val], v[i] );
		
		debug(prefix); debug(suffix);
	}
	
	ROF(i,n-1,1) {
		ans[i] = max( ans[i], ans[i+1] );
	}
	
	FOR(i,1,n)
	 cout << ans[i] << ' ';
	
}
