// #include<bits/stdc++.h>
// #include<bits/stdc++.h>
#include<iostream>
#include<utility>
// #include<string>
#include<cstring>
#include<vector>
using namespace std;



int main(){
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++){
        int N;
        cin >> N;
        int R;
        cin >> R;
        int C;
        cin >> C;
        int s_r;
        int s_c;
        cin >> s_r >> s_c;

        s_r --;
        s_c --;
        vector<vector<bool>> visted(R, vector<bool>(C, false));

        string cmd;
        cin >> cmd;
        int curr_r = s_r;
        int curr_c = s_c;
        visted[curr_r][curr_c] = true;

        // int next_r;
        // int next_c;

        for (int i=0; i<cmd.size(); i++){
            // cout <<" vv : "<< cmd[i] << endl;
            // cout << curr_r
            switch (cmd[i]){
                case 'N':
                {
                    int next_r =  curr_r - 1;
                    int next_c = curr_c;
                    while (visted[next_r][next_c])
                    {
                        next_r = next_r - 1;
                    }
                    curr_r = next_r;
                    curr_c = next_c;
                    visted[curr_r][curr_c] = true;
                    break;
                }
                case 'S':
                {
                    int next_r =  curr_r + 1;
                    int next_c = curr_c;
                    while (visted[next_r][next_c])
                    {
                        next_r = next_r + 1;
                    }
                    curr_r = next_r;
                    curr_c = next_c;
                    visted[curr_r][curr_c] = true;
                    break;
                }

                case 'W':
                {
                    int next_r =  curr_r;
                    int next_c = curr_c-1;
                    while (visted[next_r][next_c])
                    {
                        next_c = next_c - 1;
                    }
                    curr_r = next_r;
                    curr_c = next_c;
                    visted[curr_r][curr_c] = true;
                    break;
                }
                case 'E':
                {
                    int next_r =  curr_r;
                    int next_c = curr_c+1;
                    while (visted[next_r][next_c])
                    {
                        next_c = next_c + 1;
                    }
                    curr_r = next_r;
                    curr_c = next_c;
                    visted[curr_r][curr_c] = true;   
                    break;
                }
                default:
                break;
            }
            // if (cmd[i] == 'N'){
            //     int next_r =  curr_r - 1;
            //     int next_c = curr_c;
            //     while (visted[next_r][next_c])
            //     {
            //         next_r = next_r - 1;
            //     }
            //     curr_r = next_r;
            //     curr_c = next_c;
            //     visted[curr_r][curr_c] = true;
                
                

            // }else if (cmd[i] == 'S')
            // {
            //     int next_r =  curr_r + 1;
            //     int next_c = curr_c;
            //     while (visted[next_r][next_c])
            //     {
            //         next_r = next_r + 1;
            //     }
            //     curr_r = next_r;
            //     curr_c = next_c;
            //     visted[curr_r][curr_c] = true;
                
            // }else if (cmd[i] == 'W')
            // {
            //     int next_r =  curr_r;
            //     int next_c = curr_c-1;
            //     while (visted[next_r][next_c])
            //     {
            //         next_c = next_c - 1;
            //     }
            //     curr_r = next_r;
            //     curr_c = next_c;
            //     visted[curr_r][curr_c] = true;
                 
            // }else if(cmd[i] == 'E')
            // {
            //     int next_r =  curr_r;
            //     int next_c = curr_c+1;
            //     while (visted[next_r][next_c])
            //     {
            //         next_c = next_c + 1;
            //     }
            //     curr_r = next_r;
            //     curr_c = next_c;
            //     visted[curr_r][curr_c] = true;   
            // }
            
            
            
        }


        



        
        cout << "Case #"<< t << ": "<<curr_r+1 << " " << curr_c+1<<endl;
    }
}