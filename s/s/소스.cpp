#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
struct f_rank {
	char fname[30] = { 0 }, sentence[100] = { 0 };
	int score = 0;
};

int compare(const void *a, const void *b)
{
	struct f_rank *ptr_a = (struct f_rank *)a;
	struct f_rank *ptr_b = (struct f_rank *)b;

	if (ptr_a->score > ptr_b->score)
		return -1;
	else if (ptr_a->score == ptr_b->score)
		return 0;
	else
		return 1;
}

void main(int agrc, char** argv) {
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	char path[255], search[20], search_store[20], search_low[20], search_first[20], search_up[20];
	char *text, *ptr, *ptr_store = NULL, *ptr_low = NULL, *ptr_up = NULL, *ptr_first = NULL, *ptr2 = NULL;
	int size, count = 0, TEXTcount, length, i = 0, j = 0, front = 0, back = 0, alpha = 0, alpha2 = 0, fnum = 0, divide = 0, low = 0, first = 0, up = 0;
	FILE * f;
	struct f_rank rank[5000];

	/**************************************************************/
	//strcpy(path, "C:\\Users\\user\\Documents\\Visual Studio 2017\\Projects\\s\\s\\*.txt");
	sprintf(path, "%s\\%s", "C:\\Users\\user\\Documents\\Visual Studio 2017\\Projects\\s\\s", "*.txt");

	//sprintf(path, "%s\\%s", argv[0], "*.txt");
	//printf("%s", path);
	hFind = FindFirstFile((LPCSTR)path, &FindData); //project속성-구성속성-문자집합 설정안함
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("error!\n");
		system("pause");
	}

	//단어입력받아서 길이저장 
	printf("Search: ");
	scanf("%[^\n]s", search);
	length = strlen(search);
	printf("단어길이: %d \n", length);
	//대소문자생각해주기
	strcpy(search_store, search);
	strlwr(search);
	strcpy(search_low, search);
	search[0] = toupper(search[0]);
	strcpy(search_first, search);
	strupr(search);
	strcpy(search_up, search);
	

	do
	{
		count = 0;
		front = 0;
		back = 0; 
		//char fullname[200];
		//sprintf(fullname, "C:\\Users\\user\\Documents\\Visual Studio 2017\\Projects\\practice\\practice\\%s", FindData.cFileName);
		//f = fopen(fullname, "r");
		//printf("%s\n", strerror(errno));
		f = fopen(FindData.cFileName, "r");
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		text = (char*)malloc(size + 1);
		memset(text, 0, size + 1);
		fseek(f, 0, SEEK_SET);
		TEXTcount = fread(text, size, 1, f);


		//검색한단어
		ptr = strstr(text, search_store);
		i = 0;
		while (ptr != NULL) {
			//printf("앞뒤: '%c'   '%c' \n", *(ptr - 1), *(ptr + length));
			if (ptr != text) {
				if (isalpha(*(ptr - 1)))
					front = 1;
			}
			if (*(ptr + length) != '\0') {
				if (isalpha(*(ptr + length)))
					back = 1;
			}
			//printf("front: %d, back: %d \n", front, back);
			if (front + back == 0) {
				count++;
				if (i == 0) {
					//printf("1.%c", *ptr);
					ptr_store = ptr;
				}
				i++;
			}
			ptr = strstr(ptr + 1, search_store);
		}

		//검색한단어 --->소문자
		for (i = 0;i <= length;i++) {
			if (search_store[i] != search_low[i])
				low = 1;
		}
		if (low) {
			ptr = strstr(text, search_low);
			i = 0;
			while (ptr != NULL) {
				//printf("앞뒤: '%c'   '%c' \n", *(ptr - 1), *(ptr + length));
				if (ptr != text) {
					if (isalpha(*(ptr - 1)))
						front = 1;
				}
				if (*(ptr + length) != '\0') {
					if (isalpha(*(ptr + length)))
						back = 1;
				}
				//printf("front: %d, back: %d \n", front, back);
				if (front + back == 0) {
					count++;
					if (i == 0) {
						//printf("1.%c", *ptr);
						ptr_low = ptr;
					}
					i++;
				}
				ptr = strstr(ptr + 1, search_low);
			}
		}

		//검색한단어--->첫글자만 대문자
		for (i = 0;i <= length;i++) {
			if (search_store[i] != search_first[i])
				first = 1;
		}
		if (first) {
			ptr = strstr(text, search_first);
			i = 0;
			while (ptr != NULL) {
				//printf("앞뒤: '%c'   '%c' \n", *(ptr - 1), *(ptr + length));
				if (ptr != text) {
					if (isalpha(*(ptr - 1)))
						front = 1;
				}
				if (*(ptr + length) != '\0') {
					if (isalpha(*(ptr + length)))
						back = 1;
				}
				//printf("front: %d, back: %d \n", front, back);
				if (front + back == 0) {
					count++;
					if (i == 0) {
						//printf("1.%c", *ptr);
						ptr_first = ptr;
					}
					i++;
				}
				ptr = strstr(ptr + 1, search_first);
			}
		}

		//검색한단어--->대문자
		for (i = 0;i <= length;i++) {
			if (search_store[i] != search_up[i])
				up = 1;
		}
		if (up) {
			ptr = strstr(text, search_up);
			i = 0;
			while (ptr != NULL) {
				//printf("앞뒤: '%c'   '%c' \n", *(ptr - 1), *(ptr + length));
				if (ptr != text) {
					if (isalpha(*(ptr - 1)))
						front = 1;
				}
				if (*(ptr + length) != '\0') {
					if (isalpha(*(ptr + length)))
						back = 1;
				}
				//printf("front: %d, back: %d \n", front, back);
				if (front + back == 0) {
					count++;
					if (i == 0) {
						//printf("1.%c", *ptr);
						ptr_up = ptr;
					}
					i++;
				}
				ptr = strstr(ptr + 1, search_up);
			}
		}


		/*********************************************************************/
		if (ptr_store != NULL) {
			ptr2 = ptr_store;
		}
		else {
			if (ptr_up != NULL)
				ptr2 = ptr_up;
			else {
				if (ptr_first != NULL)
					ptr2 = ptr_first;
				else
					ptr2 = ptr_low;
			}
		}


		//텍스트에 검색한 단어가 있는지
		if (count != 0) {
			strcpy(rank[fnum].fname, FindData.cFileName);
			rank[fnum].score = count * 100000 / size;//랭킹점수 추가해주기
			

			printf("%c%c%c\n", *ptr2, *(ptr2 + 1), *(ptr2 + 2));
			printf("단어개수: %d \n", count);

			//printf("%d...%s...", fnum, FindData.cFileName);
			i = 0;
			if (ptr2 != NULL)
			{
				for (i = 0;i < 90;i++) {
					//printf("%c", *(ptr2 + i));
					if (*(ptr2 + i) != '\n' && *(ptr2 + i) != '\t')
						rank[fnum].sentence[i] = *(ptr2 + i);
					else 
						rank[fnum].sentence[i] = '  ';
					if (*(ptr2 + i) == '\0')
						break;
					if (i > 70) {
						if (*(ptr2 + i) == '\n' || *(ptr2 + i) == '.' || *(ptr2 + i) == '?' || *(ptr2 + i) == '!')
							break;
					}
				}
				//printf("%s", rank[fnum].sentence);
				//printf("\n");
			}
			//printf("--- size: %d, count: %d \n", size, TEXTcount);
			fnum++;
		}
		fclose(f); 
		free(text);
		//text = NULL;
	} while (FindNextFile(hFind, &FindData));

	FindClose(hFind);
	/***************************************************************/
	qsort(rank, fnum, sizeof(struct f_rank), compare);
	if (rank[0].score == 0)
		printf("'%s'에 대한 검색결과가 없습니다. \n", search_store);
	else
		for (i = 0;i < fnum;i++) {
		printf("%-3d...%16s...%s \n", i + 1, rank[i].fname, rank[i].sentence);
		//printf("--(score: %d) \n", rank[i].score);
		}


	system("pause");
}