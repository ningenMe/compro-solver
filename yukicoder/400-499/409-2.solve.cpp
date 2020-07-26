#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
 
#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);
 
template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;
 
constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;
 
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
/*
 * @title Rbst
 */
template<class Operator> class Rbst {
	using TypeNode = typename Operator::TypeNode;
	unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
	unsigned int xor_shift() {
		unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
	struct Node {
		Node *left, *right;
		TypeNode val;
		int size;
		TypeNode sum;

		Node() : val(Operator::unit_node), size(1), sum(Operator::unit_node) {
			left = right = nullptr;
		}
		Node(TypeNode v) : val(v), size(1), sum(v) {
			left = right = nullptr;
		}
	};
	Node* root;
	inline int size(Node *node) {
		return node==nullptr ? 0 : node->size;
	}
	inline TypeNode sum(Node *node) {
		return node==nullptr ? Operator::unit_node : node->sum;
	}
	inline Node* update(Node *node) {
		node->size = size(node->left) + size(node->right) + 1;
		node->sum = Operator::func_node(sum(node->left),sum(node->right),node->val);
		return node;
	}
	inline TypeNode get(Node *node, int k) {
		if (node==nullptr) return Operator::unit_node;
		if (k == size(node->left)) return node->val;
		if (k < size(node->left)) return get(node->left, k);
		else return get(node->right, k-1 - size(node->left));
	}
	inline int lower_bound(Node *node, TypeNode val) {
		if (node==nullptr) return 0;
		if (val <= node->val) return lower_bound(node->left, val);
		else return size(node->left) + lower_bound(node->right, val) + 1;
	}
	inline int upper_bound(Node *node, TypeNode val) {
		if (node==nullptr) return 0;
		if (val >= node->val) return size(node->left) + upper_bound(node->right, val) + 1;
		else return upper_bound(node->left, val);
	}
	Node* merge(Node *left, Node *right) {
		if (left==nullptr)  return right;
		if (right==nullptr) return left;
		if (xor_shift() % (left->size + right->size) < left->size) {
			left->right = merge(left->right, right);
			return update(left);
		}
		else {
			right->left = merge(left, right->left);
			return update(right);
		}
	}
	pair<Node*, Node*> split(Node* node, int k) {
		if (node==nullptr) return make_pair(node, node);
		if (k <= size(node->left)) {
			pair<Node*, Node*> sub = split(node->left, k);
			node->left = sub.second;
			return make_pair(sub.first, update(node));
		}
		else {
			pair<Node*, Node*> sub = split(node->right, k-1 - size(node->left));
			node->right = sub.first;
			return make_pair(update(node), sub.second);
		}
	}
	void print(Node *node) {
		if (node==nullptr) return;
		print(node->left);
		cout << node->val << " ";
		print(node->right);
	}
	Rbst(Node* node):root(node){}
public:
	Rbst() : root(nullptr) {}
	inline int size() {
		return size(this->root);
	}
	inline TypeNode sum() {
		return sum(this->root);
	}
	inline int lower_bound(TypeNode val) {
		return lower_bound(this->root, val);
	}
	inline int upper_bound(TypeNode val) {
		return upper_bound(this->root, val);
	}
	inline int empty(void) {
		return bool(size()==0);
	}
	inline int count(TypeNode val) {
		return upper_bound(val) - lower_bound(val);
	}
	inline TypeNode get(int k) {
		return get(this->root, k);
	}
	inline TypeNode get_median() {
		//奇数の時N/2
		return get(this->root, (size()-1)/2);
	}
	void merge(Rbst another) {
		root = merge(this->root, another.root);
	}
	void insert(const TypeNode val) {
		pair<Node*, Node*> sub = split(this->root, this->lower_bound(val));
		this->root = this->merge(this->merge(sub.first, new Node(val)), sub.second);
	}
	void erase(const TypeNode val) {
		if (!this->count(val)) return;
		pair<Node*, Node*> sub = this->split(this->root, this->lower_bound(val));
		this->root = this->merge(sub.first, this->split(sub.second, 1).second);
	}
	void print() {
		cout << "{";
		print(this->root);
		cout << "}" << endl;
	}
};
//https://atcoder.jp/contests/abc154/tasks/abc154_c
//https://atcoder.jp/contests/arc033/tasks/arc033_3
//https://atcoder.jp/contests/m-solutions2020/tasks/m_solutions2020_c
//https://yukicoder.me/problems/no/919
//https://yukicoder.me/problems/no/649
//https://yukicoder.me/problems/no/822

template<class T> struct NodeSum {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode c,TypeNode r){return l+c+r;}
};

template<class T> struct NodeSimple {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode c,TypeNode r){return 0;}
};

/*
 * @title ConvexHullTrick
 */
template<class Operator> class ConvexHullTrick {
private:
	using TypeValue = typename Operator::TypeValue;
	struct NodePair {
		using TypeNode = pair<TypeValue,TypeValue>;
		inline static constexpr TypeNode unit_node = {0,0};
		inline static constexpr TypeNode func_node(TypeNode l,TypeNode c,TypeNode r){return {0,0};}
	};
	Rbst<NodePair> lines;

	//cが不必要かどうか判定する
	inline int is_not_required(const pair<TypeValue,TypeValue>& l, const pair<TypeValue,TypeValue>& c, const pair<TypeValue,TypeValue>& r) {
		return (c.first - l.first) * (r.second - c.second) >= (c.second - l.second) * (r.first - c.first);
	}
	
	//y=ax+bの値
	inline TypeValue y(const pair<TypeValue,TypeValue> line, TypeValue x) {
		return line.first * x + line.second;
	}

public:
	ConvexHullTrick() {
		// do nothing
	} 

	//ax+bを追加
	void insert(const TypeValue a, const TypeValue b) {
		insert({a,b});
	}
	void insert(const pair<TypeValue,TypeValue> line) {
		int i;
		i=lines.lower_bound(line);
		if(i) {
			auto l=lines.get(i-1);
			//傾きが同じものがあるとき、どちらかをerase
			if(l.first==line.first) {
				if(Operator::func_compare(l.second,line.second)) return;
				else lines.erase(l);
			}	
		}	
		i=lines.lower_bound(line);
		if(i!=lines.size()) {
			auto r=lines.get(i);
			//傾きが同じものがあるとき、どちらかをerase
			if(line.first==r.first) {
				if(Operator::func_compare(r.second,line.second)) return;
				else lines.erase(r);
			}	
		}
		//傾きが小さい側の不必要な直線を取り除く
		for(i=lines.lower_bound(line);i>=2&&is_not_required(lines.get(i-2), lines.get(i-1), line);i=lines.lower_bound(line)) lines.erase(lines.get(i-1));
		//傾きが大きい側の不必要な直線を取り除く
		for(i=lines.lower_bound(line);i+1<lines.size()&&is_not_required(lines.get(i+1), lines.get(i), line);i=lines.lower_bound(line)) lines.erase(lines.get(i));
		lines.insert(line);
	}
	
	TypeValue get(TypeValue x) {
		int ng = -1, ok = (int)lines.size()-1, md;
		while (ok - ng > 1) {
			md = (ok + ng) >> 1;
			( Operator::func_compare(y(lines.get(md),x),y(lines.get(md+1),x)) ?ok:ng)=md;
		}
		return y(lines.get(ok),x);
	}

	void print() {
		lines.print();
	}
};

//最小値クエリ
template<class T> struct ValueMin {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l<r;}
};

//最大値クエリ
template<class T> struct ValueMax {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l>r;}
};

int main() {
	ll N,A,B,W; cin >> N >> A >> B >> W;
	vector<ll> D(N+2,0);
	for(int i = 1; i <= N; ++i) cin >> D[i];
	// dp[i]=min{j:[0,i)}-> dp[j]+B*k*(k+1)/2-k*A+D[i] (k=i-j-1)
	//                   -> dp[j]+B*(i-j-1)*(i-j)/2-(i-j-1)*A+D[i]
	//                   -> dp[j]+B/2*(i*i-2*i*j+j*j-i+j)-A*(i-j-1)+D[i]
	//                   -> (-B*j)*i  +  dp[j]+B/2*(j*j+j)+A*j  +  B/2*(i*i-i)-A*(i-1)+D[i] 
	ll dp=W;
	ConvexHullTrick<ValueMin<ll>> cht;
	cht.insert(0,dp);
	cht.print();
	for(ll i=1;i<=N+1;++i){
		dp=cht.get(i)+B*(i*i-i)/2-A*(i-1)+D[i];
		pair<long long,long long> line={-B*i,dp+B*(i*i+i)/2+A*i};
		// print(line);
		// cht.print();
		cht.insert(line);
		// cht.print();
	}
	cout << dp << endl;
    return 0;
}