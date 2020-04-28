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
    vector<long double> A(N),L(N),R(N),B(N),C(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    long double l = -1e6-10,r = 1e6+10,ml,mr,b=0,d=0,c=0;
    for(int _=0;_<1000;_++){
        ml=(2*l+r)/3;
        mr=(l+2*r)/3;
        for(int i = 0; i < N; ++i) L[i] = i*ml;
        for(int i = 0; i < N; ++i) R[i] = i*mr;
        for(int i = 0; i < N; ++i) B[i] = A[i] - i*ml;
        for(int i = 0; i < N; ++i) C[i] = A[i] - i*mr;
        long double sl = accumulate(ALL(B),0.)/N;
        long double sr = accumulate(ALL(C),0.)/N;
        for(int i = 0; i < N; ++i) L[i] = L[i] + sl;
        for(int i = 0; i < N; ++i) R[i] = R[i] + sr;
        long double cl = 0;
        long double cr = 0;
        for(int i = 0; i < N; ++i) {
            cl += (L[i]-A[i])*(L[i]-A[i]);
            cr += (R[i]-A[i])*(R[i]-A[i]);
        }
        if(cl <= cr) {
            r = mr;
            b = L.front();
            d = l;
            c = cl;
        }
        else {
            l = ml;
            b = R.front();
            d = r;
            c = cr;
        }
    }
    printf("%.10Lf %.10Lf\n",b,d);
    printf("%.10Lf\n",c);
    return 0;
}
