#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int find_max(int x, int y, int z) {
	if(x >= y){
		if(x >= z){
			return x;
		}
		else{
			return z;
		}
	}
	else{
		if(y >= z){
			return y;
		}
		else{
			return z;
		}
	}
}

int main(void){	
    FILE *in=fopen("ballpark.inp","r");
    FILE *out=fopen("ballpark.out","w");
	
	int N;
	int M;
	fscanf(in,"%d %d",&N,&M);
	
	int land[N][M];
	int land_max = 1;
	int ans[100000][2];
	int flag = 0;
	
	int x;
	int y;
	char buff[10];
	
	for(x = 0; x < N; x++){
		for(y = 0; y < M; y++){
			fscanf(in,"%1d",&land[x][y]);
		}
	}
	
	for(x = 1; x < N; x++){
		for(y = 1; y < M; y++){
			if(land[x][y] != 1){
				land[x][y] = find_max(land[x-1][y],land[x][y-1],land[x-1][y-1]) - 1;
				if(land[x][y] < land_max){
					land_max = land[x][y];
					ans[0][0] = y-abs(land_max)+1;
					ans[0][1] = N-x;
					flag = 1;
				}
				else if(land[x][y] == land_max){
					ans[flag][0] = y-abs(land_max)+1;
					ans[flag][1] = N-x;
					flag++;
				}
			}
		}
	}
	
	int save[2];
	
	for(x = 0; x < flag-1; x++){
		for(y = 0; y < flag-x-1; y++){
			if(ans[y][0] > ans[y+1][0]){
				save[0] = ans[y+1][0];
				save[1] = ans[y+1][1];
				
				ans[y+1][0] = ans[y][0];
				ans[y+1][1] = ans[y][1];
				
				ans[y][0] = save[0];
				ans[y][1] = save[1];
			}
			else if(ans[y][0] == ans[y+1][0] && ans[y][1] > ans[y+1][1]){
				save[0] = ans[y+1][0];
				save[1] = ans[y+1][1];
				
				ans[y+1][0] = ans[y][0];
				ans[y+1][1] = ans[y][1];
				
				ans[y][0] = save[0];
				ans[y][1] = save[1];				
			}
		}
	}
	
	fprintf(out, "%d %d\n", abs(land_max)+1, flag);
	
	for(x = 0; x < flag; x++){
		fprintf(out, "%d %d\n", ans[x][0], ans[x][1]);
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
