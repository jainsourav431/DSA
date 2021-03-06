#include <bits/stdc++.h>
#define debug(args...) //fprintf(stderr, args)
using namespace std;
 
vector< pair<int,int> > factorize(int n) {
	vector< pair<int, int> > v;
	for(int i = 2; i*i <= n; i++) {
		int count = 0;
		while((n % i) == 0) {
			count++;
			n /= i;
		}
		if(count != 0) {
			v.push_back({i, count});
		}
	}
	if(n != 1) {
		v.push_back({n, 1});
	}
	return v;
}
 
int nice(int x) {
  vector< pair<int, int> > fact = factorize(x);
  int aux = 1;
  for(int i = 0; i < fact.size(); i++)
    aux *= fact[i].first;
  return aux;
}
 
const int MAXK = 40;
 
int n, a, b, k;
vector<int> v;
vector<int> m[MAXK];
long long ans = 0;
 
void f(int idx, int cnt, int sum) {
  if(idx == n / 2) {
    debug("Montei subconjunto de tamanho %d com soma %d\n", cnt, sum);
    m[cnt].push_back(sum);
  } else {
    f(idx + 1, cnt, sum);
    f(idx + 1, cnt + 1, sum + v[idx]);
  }
}
 
void g(int idx, int cnt, int sum) {
  if(idx == n) {
    debug("Montei subconjunto de tamanho %d com soma %d\n", cnt, sum);
    for(int i = 0; i <= k - cnt; i++) {
      debug("Procurando subconjunto de tamanho %d com soma [%d, %d[\n", i, a - sum, b - sum);
      auto l = lower_bound(m[i].begin(), m[i].end(), a - sum);
      auto r = upper_bound(m[i].begin(), m[i].end(), b - sum);
      if(l != m[i].end()) {
        ans += int(r - l);
        debug("Encontrei %d\n", (r - l));
      }
    }
  } else {
    g(idx + 1, cnt, sum);
    g(idx + 1, cnt + 1, sum + v[idx]);
  }
}
 
int main() {
  scanf("%d%d%d%d", &n, &k, &a, &b);
  for(int i = 0; i < n; i++) {
    int aux;
    scanf("%d", &aux);
    debug("%d -> %d\n", aux, nice(aux));
    v.push_back(nice(aux));
  }
  f(0, 0, 0);
  for(int i = 0; i < MAXK; i++) sort(m[i].begin(), m[i].end());
  debug("...\n");
  g(n / 2, 0, 0);
  printf("%lld\n", ans);
  return 0;
}
 
