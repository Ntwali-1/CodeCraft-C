#include <stdio.h>

int fibonnaci(int n){
	if(n==0) return 0;
	if(n==1) return 1;
	return (fibonnaci(n-1)+fibonnaci(n-2));
}
int factorial(int n){
	if(n==0 || n==1) return 1;
	return (n*factorial(n-1));
}
void swap(int *a,int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int main(){
//	int n=7;
//	int i=5;
//	printf("The fibonnaci sequence of %d is: \n",n);
//
//	for(int i=0;i<n;i++){
//		printf("%d ",fibonnaci(i));
//	}
//	printf("\n");
//	
//	printf("The factorial of %d is %d",i,factorial(i));
//	printf("\n");
//	swap(&n,&i);
//	printf("%d  ",n);
//	printf("%d",i);
//	printf("\n");
//	
//	int *ptr = NULL;
//	int a;
//	
//	printf("Enter the number of values: \n");
//	scanf("%d",&a);
//	
//	ptr = (int *)malloc(a*sizeof(int));
//	
//	int sum = 0;
//	
//	printf("Enter the values: \n");
//	for(int i=0;i<a;i++){
//		scanf("%d",(ptr+i));
//		sum += *(ptr+i);
//	}
//	printf("%d\n\n",sum);
//	
//	int z = 11;
//	int v = 5;
//	int y = 4;
//	int l;
//	if(z>v){
//		if(z>y){
//			l = z;
//		}else{
//			l = y;
//		}
//	}else{
//		l = v;
//	}
//	printf("%d\n",l);
	
//	int lv=0;
//	int d = 15;
//	for(int i=2;i<d-1;i++){
//		if(d % i == 0){
//			lv+=1;
//			break;
//    	}	
//    }
//    if(lv==1){
//		printf("The number is not prime");
//	}else{
//		printf("The number is prime");
//	}
	
//	int d = 34567856,count=0;
//	while(d>0){
//		d /= 10;
//		count+=1;
//	}
//	printf("%d\n",count);
//	
//	int arr[]={21,3,2,12,43,65};
//	int n = sizeof(arr)/sizeof(arr[1]);
//	
//	for(int i=0;i<n-1;i++){
//		for(int j=0;j<n-1;j++){
//			if(arr[j]>arr[j+1]){
//				int temp = arr[j];
//				arr[j] =arr[j+1];
//				arr[j+1] = temp;
//			}
//		}
//	}
//	for(int i=0;i<n;i++){
//		printf("%d ",arr[i]);
//	}
//}

int arr[] = {1,2,3,4,5,6};
int *ptr = arr;

for(int i=0;i<6;i++){
	printf("%d  ",*(ptr+i));
}
printf("\n");
 
int *ptr2 = &ptr;

for(int i=0;i<6;i++){
	printf("%d ",*(ptr2+i));
}
}

