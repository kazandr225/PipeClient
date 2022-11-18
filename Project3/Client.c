#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	HANDLE hNamedPipe;
	while (TRUE)
	{
		hNamedPipe = CreateFile(
		
		);
	}

}