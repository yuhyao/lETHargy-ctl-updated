/**
 * Author: Antti Röyskö
 * Date: 25-10-2022
 * Description: A Treap with lazy tag support. Default behaviour supports join, split, reverse and sum.
 * Time: All updates are O(log N)
 * Status: tested on https://cses.fi/problemset/task/2074
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand() { return uniform_int_distribution<int>()(rng); }

struct Treap {
	private:
		const int pri;
		Treap *le = 0, *ri = 0;
		ll val, sum;
		int siz = 1, flip = 0;

		void update() {
			siz = 1 + getSiz(le) + getSiz(ri);
			sum = val + getSum(le) + getSum(ri);
		}
		void push() {
			if (flip) {
				swap(le, ri);
				reverse(le);
				reverse(ri);
				flip = 0;
			}
		}
	public:
		Treap(ll v) : val(v), sum(v), pri(rand()) {}
		~Treap() { delete le; delete ri; }

		static int getSiz(Treap* x) { return x ? x->siz : 0; }
		static ll getSum(Treap* x) { return x ? x->sum : 0; }
		static void reverse(Treap* x) { if (x) x->flip ^= 1; }

		static Treap* join(Treap* a, Treap* b) {
			if (!a || !b) return a ? a : b;
			Treap* res = (a->pri < b->pri ? a : b);
			
			res->push();
			if (res == a) a->ri = join(a->ri, b);
			else b->le = join(a, b->le);
			res->update();
			return res;
		}

		// Split the treap into a left and right part, the left of size "le_siz"
		static pair<Treap*, Treap*> split(Treap* x, int le_siz) {
			if (!le_siz || !x) return {0, x};
			x->push();
			
			Treap *oth;
			int rem = le_siz - getSiz(x->le) - 1;
			if (rem < 0) {
				tie(oth, x->le) = split(x->le, le_siz);
				x->update();
				return {oth, x};
			} else {
				tie(x->ri, oth) = split(x->ri, rem);
				x->update();
				return {x, oth};
			}
		}

};
