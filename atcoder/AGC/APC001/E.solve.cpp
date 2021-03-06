#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title Tree
 * @docs md/graph/Tree.md
 */
template<class Operator> class Tree {
	using TypeDist = typename Operator::TypeDist;
	size_t num;
	size_t ord;
	enum METHODS{
		MAKE_DEPTH,
		MAKE_CHILD,
		MAKE_PARENT,
		MAKE_SIZE,
		MAKE_SUBTREE,
		MAKE_ANCESTOR,
		MAKE_EOULERTOUR,
		MAKE_HEAVY_LIGHT_DECOMPOSITION,
		METHODS_SIZE,
	};
	array<int,METHODS_SIZE> executed_flag;
public:
	vector<vector<pair<size_t,TypeDist>>> edge;
	vector<size_t> depth;
	vector<size_t> order;
	vector<size_t> reorder;
	vector<TypeDist> dist;
	vector<pair<size_t,TypeDist>> parent;
	vector<vector<pair<size_t,TypeDist>>> child;
	vector<array<pair<size_t,TypeDist>,Operator::bit>> ancestor;
	vector<size_t> size;
	vector<vector<size_t>> subtree;
	vector<size_t> head;
	vector<size_t> hldorder;
	vector<size_t> eulertour;
	vector<pair<size_t,size_t>> eulertour_range;
	Tree(const int num):num(num),edge(num),depth(num,-1),order(num),dist(num),executed_flag(){}
	//O(1) anytime
	void make_edge(const int& from, const int& to, const TypeDist w = 1) {
		edge[from].push_back({to,w});
	}
	//O(N) anytime
	void make_depth(const int root) {
		if(executed_flag[MAKE_DEPTH]++) return;
		depth[root] = 0;
		dist[root] = Operator::unit_dist;
		ord = 0;
		dfs(root,-1);
		order[ord++] = root;
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//O(N) anytime for forest
	void make_depth(void) {
		if(executed_flag[MAKE_DEPTH]++) return;
		ord = 0;
		for(size_t root = 0; root < num; ++root) {
			if(depth[root] != -1) continue;
			depth[root] = 0;
			dist[root] = Operator::unit_dist;
			dfs(root,-1);
			order[ord++] = root;
		}
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//for make_depth
	void dfs(int curr, int prev){
		for(auto& e:edge[curr]){
			int next = e.first;
			if(next==prev) continue;
			depth[next] = depth[curr] + 1;
			dist[next]  = Operator::func_dist(dist[curr],e.second);
			dfs(next,curr);
			order[ord++] = next;
		}
	}
	//for make_eulertour
	void dfs(int from){
		eulertour.push_back(from);
		for(auto& e:child[from]){
			int to = e.first;            
			dfs(to);        
			eulertour.push_back(from);
		}
	}
	//O(N) after make_depth
	void make_parent(const int root = 0) {
		if(executed_flag[MAKE_PARENT]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		parent.resize(num,make_pair(num,Operator::unit_dist));
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] > depth[e.first]) parent[i] = e;
	}
	//O(N) after make_depth
	void make_child(const int root = 0) {
		if(executed_flag[MAKE_CHILD]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		child.resize(num);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] < depth[e.first]) child[i].push_back(e);
	}
	//O(NlogN) after make_parent
	void make_ancestor(const int root = 0) {
		if(executed_flag[MAKE_ANCESTOR]++) return;
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		ancestor.resize(num);
		for (size_t i = 0; i < num; ++i) ancestor[i][0] = (parent[i].first!=num?parent[i]:make_pair(i,Operator::unit_lca));
		for (size_t j = 1; j < Operator::bit; ++j) {
			for (size_t i = 0; i < num; ++i) {
				size_t k = ancestor[i][j - 1].first;
				ancestor[i][j] = Operator::func_lca(ancestor[k][j - 1],ancestor[i][j - 1]);
			}
		}
	}
	//O(logN) after make_ancestor
	//return {lca,lca_dist} l and r must be connected
	pair<size_t,TypeDist> lca(size_t l, size_t r) {
		assert(executed_flag[MAKE_ANCESTOR]);
		if (depth[l] < depth[r]) swap(l, r);
		int diff = depth[l] - depth[r];
		auto ancl = make_pair(l,Operator::unit_lca);
		auto ancr = make_pair(r,Operator::unit_lca);
		for (int j = 0; j < Operator::bit; ++j) {
			if (diff & (1 << j)) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
			}
		}
		if(ancl.first==ancr.first) return ancl;
		for (int j = Operator::bit - 1; 0 <= j; --j) {
			if(ancestor[ancl.first][j].first!=ancestor[ancr.first][j].first) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
				ancr = Operator::func_lca(ancestor[ancr.first][j],ancr);
			}
		}
		ancl = Operator::func_lca(ancestor[ancl.first][0],ancl);
		ancr = Operator::func_lca(ancestor[ancr.first][0],ancr);
		return Operator::func_lca(ancl,ancr);
	}
	//O(N) anytime
	int diameter(void){
		make_depth(0);
		int tmp = max_element(depth.begin(), depth.end()) - depth.begin();
		make_depth(tmp);
		return *max_element(depth.begin(), depth.end());
	}
	//O(N^2) after make_depth
	void make_subtree(const int root = 0) {
		if(executed_flag[MAKE_SUBTREE]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		subtree.resize(num);
		for (size_t i = 0; i < num; ++i) subtree[i].push_back(i);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[order[i]]) if (depth[order[i]] < depth[e.first]) for(auto k: subtree[e.first]) subtree[order[i]].push_back(k);
	}
	//O(N) after make_child
	void make_size(const int root = 0) {
		if(executed_flag[MAKE_SIZE]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		size.resize(num,1);
		for (size_t i:order) for (auto e : child[i]) size[i] += size[e.first];
	}
	//(N) after make_depth and make_child
	template<class TypeReroot> vector<TypeReroot> rerooting(vector<TypeReroot> rerootdp,vector<TypeReroot> rerootparent) {
		assert(executed_flag[MAKE_CHILD]);
		for(size_t pa:order) for(auto& e:child[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootdp[e.first]);
		for(size_t pa:reorder) {
			if(depth[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootparent[pa]);
			size_t m = child[pa].size();
			//paのpaを先にchにマージ
			for(int j = 0; j < m && depth[pa]; ++j){
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],rerootparent[pa]);
			}
			if(m <= 1) continue;
			vector<TypeReroot> l(m),r(m);
			for(int j = 0; j < m; ++j) {
				size_t ch = child[pa][j].first;
				l[j] = rerootdp[ch];
				r[j] = rerootdp[ch];
			}
			for(int j = 1; j+1 < m; ++j) l[j] = Operator::func_reroot_merge(l[j],l[j-1]);
			for(int j = m-2; 0 <=j; --j) r[j] = Operator::func_reroot_merge(r[j],r[j+1]);
			size_t chl = child[pa].front().first;
			size_t chr = child[pa].back().first;
			rerootparent[chl] = Operator::func_reroot(rerootparent[chl],r[1]);
			rerootparent[chr] = Operator::func_reroot(rerootparent[chr],l[m-2]);
			for(int j = 1; j+1 < m; ++j) {
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],l[j-1]);
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],r[j+1]);
			}
		}
		return rerootdp;
	}
	//O(N) after make_depth,make_parent,make_child
	void make_heavy_light_decomposition(const int root = 0){
		if(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]++) return;
		if(!executed_flag[MAKE_SIZE]) make_size(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		head.resize(num);
		hldorder.resize(num);
		iota(head.begin(),head.end(),0);
		for(size_t& pa:reorder) {
			pair<size_t,size_t> maxi = {0,num};
			for(auto& e:child[pa]) maxi = max(maxi,{size[e.first],e.first});
			if(maxi.first) head[maxi.second] = head[pa];
		}
		stack<size_t> st_head,st_sub;
		size_t cnt = 0;
		for(size_t& root:reorder){
			if(depth[root]) continue;
			st_head.push(root);
			while(st_head.size()){
				size_t h = st_head.top();
				st_head.pop();
				st_sub.push(h);
				while (st_sub.size()){
					size_t pa = st_sub.top();
					st_sub.pop();
					hldorder[pa] = cnt++;
					for(auto& e:child[pa]) {
						if(head[e.first]==head[pa]) st_sub.push(e.first);
						else st_head.push(e.first);
					}
				}				
			}
		}
	}
	//after hld type 0: vertex, 1: edge
	vector<pair<size_t,size_t>> path(size_t u,size_t v,int type = 0) {
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		vector<pair<size_t,size_t>> path;
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]!=head[v]) {
				path.push_back({hldorder[head[v]],hldorder[v]});
				v=parent[head[v]].first;
			}
			else {
				path.push_back({hldorder[u],hldorder[v]});
				break;
			}
		}
		reverse(path.begin(),path.end());
		if(type) path.front().first++;
		return path;
	}
	size_t hld_lca(size_t u,size_t v){
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]==head[v]) return u;
			v=parent[head[v]].first;
		}
	}
	//O(N) after make_child and make_parent
	void make_eulertour(const int root = 0){
		if(executed_flag[MAKE_EOULERTOUR]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		dfs(reorder.front());
		eulertour_range.resize(num);
		for(int i = 0; i < eulertour.size(); ++i) eulertour_range[eulertour[i]].second = i;
		for(int i = eulertour.size()-1; 0 <= i; --i) eulertour_range[eulertour[i]].first = i;
	}
};
//depth,dist
//https://atcoder.jp/contests/abc126/tasks/abc126_d
//child
//https://atcoder.jp/contests/abc133/tasks/abc133_e
//lca
//https://atcoder.jp/contests/abc014/tasks/abc014_4
//weighted lca
//https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h
//https://atcoder.jp/contests/cf16-tournament-round1-open/tasks/asaporo_c
//diameter
//https://atcoder.jp/contests/agc033/tasks/agc033_c
//subtree
//https://atcoder.jp/contests/code-thanks-festival-2018/tasks/code_thanks_festival_2018_f
//rerooting
//https://yukicoder.me/problems/no/922
//size
//https://yukicoder.me/problems/no/872
//eulerTour
//https://yukicoder.me/problems/no/900
//hld
//https://yukicoder.me/problems/no/399
//https://yukicoder.me/problems/no/650
template<class T> struct TreeOperator{
	using TypeDist = T;
	inline static constexpr size_t bit = 20;
	inline static constexpr TypeDist unit_dist = 0;
	inline static constexpr TypeDist unit_lca = 0;
	inline static constexpr TypeDist func_dist(const TypeDist& parent,const TypeDist& w){return parent+w;}
	inline static constexpr pair<size_t,TypeDist> func_lca(const pair<size_t,TypeDist>& l,const pair<size_t,TypeDist>& r){return make_pair(l.first,l.second+r.second);}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first+r.second,l.second+r.second};
	}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot_merge(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first,l.second+r.second};
	}
};

/*
 * @title DisjointSparseTable
 */
template<class Operator> class DisjointSparseTable{
public:
	using TypeNode = typename Operator::TypeNode;
	size_t depth;
	size_t length;
	vector<TypeNode> node;
	vector<size_t> msb;

	DisjointSparseTable(const vector<TypeNode>& vec) {
		for(depth = 0;(1<<depth)<=vec.size();++depth);
		length = (1<<depth);
		
		//msb
		msb.resize(length,0);
		for(int i = 0; i < length; ++i) for(int j = 0; j < depth; ++j) if(i>>j) msb[i] = j;

		//init value
		node.resize(depth*length,Operator::unit_node);
		for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];

		for(int i = 1; i < depth; ++i) {
			for(int r = (1<<i),l = r-1; r < length; r += (2<<i),l = r-1){
				//init accumulate
				node[i*length+l] = node[l];
				node[i*length+r] = node[r];
				//accumulate
				for(int k = 1; k < (1<<i); ++k) {
					node[i*length+l-k] = Operator::func_node(node[i*length+l-k+1],node[l-k]);
					node[i*length+r+k] = Operator::func_node(node[i*length+r+k-1],node[r+k]);
				}
			}
		}
	}

	//[l,r)
	TypeNode get(int l,int r) {
		r--;
		return (l>r||l<0||length<=r) ? Operator::unit_node: (l==r ? node[l] : Operator::func_node(node[msb[l^r]*length+l],node[msb[l^r]*length+r]));
	}
};

//sum
template<class T> struct NodeSum {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return l+r;}
};

int main() {
	int N; cin >> N;
	Tree<TreeOperator<ll>> tree(N);
	vector<ll> dim(N,0);
	for(int i = 0; i < N-1; ++i) {
		int u,v; cin >> u >> v;
		dim[u]++,dim[v]++;
		tree.make_edge(u,v);
		tree.make_edge(v,u);
	}
	corner(N==1,1);
	int root;
	for(int i = 0; i < N; ++i) if(dim[i]>1) root=i;
	tree.make_depth(root);
	tree.make_child();
	vector<pair<ll,ll>> dp(N,{N,N});
	for(int pa:tree.order){
		int m = tree.child[pa].size();
		if(m==0){
			dp[pa]={0,1};
			continue;
		}
		vector<ll> a,b;
		for(auto e:tree.child[pa]) {
			int ch=e.first;
			a.push_back(dp[ch].first);
			b.push_back(dp[ch].second);
		}
		if(m==1){
			dp[pa]={a[0],b[0]};
			continue;
		}
		DisjointSparseTable<NodeSum<ll>> s(b);
		chmin(dp[pa].second,s.get(0,m));
		for(int i = 0; i < m; ++i) chmin(dp[pa].second,s.get(0,i)+a[i]+s.get(i+1,m));
	}
	int ans=min(dp[root].first,dp[root].second);
	cout << ans << endl;
    return 0;
}
