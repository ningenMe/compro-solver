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

int main() {
	int N; cin >> N;
	vector<vector<int>> edge(N);
	for(int i = 0; i < N-1; ++i) {
		int a,b; cin >> a >> b;
		a--,b--;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	corner(N==2,"1 2");
	pair<ll,ll> ans = {HIGHINF,HIGHINF};
	for(int a = 0; a < N; ++a) {
		vector<int> depth(N,-1);
		vector<ll> cnt(N,0);
		vector<ll> child(N,0);
		queue<int> q;
		q.push(a);
		depth[a] = 0;
		while (q.size()){
			int pa = q.front();
			q.pop();
			for(int ch:edge[pa]){
				if(depth[ch]!=-1) continue;
				child[pa]++;
				q.push(ch);
				depth[ch] = depth[pa]+1;
			}
		}
		for(int i = 0; i < N; ++i) chmax(cnt[depth[i]],child[i]);
		ll sum = 1,col = 0;
		for(int i = 0; i < N && cnt[i] && sum < (1LL<<51); ++i) sum *= cnt[i],col = i;
		chmin(ans,make_pair(col+2,sum));
	}
	for(int a = 0; a < N; ++a) {
		for(int b:edge[a]){
			vector<int> depth(N,-1);
			vector<ll> cnt(N,0);
			vector<ll> child(N,0);
			queue<int> q;
			q.push(a);
			q.push(b);
			depth[a] = 0;
			depth[b] = 0;
			while (q.size()){
				int pa = q.front();
				q.pop();
				for(int ch:edge[pa]){
					if(depth[ch]!=-1) continue;
					child[pa]++;
					q.push(ch);
					depth[ch] = depth[pa]+1;
				}
			}
			for(int i = 0; i < N; ++i) chmax(cnt[depth[i]],child[i]);
			ll sum = 2,col = 0;
			for(int i = 0; i < N && cnt[i] && sum < (1LL<<51); ++i) sum *= cnt[i],col = i;
			chmin(ans,make_pair(col+2,sum));
		}
	}
	cout << ans.first << " " << ans.second << endl;

    return 0;
}
