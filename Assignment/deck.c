#include<stdio.h>
#include<math.h>

int main(void){	
    FILE *in=fopen("deck.inp","r");
    FILE *out=fopen("deck.out","w");
	
	double N;
	fscanf(in,"%lf",&N);
	
	double sum = 0;
	double exp_sum = 0;
	int count = 0;
	
	while(1) {
		int card = 0;
		fscanf(in,"%d",&card);
		if(card == 0){
			break;
		}
		sum += card;
		exp_sum += (card * card);
		count += 1;
	}
	
	double mis_sum = N*(N+1) / 2 - sum;
	double mis_exp_sum = N*(N+1)*(2*N+1) / 6 - exp_sum;
	
	if(count == N-1){
		fprintf(out, "%.0lf", mis_sum);
	}
	else{
		double a = (mis_sum - sqrt(2*mis_exp_sum - mis_sum*mis_sum)) / 2;
		double b = mis_sum - a;
		if(b > a){
			fprintf(out, "%.0lf\n%.0lf", a, b);
		}
		else{
			fprintf(out, "%.0lf\n%.0lf", b, a);
		}
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
