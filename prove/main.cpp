#include <iostream>
#include "Matrix.h"


int main(){

	Matrix A;
	Matrix B;
	A.reAllocate(5,5);
	B.reAllocate(5,5);
	B.eye();
	A.eye();
	A.show();
	B.show();
	A = B;
	A.show();

	return 0;
}
