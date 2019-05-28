// #include<bits/stdc++.h>
// #include<bits/stdc++.h>
#include<iostream>
#include<utility>
// #include<string>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;

typedef pair<int, int> node;

int main(){
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++){
        int R;
        int C;
        int K;
        cin >> R >> C >> K;

        vector<vector<int>> V(R, vector<int>(C, 0));
        for (int i=0; i<R; i++){
            for (int j=0; j<C; j++){
                cin >> V[i][j];
            }
        }

        int res = 0;
        
        for (int i=0; i<C; i++){
            vector<int> hights;
            for (int j=0; j<R; j++){
                int base = i;
                int end = i;
                int min_so_far = V[j][base];
                int max_so_far = V[j][base];
                for (int h=i;h<C; h++){
                    if (min_so_far > V[j][h]){
                        min_so_far = V[j][h];
                    }
                    if (max_so_far < V[j][h]){
                        max_so_far = V[j][h];
                    }

                    if (abs(max_so_far - min_so_far) > K){
                        break;
                    }
                    end = h;
                }

                hights.push_back(end - base + 1);
            }

            // for (auto tt: hights){
            //     cout << ":: " <<tt ;
            // }
            // cout << endl;

            stack<node> stk;
            int tmp_res = 0;

            for (int num=0; num<R; num++){
                if (stk.empty() || hights[num] >= stk.top().first){
                    stk.push(make_pair(hights[num], 1));
                }else{
                    int width = 0;
                    while (!stk.empty() && hights[num]<stk.top().first){
                        width += stk.top().second;
                        tmp_res = max(tmp_res, width * stk.top().first);
                        stk.pop();
                    }
                    stk.push(make_pair(hights[num], width+1));
                }

            }

            int wi = 0;
            while(!stk.empty()){
                wi+= stk.top().second;
                tmp_res = max(tmp_res, wi * stk.top().first);
                stk.pop();
            }

            res = max(res, tmp_res);

        }




        
        cout << "Case #"<< t << ": "<<res<<endl;
    }
}