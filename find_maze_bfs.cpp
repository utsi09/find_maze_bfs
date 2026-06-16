#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
using namespace cv;
using namespace std;
int adj[30][30];
int visited[30][30];

int H = 30;
int W = 30;
int cell = 30;
Mat img(W*cell, H*cell, CV_8UC3, Scalar(255,255,255));
int ii, jj;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

void init_map(){
    fill(&adj[0][0], &adj[0][0]+30*30, 0);
    for(int i=0; i<H; i++){
            for(int j=0; j<W; j++){
                rectangle(img, Rect(i*cell,j*cell,cell,cell), Scalar(255,255,255),FILLED);
        }
    }
    srand(time(NULL));
    for(int i=0; i<H*10; i++){
        int tmp_h = rand() % H; 
        int tmp_w = rand() % W;
        adj[tmp_h][tmp_w] = 1;
    }
    adj[0][0] = 0;
    adj[29][29] = 0;
    return;
}

int bfs(int i, int j){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(q.size()){
        tie(ii,jj) = q.front(); q.pop();
        if(ii==29 && jj==29){
            int ret=0;
            (visited[29][29]==0 ? ret = 98765432 : ret = visited[29][29]);
            return ret; //거리 반환
        }
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            if(ny<0 || nx<0 || ny>=H || nx>=W || visited[ny][nx] != 0) continue;
            if(adj[ny][nx] == 1) continue;
            q.push({ny,nx});
            visited[ny][nx] = visited[ii][jj] + 1;
        }

    }
    return 98765432;
}

int main(){
    while(1){
        init_map(); //맵 초기화
        
        for(int i=0; i<H; i++){
            for(int j=0; j<W; j++){
                if(i==0&&j==0){
                    rectangle(img, Rect(i*cell,j*cell,cell,cell), Scalar(0,255,0),FILLED);
                    continue;
                }     
                else if(i==H-1&&j==W-1){
                    rectangle(img, Rect(i*cell,j*cell,cell,cell), Scalar(0,0,255),FILLED);
                    continue;
                }
                else if(adj[i][j] == 1){
                    rectangle(img, Rect(i*cell,j*cell,cell,cell), Scalar(0,0,0),FILLED);
                }
                rectangle(img, Rect(i*cell,j*cell,cell,cell), Scalar(0,0,0)); 
                
            }
        }
        int tmp_i=0; int tmp_j=0;
        
        while(1){
            int best_d = -1;
            int best_ret =98765432;
            for(int d=0; d<4; d++){
                fill(&visited[0][0], &visited[0][0]+30*30, 0);
                int ny = tmp_i + dy[d];
                int nx = tmp_j + dx[d];
                if(ny<0 || nx<0 || ny>=H || nx>=W || visited[ny][nx] != 0) continue;
                if(adj[ny][nx] == 1) continue;
                int ret = bfs(ny,nx);
                if(best_ret > ret){
                    best_d = d;
                    best_ret = ret;
                }
            }
            if(best_ret == 98765432){
                rectangle(img, Rect(tmp_i*cell, tmp_j*cell, cell, cell), Scalar(0,0,255),5); //답없으면 빨간색
                imshow("FIND MAZE", img);
                waitKey(30);
                break;
            }
            tmp_i += dy[best_d];
            tmp_j += dx[best_d];
            rectangle(img, Rect(tmp_i*cell,tmp_j*cell,cell,cell), Scalar(255,0,0),5); //새 블록 파란색
            imshow("FIND MAZE", img);
            waitKey(30);
            if(tmp_i==29 && tmp_j == 29) break;
        }   
        imshow("FIND MAZE", img);
        if(waitKey(0) == 'q'){
            rectangle(img, Rect(0,0,900,900), Scalar(255,255,255),FILLED); //새 블록 파란색
            putText(img, "Thank you!! (developed by taewook)", Point(5*cell, 15*cell), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 1.5);
            imshow("FIND MAZE", img);
            waitKey(0);
            break;
        }
    }
    return 0;
}
