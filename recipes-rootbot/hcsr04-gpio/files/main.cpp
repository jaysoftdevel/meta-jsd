#include <iostream>
#include <chrono>

extern "C" {
	#include "iolib.h"
	#include <unistd.h>
}
using namespace std;

int gpio_pinner(){
	int cnt=0;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	cout << "### Do iolib_init" << endl;
	if(iolib_init()!=0){
		cout << "### Error during iolib_init()" << endl;
		return -1;
	}
	cout << "### Do iolib_setdir for P8_46, output" << endl;
	if(iolib_setdir(8,46,DIR_IN)){
		cout << "### Error during iolib_setdir(8,46,DIR_IN)" << endl;
		return -2;
	}
	cout << "### Do iolib_setdir for P8_41, input" << endl;
	if(iolib_setdir(8,41,DIR_OUT)){
		cout << "### Error during iolib_setdir(8,41,DIR_OUT)" << endl;
		return -2;
	}
	cout << "### set initial value of trigger pin to low" << endl;
	pin_low(8,41);
	cout << "### Starting loop" << endl;
	while(cnt++<200){
		cout << "### Send 1ms impulse to trigger" << endl;
		pin_high(8,41);
		usleep(10000);
		pin_low(8,41);
		while(!is_high(8,46)){
			// implement exit strategy
		}
		// start clock
		start = std::chrono::steady_clock::now();
		while(!is_low(8,46)){
			// implement exit strategy
		}
		end = std::chrono::steady_clock::now();
		auto duration = (end - start).count();
		// very rough calculation, to be fixed!!
		cout << "### Distance of travelled sound: " << duration / 58440 << "cm ##" << endl;
		usleep(500000);
	}
	cout << "### end of measurement #" << endl;
	if(iolib_free()!=0){
		cout << "### Error freeing iolib" << endl;
		return -3;
	}
	return 0;
}

int main(void){
	cout << "### Starting..." << endl;
	gpio_pinner();
	cout << "### Done..." << endl;
	return 0;
}
