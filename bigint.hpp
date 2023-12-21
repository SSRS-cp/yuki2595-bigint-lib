#include <vector>
#include <string>
#include <atcoder/convolution>
const int DIGIT = 6;
const int BASE = 1000000;
struct positive_bigint{
  std::vector<int> d;
  positive_bigint(){
  }
  positive_bigint(long long X){
    while (X > 0){
      d.push_back(X % BASE);
      X /= BASE;
    }
  }
  positive_bigint(std::string S){
    if (S == "0"){
      S = "";
    }
    int L = S.size();
    d.resize((L + DIGIT - 1) / DIGIT, 0);
    for (int i = L - 1; i >= 0; i -= 6){
      for (int j = std::max(i - 5, 0); j <= i; j++){
        d[i / DIGIT] *= 10;
        d[i / DIGIT] += S[j] - '0';
      }
    }
    std::reverse(d.begin(), d.end());
  }
  bool empty() const {
    return d.empty();
  }
  int size() const {
    return d.size();
  }
  int& operator [](int i){
    return d[i];
  }
  int operator [](int i) const {
    return d[i];
  }
};
std::string to_string(const positive_bigint &A){
  int N = A.size();
  std::string ans;
  for (int i = N - 1; i >= 0; i--){
    std::string tmp = std::to_string(A[i]);
    if (i < N - 1){
      ans += std::string(DIGIT - tmp.size(), '0');
    }
    ans += tmp;
  }
  if (ans.empty()){
    ans = "0";
  }
  return ans;
}
std::istream& operator >>(std::istream &is, positive_bigint &A){
  std::string S;
  is >> S;
  A = positive_bigint(S);
  return is;
}
std::ostream& operator <<(std::ostream &os, positive_bigint &A){
  os << to_string(A);
  return os;
}
int cmp(const positive_bigint &A, const positive_bigint &B){
  int N = A.size();
  int M = B.size();
  if (N < M){
    return -1;
  } else if (N > M){
    return 1;
  } else {
    for (int i = N - 1; i >= 0; i--){
      if (A[i] < B[i]){
        return -1;
      }
      if (A[i] > B[i]){
        return 1;
      }
    }
    return 0;
  }
}
bool operator ==(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) == 0;
}
bool operator !=(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) != 0;
}
bool operator <(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) < 0;
}
bool operator >(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) > 0;
}
bool operator <=(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) <= 0;
}
bool operator >=(const positive_bigint &A, const positive_bigint &B){
  return cmp(A, B) >= 0;
}
positive_bigint& operator +=(positive_bigint &A, const positive_bigint &B){
  int N = A.size();
  int M = B.size();
  while (N < M){
    A.d.push_back(0);
    N++;
  }
  for (int i = 0; i < M; i++){
    A[i] += B[i];
  }
  for (int i = 0; i < N - 1; i++){
    if (A[i] >= BASE){
      A[i] -= BASE;
      A[i + 1]++;
    }
  }
  if (N > 0){
    if (A[N - 1] >= BASE){
      A.d.push_back(1);
      A[N - 1] -= BASE;
    }
  }
  return A;
}
positive_bigint operator +(const positive_bigint &A, const positive_bigint &B){
  positive_bigint A2 = A;
  A2 += B;
  return A2;
}
positive_bigint& operator -=(positive_bigint &A, const positive_bigint &B){
  int N = A.size();
  int M = B.size();
  for (int i = 0; i < M; i++){
    A[i] -= B[i];
  }
  for (int i = 0; i < N - 1; i++){
    if (A[i] < 0){
      A[i] += BASE;
      A[i + 1]--;
    }
  }
  while (!A.empty()){
    if (A.d.back() == 0){
      A.d.pop_back();
    } else {
      break;
    }
  }
  return A;
}
positive_bigint operator -(const positive_bigint &A, const positive_bigint &B){
  positive_bigint A2 = A;
  A2 -= B;
  return A2;
}
positive_bigint operator *(const positive_bigint &A, const positive_bigint &B){
  if (A.empty() || B.empty()){
    return 0;
  }
  int N = A.size();
  int M = B.size();
  std::vector<long long> a(N);
  for (int i=  0; i < N; i++){
    a[i] = A[i];
  }
  std::vector<long long> b(M);
  for (int i = 0; i < M; i++){
    b[i] = B[i];
  }
  std::vector<long long> C = atcoder::convolution_ll(a, b);
  for (int i = 0; i < N + M - 2; i++){
    C[i + 1] += C[i] / BASE;
    C[i] %= BASE;
  }
  if (C[N + M - 2] >= BASE){
    C.resize(N + M);
    C[N + M - 1] += C[N + M - 2] / BASE;
    C[N + M - 2] %= BASE;
  }
  positive_bigint ans;
  ans.d.resize(C.size());
  for (int i = 0; i < C.size(); i++){
    ans[i] = C[i];
  }
  return ans;
}
positive_bigint operator *=(positive_bigint &A, const positive_bigint &B){
  A = A * B;
  return A;
}
struct bigint{
  bool neg = false;
  positive_bigint a;
  bigint(){
  }
  bigint(long long X): neg(X < 0), a(abs(X)){
  }
  bigint(const positive_bigint &X, bool neg = false): neg(neg), a(X){
  }
  bigint(const std::string &s){
    if (!s.empty()){
      if (s[0] == '-'){
        neg = true;
        a = positive_bigint(s.substr(1, s.size() - 1));
      } else {
        a = positive_bigint(s);
      }
    }
  }
  bool empty() const {
    return a.empty();
  }
  int size() const {
    return a.size();
  }
  int& operator [](int i){
    return a[i];
  }
};
std::string to_string(const bigint &A){
  std::string ans;
  if (A.neg){
    ans += '-';
  }
  ans += to_string(A.a);
  return ans;
}
std::istream& operator >>(std::istream &is, bigint &A){
  std::string S;
  is >> S;
  if (S != "0"){
    A = bigint(S);
  }
  return is;
}
std::ostream& operator <<(std::ostream &os, bigint A){
  os << to_string(A);
  return os;
}
positive_bigint abs(const bigint &A){
  return A.a;
}
int cmp(const bigint &A, const bigint &B){
  if (!A.neg){
    if (!B.neg){
      return cmp(A.a, B.a);
    } else {
      return 1;
    }
  } else {
    if (!B.neg){
      return -1;
    } else {
      return cmp(B.a, A.a);
    }
  }
}
bool operator ==(const bigint &A, const bigint &B){
  return cmp(A, B) == 0;
}
bool operator !=(const bigint &A, const bigint &B){
  return cmp(A, B) != 0;
}
bool operator <(const bigint &A, const bigint &B){
  return cmp(A, B) < 0;
}
bool operator >(const bigint &A, const bigint &B){
  return cmp(A, B) > 0;
}
bool operator <=(const bigint &A, const bigint &B){
  return cmp(A, B) <= 0;
}
bool operator >=(const bigint &A, const bigint &B){
  return cmp(A, B) >= 0;
}
bigint operator +(const bigint &A){
  return A;
}
bigint operator -(const bigint &A){
  bigint A2 = A;
  if (!A2.empty()){
    A2.neg = !A2.neg;
  }
  return A2;
}
bigint& operator +=(bigint &A, const bigint &B){
  if (A.neg == B.neg){
    A.a += B.a;
  } else {
    int c = cmp(A.a, B.a);
    if (c > 0){
      A.a -= B.a;
    } else if (c < 0){
      A.a = B.a - A.a;
      A.neg = !A.neg;
    } else {
      A = 0;
    }
  }
  return A;
}
bigint operator +(const bigint &A, const bigint &B){
  bigint A2 = A;
  A2 += B;
  return A2;
}
bigint& operator -=(bigint &A, const bigint &B){
  if (A.neg != B.neg){
    A.a += B.a;
  } else {
    int c = cmp(A.a, B.a);
    if (c > 0){
      A.a -= B.a;
    } else if (c < 0){
      A.a = B.a - A.a;
      A.neg = !A.neg;
    } else {
      A = 0;
    }
  }
  return A;
}
bigint operator -(const bigint &A, const bigint &B){
  bigint A2 = A;
  A2 -= B;
  return A2;
}
bigint operator *=(bigint &A, const bigint &B){
  if (A.empty() || B.empty()){
    A = 0;
  } else {
    if (B.neg){
      A.neg = !A.neg;
    }
    A.a *= B.a;
  }
  return A;
}
bigint operator *(const bigint &A, const bigint &B){
  bigint A2 = A;
  A2 *= B;
  return A2;
}