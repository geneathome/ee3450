#include"generate_maze.h"
#include<math.h>
#include"lfsr.h"
const uint64_t FEEDBACK=0x800000000000000D;

int nexti,nextj;

void generate_maze(uint64_t* maze, int h, int w, int i_i, int i_j, uint64_t* seed) {
// "h" is the number of cell in one column, "w" is the number of cell in one row
//"i_i","i_j" is the index of the initial position, where this maze should start.
//***************************your code write here********
    int j = 0x0000000000000001;
    maze[i_i]=maze[i_i]^(j<<i_j);
    int direction;
    int r;
    int range;
    do {    
            range = available_dir(maze, i_i, i_j ) ;
            if (range == -1){
                break;
            }
            r = random_dir(seed, range);
            direction = choose_dir(maze,i_i,i_j,r);
            
            if ( direction == 0 ) { 
                j = 0x0000000000000001;
                maze[i_i]=maze[i_i]^(j<<(i_j+1)); 
                nexti = i_i;
                nextj = i_j+2;
            }
            
            else if(direction==1){ 
                j = 0x0000000000000001;
                maze[i_i+1]=maze[i_i+1]^(j<<(i_j)); 
                nexti = i_i + 2;
                nextj = i_j ;
            }
            
            else if(direction==2){ 
                j = 0x0000000000000001;
                maze[i_i]=maze[i_i]^(j<<(i_j-1)); 
                nexti = i_i;
                nextj = i_j -2;
            }
            else if(direction==3){  
                j = 0x0000000000000001;
                maze[i_i-1]=maze[i_i-1]^(j<<(i_j)); 
                nexti = i_i -2;
                nextj = i_j;     
            }
            
           generate_maze(maze,h,w,nexti,nextj,seed); 
    }while (range!=-1);

	return;
}
//************you can define your function here

int available_dir(uint64_t* maze, int i_i, int i_j) {
// this function will output number of available direction at current position
// "i_i","i_j" is the index of the current position
// if there is no available direction, it returns -1.
	uint64_t j = 0x0000000000000001;
    int num;
    int i;

	j = j << i_j;

	num = 0;
    // right
    if ((maze[i_i] & (j << 2)) != 0)
        num++;
    // down
    if ((maze[i_i+2] & (j)) != 0)
        num++;
    // left
    if ((maze[i_i] & (j >> 2)) != 0)
        num++;
    // up
    if ((maze[i_i-2] & (j)) != 0)
        num++;   
	if(num==0)
		return -1;
    return num;
}

int random_dir(uint64_t* seed, int range) {
// this function picks one number randomly from 0 to range-1
// "seed" is used by lfsr function, when you use this function in generate_maze() you do not need to modified "seed", like following example.
	int n;

    *seed = lfsr64(*seed, FEEDBACK); 	
    n = random_lfsr(*seed, range-1);
    return n;
}

int choose_dir(uint64_t* maze, int i_i, int i_j, int r) {
// this function will output an available direction at current position
// "i_i","i_j" is the index of the current position
// output 0 means left, 1 means down, 2 means right, 3 means up
    uint64_t j = 0x0000000000000001;
    int ava_dir[4];
    int num = 0;
    int i;

    j = j << i_j;
    // right
    if ((maze[i_i] & (j << 2)) != 0)
        ava_dir[num++] = 0;
    // down
    if ((maze[i_i+2] & (j)) != 0)
        ava_dir[num++] = 1;
    // left
    if ((maze[i_i] & (j >> 2)) != 0)
        ava_dir[num++] = 2;
    // up
    if ((maze[i_i-2] & (j)) != 0)
        ava_dir[num++] = 3;

    return ava_dir[r];
}





