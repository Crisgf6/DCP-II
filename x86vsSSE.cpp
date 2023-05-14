#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#define VSIZE 100000000
#define MAXRAND 42

class timer
{
public:
	timer() = default;
	void start(const std::string& text_)
	{
		text = text_;
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << std::setw(20) << text << " timing:" << std::setw(5) << ms << "ms" << std::endl;
	}

private:
	std::string text;
	std::chrono::high_resolution_clock::time_point begin;
};

int recursive_fibSSE(int n) {

	unsigned long int i, j, k;
	
	_asm {
		mov i, 0;
		mov j, 0;
		mov eax, n;

	inicio:
		dec n;
		cmp n, 2;
		jg recursive;
		jmp fin;

	recursive:
		add i, eax;
		add j, eax;
		sub i, 2;
		sub j, 1;
		addss eax, i;
		addss eax, j;
		jmp inicio

	fin:

	}
	
}

int recursive_fibASM(unsigned long int* n, bool* g, int tam) {
		unsigned long int i, j, a, b;
		__asm {
			mov eax, n;
			mov ebx, g;
			mov i, 0;
		bucle_guessIfFibonacci:
			mov edi, tam;
			cmp i, edi;
			je fin_bucle_guessIfFibonacci;

			mov a, 0;
			mov b, 1;
			mov edi, 1;
			mov j, 0; 
		bucle_isFibonacci:
			
			cmp j, 0;
			je primerFibonacci;

			mov edx, 1; 
		bucle_getFibonacci:
			cmp j, edi;
			je fin_bucle_getFibonacci;

			xor edx, edx;
			add edx, a;
			add edx, b;
			mov ecx, b;
			mov a, ecx; 
			mov b, edx; 

			inc edi; 
			jmp bucle_getFibonacci;

		primerFibonacci:
			mov edx, 0;
			jmp fin_bucle_getFibonacci;

		fin_bucle_getFibonacci:
			
			mov esi, i;
			mov esi, [eax + esi * 4];
			cmp esi, edx; 
			jg nextFibonacci;
			cmp esi, edx; 
			je fibonacciTrue;
			jmp fibonacciFalse; 

		nextFibonacci:
			inc j; 
			jmp bucle_isFibonacci;

		fibonacciTrue:
			mov esi, i;
			mov[ebx + esi], 1; 
			inc i; 
			jmp bucle_guessIfFibonacci;

		fibonacciFalse:
			mov esi, i;
			mov[ebx + esi], 0; 
			inc i; 
			jmp bucle_guessIfFibonacci;

		fin_bucle_guessIfFibonacci:
	}
}

void 
generateRandomNumbers(unsigned long int* v, int tam) {
	srand(0);
	
	for (int i = 0; i < tam; i++) v[i] = rand() % MAXRAND;
}

int main()
{
	timer stopwatch;
	std::int64_t n = 0;

	unsigned long int* numbers = new unsigned long int[VSIZE];
	generateRandomNumbers(numbers, VSIZE);

	

	stopwatch.start("fibonacci_SSE");
	for (int i = 0; i < VSIZE; i++) {
		recursive_fibSSE(numbers[i]);
	
	}
	
	stopwatch.stop();	

	stopwatch.start("fibonacci_x86");
	bool* fibonacci = new bool[VSIZE];
	recursive_fibASM(numbers, fibonacci, VSIZE);
	stopwatch.stop();
	system("PAUSE");
}