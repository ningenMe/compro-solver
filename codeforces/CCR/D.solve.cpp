#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
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
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title SegmentTree - 非再帰抽象化セグメント木
 * @docs md/segment/SegmentTree.md
 */
template<class Operator> class SegmentTree {
    using TypeNode = typename Operator::TypeNode; 
    size_t length;
    size_t num;
    vector<TypeNode> node;
    vector<pair<int,int>> range;
    inline void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    SegmentTree(const size_t num): num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Operator::unit_node);
        build();
    }

    //vectorで初期化
    SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, Operator::unit_node);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }
 
    //同じinitで初期化
    SegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Operator::unit_node);
        for (int i = 0; i < length; ++i) node[i+length] = init;
        build();
    }
    
    //[idx,idx+1)
    void update(size_t idx, const TypeNode var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx] = Operator::func_merge(node[idx],var);
        while(idx >>= 1) node[idx] = Operator::func_node(node[(idx<<1)+0],node[(idx<<1)+1]);
    }

    //[l,r)
    TypeNode get(int l, int r) {
        if (l < 0 || length <= l || r < 0 || length < r) return Operator::unit_node;
        TypeNode vl = Operator::unit_node, vr = Operator::unit_node;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Operator::func_node(vl,node[l++]);
            if(r&1) vr = Operator::func_node(node[--r],vr);
        }
        return Operator::func_node(vl,vr);
    }

    //range[l,r) return [l,r] search max right
    int prefix_binary_search(int l, int r, TypeNode var) {
        assert(0 <= l && l < length && 0 < r && r <= length);
        TypeNode ret = Operator::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Operator::func_check(Operator::func_node(ret,node[idx]),var)) {
                ret = Operator::func_node(ret,node[idx]);
                off = range[idx++].second;
                if(!(idx&1)) idx >>= 1;			
            }
            else{
                idx <<=1;
            }
        }
        return off;
    }

    //range(l,r] return [l,r] search max left
    int suffix_binary_search(const int l, const int r, const TypeNode var) {
        assert(-1 <= l && l < (int)length-1 && 0 <= r && r < length);
        TypeNode ret = Operator::unit_node;
        int off = r;
        for(size_t idx = r+length; idx < 2*length && l < off; ){
            if(l < range[idx].first && !Operator::func_check(Operator::func_node(node[idx],ret),var)) {
                ret = Operator::func_node(node[idx],ret);
                off = range[idx--].first-1;
                if(idx&1) idx >>= 1;
            }
            else{
                idx = (idx<<1)+1;
            }
        }
        return off;
    }

    void print(){
        // cout << "node" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << node[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        cout << "vector" << endl;
        cout << "{ " << get(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
        cout << " }" << endl;
    }
};


//一点加算 区間総和
template<class T> struct NodeSumPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr TypeNode func_merge(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> a(N);
    for(int i=0;i<N;++i) cin >> a[i];
    SegmentTree<NodeSumPointAdd<int>> seg1for1(N,0),seg1for23(N,0),seg2for1(N,0);
    vector<vector<int>> b(N);
    for(int i=N-1; 0 <= i; --i) {
        if(a[i]==0) {
        }
        if(a[i]==1) {
            seg1for1.update(i,1);
            b[i].push_back(i);
        }
        if(a[i]==2) {
            int j = seg1for1.prefix_binary_search(i,N,1);
            // int k = seg2for1.prefix_binary_search(i,N,1);
            corner(j==N,-1);
            // if(k<N) {
            //     seg2for1.update(k,-1);
            //     int y = b[k].front();
            //     seg1for23.update(i,1);
            //     b[i].push_back(y);
            // }
            if(j<N){
                seg1for1.update(j,-1);
                int y = b[j].back();
                seg1for23.update(i,1);
                b[i].push_back(y);
            }
        }
        if(a[i]==3) {
            int j = seg1for23.prefix_binary_search(i,N,1);
            int k = seg1for1.prefix_binary_search(i,N,1);
            corner(j==N&&k==N,-1);
            if(j<N) {
                seg1for23.update(j,-1);
                seg1for23.update(i,1);
                b[i].push_back(i);
                b[j].push_back(i);
            }
            else if(k<N) {
                int y = b[k].back();
                seg1for1.update(k,-1);
                seg1for23.update(i,1);
                // seg2for1.update(k,1);
                b[i].push_back(i);
                b[k].push_back(i);
            }
        }
    }
    vector<pair<int,int>> ans;
    for(int i=0;i<N;++i) {
        for(int j:b[i]) ans.push_back({j+1,i+1});
    }
    cout << ans.size() << endl;
    for(auto& p:ans) cout << p.first << " " << p.second << endl;
    return 0;
}
