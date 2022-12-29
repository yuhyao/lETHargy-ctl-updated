/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Let $f(x)$ be a continuous function over $[a, b]$ and have a fourth derivative,
 *  $f^{(4)}(x)$, over this interval. If $M$ is the maximum value of $|f^{(4)}(x)|$ over $[a, b]$,
 *  then the upper bound for the error is $O \left( \frac{M(b - a)^5}{N^4} \right)$.
 * Time: O(N \cdot T), where $T$ is the time for evaluating $f$ once.
 * Status: tested on https://official.contest.yandex.com/opencupXXII/contest/38278/problems/K/.
 */
template<class T = double> 
T SimpsonsRule(const function<T(T)> &f, T a, T b, int N = 1000) {
	T res = 0;
	T h = (b - a) / (N * 2);
	res += f(a);
	res += f(b);
	rep(i, 1, N * 2 - 1) res += f(a + h * i) * (i & 1 ? 4 : 2);
	return res * h / 3;
}
