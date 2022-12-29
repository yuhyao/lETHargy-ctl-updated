/**
 * Author: Yuhao Yao 
 * Date: 22-11-01
 * Description: Suppose $x_0$ satisfies that for $\frac{a}{b} < x_0$, $check(a, b) = 0$ and $\frac{a}{b} \ge x_0$, $check(a, b) = 1$. 
 *  Then returned pair $(p, q)$ satisfies $check(p, q) = 1$ and $\frac{p}{q} < x_0 + \epsilon$.
 *  Function $stop$ is used to measure the error: $stop(a_mid, b_mid) = 1$ means we are satisfied with the error.
 * Time: might be O(\log^2 \left(\frac{1}{\epsilon}\right) \cdot A), where $A$ is the running time of $check$. Not sure.
 * Status: tested on https://qoj.ac/contest/554/problem/3019.
 */
template<class T>
pair<T, T> ContinuedFrac(function<bool(T, T)> check, function<bool(T, T)> stop) {
	vector<T> as{0, 1}, bs{1, 0};
	while (stop(as[0] + as[1], bs[0] + bs[1]) == 0) {
		T amid = as[0] + as[1];
		T bmid = bs[0] + bs[1];
		int d = check(amid, bmid);
		T step = 1;
		while (check(as[d] + as[d ^ 1] * step, bs[d] + bs[d ^ 1] * step) == d) {
			as[d] += as[d ^ 1] * step;
			bs[d] += bs[d ^ 1] * step;
			step <<= 1;
			if (stop(as[0] + as[1], bs[0] + bs[1])) break;
		}
		while (step) {
			if (check(as[d] + as[d ^ 1] * step, bs[d] + bs[d ^ 1] * step) == d) {
				as[d] += as[d ^ 1] * step;
				bs[d] += bs[d ^ 1] * step;
			}
			step >>= 1;
		}
	}
	return {as[1], bs[1]};
}
