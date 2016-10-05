#include <stdio.h>

void insertqueue(int a[], int *length, int item){
	int parent;
	int tmp;
	int child;
	*(length) = *(length) + 1;
	a[*(length)] = item;
	parent = *(length)/2;
	child = *(length);
	while(parent>0){
		if(a[parent]<a[child]){
			tmp = a[child];
			a[child] = a[parent];
			a[parent] = tmp;
			parent = parent/2;
			child = child/2;
		}else break;
	}
}
void MaxHeapify(int a[], int p, int length){
	int left, right;
	int tmp;
	left = p*2;
	right = p*2 + 1;
	if(right<=length){
	if(a[left] > a[right]){
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
int deletequeue(int a[], int* length){
	int tmp;
	tmp = a[1];
	a[1] = a[*(length)];
	*(length) = *(length)-1;
	MaxHeapify(a, 1, *(length));	
	return tmp;
}
void changeItem(int a[], int index, int item, int *length){
	int parent, child;
	int tmp;
	a[index] = item;
	parent = index/2;
	child = index;
	while(parent>0){
		if(a[parent]<a[child]){
			tmp = a[child];
			a[child] = a[parent];
			a[parent] = tmp;
			parent /= 2;
			child /= 2;
		}else break;
	}MaxHeapify(a, child, *(length));	
}
int main(){
	int a[100001];
	int Max[100000];
	int length = 0;
	int ctrl, index, item;
	int count = 0;
	
	while(1){
	scanf("%d",&ctrl);
	if(ctrl == 0){
		int i;
		for(i =0;i<count-1;i++)
			printf("%d ",Max[i]);
		if ( count != 0 )
			printf("%d", Max[count-1]);
		printf("\n");
		for(i =1;i<length;i++)
			printf("%d ",a[i]);
		if(length>0) printf("%d", a[length]);
		printf("\n");
		return 0;
	}else if(ctrl == 1){
		scanf("%d",&item);
		insertqueue(a,&length,item);
	}else if(ctrl == 2){
		if(length>0){
		Max[count] = deletequeue(a,&length);
		count++;
		}
	}else if(ctrl == 3){
		scanf("%d %d",&index,&item);
		changeItem(a,index,item,&length);
	}}
}

