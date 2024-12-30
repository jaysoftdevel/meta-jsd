#include <iostream>

int main(void){
	#ifdef defined(ARM_TARGET)
		std::cout << "on arm target!" << std::endl;
	#elif defined(QEMU_TARGET)
		std::cout << "on QEMU target!" << std::endl;
	#else
		std::cout << "UNKNOWN TARGET!!!!" << std::endl;
	#endif
}
