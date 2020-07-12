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

int main() {
    SPEED
    int N,M; cin >> N >> M;
    vector<vector<int>> edge(N),redge(N);
    while(M--){
        int u,v; cin >> u >> v;
        u--,v--;
        edge[u].push_back(v);
        redge[v].push_back(u);
    }
    string S; cin >> S;
    S += "\"";
    auto VS = split(S,'"');
    int L = 0;
    set<int> st;
    for(auto& T:VS) {
        L++;
        if(T.substr(0,5)=="group") {
            string U = T.substr(5,T.size());
            if(T.back()=='w') {
                T = "ww";
                U.pop_back();
            }
            else {
                T = "";
            }
            st.insert(stoi(U)-1);
            break;
        }
    }
    for(int i = L-1; i < VS.size(); ++i) {
        if(VS[i]=="ww") {
            set<int> tmp;
            for(auto to:st){
                for(int from:redge[to]) tmp.insert(from);
            }            
            st=tmp;
        }
        else{
            vector<int> v(N,st.size());
            for(auto to:st){
                for(int from:redge[to]) v[from]--;
            }
            set<int> tmp;
            for(int i = 0; i < N; ++i) if(v[i]) tmp.insert(i);
            st=tmp;
        }
    }
    cout << st.size() << endl;
    return 0;
}
