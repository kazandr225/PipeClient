#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//им€ канала (такое жеб как и на сервере)
	HANDLE hNamedPipe;
	while (TRUE)
	{
		hNamedPipe = CreateFile(//открываем канал поп аналогии с открытием файла
			lpszPipeName, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);

		DWORD dwMode = PIPE_READMODE_MESSAGE;

		BOOL isSucces = SetNamedPipeHandleState(
			hNamedPipe,
			&dwMode,
			NULL,
			NULL
		);
		if (!isSucces)
		{
			printf("—ервер не отвечает\n");
		}
		else
		{
			printf("—оединение установлено\n");
			DWORD size_buffer = SIZE_BUFFER; //размер буффера дл€ записи
			DWORD actual_written; //сколько на самом деле было записано байт

			char message[SIZE_BUFFER];
			printf("¬ведите вообщение дл€ сервера:\n");
			gets(message);
			LPWSTR buffer = &message; //строкова€ переменна€, значение которой записываетс€ в канал
			WriteFile(hNamedPipe, buffer, size_buffer,
				&actual_written, NULL);
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}

}