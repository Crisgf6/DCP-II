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

#define TAM_VECTOR 19999
#define RANGO_MAXIMO 1000000

#define TAM_VECTOR2 19999
#define RANGO_MAXIMO2 1000000

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

int iterativo_fib(int n)
{
	if (n < 2)
		return n;

	int second_fib = 0, first_fib = 1, current_fib = 0;
	for (int i = 2; i <= n; i++)
	{
		current_fib = second_fib + first_fib;
		second_fib = first_fib;
		first_fib = current_fib;
	}
	return current_fib;
}

int iterativo_fibASM(unsigned long int* n, bool* g, int tam) {

		unsigned long int i, j, a, b;


		__asm {
			mov eax, n;
			mov ebx, g;
			mov i, 0;

		fib_for:
			mov edi, tam;
			cmp i, edi;
			je fin_fib_for;
			mov a, 0; // Primer numero fib
			mov b, 1; // Segundo numero fib
			mov edi, 1; 
			mov j, 0; // nth fib number

		fib_forPertenece:
			cmp j, 0; // Comparamos con el primer numero
			je fib_First;
			mov edx, 1; // Else minimo 0

		ConseguirFib_for:
			// Bucle for de la forma iterativa de fib.
			cmp j, edi; 
			je fin_ConseguirFib_for;
			xor edx, edx;
			add edx, a;
			add edx, b;
			mov ecx, b;
			mov a, ecx; 
			mov b, edx; 
			// Se incrementa el contador del bucle.
			inc edi;
			jmp ConseguirFib_for;

		fib_First:
			mov edx, 0;
			jmp fin_ConseguirFib_for;

		fin_ConseguirFib_for:
			mov esi, i;
			mov esi, [eax + esi * 4]; 
			cmp esi, edx; 
			jg fib_Siguiente;
			cmp esi, edx; 
			je fib_Pertenece; // Si pertenece a secuencia fib
			jmp fib_NoPertenece;  // Si no pertenece a secuecia fib

		fib_Pertenece:
			mov esi, i;
			mov[ebx + esi], 1;
			inc i;
			jmp fib_for;

		fib_NoPertenece:
			mov esi, i;
			mov[ebx + esi], 0;
			inc i;
			jmp fib_for;

		fib_Siguiente:
			inc j; 
			jmp fib_forPertenece;

		fin_fib_for:
	}
}

void generateRandomNumbers(unsigned long int* v, int tam) {


	srand(0);
	for (int i = 0; i < tam; i++) 
		v[i] = rand() % RANGO_MAXIMO;


}

void generateRandomNumbers2(unsigned long int* v, int tam) {


	srand(0);
	for (int i = 0; i < tam; i++) 
		v[i] = rand() % RANGO_MAXIMO2;


}
int main()
{
	timer stopwatch;
	std::int64_t n = 0;

	unsigned long int* numbers = new unsigned long int[TAM_VECTOR];
	unsigned long int* numbers2 = new unsigned long int[TAM_VECTOR2];
	generateRandomNumbers(numbers, TAM_VECTOR);
	generateRandomNumbers2(numbers2, TAM_VECTOR2);

	stopwatch.start("iterativo_fib");
	for (int i = 0; i < TAM_VECTOR; i++) {
		iterativo_fib(numbers[i]);
	}
	stopwatch.stop();	

	stopwatch.start("iterativo_fibASM");
	bool* fibonacci = new bool[TAM_VECTOR2];
	iterativo_fibASM(numbers2, fibonacci, TAM_VECTOR2);
	stopwatch.stop();
	system("PAUSE");
}