#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
	int nCases;
	cin >> nCases;
	
	for (int iCase = 0; iCase < nCases; ++iCase) {

		int N, P;
		cin >> N >> P;
		vector<int> S(N);
		for (int i = 0; i < N; ++i) cin >> S[i];

		sort(S.begin(), S.end(), [](const int & a, const int & b) {
			return a > b;
		});

		long long res = numeric_limits<int>::max();

		vector<long long> needs(N,0);

		for (int i = 0; i < P; ++i) {
			needs[0] += S[0] - S[i];
		}
		res = min(res, needs[0]);


		for (int i = 1; i <= N - P; ++i) { 
			needs[i] = needs[i - 1] - (P - 1) * (S[i - 1] - S[i]) + S[i] - S[i + P - 1];
			res = min(res, needs[i]);
		}

		cout << "Case #" << iCase + 1 << ": " << res << endl;
	}
}