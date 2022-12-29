/**
 * Author: Antti Roeyskoe
 * Date: 22-06-15
 * License: MIT
 * Source: self
 * Description: Skew heap: a priority queue with fast merging
 * Time: all operations O(\log N).
 * Usage: ??
 * Status: not tested
 */


// Skew Heap
class SkewHeap {
	private:
		struct Node {
			ll val, inc = 0;
			int ch[2] = {-1, -1};
			Node(ll v) : val(v) {}
		};
		vector<Node> nodes;
	public:
		int makeNode(ll v) {
			nodes.emplace_back(v);
			return (int)nodes.size() - 1;
		}
		
		// Increment all values in heap p by v
		void add(int i, ll v) {
			if (i == -1) return;
			nodes[i].val += v;
			nodes[i].inc += v;
		}
		
		// Merge heaps a and b
		int merge(int a, int b) {
			if (a == -1 || b == -1) return a + b + 1;
			if (nodes[a].val > nodes[b].val) swap(a, b);
			if (nodes[a].inc) {
				add(nodes[a].ch[0], nodes[a].inc);
				add(nodes[a].ch[1], nodes[a].inc);
				nodes[a].inc = 0;
			}
			swap(nodes[a].ch[0], nodes[a].ch[1]);
			nodes[a].ch[0] = merge(nodes[a].ch[0], b);
			return a;
		}
		pair<int, ll> top(int i) const { return {i, nodes[i].val}; }
		void pop(int& p) { p = merge(nodes[p].ch[0], nodes[p].ch[1]); }
};
