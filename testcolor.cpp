#include <iostream>
#include <string>
#include <windows.h>

int main(int argc, char **argv) {

	// printf("\n");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 1; k < 255; k++) {
		SetConsoleTextAttribute(hConsole, k);
		printf("%i\t", k);
	}
	SetConsoleTextAttribute(hConsole, 7);
	return 0;
}