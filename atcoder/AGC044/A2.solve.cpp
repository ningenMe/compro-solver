#include <bits/stdc++.h>
using namespace std;
// using ll = long long;
using ll = __int128_t;

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

/*
 * @title NBase
 */
class NBase{
public:
	inline static vector<ll> translate(long long X,long long N) {
		assert(abs(N)>1);
		vector<ll> res;
		while(1) {
			long long b = (X%abs(N)+abs(N)) % abs(N);
			res.push_back(b);
			(X -= b) /= N;
			if(X==0) break;
		}
		return res;
	}
	//Digit Sum
	inline static constexpr long long digit_sum(long long N, long long K) {
		long long sum = 0;
		for (; N > 0; N /= K) sum += N % K;
		return sum;
	}
};


int main() {
    int T; cin >> T;
    while(T--) {
        long long N,A,B,C,D; cin >> N >> A >> B >> C >> D;
        map<ll,ll> dp;
        PQR<pair<ll,ll>> pq;
        dp[N]=0;
        pq.push({0,N});
        ll ans = 1e18;
        while(pq.size()) {
            ll X = pq.top().second;
            pq.pop();
            ll cost = dp[X];
            if(X==0) break;
            ll nxt; 
            nxt = (X - (X%2)) / 2;
            if(!dp.count(nxt) || dp[nxt] > cost + (X%2)*D + A) {
                dp[nxt] = cost + (X%2)*D + A;
                pq.push({dp[nxt],nxt});                
            }
            nxt = (X + (2-(X%2))) / 2;
            if(!dp.count(nxt) || dp[nxt] > cost + (2-(X%2))*D + A) {
                dp[nxt] = cost + (2-(X%2))*D + A;
                pq.push({dp[nxt],nxt});                
            }
            nxt = (X - (X%3)) / 3;
            if(!dp.count(nxt) || dp[nxt] > cost + (X%3)*D + B) {
                dp[nxt] = cost + (X%3)*D + B;
                pq.push({dp[nxt],nxt});                
            }
            nxt = (X + (3-(X%3))) / 3;
            if(!dp.count(nxt) || dp[nxt] > cost + ((3-(X%3)))*D + B) {
                dp[nxt] = cost + (3-(X%3))*D + B;
                pq.push({dp[nxt],nxt});                
            }
            nxt = (X - (X%5)) / 5;
            if(!dp.count(nxt) || dp[nxt] > cost + (X%5)*D + C) {
                dp[nxt] = cost + (X%5)*D + C;
                pq.push({dp[nxt],nxt});                
            }
            nxt = (X + (5-(X%5))) / 5;
            if(!dp.count(nxt) || dp[nxt] > cost + (5-(X%5))*D + C) {
                dp[nxt] = cost + (5-(X%5))*D + C;
                pq.push({dp[nxt],nxt});                
            }
            chmin(ans,cost+X*D);
        }
        chmin(ans,dp[0]);
        long long ans2 = ans;
        cout << ans2 << endl;        
    }

    return 0;
}