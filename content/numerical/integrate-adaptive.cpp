/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Adaptive Simpson's Rule. It is somehow necessary to set the minimum depth of recursion. We use $dep$ here.
 *  Change it smaller if Time Limit is tight.
 */
template<class T = double> 
T AdaptiveIntegrate(const function<T(T)> &f, T a, T b, T eps = 1e-8, int dep = 5) {
	auto simpson = [&](T a, T b) {
		T c = (a + b) / 2;
		return (f(a) + f(c) * 4 + f(b)) * (b - a) / 6;
	};
	auto rec = [&](auto &dfs, T a, T b, T eps, T S, int dep) -> T {
		T c = (a + b) / 2;
		T S1 = simpson(a, c), S2 = simpson(c, b), sum = S1 + S2;
		if ((abs(sum - S) <= 15 * eps || b - a < 1e-10) && dep <= 0) return sum + (sum - S) / 15;
		return dfs(dfs, a, c, eps / 2, S1, dep - 1) + dfs(dfs, c, b, eps / 2, S2, dep - 1);
	};
	return rec(rec, a, b, eps, simpson(a, b), dep);
}
