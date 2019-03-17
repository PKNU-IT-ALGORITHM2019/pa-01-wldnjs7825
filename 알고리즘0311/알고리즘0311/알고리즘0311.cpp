#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct word {
	char name[15]; //단어
	char cla[10]; //품사
	char exp[5000];//단어 설명
} w_list[200000];

int bi_search(char w_name[], int first, int last);
char *token;

int main() {
	FILE *fp;
	char buffer[5000];
	char f_word[15];
	int w_cnt = 0;
	char *cont = NULL;

	fopen_s(&fp, "dict.txt", "r");

	if (fp == NULL)
	{
		printf("test.txt 파일 오픈 불가\n");    //화면에 오류 표시
		fclose(fp);
	}
	while (!feof(fp)) {
		fgets(buffer, sizeof(buffer), fp);
		//strcpy_s(w_list[w_cnt].exp, 5000, buffer);
		
		token = strtok_s(buffer, " ", &cont);
		strcpy_s(w_list[w_cnt].name, 5000, token); 
		token = strtok_s(NULL, " ", &cont);
		strcpy_s(w_list[w_cnt].cla, 5000, token); 
		w_cnt++;
		fgetc(fp);
	}
	printf("szie = %d\n", w_cnt);
	
	printf("단어를 입력하시오:\n");
	scanf_s("%s", f_word, 15);
	f_word[0] = f_word[0] - 32;
	int bi_list = bi_search(f_word, 0, w_cnt - 1);
	if (bi_list == -1) 
		printf("찾는 단어가 없습니다.\n");
    else
	{
		int count = -1, i = bi_list;
		while (i< w_cnt&& strcmp(w_list[i++].name, f_word) == 0)
			count++;
		printf("단어를 찾았습니다.\n");
		printf("%s \n", w_list[bi_list].name);
		for (int i = bi_list + 1; i <= bi_list + count; i++)
			printf("%s (%s)\n", w_list[i].name, w_list[bi_list]);	
	}			

	fclose(fp);
	return 0;
}

int bi_search(char w_name[], int first, int last) {
    int i;

    int key = (last + first ) / 2;
	   i = strcmp(w_list[key].name, w_name);
		   if (i == 0)return key;
	   else if (first > last)return -1 ;
	   else if (i == 1)return  bi_search(w_name, first,  key - 1);
	   else  return  bi_search(w_name, key + 1, last);
}

