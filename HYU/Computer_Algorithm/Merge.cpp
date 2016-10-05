//2011004095_leejongwon_eunokpaek's class
#include <stdio.h>

void merge(int a[], int p, int q, int r){
	int tmp[50000] = {0,};
	int i = 0;
	int j = 0;
	int l, m, h;
	l = p; m = q +1; h = r;
	while(l<=q&&m<=r){
		if(a[l]>=a[m]){
			tmp[i] = a[l];
			l = l+1;
		}
		else{
			tmp[i] = a[m];
			m = m+1;
		}
		i = i+1;
	}
	if(l>q){
		for(j=m;j<=r;j++){
			tmp[i] = a[j];
			i = i+1;
		}
	}
	else{
		for(j=l;j<=q;j++){
			tmp[i] = a[j];
			i = i+1;
		}
	}
	for(j=p;j<=r;j++){
		a[j] = tmp[j-p];
	}  	
}

void mergesort(int a[], int p, int q){
	int mid;
	if(p<q){
		mid = p+q;
		mid = mid/2;
		mergesort(a, p, mid);
		mergesort(a, mid+1, q);
		merge(a, p, mid, q);
	}
}

int main(){
	int N = 0;
	int i = 0;
	int a[100000] = {0,};

	scanf("%d",&N);

	for(i=0;i<N;i++){
		scanf("%d",&a[i]);
	}
	
	mergesort(a, 0, N-1);

	for(i=0;i<N;i++){
		printf("%d\n",a[i]);
	}

	return 0;
}
