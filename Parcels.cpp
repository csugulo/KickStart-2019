#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

#define INT_MAX numeric_limits<int>::max()
#define INT_LOW numeric_limits<int>::lowest()

typedef pair<int, int> Point2i;

void bfs(vector<vector<int>> & distanceMap, deque<Point2i> & offices){

    int R(distanceMap.size()), C(distanceMap[0].size());

    deque<Point2i> current = offices;
    int distance = 0;

    while(!current.empty()){
        int currentSize = current.size();
        for(int i = 0; i < currentSize; ++i){
            Point2i & p = current[i];
            distanceMap[p.first][p.second] = distance;
        }

        for(int i = 0; i < currentSize; ++i){
            Point2i p = current.front();
            current.pop_front();
            // up
            if(p.first > 0 && distanceMap[p.first - 1][p.second] == INT_MAX)
                current.push_back(Point2i(p.first - 1 , p.second));
            // down
            if(p.first < R - 1 && distanceMap[p.first + 1][p.second] == INT_MAX)
                current.push_back(Point2i(p.first + 1 , p.second));
            // left
            if(p.second > 0 && distanceMap[p.first][p.second - 1] == INT_MAX)
                current.push_back(Point2i(p.first, p.second - 1));
            // right
            if(p.second < C - 1 && distanceMap[p.first][p.second + 1] == INT_MAX)
                current.push_back(Point2i(p.first, p.second + 1));     
        }

        sort(current.begin(), current.end());
        auto end_unique = unique(current.begin(), current.end());
        current.erase(end_unique, current.end());
        distance++;

    }
}


bool check(vector<vector<int>> & distanceMap, int k){

    vector<Point2i> positions;
        int R(distanceMap.size()), C(distanceMap[0].size());
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            if(distanceMap[i][j] > k) positions.push_back(Point2i(i,j));
        }
    }

    if(positions.size() == 0) return true;

    int maxRplusC(INT_LOW), minRplusC(INT_MAX), maxRminusC(INT_LOW), minRminusC(INT_MAX);

    for(int i = 0; i < positions.size(); ++i){
        Point2i & p = positions[i];
        maxRplusC = max(maxRplusC, p.first + p.second);
        minRplusC = min(minRplusC, p.first + p.second);
        maxRminusC = max(maxRminusC, p.first - p.second);
        minRminusC = min(minRminusC, p.first - p.second);
    }

    bool exist = false;
    for(int i = 0; i < R && !exist; ++i){
        for(int j = 0; j < C && !exist; ++j){
            int d1 = max(abs(i + j - maxRplusC), abs(i - j - maxRminusC));
            int d2 = max(abs(i + j - minRplusC), abs(i - j - maxRminusC));
            int d3 = max(abs(i + j - maxRplusC), abs(i - j - minRminusC));
            int d4 = max(abs(i + j - minRplusC), abs(i - j - minRminusC));
            int distance = max(max(d1,d2),max(d3,d4));
            if(distance <= k) exist = true;
        }
    }

    return exist;

}

int binarySearch(vector<vector<int>> & distanceMap, int start, int end){
    if(start == end) return start;
    int mid = (start + end) / 2;
    if(check(distanceMap, mid)) return binarySearch(distanceMap, start, mid);
    else return binarySearch(distanceMap, mid + 1, end);
}


int main(){

    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++){
        int R, C;
        cin >> R >> C;
        deque<Point2i> offices;
        vector<vector<int>> distanceMap(R, vector<int>(C, INT_MAX));
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                char c;
                cin >> c;
                if(c == '1'){
                    Point2i p(i,j);
                    offices.push_back(p);
                }
            }
        }

        bfs(distanceMap, offices);

        int res = binarySearch(distanceMap, 0, R + C);

        cout << "Case #" << iCase + 1 << ": " << res << endl;


    }
    


    return 0;
}