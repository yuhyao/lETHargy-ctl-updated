/**
 * Author: Yuhao Yao
 * Date: 22-08-29
 * Description: Calculate the signed area of a simple Polygon $poly$. Positive area means counter-clockwise order.
 * Time: O(|poly|).
 * Status: tested on https://codeforces.com/gym/101673/problem/A.
 */
template<class T>
T PolyArea(const vector<Point<T>> &poly) {
	if (poly.empty()) return 0;
	T sum = 0;
	rep(i, 0, sz(poly) - 1) sum += (poly[i] - poly[0]).cross(poly[(i + 1) % sz(poly)] - poly[0]);
	return sum / 2;
}
