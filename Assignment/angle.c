#include<stdio.h>

#define AMAX 100

int N;
int bucket[8][AMAX][3]; //x, y, index
int len[8];

int sign_shoelace(int p1[3], int p2[3]){ //시계방향 음수, 반시계방향 양수 
	return (p1[0]*p2[1] - p2[0]*p1[1]);
}

int comp_sqare(int p1[3], int p2[3]){
	if(p1[0]*p1[0] + p1[1]*p1[1] > p2[0]*p2[0] + p2[1]*p2[1]){
		return 1;
	}
	else{
		return 0;
	}
}

void inp_loc(int x, int y, int i, int sig){
	bucket[sig][len[sig]][0] = x;
	bucket[sig][len[sig]][1] = y;
	bucket[sig][len[sig]][2] = i+1;
	len[sig]++;	
}

void ary_swap(int* a, int* b){
	int temp[3];
	temp[0] = a[0];
	temp[1] = a[1];
	temp[2] = a[2];
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	b[0] = temp[0];
	b[1] = temp[1];
	b[2] = temp[2];	
}

int main(void){
	FILE *in=fopen("angle.inp","r");
    FILE *out=fopen("angle.out","w");
    
    fscanf(in,"%d",&N);
    
	int i;
	for(i = 0; i < N; i++){
		int x,y;
		fscanf(in,"%d %d",&x,&y);
		
		if(x > 0 && y == 0){
			inp_loc(x, y, i, 0);
		}
		else if(x > 0 && y > 0){
			inp_loc(x, y, i, 1);
		}
		else if(x == 0 && y > 0){
			inp_loc(x, y, i, 2);
		}
		else if(x < 0 && y > 0){
			inp_loc(x, y, i, 3);
		}
		else if(x < 0 && y == 0){
			inp_loc(x, y, i, 4);
		}
		else if(x < 0 && y < 0){
			inp_loc(x, y, i, 5);
		}
		else if(x == 0 && y < 0){
			inp_loc(x, y, i, 6);
		}
		else{
			inp_loc(x, y, i, 7);
		}
	}
	
	int j, k;
	
	for(i = 0; i < 8; i++){
		for(j = 0; j < len[i] - 1; j++){
			for(k = 0; k < len[i] - 1 - j; k++){
				if(sign_shoelace(bucket[i][k], bucket[i][k+1]) < 0){
					ary_swap(bucket[i][k], bucket[i][k+1]);
				}
				else if(sign_shoelace(bucket[i][k], bucket[i][k+1]) == 0 && comp_sqare(bucket[i][k],bucket[i][k+1])){
					ary_swap(bucket[i][k], bucket[i][k+1]);
				}
			}
		}
	}
	
	for(i = 0; i < 8; i++){
		for(j = 0; j < len[i]; j++){
			fprintf(out,"%d\n",bucket[i][j][2]);
		}
	}

    fclose(in);
    fclose(out);    
    
	return 0;
}
