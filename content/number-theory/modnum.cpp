/**
 * Author: Yuhao Yao
 * Date: 22-10-29
 * Description: Modular integer with $mod \le 2^{30} - 1$. Note that there are several advantages to use this code:
   1. You do not need to keep writing $\%\, mod$;
   2. It is good to use this struct when doing Gaussian Elimination / Fast Walsh-Hadamard Transform;
   3. Sometimes the input number is greater than $mod$ and this code handles it.
  Do not write things like $Mint\{1 / 3\}.pow(10)$ since $1 / 3$ simply equals $0$.
  Do not write things like $Mint\{a * b\}$ where $a$ and $b$ are int since you might first have integer overflow.
 * Usage: Define the followings globally:
   const int mod = 998244353;
   using Mint = Z<mod>;
 * Status: tested on https://ac.nowcoder.com/acm/contest/33191/F.
 */
template<const int &mod>
struct Z {
	/// start-hash
	int x;
	Z(ll a = 0): x(a % mod) { if (x < 0) x += mod; }
	explicit operator int() const { return x; }

	Z& operator +=(Z b) { x += b.x; if (x >= mod) x -= mod; return *this; }
	Z& operator -=(Z b) { x -= b.x; if (x < 0) x += mod; return *this; }
	Z& operator *=(Z b) { x = 1ll * x * b.x % mod; return *this; }
	friend Z operator +(Z a, Z b) { return a += b; }
	friend Z operator -(Z a, Z b) { return a -= b; }
	friend Z operator *(Z a, Z b) { return a *= b; }
	/// end-hash

	// the followings are for ntt and polynomials.
	Z pow(ll k) const { /// start-hash
		Z res = 1, a = *this;
		for (; k; k >>= 1, a = a * a) if (k & 1) res = res * a;
		return res;
	}
	Z& operator /=(Z b) {
		assert(b.x != 0);
		return *this *= b.pow(mod - 2);
	}
	friend Z operator /(Z a, Z b) { return a /= b; }
	friend bool operator ==(Z a, Z b) { return a.x == b.x; }
	friend bool operator <(Z a, Z b) { return a.x < b.x; }

	static int getMod() { return mod; } // ntt need this.
	/// end-hash

	friend string to_string(Z a) { return to_string(a.x); }
};
