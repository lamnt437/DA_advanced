#include "libfdr/jval.h"
#include <stdio.h>

void main(){
	Jval value = new_jval_i(5);
	printf("Jval's value: %d\n", jval_i(value));
}