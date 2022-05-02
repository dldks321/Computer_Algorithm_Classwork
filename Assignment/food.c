#include<stdio.h>
#include<string.h>

typedef struct nutrient{
	int protein;
	int fat;
	int carb;
	int vitamin;
	int price;
}Nutrient;

Nutrient ingredients[50];
Nutrient Need;
Nutrient Best;
int b_lis[50];

int k;

int backtrack(Nutrient nut, int loca, int* lis){
	//printf("%d %d %d %d %d\n", nut.protein, nut.fat, nut.carb, nut.vitamin, nut.price);
	if(nut.protein >= Need.protein && nut.fat >= Need.fat && nut.carb >= Need.carb && nut.vitamin >= Need.vitamin){
		//printf("%d %d %d %d %d\n", nut.protein, nut.fat, nut.carb, nut.vitamin, nut.price);
		if(Best.protein == 0){
			Best.protein = nut.protein;
			Best.fat = nut.fat;
			Best.carb = nut.carb;
			Best.vitamin = nut.vitamin;
			Best.price = nut.price;
			memmove(b_lis,lis,sizeof(int)*50);
		}
		else if(Best.price > nut.price){
			Best.protein = nut.protein;
			Best.fat = nut.fat;
			Best.carb = nut.carb;
			Best.vitamin = nut.vitamin;
			Best.price = nut.price;
			memmove(b_lis,lis,sizeof(int)*50);
		}
		else if(Best.price == nut.price && (nut.protein+nut.fat+nut.carb+nut.carb) > (Best.protein+Best.fat+Best.carb+Best.vitamin)){
			Best.protein = nut.protein;
			Best.fat = nut.fat;
			Best.carb = nut.carb;
			Best.vitamin = nut.vitamin;
			Best.price = nut.price;
			memmove(b_lis,lis,sizeof(int)*50);
		}
		//printf("%d\n",Best.price);
	}
	/*if(Best.protein != 0 && nut.price > Best.price){
		return 0;
	}*/
	
	int i;
	
	for(i = loca; i < k; i++){
		if(Best.protein != 0 && nut.price+ingredients[i].price > Best.price){
			continue;
		}
		Nutrient Next = {nut.protein+ingredients[i].protein, nut.fat+ingredients[i].fat, nut.carb+ingredients[i].carb, nut.vitamin+ingredients[i].vitamin, nut.price+ingredients[i].price};
		int n_lis[50] = {0,};
		memmove(n_lis,lis,sizeof(int)*50);
		int j = 0;
		while(1){
			if(n_lis[j] == 0){
				n_lis[j] = i+1;
				break;
			}
			j++;
		}
		backtrack(Next, i+1, n_lis);
	}
	return 0;
}

int main(void){	
    FILE *in=fopen("food.inp","r");
    FILE *out=fopen("food.out","w");
	
	fscanf(in, "%d", &k);
	
	int i;
	
	fscanf(in, "%d %d %d %d", &Need.protein, &Need.fat, &Need.carb, &Need.vitamin);
	
	for(i = 0; i < k; i++){
		fscanf(in, "%d %d %d %d %d", &ingredients[i].protein, &ingredients[i].fat, &ingredients[i].carb, &ingredients[i].vitamin, &ingredients[i].price);
	}
	
	/*printf("%d %d %d %d\n",Need.protein, Need.fat, Need.carb, Need.vitamin);
	
	for(i = 0; i < k; i++){
		printf("%d %d %d %d %d\n", ingredients[i].protein, ingredients[i].fat, ingredients[i].carb, ingredients[i].vitamin, ingredients[i].price);
	}*/
	
	Nutrient init = {0, 0, 0, 0, 0};
	int lis[50] = {0,};
	
	backtrack(init, 0, lis);
	
	//printf("%d %d %d %d %d", Best.protein, Best.fat, Best.carb, Best.vitamin, Best.price);
	i = 0;
	int flag = 1;
	while(1){
		if(b_lis[i] != 0){
			fprintf(out,"%d ",b_lis[i]);
			flag *= 0;
		}
		else{
			break;
		}
		i++;
	}
	if(flag == 1){
		fprintf(out,"%d",0);
	}
	
    fclose(in);
    fclose(out);
	
	return 0;
}
