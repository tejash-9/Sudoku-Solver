#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <string.h>

class Set { 
    public:
        int* cells[9];
        bool dupe(int val){
            return std::any_of(std::begin(cells), std::end(cells), [&](int* i){
                return *i == val;
            });
        };
        void print(){
            for(int i = 0; i < 9; i++){
                std::cout << (*cells[i]) << " ";
            }
            std::cout << "\n";
        };
};

class Board {
    public:
        int data[9][9] = {{0}}; 
        Set rows[9];
        Set cols[9]; 
        Set sqrs[9];
        int (*fixed)[9][9]; 
        Board(int (*f)[9][9]):fixed(f){
            for(int i = 0; i < 9; i++){ 
                for(int j = 0; j < 9; j++){ 
                    rows[i].cells[j] = &(data[i][j]);
                    cols[i].cells[j] = &(data[j][i]);
                    sqrs[i].cells[j] = &( data[j/3+(i/3)*3][j%3+(i*3)%9] );
                    
                }
            }
        };
        bool isDuplicate(int i, int j, int val){
            
            rows[i].dupe(val) || cols[j].dupe(val) || sqrs[j/3+(i/3)*3].dupe(val);
            return rows[i].dupe(val) || cols[j].dupe(val) || sqrs[j/3+(i/3)*3].dupe(val);
        };
        void solve(){
            
            memcpy(&data,fixed,9*9*sizeof(int));
        
            for(int i = 0; i < 9; i++){ 
                for(int j = 0; j < 9; j++){
                
                    if((*fixed)[i][j] == 0){
                        
                        int n = data[i][j];
                        while(true){
                            n++;
                            
                            if(n > 9){
                                
                                data[i][j] = 0;
                                
                                do{
                                    if(--j < 0){
                                        j = 8;
                                        i--;
                                    }
                                }while((*fixed)[i][j]>0);
                                
                                j--; 
                                break;
                            }
                            
                            if(!isDuplicate(i,j,n)){
                                data[i][j] = n;
                                break;
                            };
                        }
                    }
                }
            }
        };
        void print(){
            for(int i = 0; i < 9; i++){ 
                for(int j = 0; j < 9; j++){
                    std::cout << data[i][j] << " ";
                    if(j == 2 || j == 5){
                        std::cout << "| ";
                    }
                }
                std::cout << "\n";
                if(i == 2 || i == 5){
                    for(int k = 0; k < 22; k++){
                        std::cout << "\u2014";
                    }
                    std::cout << "\n";
                }
            }
        };
};


int main(int, const char** argv){
    int easy[9][9] = {{0,2,0,1,7,8,0,3,0},
                      {0,4,0,3,0,2,0,9,0},
                      {1,0,0,0,0,0,0,0,6},
                      {0,0,8,6,0,3,5,0,0},
                      {3,0,0,0,0,0,0,0,4},
                      {0,0,6,7,0,9,2,0,0},
                      {9,0,0,0,0,0,0,0,2},
                      {0,8,0,9,0,1,0,6,0},
                      {0,1,0,4,3,6,0,5,0}};
                      
    int hard[9][9] = {{1,2,0,4,0,0,3,0,0},
                      {3,0,0,0,1,0,0,5,0},
                      {0,0,6,0,0,0,1,0,0},
                      {7,0,0,0,9,0,0,0,0},
                      {0,4,0,6,0,3,0,0,0},
                      {0,0,3,0,0,2,0,0,0},
                      {5,0,0,0,8,0,7,0,0},
                      {0,0,7,0,0,0,0,0,5},
                      {0,0,0,0,0,0,0,9,8}};
    Board board(&easy);
    
    std::clock_t start;
    start = std::clock();
    board.solve();
    std::cout << " Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    board.print();
    return 0;
}