// #include<bits/stdc++.h>
// #include<bits/stdc++.h>
#include<iostream>
#include<utility>
// #include<string>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;

typedef pair<int, int> dog;

/**
 * 分析
 * 1. Bundle不会再穿以前穿过的颜色，因为这不会产生一个更好的解;
 * 2. 对于相同颜色的狗，如果她观察了一只狗，那么在这只狗之前的所有具有相同颜色的狗都应该被观察过
 * 3. 最后一个条件：观察完最后一只狗不必回到家，有点tricky，我们先考虑简化版本：必须返回家的情况
 * 
 * 对于简化版本，有以下几点：
 * 1. Bundle 穿的 T-shirts颜色顺序并不重要
 * 2. 方法一（时间复杂度：O(n^3)） （test1 可以过，test2超时）：
 *    简化版本的动态规划：
 *    dp[i][j]: 共有i种颜色的狗，观察j只狗所用最少时间；
 *    dp[i][j] = min(dp[i-1][j]+0, dp[i-1][j-1]+2*X_{i,1}, dp[i-1][j-2]+2*X_{i,2}, dp[i-1][j-3]+2*X_{i,3} ... )
 *    其中 X_{i, k}表示i颜色的狗中的第k条。
 *    最后考虑每个颜色作为最后一条狗时的代价，
 * 
 *    方法二 (O(n^2)):
 *    增加一个状态位维度表示是否已经选择了最后一种颜色，
 *    dp[i][j][k]: dp[i][j][0]表示共有i种颜色的狗，还未选最后一种颜色，观察j只狗的最少时间
 *                 dp[i][j][1]表示共有i种颜色的狗，已经选择了最后一种颜色，观察j只狗的最少时间
 * 
 *    状态转移方程：
 *    dp[i][j][0] = min( dp[i-1][j][0], dp[i-1][j-1]+2*X_{i,1}, dp[i-1][j-2]+2*X_{i,2}, dp[i-1][j-3]+2*X_{i,3} ... )
 *    dp[i][j][1] = min( 前i-1种颜色中已经选择了最后一种颜色, 前i-1种颜色还没选择最后一种颜色+当前的第i种颜色作为最后一种颜色 ) 
 *                = min( min( dp[i-1][j][1], dp[i-1][j-1][1]+2*X_{i,1}, ... ), min( dp[i-1][j][0]+0, dp[i-1][j-1][0]+X_{i, 1}, dp[i-1][j-2][0]+X_{i, 2}, ... ) )
 * 
 **/

int main(){
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++){
        int N;
        int K;
        cin >> N >> K;
        vector<int> P(N);
        for (int i=0; i<N; i++){
            cin >> P[i]; // position
        }

        vector<int> A(N);
        unordered_set<int> colors;

        for (int i=0; i<N ;i++){
            cin >> A[i]; // color
            colors.insert(A[i]);
        }

        int siz = 1;
        unordered_map<int, int> color_index;
        color_index[0] = 0;
        for (unordered_set<int>::iterator it=colors.begin(); it!=colors.end(); it++){
            color_index[siz] = (*it);
            siz ++ ;
        }

        // vector<dog> dogs;
        // for (int i=0; i<N; i++){
        //     dogs.push_back(make_pair(P[i], A[i]));
        // }
        unordered_map<int, vector<int>> color_distances;

        for (int i=0; i<N; i++){
            color_distances[A[i]].push_back(P[i]);
            // if (color_distances.find(A[i]) != color_distances.end() ){
            //     color_distances[A[i]].push_back(P[i]);
            // }else{
            //     color_distances[]
            // }
        }
        
        int res = 0x3f3f3f3f;


        // cout << "color_index" <<endl;
        // for (unordered_map<int, int>::iterator it = color_index.begin(); it!= color_index.end(); it++){
        //     cout << (*it).first << ": " << (*it).second <<endl;
        // }

        // cout << "color_distances" <<endl;
        // for (unordered_map<int, vector<int>>::iterator it = color_distances.begin(); it!= color_distances.end(); it++){
        //     cout << (*it).first << ": ";
        //     for (auto t: (*it).second){
        //         cout << t << " ";
        //     }
        //     cout << endl;
        // }

        // cout << "siz: " << siz << " K: "<<K<< endl;

        for (unordered_map<int, vector<int>>::iterator it = color_distances.begin(); it!= color_distances.end(); it++){
            sort((*it).second.begin(), (*it).second.end());
        }

        for (int last_color = 1; last_color<siz;last_color++){

            // cout << "last_color: "<<last_color << endl;
            vector<vector<int>> dp(siz-1, vector<int>(K+1, 0x3f3f3f3f));  
            for (int i=0;i<siz-1;i++){
                dp[i][0] = 0;
            }

            for (int i=1; i<siz; i++){
                int new_i = i;
                if (last_color < i){
                    new_i = i-1;
                }else if (last_color == i)
                {
                    continue;
                }
                

                int clr = color_index[i];

                for (int j=1; j<=K; j++){
                    dp[new_i][j] = min(dp[new_i][j], dp[new_i-1][j]);
                    for (int d=0; d<color_distances[clr].size();d++){
                        if (j-d-1 < 0) break;

                        // cout << "dp[new_i-1][j- d -1] + 2 * color_distances[clr][d]: "<<dp[new_i-1][j- d -1] + 2 * color_distances[clr][d] << endl;
                        
                        dp[new_i][j] = min(dp[new_i][j], dp[new_i-1][j- d -1] + 2 * color_distances[clr][d] );


                    }

                    // cout << "dp["<<new_i<<"]"<<"["<<j<<"]: "<<dp[new_i][j]<<endl;

                }
            }

            int clr = color_index[last_color];
            res = min(res, dp[siz-2][K]);
            for (int d=0; d<color_distances[clr].size(); d++){
                if (K-d-1<0) break;
                res = min (res, dp[siz-2][K-d-1] + color_distances[clr][d] );
            }

            


        }


        



        
        cout << "Case #"<< t << ": "<<res<<endl;
    }
}