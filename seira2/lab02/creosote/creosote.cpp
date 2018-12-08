#include <limits>
#include <set>
#include <iostream>
#include <math.h>
using namespace std;
typedef long long int lli ;

lli n,A,B,C;
lli i,j,line_a,line_b;
lli x[1000000];
lli s[1000000];
lli c[1000000];

class hull_optimizer {
  struct line {
    long long m, b, value;
    double xlo;
    bool is_query, query_max;

    line(long long m, long long b, long long v, bool is_query, bool query_max)
        : m(m), b(b), value(v), xlo(-std::numeric_limits<double>::max()),
          is_query(is_query), query_max(query_max) {}

    double intersect(const line &l) const {
      if (m == l.m) {
        return std::numeric_limits<double>::max();
      }
      return (double)(l.b - b)/(m - l.m);
    }

    bool operator<(const line &l) const {
      if (l.is_query) {
        return query_max ? (xlo < l.value) : (l.value < xlo);
      }
      return m < l.m;
    }
  };

  std::set<line> hull;
  bool query_max;

  typedef std::set<line>::iterator hulliter;

  bool has_prev(hulliter it) const {
    return it != hull.begin();
  }

  bool has_next(hulliter it) const {
    return (it != hull.end()) && (++it != hull.end());
  }

  bool irrelevant(hulliter it) const {
    if (!has_prev(it) || !has_next(it)) {
      return false;
    }
    hulliter prev = it, next = it;
    --prev;
    ++next;
    return query_max ? (prev->intersect(*next) <= prev->intersect(*it))
                     : (next->intersect(*prev) <= next->intersect(*it));
  }

  hulliter update_left_border(hulliter it) {
    if ((query_max && !has_prev(it)) || (!query_max && !has_next(it))) {
      return it;
    }
    hulliter it2 = it;
    double value = it->intersect(query_max ? *--it2 : *++it2);
    line l(*it);
    l.xlo = value;
    hull.erase(it++);
    return hull.insert(it, l);
  }

 public:
  hull_optimizer(bool query_max = true) : query_max(query_max) {}

  void add_line(long long m, long long b) {
    line l(m, b, 0, false, query_max);
    hulliter it = hull.lower_bound(l);
    if (it != hull.end() && it->m == l.m) {
      if ((query_max && it->b < b) || (!query_max && b < it->b)) {
        hull.erase(it++);
      } else {
        return;
      }
    }
    it = hull.insert(it, l);
    if (irrelevant(it)) {
      hull.erase(it);
      return;
    }
    while (has_prev(it) && irrelevant(--it)) {
      hull.erase(it++);
    }
    while (has_next(it) && irrelevant(++it)) {
      hull.erase(it--);
    }
    it = update_left_border(it);
    if (has_prev(it)) {
      update_left_border(--it);
    }
    if (has_next(++it)) {
      update_left_border(++it);
    }
  }

  long long query(long long x) const {
    line q(0, 0, x, true, query_max);
    hulliter it = hull.lower_bound(q);
    if (query_max) {
      --it;
    }
    return it->m*x + it->b;
  }
};

/*** Example Usage ***/

#include <cassert>

int main() {
  hull_optimizer h;
  scanf("%lli",&n);
  scanf("%lli",&A);
  scanf("%lli",&B);
  scanf("%lli",&C);
  for (i = 0; i < n; i++){
    scanf("%lli",&x[i]);
  }
  s[0] = 0;
  s[1] = x[0];
  for (i = 2; i < n + 1; i++){
    s[i] = s[i-1] + x[i - 1];
  }
  c[0] = 0;
  c[1] =  (  A * s[1] * s[1]  + B * s[1] + C ) ;
  line_a = (-2) * A * s[0];
  line_b = ( c[0] + A * s[0] * s[0] );
  h.add_line(line_a,line_b);


  for(i = 2;i < n + 1 ;i++){

      j = i;
      line_a = (-2) * A * s[j-1];
      line_b = ( c[j - 1] + A * s[j - 1] * s[j - 1]  - B * s[j - 1] );
      h.add_line(line_a,line_b);
      c[i] = ( A *  s[i] * s[i]  + B * s[i] + C ) + h.query(s[i]);
  }

  printf("%lli\n", c[n] );
  return 0;
}
