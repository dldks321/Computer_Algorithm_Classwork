#include<stdio.h>
#include<stdlib.h>

int CT[8][8];
int Z_ray[4][15];
int state[4][15][3];
int N;
int know_count = 0;

void straighten_out(){
	know_count = 0;
	int i;
	int j;
	
	int b_cnt;
	int m_cnt;
	for(i = 0; i < N; i++){
		b_cnt = 0;
		m_cnt = 0;
		for(j = 0; j < N; j++){
			if(CT[j][i] == -1){
				m_cnt += 1;
				know_count += 1;
			}
			if(CT[j][i] == 1){
				b_cnt += 1;
				know_count += 1;
			}
		}
		state[0][i][0] = m_cnt;
		state[0][i][2] = b_cnt;
		state[0][i][1] = N - (m_cnt + b_cnt);
	}
	for(i = 0; i < N; i++){
		b_cnt = 0;
		m_cnt = 0;
		for(j = 0; j < N; j++){
			if(CT[i][j] == -1){
				m_cnt += 1;
			}
			if(CT[i][j] == 1){
				b_cnt += 1;
			}
		}
		state[1][i][0] = m_cnt;
		state[1][i][2] = b_cnt;
		state[1][i][1] = N - (m_cnt + b_cnt);
	}
	for(i = 0; i < 2*N-1; i++){
		b_cnt = 0;
		m_cnt = 0;	
		for(j = 0; j < N - abs(i + 1 - N); j++){
			if(N-1-i < 0){
				if(CT[abs(N-1-i)+j][j] == -1){
					m_cnt += 1;
				}
				if(CT[abs(N-1-i)+j][j] == 1){
					b_cnt += 1;
				}
			}
			else{
				if(CT[j][abs(N-1-i)+j] == -1){
					m_cnt += 1;
				}
				if(CT[j][abs(N-1-i)+j] == 1){
					b_cnt += 1;
				}
			}
		}
		state[2][i][0] = m_cnt;
		state[2][i][2] = b_cnt;
		state[2][i][1] = (N - abs(i + 1 - N)) - (m_cnt + b_cnt);
	}
	for(i = 0; i < 2*N-1; i++){
		b_cnt = 0;
		m_cnt = 0;
		for(j = 0; j < N - abs(i + 1 - N); j++){
			if(i < N-1){
				if(CT[i-j][j] == -1){
					m_cnt += 1;
				}
				if(CT[i-j][j] == 1){
					b_cnt += 1;
				}
			}
			else{
				if(CT[N-1-j][abs(N-1-i)+j] == -1){
					m_cnt += 1;
				}
				if(CT[N-1-j][abs(N-1-i)+j] == 1){
					b_cnt += 1;
				}
			}
		}
		state[3][i][0] = m_cnt;
		state[3][i][2] = b_cnt;
		state[3][i][1] = (N - abs(i + 1 - N)) - (m_cnt + b_cnt);
	}	
}

void print(void){
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d\t",CT[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void){	
    FILE *in=fopen("ct.inp","r");
    FILE *out=fopen("ct.out","w");
	
	int i;
	int j;
	
	//input data
	fscanf(in,"%d", &N);
	
	for(i = 0; i < 4; i++){
		if(i < 2){
			for(j = 0; j < N; j++){
				fscanf(in,"%d ",&Z_ray[i][j]);
				state[i][j][1] = N;
			}
		}
		else{
			for(j = 0; j < 2*N-1; j++){
				fscanf(in,"%d ",&Z_ray[i][j]);
				state[i][j][1] = 2*N-1;
			}
		}
	}
	
	/*for(i = 0; i < 4; i++){
		for(j = 0; j < 15; j++){
			printf("%d ",Z_ray[i][j]);
		}
		printf("\n");
	}*/
	
	int res;
	
	//init CT
	for(i = 0; i < N; i++){
		if(Z_ray[0][i] == 0){
			for(j = 0; j < N; j++){
				CT[j][i] = -1;
			}
		}
		if(Z_ray[0][i] == N){
			for(j = 0; j < N; j++){
				CT[j][i] = 1;
			}
		}
	}
	for(i = 0; i < N; i++){
		if(Z_ray[1][i] == 0){
			for(j = 0; j < N; j++){
				CT[i][j] = -1;
			}
		}
		if(Z_ray[1][i] == N){
			for(j = 0; j < N; j++){
				CT[i][j] = 1;
			}
		}
	}
	for(i = 0; i < 2*N-1; i++){
		res = 0;
		if(Z_ray[2][i] == 0){
			res = -1;
		}
		else if(Z_ray[2][i] == N - abs(i + 1 - N)){
			res = 1;
		}
		if(res == 0){
			continue;
		}	
		for(j = 0; j < N - abs(i + 1 - N); j++){
			if(N-1-i < 0){
				CT[abs(N-1-i)+j][j] = res;
			}
			else{
				CT[j][abs(N-1-i)+j] = res;
			}
		}
	}
	for(i = 0; i < 2*N-1; i++){
		res = 0;
		if(Z_ray[3][i] == 0){
			res = -1;
		}
		else if(Z_ray[3][i] == N - abs(i + 1 - N)){
			res = 1;
		}
		if(res == 0){
			continue;
		}
		for(j = 0; j < N - abs(i + 1 - N); j++){
			if(i < N-1){
				CT[i-j][j] = res;
			}
			else{
				CT[N-1-j][abs(N-1-i)+j] = res;
			}
		}
	}
	
	//straighten out state array
	straighten_out();
	while(know_count < N*N){
		int s_res;
		for(i = 0; i < N; i++){
			s_res = 0;
			if(state[0][i][2] == Z_ray[0][i]){
				s_res = -1;
			}
			else if(state[0][i][0] == N - Z_ray[0][i]){
				s_res = 1;
			}
			if(s_res == 0){
				continue;
			}
			for(j = 0; j < N; j++){
				if(CT[j][i] == 0){
					CT[j][i] = s_res;
				}
			}
		}
		straighten_out();
		for(i = 0; i < N; i++){
			s_res = 0;
			if(state[1][i][2] == Z_ray[1][i]){
				s_res = -1;
			}
			else if(state[1][i][0] == N - Z_ray[1][i]){
				s_res = 1;
			}
			if(s_res == 0){
				continue;
			}
			for(j = 0; j < N; j++){
				if(CT[i][j] == 0){
					CT[i][j] = s_res;
				}
			}
		}
		straighten_out();
		for(i = 0; i < 2*N-1; i++){
			s_res = 0;
			if(state[2][i][2] == Z_ray[2][i]){
				s_res = -1;
			}
			else if(state[2][i][0] == N - abs(i + 1 - N) - Z_ray[2][i]){
				s_res = 1;
			}
			if(s_res == 0){
				continue;
			}	
			for(j = 0; j < N - abs(i + 1 - N); j++){
				if(N-1-i < 0 && CT[abs(N-1-i)+j][j] == 0){
					CT[abs(N-1-i)+j][j] = s_res;
				}
				else if(N-1-i >= 0 && CT[j][abs(N-1-i)+j] == 0){
					CT[j][abs(N-1-i)+j] = s_res;
				}
			}
		}
		straighten_out();
		for(i = 0; i < 2*N-1; i++){
			s_res = 0;
			if(state[3][i][2] == Z_ray[3][i]){
				s_res = -1;
			}
			else if(state[3][i][0] == N - abs(i + 1 - N) - Z_ray[3][i]){
				s_res = 1;
			}
			if(s_res == 0){
				continue;
			}
			for(j = 0; j < N - abs(i + 1 - N); j++){
				if(i < N-1 && CT[i-j][j] == 0){
					CT[i-j][j] = s_res;
				}
				else if(i >= N-1 && CT[N-1-j][abs(N-1-i)+j] == 0){
					CT[N-1-j][abs(N-1-i)+j] = s_res;
				}
			}
		}
		straighten_out();
	}

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(CT[i][j] == 1){
				fprintf(out,"B ");
			}
			else{
				fprintf(out,"- ");
			}
		}
		fprintf(out, "\n");
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
