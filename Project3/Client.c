#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//��� ������ (����� ��� ��� � �� �������)
	HANDLE hNamedPipe;
	while (TRUE)
	{
		hNamedPipe = CreateFile(//��������� ����� ��� �������� � ��������� �����
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
			printf("������ �� ��������\n");
		}
		else
		{
			printf("���������� �����������\n");
			DWORD size_buffer = SIZE_BUFFER; //������ ������� ��� ������
			DWORD actual_written; //������� �� ����� ���� ���� �������� ����

			char message[SIZE_BUFFER];
			printf("������� ��������� ��� �������:\n");
			gets(message);
			LPWSTR buffer = &message; //��������� ����������, �������� ������� ������������ � �����
			WriteFile(hNamedPipe, buffer, size_buffer,
				&actual_written, NULL);
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}

}