#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#define PRECISION 0.0001

float get_rate(char curr);
bool is_equal(float a, float b);
void test(void);

int main(void) {
	test();
	char cur_type;
	printf("Enter the currency you would like to receive: \n"
			"- p for GBP\n"
			"- d for USD\n"
			"- e for EUR\n");
	cur_type = getchar();
	float rate = get_rate(cur_type);
	printf("The exchange rate for %c is %f", cur_type, rate);
}

float get_rate(char curr) {
	switch(curr) {
		case 'p':
			return 1.0;
		case 'd':
			return 1.3;
		case 'e':
			return 1.11;
		default:
			return -1;
	}
}

bool is_equal(float a, float b) {
	if(a >= b - PRECISION && a <= b + PRECISION) {
		return true;
	} else {
		return false;
	}
}

void test(void) {
	// is_equal()
	// basic testing
	assert(is_equal(1.0, 1.0) == true);
	assert(is_equal(1.1, 1.0) == false);
	assert(is_equal(-1, -1) == true);
	// overfloat testing
	assert(is_equal(3.402823e+38, 3.402823e+38) == true);
	assert(is_equal(1.175494e-38, 3.402823e+38) == false);
	// get_rate()
	assert(is_equal(get_rate('p'), 1.0) == true);
	assert(is_equal(get_rate('d'), 1.0) == false);
	assert(is_equal(get_rate('z'), -1) == true);
	assert(is_equal(get_rate('\n'), -1) == true);
	assert(is_equal(get_rate(0), -1) == true);
	assert(is_equal(get_rate(100), 1.3) == true);
}
