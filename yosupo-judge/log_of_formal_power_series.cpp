#include <bits/stdc++.h>
using namespace std;

constexpr long long MOD = 998244353;

/*
 * @title ModInt
 */
template<long long mod> class ModInt {
public:
    long long x;
    constexpr ModInt():x(0) {}
    constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    ModInt &operator+=(const ModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator+=(const long long y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator+=(const int y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const ModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const long long y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const int y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator*=(const ModInt &p) {x = (x * p.x % mod);return *this;}
    ModInt &operator*=(const long long y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    ModInt &operator*=(const int y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    ModInt &operator^=(const ModInt &p) {x = (x ^ p.x) % mod;return *this;}
    ModInt &operator^=(const long long y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    ModInt &operator^=(const int y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    ModInt &operator/=(const ModInt &p) {*this *= p.inv();return *this;}
    ModInt &operator/=(const long long y) {ModInt p(y);*this *= p.inv();return *this;}
    ModInt &operator/=(const int y) {ModInt p(y);*this *= p.inv();return *this;}
    ModInt operator=(const int y) {ModInt p(y);*this = p;return *this;}
    ModInt operator=(const long long y) {ModInt p(y);*this = p;return *this;}
    ModInt operator-() const {return ModInt(-x); }
    ModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    ModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    ModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return ModInt(u);}
    ModInt pow(long long n) const {ModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const ModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, ModInt &a) {long long t;is >> t;a = ModInt<mod>(t);return (is);}
};
using modint = ModInt<MOD>;


/*
 * @title FormalPowerSeries
 */
template<int mod> struct FormalPowerSeries : public vector<ModInt<mod>> {
    inline static constexpr int prime1 =1004535809;
    inline static constexpr int prime2 =998244353;
    inline static constexpr int prime3 =985661441;
    inline static constexpr int inv21  =332747959; // ModInt<mod2>(mod1).inv().x;
    inline static constexpr int inv31  =766625513; // ModInt<mod3>(mod1).inv().x;
    inline static constexpr int inv32  =657107549; // ModInt<mod3>(mod2).inv().x;
    inline static constexpr int prime12=(1002772198720536577LL) % mod;
    inline static constexpr array<int,26> pow2 = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432};
    using vector<ModInt<mod>>::vector;
    using Mint  = ModInt<mod>;
    using Mint1 = ModInt<prime1>;
    using Mint2 = ModInt<prime2>;
    using Mint3 = ModInt<prime3>;
    using Fps   = FormalPowerSeries<mod>;
    Fps even(void) const {Fps ret;for(int i = 0; i < this->size(); i+=2) ret.push_back((*this)[i]);return ret;}
    Fps odd(void)  const {Fps ret;for(int i = 1; i < this->size(); i+=2) ret.push_back((*this)[i]);return ret;}
    Fps minus_x(void) const {Fps ret(this->size());for(int i = 0; i < ret.size(); ++i) ret[i] = (*this)[i]*(i&1?-1:1);return ret;}
    inline Mint garner(const Mint1& b1,const Mint2& b2,const Mint3& b3) {Mint2 t2 = (b2-b1.x)*inv21;Mint3 t3 = ((b3-b1.x)*inv31-t2.x)*inv32;return Mint(prime12*t3.x+b1.x+prime1*t2.x);}
    template<int prime> inline void ntt(vector<ModInt<prime>>& f) {
        const int N = f.size(), M = N>>1;
        const int log2N = __builtin_ctz(N);
        ModInt<prime> h(3);
        vector<ModInt<prime>> g(N),base(log2N);
        for(int i=0;i<log2N;++i) base[i] = h.pow((prime - 1)/pow2[i+1]);
        for(int n=0;n<log2N;++n) {
            const int& p = pow2[log2N-n-1];
            ModInt<prime> w = 1;
            for (int i=0,k=0;i<M;i+=p,k=i<<1,w*=base[n]) {
                for(int j=0;j<p;++j) {
                    ModInt<prime> l = f[k|j],r = w*f[k|j|p];
                    g[i|j]   = l + r;
                    g[i|j|M] = l - r;
                }
            }
            swap(f,g);
        }
    }
    template<int prime=mod> inline vector<ModInt<prime>> convolution_friendrymod(const vector<Mint>& a,const vector<Mint>& b){
        if (min(a.size(), b.size()) <= 60) {
            vector<ModInt<prime>> f(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++) f[i+j]+=a[i].x*b[j].x;
            return f;
        }
        int N,M=a.size()+b.size()-1; for(N=1;N<M;N*=2);
        ModInt<prime> inverse(N); inverse = inverse.inv();
        vector<ModInt<prime>> g(N,0),h(N,0);
        for(int i=0;i<a.size();++i) g[i]=a[i].x;
        for(int i=0;i<b.size();++i) h[i]=b[i].x;
        ntt<prime>(g); ntt<prime>(h);
        for(int i = 0; i < N; ++i) g[i] *= h[i]*inverse;
        reverse(g.begin()+1,g.end());
        ntt<prime>(g);
        return g;
    }
    inline vector<Mint> convolution_arbitrarymod(const vector<Mint>& g,const vector<Mint>& h){
        auto f1 = convolution_friendrymod<prime1>(g, h);
        auto f2 = convolution_friendrymod<prime2>(g, h);
        auto f3 = convolution_friendrymod<prime3>(g, h);
        vector<Mint> f(f1.size());
        for(int i=0; i<f1.size(); ++i) f[i] = garner(f1[i],f2[i],f3[i]);
        return f;
    }
    inline vector<ModInt<998244353>> convolution(const vector<ModInt<998244353>>& g,const vector<ModInt<998244353>>& h){
		return convolution_friendrymod<998244353>(g,h);
	}
    inline vector<ModInt<1000000007>> convolution(const vector<ModInt<1000000007>>& g,const vector<ModInt<1000000007>>& h){return convolution_arbitrarymod(g,h);}
    /**
     * O(log(n)*Nlog(N)) N = fps.size()
     * fpsのn項目のみを求める。
     * @param n 求めたい項数
     * @param numerator 分子のfps
     * @param denominator 分母のfps
     * @see http://q.c.titech.ac.jp/docs/progs/polynomial_division.html
     */
    static inline Mint nth_term_impl(long long n, Fps numerator,Fps denominator) {
        while(n) {
            numerator   *= denominator.minus_x();
            numerator    = ((n&1)?numerator.odd():numerator.even());
            denominator *= denominator.minus_x();
            denominator  = denominator.even();
            n >>= 1;
        }
        return numerator[0];
    }
public:
    //a0 + a_1*x^1 + a_2*x^2 + ... + a_(n-1)*x^(n-1)
    inline static Mint nth_term(long long n,const Fps& numerator,const Fps& denominator) {return nth_term_impl(n,numerator,denominator);}
    FormalPowerSeries(vector<Mint> v){*this=FormalPowerSeries(v.size());for(int i=0;i<v.size();++i) (*this)[i]=v[i];}
    Fps operator*(const Fps& r) const { return Fps(*this) *= r; }
    Fps &operator*=(const Fps& r) {return *this = convolution(*this,r);}
    Fps operator*(const int r) const {return Fps(*this) *= r; }
    Fps &operator*=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] *= r; return *this; }
    Fps operator+(const Fps& r) const { return Fps(*this) += r; }
    Fps &operator+=(const Fps& r) {if(r.size() > this->size()) this->resize(r.size());for(int i = 0; i < r.size(); i++) (*this)[i] += r[i];return *this;}
    Fps operator+(const int r) const {return Fps(*this) += r; }
    Fps &operator+=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] += r; return *this; }
    Fps operator-(void) const {return Fps(*this) *= (-1);}
    Fps operator-(const Fps& r) const { return Fps(*this) -= r; }
    Fps &operator-=(const Fps& r) {if(r.size() > this->size()) this->resize(r.size());for(int i = 0; i < r.size(); i++) (*this)[i] -= r[i];return *this;}
    Fps operator-(const int r) const {return Fps(*this) -= r; }
    Fps &operator-=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] -= r; return *this; }
    Fps prefix(size_t n) const {return Fps(this->begin(),this->begin()+min(n,this->size()));}
    Fps pow(long long n) const {Fps ret(1,1), mul(*this);for(;n > 0;mul *= mul,n >>= 1LL) if(n & 1LL) ret *= mul;return ret;}
    Fps inv(size_t n) const {Fps ret({Mint(1)/(*this)[0]});for(size_t i=1;ret.size() < n; i<<=1) ret = (ret*2-ret*(ret*(this->prefix(i<<1))).prefix(i<<1)).prefix(i<<1);return ret.prefix(n);}
    Fps inv(void) const {return inv(this->size());}
    Fps diff(void) const {Fps ret(max(0,int(this->size())-1));for(int i=0;i<ret.size(); ++i) ret[i]=(*this)[i+1]*(i+1);return ret;}
    Fps intg(void) const {Fps ret(this->size()+1);for(int i=1;i<ret.size(); ++i) ret[i]=(*this)[i-1]/i;return ret;}
    Fps log(size_t n) const {return (this->diff()*this->inv(n)).intg().prefix(n);}
    Fps log(void) const {return log(this->size());}
    Fps exp(size_t n) const {
        Fps ret(1,1);
        for(size_t i=1;ret.size()<n;i<<=1) ret = (ret*(this->prefix(i<<1) + Fps(1,1) - ret.log(i<<1))).prefix(i<<1);
        return ret.prefix(n);}
    Fps exp(void) const {return exp(this->size());}
    friend ostream &operator<<(ostream &os, const Fps& fps) {os << "{" << fps[0];for(int i=1;i<fps.size();++i) os << ", " << fps[i];return os << "}";}
};

using fps = FormalPowerSeries<MOD>;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    fps f(N);
    for(int i=0;i<N;++i) cin >> f[i];
    f = f.log();
    for(int i=0;i<f.size();++i) cout << f[i] << " \n"[i==N-1];
    return 0;
}
