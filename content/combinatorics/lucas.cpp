/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Lucas's theorem: Let $n, m$ be non-negative integers and $p$ be a prime.
 *  Write $n = n_k p^k + ... + n_1 p + n_0$ and $m = m_k p^k + ... + m_1 p +m_0$.
 *  Then $\binom{n}{m} \equiv \prod_{i=0}^k\binom{n_i}{m_i} \pmod{p}$.
 *  It is used when $p$ is not large but $n, m$ are large.
 *  Usually we use $modnum$ as template parameter.
 * Time: O(p) for preprosessing and O(\log_p n) for one query.
 * Status: tested on https://www.luogu.com.cn/problem/P3807.
 */
template<class Mint>
struct Lucas {
	int p;
	vector<Mint> fac, ifac;
	Lucas(int p = Mint::getMod()): p(p), fac(p), ifac(p) {
		fac[0] = 1;
		rep(i, 1, p - 1) fac[i] = fac[i - 1] * i;
		ifac[p - 1] = 1 / fac[p - 1];
		revrep(i, 1, p - 1) ifac[i - 1] = ifac[i] * i;
	}

	template<class T = ll>
	Mint binom(T n, T m) {
		Mint res = 1;
		while (n || m) {
			T a = n % p, b = m % p;
			if (a < b) return 0;
			res *= fac[a] * ifac[b] * ifac[a - b];
			n /= p;
			m /= p;
		}
		return res;
	}
};
