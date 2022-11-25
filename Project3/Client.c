#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251>nul");
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//��� ������ (����� ��� ��� � �� �������)
	
	BOOL flag_otvet = TRUE;
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER; //������ ������� ��� ������
	DWORD actual_written; //������� �� ����� ���� ���� �������� ����
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	DWORD actual_readen;
	BOOL SuccessRead;

	HANDLE hNamedPipe;
	while (TRUE)
	{
		hNamedPipe = CreateFile(//��������� ����� ��� �������� � ��������� �����
			lpszPipeName, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		
		DWORD dwMode = PIPE_READMODE_MESSAGE;
		BOOL isSucces = SetNamedPipeHandleState(hNamedPipe,&dwMode,NULL,NULL);
		if (!isSucces)
		{
			printf("������ �� ��������\n");
			flag_otvet = TRUE;
		}
		else
		{
			//printf("���������� �����������\n");
			if (flag_otvet)
			{
				printf("������� ��������� ��� �������:\n");
				gets(message);
				buffer = &message; //��������� ����������, �������� ������� ������������ � �����
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_written, NULL);
				flag_otvet = FALSE;
			}
			SuccessRead = ReadFile(hNamedPipe,buffer,SIZE_BUFFER, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\n������ �����: ");
				printf(buffer);
				printf("\n");
				flag_otvet = TRUE;
				/*if (buffer == NULL)
				{
					printf("�����\n");
				}*/
			}
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}

}