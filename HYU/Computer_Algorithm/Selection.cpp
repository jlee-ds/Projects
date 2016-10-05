//2011004095_leejongwon_eunokpaek's class
#include <stdio.h>

void selection_sort(int a[], int N, int count){
	int i = 0;
	int j = 0;
	int tmp = 0;
	int tmp_2 = 0;

	for(i=0;i<count;i++){
		tmp = i;
		for(j=i+1;j<N;j++)
			if(a[tmp]>a[j]) tmp = j;
		tmp_2 = a[tmp];
		a[tmp] = a[i];
		a[i] = tmp_2;
	}
}

int main(){
	int i = 0;
	int N = 0;
	int count = 0;
	int a[30000] = {0,};
	
	scanf("%d %d",&N,&count);

	for(i=0;i<N;i++)	
		scanf("%d",&a[i]);

	selection_sort(a, N, count);
	
	for(i=0;i<N;i++)
		printf("%d\n",a[i]);

	return 0;
}
