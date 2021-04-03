#include "def.h"
//�½�data
struct data* Creatdata()
{
	struct data* new_data = (struct data*)malloc(sizeof(struct data));
	new_data->next = NULL;
	new_data->num = 0;
	return new_data;
}

//�½�line
struct line* Creatline()
{
	struct line* new_line = (struct line*)malloc(sizeof(struct line));
	new_line->next = NULL;
	new_line->head = NULL;
	return new_line;
}

//��ȡcnf�ļ�
struct line* Read_cnf(char* filename, int* weight, int* variable,int* linenum)
{
	char read[64];
	int i = 0;
	char* temp;
	struct data* current_data = NULL, * pre_data = NULL;
	struct line* root = NULL, * current_line = NULL, * pre_line = NULL;
	FILE* fp = fopen(filename, "r");
	if (!fp) return NULL;
	while (fgets(read, 64, fp))		//��ȡһ��
	{
		if (read[0] == 'c') continue;
		if (read[0] == 'p')
		{
			sscanf(read, "p cnf %d %d", variable, linenum);		//��ȡ��Ԫ���;�����
			continue;
		}
		current_line = Creatline();
		if (!root) root = current_line;
		temp = strtok(read, (const char*)" ");		//���ո�ָ��ȡ
		while (temp)
		{
			current_data = Creatdata();
			i = atoi(temp);			//atoi�������ַ���ת��Ϊ��ֵ
			if (i > 0) weight[i]++;
			else weight[-i]++;
			current_data->num = i;
			if (current_data->num)
			{
				if (!current_line->head) current_line->head = current_data;
				if (pre_data) pre_data->next = current_data;
			}
			pre_data = current_data;
			temp = strtok(NULL, (const char*)" ");
		}
		if (pre_line) pre_line->next = current_line;
		pre_line = current_line;
		pre_data = NULL;
	}
	fclose(fp);
	return root;
}