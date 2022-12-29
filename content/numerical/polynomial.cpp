/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Basic polynomial struct. Usually we use $modnum$ as template parameter. $inv(k)$ gives the inverse of the polynomial $mod~ x^k$ (by default $k$ is the highest power plus one).
 * Status: inv() tested on https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 */
template<class T>
struct poly: vector<T> {
	using vector<T>::vector; /// start-hash
	poly(const vector<T> &vec): vector<T>(vec) {}
	
	friend poly& operator *=(poly &a, const poly &b) { 
		FFT<T> fft;
		a = fft.conv(a, b);
		return a;
	}
	friend poly operator *(const poly &a, const poly &b) { auto c = a; return c *= b; }

	poly inv(int n = 0) const {
		const poly &f = *this;
		assert(sz(f) > 0);
		if (n == 0) n = sz(*this);
		poly res{1 / f[0]};
		FFT<T> fft;
		for (int m = 2; m < n * 2; m <<= 1) {
			poly a(f.begin(), f.begin() + m);
			a.resize(m * 2, 0);
			res.resize(m * 2, 0);
			fft.pre(m * 2);
			fft.dft(a, 0); fft.dft(res, 0);
			rep(i, 0, m * 2 - 1) res[i] = (2 - a[i] * res[i]) * res[i];
			fft.dft(res, 1);
			res.resize(m);
		}
		res.resize(n);
		return res;
	} /// end-hash

	// the following is seldom used.
	friend poly& operator +=(poly &a, const poly &b) { /// start-hash
		if (sz(a) < sz(b)) a.resize(sz(b), 0);
		rep(i, 0, sz(b) - 1) a[i] += b[i];
		return a;
	} 
	friend poly operator +(const poly &a, const poly &b) { auto c = a; return c += b; }

	friend poly& operator -=(poly &a, const poly &b) {
		if (sz(a) < sz(b)) a.resize(sz(b), 0);
		rep(i, 0, sz(b) - 1) a[i] -= b[i];
		return a;
	}
	friend poly operator -(const poly &a, const poly &b) { auto c = a; return c -= b; }
	/// end-hash
};
