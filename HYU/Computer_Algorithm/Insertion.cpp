//2011004095_leejongwon_eunokpaek's class
#include <stdio.h>

void insertion_sort(int a[], int n){
	int i = 0;
	int j = 0;
	int key = 0;
	for(i=1;i<n;i++){
		key = a[i];
		j = i-1;
		while(j>-1&&a[j]<key){
			a[j+1] = a[j];
			j = j-1;
		}
		a[j+1] = key;
	}		
}

int main(){
	int N = 0;
	int i = 0;
	int input_num = 0;
	int sort[30000] = {0,};
	
	//printf("input the length of array to sort(0<N<=30000) > ");
	scanf("%d",&N);

	//printf("input number to sort -----\n");
	for(i=0;i<N;i++){
		scanf("%d",&input_num);
		sort[i] = input_num;
	}

	insertion_sort(sort, N);
	
	//printf("result of sorting -----\n");
	for(i=0;i<N;i++){
		printf("%d\n",sort[i]);
	}

	return 0;
}
