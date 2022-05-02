#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/*
char *make_substr(int init, int end, char *stri){
	char *desti = (char *)malloc(sizeof(char)*(end-init+2));
	strncpy(desti, stri+init, end-init+1);
	desti[end-init+1] = 0;
	return desti;
}
*/
int DP[2001][2001];

int match;
int mis_match;
int gap;

struct btxy{
	int x;
	int y;
};

int Max(int x, int y, int z){
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

struct btxy back_track(int i, int e){
	struct btxy ans = {i, e};
	
	struct btxy ans1 = {2002, 2002};
	struct btxy ans2 = {2002, 2002};
	struct btxy ans3 = {2002, 2002};
	struct btxy ans4 = {2002, 2002};
	
	if(DP[ans.y][ans.x] == 0){
		return ans;
	}
	
	if(DP[ans.y][ans.x] == DP[ans.y-1][ans.x-1] + match){
		ans1 = back_track(ans.x-1,ans.y-1);
	}
	else if(DP[ans.y][ans.x] == DP[ans.y-1][ans.x] + gap){		
		ans2 = back_track(ans.x,ans.y-1);
	}
	else if(DP[ans.y][ans.x] == DP[ans.y][ans.x-1] + gap){
		ans3 = back_track(ans.x-1,ans.y);
	}
	else{
		ans4 = back_track(ans.x-1,ans.y-1);
	}
	
	if(ans1.x <= ans2.x && ans1.x <= ans3.x && ans1.x <= ans4.x){
		return ans1;
	}
	else if(ans2.x <= ans1.x && ans2.x <= ans3.x && ans2.x <= ans4.x){
		return ans2;
	}
	else if(ans3.x <= ans1.x && ans3.x <= ans2.x && ans3.x <= ans4.x){
		return ans3;
	}
	else{
		return ans4;
	}
}

int main(void){	
    FILE *in=fopen("music.inp","r");
    FILE *out=fopen("music.out","w");
	/*
	int match;
	int mis_match;
	int gap;
	*/
	fscanf(in,"%d %d %d",&match,&mis_match,&gap);
	
	char stri[2001];
	fscanf(in,"%s",stri);
	
	int f_max = 0;
	char f_s1[2001];
	char f_s2[2001];
	
	int i = 0;
	int x = 0;
	int y = 0;
	for(i = 1; i < strlen(stri); i++){
		char s1[2001];
		char s2[2001];
		strncpy(s1,stri,i);
		strcpy(s2,stri+i);
		//char* s1 = make_substr(0,i-1,stri);
		//char* s2 = make_substr(i,strlen(stri)-1,stri);
		
		int the_max = 0;
		int mx = 0;
		int my = 0;
		
		int m_test = 0;
		
		//DP = { 0, };
		
		for(y = 0; y < strlen(s2); y++){
			for(x = 0; x < strlen(s1); x++){
				if(s1[x] == s2[y]){
					m_test = match;
				}
				else{
					m_test = mis_match;
				}
				DP[y+1][x+1] = MAX(Max(DP[y][x] + m_test, DP[y][x+1] + gap, DP[y+1][x] + gap),0);
				if(DP[y+1][x+1] > the_max){
					the_max = DP[y+1][x+1];
					mx = x+1;
					my = y+1;
				}
			}
		}
		/*while(1){
			if(DP[bty][btx] == 0){
				break;
			}
			if(DP[bty][btx] == DP[bty-1][btx-1] + match){
				bty -= 1;
				btx -= 1;
			}
			else if(DP[bty][btx] == DP[bty-1][btx] + gap){
				bty -= 1;				
			}
			else if(DP[bty][btx] == DP[bty][btx-1] + gap){
				btx -= 1;
			}
			else{
				bty -= 1;
				btx -= 1;
			}
		}*/
		
		if(the_max > f_max){
			f_max = the_max;
			
			int btx = mx;
			int bty = my;
			struct btxy bt = back_track(btx,bty);
			
			//f_s1 = make_substr(btx,mx,s1);
			strncpy(f_s1,s1+bt.x,mx-bt.x);
			//f_s2 = make_substr(bty,my,s2);
			strncpy(f_s2,s2+bt.y,my-bt.y);
			f_s1[mx-bt.x] = '\0';
			f_s2[my-bt.y] = '\0';
		}
		//free(s1);
		//free(s2);
	}
	
	fprintf(out,"%s\n",f_s1);
	fprintf(out,"%s\n",f_s2);
	fprintf(out,"%d",f_max);
	
	//free(f_s1);
	//free(f_s2);
	
    fclose(in);
    fclose(out);
	
	//return 0;
}
