/**
 * Author: Yuhao Yao
 * Date: 22-10-26
 * Description: get the smallest primitive root of given integer $n$, assuming $n$ has primitive roots.
 * Time: Roughly O(n^{1 / 4} \log^2 n) for $n \le 10^9$. Practically really fast.
 * Status: tested on https://www.luogu.com.cn/problem/P6091.
 */
ll getPrimitiveRoot(ll n) {
	auto getps = [](ll x) {
		vector<ll> ps;
		for (ll i = 2; i * i <= x; i++) {
			if (x % i == 0) {
				ps.push_back(i);
				while (x % i == 0) x /= i;
			}
		}
		if (x > 1) ps.push_back(x);
		return ps;
	};
	auto ps = getps(n);
	ll phi = n;
	for (auto p: ps) phi = phi / p * (p - 1);
	auto qs = getps(phi);

	auto check = [&](ll x) {
		if (gcd(x, n) != 1) return 0;
		for (auto p: qs) {
			ll k = phi / p, a = x, res = 1;
			for (; k; k >>= 1, a = (__int128) a * a % n) {
				if (k & 1) res = (__int128) res * a % n;
			}
			if (res == 1) return 0;
		}
		return 1;
	};
	ll a = 1;
	while (check(a) == 0) a++;
	return a;
}
