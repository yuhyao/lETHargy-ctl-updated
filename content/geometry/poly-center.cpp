/**
 * Author: Yuhao Yao
 * Date: 22-10-26
 * Description: Calculate the signed geometry center of a simple Polygon $poly$. 
 * Time: O(|poly|).
 * Status: not tested.
 */
template<class P>
P PolyCenter(const vector<P> &poly) {
	auto S = PolyArea(poly);
	if (P::sgn(S) == 0) return P{}; // think twice here.
	P cen{};
	rep(i, 0, sz(poly) - 1) {
		P p = poly[i] - poly[0];
		P q = poly[(i + 1) % sz(poly)] - poly[0];
		cen = cen + (p + q) * (p.cross(q) / (S * 6));
	}
	return cen + poly[0];
}
