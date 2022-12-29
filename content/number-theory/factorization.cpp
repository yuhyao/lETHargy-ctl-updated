/**
 * Author: Yuhao Yao
 * Date: 22-10-30
 * Description: Primality test and Fast Factorization. The $mul$ function supports $0 \le a, b < c < 7.268 \times 10^{18}$ and is a little bit faster than \_\_int128.
 * Time: O(x ^ {1 / 4}) for pollard-rho and same for factorizing $x$.
 * Status: tested on https://judge.yosupo.jp/problem/factorize, https://qoj.ac/contest/821/problem/2574.
 */
namespace Factorization {
	inline ll mul(ll a, ll b, ll c) { /// start-hash
		ll s = a * b - c * ll((long double) a / c * b + 0.5);
		return s < 0 ? s + c : s;
	}

	ll mPow(ll a, ll k, ll mod) {
		ll res = 1;
		for (; k; k >>= 1, a = mul(a, a, mod)) if (k & 1) res = mul(res, a, mod);
		return res;
	}

	bool miller(ll n) {
		auto test = [&](ll n, int a) {
			if (n == a) return true;
			if (n % 2 == 0) return false;

			ll d = (n - 1) >> __builtin_ctzll(n - 1);
			ll r = mPow(a, d, n);
			while (d < n - 1 && r != 1 && r != n - 1) {
				d <<= 1;
				r = mul(r, r, n);
			}
			return r == n - 1 || d & 1;
		};

		if (n == 2) return 1;
		for (auto p: vi{2, 3, 5, 7, 11, 13}) if (test(n, p) == 0) return 0;
		return 1;
	} /// end-hash

	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); /// start-hash
	ll myrand(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

	ll pollard(ll n) { // return some nontrivial factor of n.
		auto f = [&](ll x) { return ((__int128) x * x + 1) % n; };

		ll x = 0, y = 0, t = 30, prd = 2;
		while (t++ % 40 || gcd(prd, n) == 1) {
			// speedup: don't take __gcd in each iteration.
			if (x == y) x = myrand(2, n - 1), y = f(x);
			ll tmp = mul(prd, abs(x - y), n);
			if (tmp) prd = tmp;
			x = f(x), y = f(f(y));
		}
		return gcd(prd, n);
	}

	vector<ll> factorize(ll n) {
		vector<ll> res;

		auto dfs = [&](auto &dfs, ll x) {
			if (x == 1) return;
			if (miller(x)) res.push_back(x);
			else {
				ll d = pollard(x);
				dfs(dfs, d);
				dfs(dfs, x / d);
			}
		};
		dfs(dfs, n);
		return res;
	} /// end-hash
}
