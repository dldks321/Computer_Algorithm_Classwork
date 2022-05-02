#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int N;
int M;

char vertex[26];
char edge[26][26];
int length[26][26];

char route[10000];

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
	if(leng > 42){
		return 0;
	}
	if(strlen(road) != 1 && road[0] == road[strlen(road)-1]){
		if(leng == 42){
			if((strlen(route) < strlen(road))||(strlen(route) == strlen(road) && strcmp(route,road) > 0)){
				strcpy(route, road);
			}
		}
		return 0;
	}
	int i = 0;
	while(edge[road[strlen(road)-1]-97][i] != '\0'){
		if(edge[road[strlen(road)-1]-97][i] != 'a' && repeat_test(edge[road[strlen(road)-1]-97][i], road)){
			i++;
			continue;
		}
		char n_road[5000];
		strcpy(n_road,road);
		strncat(n_road,&edge[road[strlen(road)-1]-97][i],1);
		backtrack(n_road, leng + length[road[strlen(road)-1]-97][i]);
		i++;
	}
	return 0;
}

int main(void){	
    FILE *in=fopen("marathon.inp","r");
    FILE *out=fopen("marathon.out","w");

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

		int j = 0;
		while(1){
			if(edge[v1 - 97][j] == '\0'){
				edge[v1 - 97][j] = v2;
				length[v1 - 97][j] = leng;
				break;
			}
			j++;
		}
		j = 0;
		while(1){
			if(edge[v2 - 97][j] == '\0'){
				edge[v2 - 97][j] = v1;
				length[v2 - 97][j] = leng;
				break;
			}
			j++;
		}		
	}
	backtrack("a",0);
	
	int s;
	char s_temp[5000];
	
	if(route == "\0"){
		fprintf(out,"NONE");
	}
	else{
		/*printf("before\n");
		for(i = 0; i < counter; i++){
			printf("%s\n", route[i]);
		}
		for(s = 0; s < counter-1; s++){
			for(i = 0; i < counter-1-s; i++){
				if(strlen(route[i]) < strlen(route[i+1])){
					strcpy(s_temp, route[i]);
					strcpy(route[i], route[i+1]);
					strcpy(route[i+1], s_temp);
				}
				else if(strlen(route[i]) == strlen(route[i+1]) && strcmp(route[i],route[i+1]) > 0){
					strcpy(s_temp, route[i]);
					strcpy(route[i], route[i+1]);
					strcpy(route[i+1], s_temp);
				}
			}
		}
		printf("after\n");
		for(i = 0; i < counter; i++){
			printf("%s\n", route[i]);
		}*/
		fprintf(out,"%d\n",strlen(route)-1);
		for(i = 0; i < strlen(route)-1; i++){
			fprintf(out,"%c ",route[i]);
		}
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
