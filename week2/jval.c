#include <stdio.h>
#include <stdlib.h>

typedef union {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} Jval; 

Jval new_jval_i(int i) { Jval j; j.i = i; return j; }
Jval new_jval_l(long l) { Jval j; j.l = l; return j; }
Jval new_jval_f(float f) { Jval j; j.f = f; return j; }
Jval new_jval_d(double d) { Jval j; j.d = d; return j; }
Jval new_jval_v(void *v) { Jval j; j.v = v; return j; }

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }

int compare_jval_i(Jval *a, Jval *b);
void swap_jval(Jval *a, Jval *b);
void sort_gen ( Jval a[], int l, int r, int (*compare)(Jval*, Jval*) );
int search_gen ( Jval a[], int l, int r, Jval item, int (*compare)(Jval*, Jval*) );


void main(){
	printf("Hello, world!\n");
	Jval arr[10];
	for(int i = 0; i < 10; i++){
		arr[i] = new_jval_i(10 - i);
		printf("%d ", jval_i(arr[i]));
	}
	printf("\n");
	sort_gen(arr, 0, 9, compare_jval_i);
	for(int i = 0; i < 10; i++){
		printf("%d ", jval_i(arr[i]));
	}

	int n;
	printf("Enter int to search: ");
	scanf("%d", &n);
	Jval item = new_jval_i(n);
	printf("Result: %d\n", search_gen(arr, 0, 9, item, compare_jval_i));
}

void swap_jval(Jval *a, Jval *b){
	Jval temp = *a;
	*a = *b;
	*b = temp;
}

int compare_jval_i(Jval *a, Jval *b){
	int int_a = jval_i(*a);
	int int_b = jval_i(*b);
	return int_a - int_b;
}

void sort_gen(Jval a[], int l, int r, int (*compare)(Jval*, Jval*)){
	if(r <= l)
		return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1){
		while(compare(&a[++i], &a[r]) < 0);
		while(compare(&a[r], &a[--j]) < 0) if(j == l) break;
		if(i >= j) break;
		swap_jval(&a[i], &a[j]);
		if(compare(&a[i], &a[r]) == 0) swap_jval(&a[++p], &a[i]);
		if(compare(&a[j], &a[r]) == 0) swap_jval(&a[--q], &a[j]);
	}
	swap_jval(&a[i], &a[r]);
	j = i - 1;
	i = i + 1;
	for(int k = l; k <= p; k++) swap_jval(&a[k], &a[j--]);
	for(int k = r - 1; k >= q; k--) swap_jval(&a[k], &a[i++]);
	sort_gen(a, l, j, compare);
	sort_gen(a, i, r, compare);
}

int search_gen ( Jval a[], int l, int r, Jval item, int (*compare)(Jval*, Jval*) ){
	if(l > r)
		return -1;
	int m = (l + r)/2;
	if(compare(&item, &a[m]) == 0)
		return m;
	if(compare(&item, &a[m]) > 0)
		return search_gen(a, m + 1, r, item, compare);
	return search_gen(a, l, m - 1, item, compare);
}
