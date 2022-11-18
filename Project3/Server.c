//код сервера

#include <stdio.h>
#include <Windows.h>

int main()
{
	system("chcp 1251<nul");
	while (TRUE)
	{
		HANDLE hNamedPipe;
		LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
		hNamedPipe = CreateNamePipe(
			lpszPipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			512,
			512,
			INFINITE,
			NULL);

		BOOL Connected = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connected)
		{
			printf("\nКлиент успешно подключился\n");
			DWORD size_buffer = 100;
			LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));

			DWORD actual_readen;
			BOOL SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			if (!SuccessRead)
			{
				printf("\nКлиент отключился от сервера\n");
			}
			printf(buffer);
			CloseHandle(hNamedPipe);
		}
	}
}