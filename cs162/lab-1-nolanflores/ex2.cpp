#include <iostream>

void function(int num, int ctr, int &r) {//determines if a number is prime
	int i;
	for(i = 2;i <= num/2; i++){//loop from 2 to half of num
		if(num % i==0){//i is a factor of num
			ctr++;//add 1 to the count of factors
			break;
		}
	}
	if(ctr == 0 && num != 1) {//there were no factors, and num is not 1
		r = 1;//the number is a prime number
	} else {
		r = 0;//the number is not a prime number
	}
}

int main() {

	int num, ctr = 0, r = -1;//ctr is needlessly declared in main
	std::cout << "Input a number: ";
	std::cin >> num;//take number input
	
	function(num, ctr, r);//r is passed by reference, it will be modified
	std::cout << r << std::endl;//print if num is prime

	return 0;
}
