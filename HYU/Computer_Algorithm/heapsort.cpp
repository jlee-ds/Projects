#include <stdio.h>

void MaxHeapify(int a[], int p, int length){
	int left, right;
	int tmp;
	left = p*2;
	right = p*2 + 1;
	if(right<=length){
	if(a[left] >= a[right]){
		if(a[left] > a[p]){
			tmp = a[left];
			a[left] = a[p];
			a[p] = tmp;	
			MaxHeapify(a, left, length);
		}
	}	
	else{
		if(a[right] > a[p]){
			tmp = a[right];
			a[right] = a[p];
			a[p] = tmp;
			MaxHeapify(a, right, length);
		}
	}
	}
	else if(left<=length&&right>length){
		if(a[left] > a[p]){
			tmp = a[left];
			a[left] = a[p];
			a[p] = tmp;
		}
	}
}

void BuildHeap(int a[], int length){
	int p;
	p = (length)/2;
	for(;p>0;p--){
		MaxHeapify(a, p, length);
	}	
}

int DeleteHeap(int a[], int* length){
	int tmp;
	tmp = a[1];
	a[1] = a[*(length)];
	*(length) = *(length)-1;
	MaxHeapify(a, 1, *(length));	
	return tmp;
}

int main(void){
	int a[100000];
	int length;
	int execount;
	int i;
	int Max;

	scanf("%d %d",&length,&execount);
	for(i=1;i<=length;i++){
		scanf("%d",&a[i]);
	}
	BuildHeap(a, length);
	//for(i=1;i<=length;i++)
		//printf("%d ",a[i]);
	for(i=1;i<=execount;i++){
		Max = DeleteHeap(a, &length);
		printf("%d ",Max);
	}
	printf("\n");
	for(i=1;i<=length;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
