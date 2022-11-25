#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//имя канала (такое жеб как и на сервере)
	
	BOOL flag_otvet = TRUE;
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER; //размер буффера для записи
	DWORD actual_written; //сколько на самом деле было записано байт
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	DWORD actual_readen;
	BOOL SuccessRead;

	HANDLE hNamedPipe;
	while (TRUE)
	{
		hNamedPipe = CreateFile(//открываем канал поп аналогии с открытием файла
			lpszPipeName, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		
		DWORD dwMode = PIPE_READMODE_MESSAGE;
		BOOL isSucces = SetNamedPipeHandleState(hNamedPipe,&dwMode,NULL,NULL);
		if (!isSucces)
		{
			printf("Сервер не отвечает\n");
			flag_otvet = TRUE;
		}
		else
		{
			//printf("Соединение установлено\n");
			if (flag_otvet)
			{
				printf("Введите вообщение для сервера:\n");
				gets(message);
				buffer = &message; //строковая переменная, значение которой записывается в канал
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_written, NULL);
				flag_otvet = FALSE;
			}
			SuccessRead = ReadFile(hNamedPipe,buffer,SIZE_BUFFER, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\nСервер пишет: ");
				printf(buffer);
				printf("\n");
				flag_otvet = TRUE;
				/*if (buffer == NULL)
				{
					printf("Пусто\n");
				}*/
			}
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}

}