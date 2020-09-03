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
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

template<class T> class Mo{
    int N;
    int bucket;
    vector<pair<int,int>> range;
	vector<int> idx;
    vector<T> ans;
public:

    //range is [l,r]
    Mo(int N, const vector<pair<int,int>>& range) : N(N),range(range),idx(range.size()),ans(range.size()),bucket(1000) {
        iota(idx.begin(),idx.end(),0);
        sort(idx.begin(),idx.end(),[&](int a, int b){
            auto  al = range[a].first/bucket;
            auto  ar = range[a].second;
            auto  bl = range[b].first/bucket;
            auto  br = range[b].second;
            return (al != bl) ? (al < bl) : ((al%2)?(ar > br):(ar < br));
        });
    }
    
    //参照でvectorを渡したりすると良い
    void solve(const vector<int>& A,vector<int>& cnt,int& sum){
        int l = 0, r = 0;
        for(int& i:idx){
            auto& xl = range[i].first;
            auto& xr = range[i].second;
            
            //左端を広げる
            while(xl < l){
                l--;
                extend(l,A,cnt,sum);
            }
            //右端を広げる
            while(r < xr){
                r++;
                extend(r,A,cnt,sum);
            }
            //左端を狭める
            while(l < xl){
                shrink(l,A,cnt,sum);
                l++;
            }
            //右端を狭める
            while(xr < r){
                shrink(r,A,cnt,sum);
                r--;
            }
            ans[i] = get(sum);
        }
    }

    T& operator [] (int k) {
        return ans[k];
    }

private:
    
    //伸びるとき
    inline void extend(int k,const vector<int>& A, vector<int>& cnt, int& sum){
        cnt[A[k]]++;
        if(cnt[A[k]]==1) sum++;
    }

    //縮むとき
    inline void shrink(int k,const vector<int>& A, vector<int>& cnt, int& sum){
        cnt[A[k]]--;
        if(cnt[A[k]]==0) sum--;
    }

    //クエリ結果
    inline T get(int& sum){
        return sum;
    }
};

int main() {
	int N,Q;
    scanf("%d %d",&N,&Q);
    vector<int> A(N);
	for(int i = 0; i < N; ++i) scanf("%d",&A[i]);
	//クエリ区間を列挙
	vector<pair<int,int>> range(Q);
	for(int i = 0; i < Q; ++i) {
        int l,r; cin >> l >> r;
        l--,r--;
        range[i]={l,r};
	}
	
	//Mo O(N*sqrt(N))
    Mo<int> mo(N,range);
    vector<int> cnt(N+1,0);
    int sum=1;
    cnt[A[0]]++;
    mo.solve(A,cnt,sum);
	for(int i = 0; i < Q; ++i) {
        printf("%d\n",mo[i]);
	}


    return 0;
}