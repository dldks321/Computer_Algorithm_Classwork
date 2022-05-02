#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAXVAL 901

int location[MAXVAL];
int Copyloc[MAXVAL];
int Search[MAXVAL];

int n,m;
int S,T;

int V;
int counter = 0;
int discovered[MAXVAL];
bool testCutVertex[MAXVAL];
vector<int> Road[MAXVAL];

int ans[MAXVAL];

void ary_sort(int ary[], int len){
	int i,j;
	for(i = 0; i < len-1; i++){
		for(j = 0; j < len-1-i; j++){
			if((ary[j]-1)%m+1 > (ary[j+1]-1)%m+1){
				int temp;
				temp = ary[j];
				ary[j] = ary[j+1];
				ary[j+1] = temp;
			}
			else if((ary[j]-1)%m+1 == (ary[j+1]-1)%m+1 && (ary[j]-1)/m+1 > (ary[j+1]-1)/m+1){
				int temp;
				temp = ary[j];
				ary[j] = ary[j+1];
				ary[j+1] = temp;
			}
		}
	}
}

int nest_test(int point, int route[]){
	int i = 0;
	int flag = 1;
	while(1){
		if(i != 0 && route[i] == 0){
			break;
		}
		if(point == route[i]){
			flag *= 0;
			break;
		}
		i++;
	}
	return flag;
}

void isDivided(int p){
	int x,y;
	x = p % m;
	y = p / m;
	if(y < n-1 && Copyloc[p+m] == 0 && nest_test(p+m+1, Search)){
		int i = 0;
		while(1){
			if(Search[i] == 0){
				Search[i] = p+m+1;
				break;
			}
			i++;
		}
		isDivided(p+m);
	}
	if(x < m-1 && Copyloc[p+1] == 0 && nest_test(p+1+1, Search)){
		int i = 0;
		while(1){
			if(Search[i] == 0){
				Search[i] = p+1+1;
				break;
			}
			i++;
		}
		isDivided(p+1);
	}
	if(y > 0 && Copyloc[p-m] == 0 && nest_test(p-m+1, Search)){
		int i = 0;
		while(1){
			if(Search[i] == 0){
				Search[i] = p-m+1;
				break;
			}
			i++;
		}
		isDivided(p-m);
	}
	if(x > 0 && Copyloc[p-1] == 0 && nest_test(p-1+1, Search)){
		int i = 0;
		while(1){
			if(Search[i] == 0){
				Search[i] = p-1+1;
				break;
			}
			i++;
		}
		isDivided(p-1);
	}
}

int DFS(int a, bool root_test){
    discovered[a]= ++counter;
    
    int res = discovered[a];
    int child = 0;
    
    for(int i = 0; i < (int)Road[a].size(); i++){
        int next = Road[a][i];
        
        if(!discovered[next]){
            
			child++;
            int low = DFS(next, false);
            
            if(!root_test && low >= discovered[a]){
            	testCutVertex[a] = true;
			}
            res = min(res, low);
        }
		else{
            res = min(res, discovered[next]);
        }
    }
    
    if(root_test){
    	testCutVertex[a] = (child >= 2);
	}
    return res;
}

int main(){
	FILE *in=fopen("lock.inp","r");
    FILE *out=fopen("lock.out","w");
    
	fscanf(in,"%d %d",&n,&m);
	
	int i, j;
	
	for(i = n-1; i >= 0; i--){
		for(j = 0; j < m; j++){
			char inp;
			fscanf(in,"%c",&inp);
			//printf("%c ",inp);
			if(inp == '#'){
				location[i*m + j] = 1;
			}
			else if(inp == 'S'){
				location[i*m + j] = 0;
				S = i*m + j;
			}
			else if(inp == 'T'){
				location[i*m + j] = 0;
				T = i*m + j;
			}
			else if(inp == '\n'){ // 입력받는 '\n'대비 
				j--;
				continue;
			}
			else{
				location[i*m + j] = 0;
			}
			//printf("%d ",location[i*m + j]);
		}
		//printf("\n");
	}    
	
	V = m*n;
	for(j = 0; j < n; j++){ //가로축 edge 첨부 
		for(i = 0; i < m-1; i++){
			if(location[j*m + i] == 0 && location[j*m + i + 1] == 0){
		        Road[j*m + i+1].push_back(j*m + i + 1+1);
		        Road[j*m + i + 1+1].push_back(j*m + i+1);				
			}
		}
	}
	
	for(j = 0; j < m; j++){ //세로축 edge 첨부 
		for(i = 0; i < n-1; i++){
			if(location[i*m + j] == 0 && location[i*m + j + m] == 0){
		        Road[i*m + j+1].push_back(i*m + j + m+1);
		        Road[i*m + j + m+1].push_back(i*m + j+1);				
			}
		}
	}

    for(i = 1; i <= V; i++){
        if(!discovered[i])
            DFS(i, true);
    }

    int cnt=0;
    for(i =1 ; i<= V; i++){
        if(testCutVertex[i]){
        	int j = 0;
        	while(1){
        		if(Search[j] == 0){
        			break;
				}
				Search[j] = 0;
				j++;
			}
        	
        	//fill_n(Search, MAXV, 0);
			memcpy(Copyloc, location, sizeof(Copyloc));
			Copyloc[i-1] = 1;
			Search[0] = S+1;
			isDivided(S);
			/*int k;
			while(1){
				if(Search[k] == 0){
					break;
				}
				printf("%d ",Search[k]);
				k++;
			}
			printf("\n");*/
			if(nest_test(T+1,Search)){
				ans[cnt] = i;
				cnt++;
			}
		}
    } 
    
	j = 0;
    while(1){
       	if(Search[j] == 0){
        	break;
		}
		Search[j] = 0;
		j++;
	}
	memcpy(Copyloc, location, sizeof(Copyloc));
	Search[0] = S+1;
	isDivided(S);  
	/*int k = 0;
	while(1){
		if(Search[k] == 0){
			break;
		}
		printf("%d ",Search[k]);
		k++;
	}
	printf("\n");*/
	int CutVertexT = 0;
	if(!nest_test(T+1,ans)){
		CutVertexT--;
	}
    if(nest_test(T+1,Search)){
    	fprintf(out,"0");
	}
    else{
    	ary_sort(ans,cnt);
    
		fprintf(out,"%d\n", cnt+CutVertexT);
		for(i = 0; i < cnt; i++){
			if(ans[i] == T+1){
				continue;
			}
			else{
				fprintf(out,"%d %d\n",(ans[i]-1)%m+1,(ans[i]-1)/m+1);
			}
		}   	
	}
    
    fclose(in);
    fclose(out);
    
    return 0;
}
