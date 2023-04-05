#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<ll>;
using vs = vector<string>;

class P {
public:
	P(int r, int c, int bc)
		: r_{ r }
		, c_{ c }
		, bc_{ bc } {
	}

	int r_{};
	int c_{};
	int bc_{};
};

using qP = queue<P>;

constexpr auto inf = int{ 987'654'321 };

const auto& dr = vi{ -1,1,0,0 };
const auto& dc = vi{ 0,0,-1,1 };

int solve(int n, int m, const vs& map) {
	auto dist = vvvi(n, vvi(m, vi(2, inf)));
	dist[0][0][0] = 1;

	auto q = qP{};

	const auto& p0 = P{ 0, 0, 0 };
	q.push(p0);

	while (!q.empty()) {
		auto f = q.front();
		q.pop();

		if (n - 1 == f.r_ &&
			m - 1 == f.c_) {
			break;
		}

		for (auto d = 0; d < 4; ++d) {
			const auto& nr = f.r_ + dr[d];
			const auto& nc = f.c_ + dc[d];

			if (nr < 0 || n <= nr ||
				nc < 0 || m <= nc) {
				continue;
			}

			if ('1' == map[nr][nc] &&
				1 == f.bc_) {
				continue;
			}

			if ('1' == map[nr][nc] && 0 == f.bc_) {
				const auto& newDist = dist[f.r_][f.c_][0] + 1;
				if (newDist < dist[nr][nc][1]) {
					dist[nr][nc][1] = newDist;
					const auto& p1 = P{ nr, nc, 1 };
					q.push(p1);
				}
			}

			if ('0' == map[nr][nc]) {
				const auto& newDist = dist[f.r_][f.c_][f.bc_] + 1;
				if (newDist < dist[nr][nc][f.bc_]) {
					dist[nr][nc][f.bc_] = newDist;
					const auto& p1 = P{ nr, nc, f.bc_ };
					q.push(p1);
				}
			}
		}
	}

	const auto& d0 = dist[n - 1][m - 1][0];
	const auto& d1 = dist[n - 1][m - 1][1];
	if (inf == d0 &&
		inf == d1) {
		return -1;
	}
	else {
		return (d0 < d1 ? d0 : d1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	auto map = vs(n);
	for (auto r = 0; r < n; ++r) {
		cin >> map[r];
	}

	const auto& ans = solve(n, m, map);
	cout << ans;

	return 0;
}