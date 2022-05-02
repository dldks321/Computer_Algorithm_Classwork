/* 
90 / 100 socre source code ( time over )
Cause : Increased overhead due to excessive recursion
Solution : DFS using the stack
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int N;
int M;

char vertex[26];
int edge[26][26];
int length[26][26];

int len_max = 0;

char route[1000];
int route_max = 0;

int repeat_test(char cha, char *str){
	int i;
	char *s = str;
	char c = cha;
	int leng = strlen(str);
	
	for(i = 0; i < leng - 1; i++){
		if(s[i] == c){
			return 1;
		}
	}
	return 0;
}

int backtrack(char road[], int leng){
	//Bound 1. Checking all the edges of a are included in the road
	int p;
	int flag = 1;
	int t = 1;
	for(p = 1; p < 26; p++){
		if(edge[0][p] != 0 && 'a' + p == road[strlen(road)-1]){
			t *= 0;
		}
	}
	if(t != 0){
		for(p = 1; p < 26; p++){
			if(edge[0][p] != 0){
				flag *= repeat_test('a'+p,road);
			}
		}
		if(road[0] != road[strlen(road)-1] && flag == 1){
			return 0;
		}	
	}
	
	//Bound 2. Checking possibility of maximun
	if(road[0] != road[strlen(road)-1] && route_max > leng+20*(N - strlen(road) + 1)){
		return 0;
	}
	
	//Bound 3. passing edge is 1
	/*if(strlen(edge[road[strlen(road)-1]-97]) <= 1){
		return 0;
	}*/
	
	//Bound 4. eliminate last connected at edge a
	for(p = 25; p >= 0; p--){
		if(edge[0][p] != 0){
			if(strlen(road) == 2 && road[1] == 'a'+p){
				return 0;
			}
			break;
		}
	}
	
	if(strlen(road) != 1 && road[0] == road[strlen(road)-1]){
		if(leng > route_max){
			strcpy(route, road);
			route_max = leng;
		}
		if(leng == route_max){
			if((strlen(route) < strlen(road))||(strlen(route) == strlen(road) && strcmp(route,road) > 0)){
				strcpy(route, road);
			}
		}
		return 0;
	}
	int i = 0;
	for(i = 0; i < 26; i++){
		if(edge[road[strlen(road)-1]-97][i] != 0){
			if(i != 0 && repeat_test('a'+i, road)){
				continue;
			}
			char n_road[1000];
			strcpy(n_road,road);
			char mid = 'a'+i;
			strncat(n_road,&mid,1);
			backtrack(n_road, leng + edge[road[strlen(road)-1]-97][i]);	
		}
	}
	return 0;
}

int main(void){	
    FILE *in=fopen("iron.inp","r");
    FILE *out=fopen("iron.out","w");

	fscanf(in,"%d %d",&N,&M);
	
	int i;
	
	for(i = 0; i < 26; i++){
		vertex[i] = 'a' + i;
	}
	
	for(i = 0; i < M; i++){
		char v1;
		char v2;
		int leng;
		fscanf(in,"%s %c %d",&v1,&v2,&leng);
		
		/*if(len_max < leng){
			len_max = leng;
		}*/
		
		edge[v1 - 97][v2 - 97] = leng;
		edge[v2 - 97][v1 - 97] = leng;	
	}
	
	while(1){
		int flg = 0;
		for(i = 0; i < 26; i++){
			int j;
			int cnt = 0;
			for(j = 0; j < 26; j++){
				if(edge[i][j] != 0){
					cnt++;
				}
			}
			if(cnt == 1){
				for(j = 0; j < 26; j++){
					if(edge[i][j] != 0){
						edge[i][j] = 0;
						edge[j][i] = 0;
						N--;
						break;
					}
				}
				flg = 1;
				break;
			}
		}
		if(flg == 1){
			continue;
		}
		else{
			break;
		}
	}
	
	backtrack("a",0);
	
	int s;
	char s_temp[1000];
	
	if(route == "\0"){
		fprintf(out,"NONE");
	}
	else{
		fprintf(out,"%d\n",route_max);
		for(i = 0; i < strlen(route)-1; i++){
			fprintf(out,"%c ",route[i]);
		}
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
