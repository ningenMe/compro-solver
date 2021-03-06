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
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}


template<class Operator> class Tree {
	Operator Op;
	using typeDist = decltype(Op.unitDist);
	size_t num;
	size_t ord;
public:
	vector<vector<pair<size_t,typeDist>>> edge;
	vector<size_t> depth;
	vector<size_t> order;
	vector<size_t> reorder;
	vector<typeDist> dist;
	vector<pair<size_t,typeDist>> parent;
	vector<vector<pair<size_t,typeDist>>> child;
	vector<array<pair<size_t,typeDist>,Operator::bit>> ancestor;
	vector<size_t> size;
	vector<vector<size_t>> descendant;
	vector<size_t> head;
	vector<size_t> hldorder;
    vector<size_t> eulertour;
    vector<pair<size_t,size_t>> eulertourrange;
	Tree(const int num):num(num),edge(num),depth(num,-1),order(num),dist(num){}
	//O(1) anytime
	void makeEdge(const int& from, const int& to, const typeDist w = 1) {
		edge[from].push_back({to,w});
	}
	//O(N) anytime
	void makeDepth(const int root) {
		depth[root] = 0;
		dist[root] = Op.unitDist;
		ord = 0;
		dfs1(root);
		order[ord++] = root;
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//O(N) anytime
	void makeDepth(void) {
		ord = 0;
		for(size_t root = 0; root < num; ++root) {
			if(depth[root] != -1) continue;
			depth[root] = 0;
			dist[root] = Op.unitDist;
			dfs1(root);
			order[ord++] = root;
		}
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//for makeDepth
	void dfs1(int curr, int prev = -1){
		for(auto& e:edge[curr]){
			int next = e.first;
			if(next==prev) continue;
			depth[next] = depth[curr] + 1;
			dist[next]  = Op.funcDist(dist[curr],e.second);
			dfs1(next,curr);
			order[ord++] = next;
		}
	}
	//O(N) after makeDepth
	void makeParent(void) {
		parent.resize(num,make_pair(num,Op.unitDist));
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] > depth[e.first]) parent[i] = e;
	}
	//O(N) after makeDepth
	void makeChild(void) {
		child.resize(num);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] < depth[e.first]) child[i].push_back(e);
	}
	//O(NlogN) after makeDepth and makeParent
	void makeAncestor(void) {
		ancestor.resize(num);
		for (size_t i = 0; i < num; ++i) ancestor[i][0] = (parent[i].first!=num?parent[i]:make_pair(i,Op.unitLca));
		for (size_t j = 1; j < Operator::bit; ++j) {
			for (size_t i = 0; i < num; ++i) {
				size_t k = ancestor[i][j - 1].first;
				ancestor[i][j] = Op.funcLca(ancestor[k][j - 1],ancestor[i][j - 1]);
			}
		}
	}
	//O(logN) after makeAncestor
	//return {lca,lca_dist} l and r must be connected
	pair<size_t,typeDist> lca(size_t l, size_t r) {
		if (depth[l] < depth[r]) swap(l, r);
		int diff = depth[l] - depth[r];
		auto ancl = make_pair(l,Op.unitLca);
		auto ancr = make_pair(r,Op.unitLca);
		for (int j = 0; j < Operator::bit; ++j) {
			if (diff & (1 << j)) {
				ancl = Op.funcLca(ancestor[ancl.first][j],ancl);
			}
		}
		if(ancl.first==ancr.first) return ancl;
		for (int j = Operator::bit - 1; 0 <= j; --j) {
			if(ancestor[ancl.first][j].first!=ancestor[ancr.first][j].first) {
				ancl = Op.funcLca(ancestor[ancl.first][j],ancl);
				ancr = Op.funcLca(ancestor[ancr.first][j],ancr);
			}
		}
		ancl = Op.funcLca(ancestor[ancl.first][0],ancl);
		ancr = Op.funcLca(ancestor[ancr.first][0],ancr);
		return Op.funcLca(ancl,ancr);
	}
	//O(N) anytime
	int diameter(void){
		makeDepth(0);
		int tmp = max_element(depth.begin(), depth.end()) - depth.begin();
		makeDepth(tmp);
		return *max_element(depth.begin(), depth.end());
	}
	//O(N^2) after makeDepth (include self)
	void makeDescendant(void) {
		descendant.resize(num);
		for (size_t i = 0; i < num; ++i) descendant[i].push_back(i);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[order[i]]) if (depth[order[i]] < depth[e.first]) for(auto k: descendant[e.first]) descendant[order[i]].push_back(k);
	}
	//O(N) after makeChild
	void makeSize(void) {
		size.resize(num,1);
		for (size_t i:order) for (auto e : child[i]) size[i] += size[e.first];
	}
	//(N) after makeDepth and makeChild
	template<class typeReroot> vector<typeReroot> rerooting(vector<typeReroot> rerootdp,vector<typeReroot> rerootparent) {
		for(size_t pa:order) for(auto& e:child[pa]) rerootdp[pa] = Op.funcReroot(rerootdp[pa],rerootdp[e.first]);
		for(size_t pa:reorder) {
			if(depth[pa]) rerootdp[pa] = Op.funcReroot(rerootdp[pa],rerootparent[pa]);
			size_t m = child[pa].size();
			for(int j = 0; j < m && depth[pa]; ++j){
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Op.funcReroot(rerootparent[ch],rerootparent[pa]);
			}
			if(m <= 1) continue;
			vector<typeReroot> l(m),r(m);
			for(int j = 0; j < m; ++j) {
				size_t ch = child[pa][j].first;
				l[j] = rerootdp[ch];
				r[j] = rerootdp[ch];
			}
			for(int j = 1; j+1 < m; ++j) l[j] = Op.funcRerootMerge(l[j],l[j-1]);
			for(int j = m-2; 0 <=j; --j) r[j] = Op.funcRerootMerge(r[j],r[j+1]);
			size_t chl = child[pa].front().first;
			size_t chr = child[pa].back().first;
			rerootparent[chl] = Op.funcReroot(rerootparent[chl],r[1]);
			rerootparent[chr] = Op.funcReroot(rerootparent[chr],l[m-2]);
			for(int j = 1; j+1 < m; ++j) {
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Op.funcReroot(rerootparent[ch],l[j-1]);
				rerootparent[ch] = Op.funcReroot(rerootparent[ch],r[j+1]);
			}
		}
		return rerootdp;
    }
	//O(N) after makeDepth,makeParent,makeChild
	void heavyLightDecomposition(){
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
	size_t hldLca(size_t u,size_t v){
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]==head[v]) return u;
			v=parent[head[v]].first;
		}
	}
    //O(N) after makeChild and makeParent
	void makeEulerTour(void){
        dfs2(reorder.front());
        eulertourrange.resize(num);
        for(int i = 0; i < eulertour.size(); ++i) eulertourrange[eulertour[i]].second = i;
        for(int i = eulertour.size()-1; 0 <= i; --i) eulertourrange[eulertour[i]].first = i;
		return;
	}
    //for makeEulerTour
	void dfs2(int from, int prev = -1){
		eulertour.push_back(from);
        for(auto& e:child[from]){
            int to = e.first;            
            dfs2(to,from);        
    		eulertour.push_back(from);
        }
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
//descendant
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
template<class typeDist> struct treeOperator{
	static const size_t bit = 20;
	typeDist unitDist = 0;
	typeDist unitLca = 0;
	typeDist funcDist(const typeDist& parent,const typeDist& w){return parent+w;}
	pair<size_t,typeDist> funcLca(const pair<size_t,typeDist>& l,const pair<size_t,typeDist>& r){return make_pair(l.first,l.second+r.second);}
	template<class typeReroot> typeReroot funcReroot(const typeReroot& l,const typeReroot& r) {
		return {l.first+r.first+r.second,l.second+r.second};
	}
	template<class typeReroot> typeReroot funcRerootMerge(const typeReroot& l,const typeReroot& r) {
		return {l.first+r.first,l.second+r.second};
	}
};
//Tree<treeOperator<ll>> tree(N);

vector<ll> c,anc;
map<pair<int,int>,ll> mp;
void dfs(int curr,vector<pair<int,int>>& last, Tree<treeOperator<int>>& tree){
	int d = c[curr];
	if(last[d]==make_pair(-1,-1)){
		anc[d] -= (ll)tree.size[curr];
	}
	else{
		mp[last[d]] -= (ll)tree.size[curr];
	}
	for(auto e:tree.child[curr]){
		int next = e.first;
		mp[{curr,next}] += (ll)tree.size[next];
		auto prev_last = last[d];
		last[d] = {curr,next};
		dfs(next,last,tree);
		last[d] = prev_last;
	}
}

int main() {
	ll N; cin >> N;
	c.resize(N);
	anc.resize(N,N);
	for(int i = 0; i < N; ++i) cin >> c[i],c[i]--;
	Tree<treeOperator<int>> tree(N);
	for(int i = 0; i < N-1; ++i) {
		int a,b; cin >> a >> b;
		a--,b--;
		tree.makeEdge(a,b);
		tree.makeEdge(b,a);
	}
	tree.makeDepth(0);
	tree.makeChild();
	tree.makeSize();
	vector<pair<int,int>> last(N,{-1,-1});
	dfs(0,last,tree);
	vector<ll> ans(N,N*(N+1)/2);
	for(int i = 0; i < N; ++i) {
		ans[i] -= (anc[i]*(anc[i]+1))/2;
	}
	for(auto& e:mp) {
		int i = e.first.first;
		ll x = e.second;
		ans[c[i]] -= (x*(x+1))/2;
	}
	for(int i = 0; i < N; ++i) cout << ans[i] << endl;
    return 0;
}
