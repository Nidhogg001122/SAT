/*-----------------------------------չʾ����--------------------------------*/

#include "def.h"

int main()
{

	char filename[32];
	char* result;
	int choice = 1, sat = 0, sat_choice = 0;
	int i = 0;		//������
	int weight[4000] = { 0 };
	int order[4000] = { 1 };
	int variable, linenum;
	int value[4000] = { 0 }; //��ֵ��
	int solution[256] = { 0 };
	clock_t start, end;
	double runtime;
	while (choice)
	{
	start:
		system("cls");
		printf("\n1.SAT			2.����				3.����\n\n��ѡ�� ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1://SAT���CNF
		{
			system("cls");
			printf("\n1.��ȡcnf�ļ�			2.����\n\n��ѡ�� ");
			scanf("%d", &sat);
			switch (sat)
			{
			case 1:
			{
				system("cls");
				printf("\n�������ļ���ַ��");
				scanf("%s", &filename);
				struct line* root = Read_cnf(filename,weight,&variable, &linenum);
				result = strtok(filename, ".");
				if (root)
				{
					printf("\n��ȡ�ɹ�		��Ԫ����%d		��������%d", variable, linenum);
				}
				else
				{
					printf("\n��ȡʧ��\n\n");
					system("pause");
					goto start;
				}
				printf("\n\n1.�Ż�ǰ			2.�Ż���		3.�����ļ�����\n\n��ѡ�� ");
				scanf("%d", &sat_choice);			//ѡ���Ż������㷨
				switch (sat_choice)
				{
				case 1:		//�Ż�ǰ
				{
					start = clock();
					i = DPLL(root, value);
					end = clock();
					result = strcat(result, ".res");
					FILE* fp = fopen(result, "w+");
					if (i)
					{
						runtime = (double)(end - start);
						fprintf(fp, "s %d\nv ", i);
						printf("\n\n����ɽ�,����ʱ��Ϊ%.2f ms������ѱ���\n\n", runtime);
						int j = 0;
						for (i = 1; i <= variable; i++)
						{
							if (j < 15)
							{
								if (value[i])
								{
									fprintf(fp, "%d ", i);
									printf("%d ", i);
								}
								else
								{
									fprintf(fp, "%d ", -i);
									printf("%d ", -i);
								}
								j++;
							}
							else
							{
								j = 0;
								if (value[i])
								{
									fprintf(fp, "%d", i);
									printf("%d", i);
								}
								else
								{
									fprintf(fp, "%d", -i);
									printf("%d", -i);
								}
								fprintf(fp, "\n");
								printf("\n");
							}
						}
						printf("\n\n");

					}
					else
					{
						runtime = (double)(end - start);
						fprintf(fp, "s %d\nv ", i);
						printf("\n\n���ⲻ�ɽ�,����ʱ��Ϊ%.2f ms,����ѱ���\n\n", runtime);
					}
					fprintf(fp, "\nt %.2f", runtime);
					fclose(fp);
					break;
				}
				case 2:		//�Ż���
				{
					start = clock();
					i = DPLL_better(root,value,weight,variable);
					end = clock();
					result = strcat(result, "_2.res");
					FILE* fp = fopen(result, "w+");
					if (i)
					{
						runtime = (double)(end - start);
						fprintf(fp, "s %d\nv ", i);
						printf("\n\n����ɽ�,����ʱ��Ϊ%.2f ms������ѱ���\n\n", runtime);
						int j = 0;
						for (i = 1; i <= variable; i++)
						{
							if (j < 16)
							{
								if (value[i])
								{
									fprintf(fp, "%d ", i);
									printf("%d ", i);
								}
								else
								{
									fprintf(fp, "%d ", -i);
									printf("%d ", -i);
								}
								j++;
							}
							else
							{
								j = 0;
								if (value[i])
								{
									fprintf(fp, "%d", i);
									printf("%d", i);
								}
								else
								{
									fprintf(fp, "%d", -i);
									printf("%d", -i);
								}
								fprintf(fp, "\n");
								printf("\n");
							}
						}
						printf("\n\n");

					}
					else
					{
						runtime = (double)(end - start);
						printf("\n\n���ⲻ�ɽ�,����ʱ��Ϊ%.2f ms,����ѱ���\n\n", runtime);
					}
					fprintf(fp, "\nt %.2f", runtime);
					fclose(fp);
					break;
				}
				case 3:		//������ȡ�����ļ�
				{
					struct line* now = root;
					struct data* show;
					while (now)
					{
						show = now->head;
						while (show)
						{
							printf("%d ", show->num);
							show = show->next;
						}
						printf("\n");
						now = now->next;
					}
					system("pause");
					break;
				}
				}

			}
			system("pause");
			case 2:
			{
				goto start;		//�����ڷ������˵�
			}
			}
		}
		case 2://��������������
		{
			struct board check[100];
			system("cls");
			printf("\n�������ļ���ַ��");
			scanf("%s", &filename);
			int space = 0;
			space = Read_checkboard(filename,check);
			if (space)
			{
				printf("\n\n��ȡ�ɹ�:\n\n");
				show_check(check,space);
			}
			else
			{
				printf("\n\n��ȡʧ��");
				printf("\n\n");
				exit(-1);
			}
			printf("\n�����뱣��CNF�ļ��ĵ�ַ��");
			scanf("%s", &filename);
			check_to_cnf(check, filename, space);
			int play = 0;
			printf("\n1.���			2.DPLL���				\n\n��ѡ�� ");
			scanf("%d", &play);
			switch (play)
			{
			case 1:
			{
				PlaySuDoKu(check, space);
				struct line* root = Read_cnf(filename, weight, &variable, &linenum);
				DPLL_better(root, value, weight, variable);
				result = strtok(filename, ".");
				result = strcat(result, ".res");
				FILE* fp = fopen(result, "w+");
				if (fp)
				{
					fprintf(fp, "s %d\nv ", i);
					int j = 0;
					for (i = 1; i <= variable; i++)
					{
						if (j < 16)
						{
							if (value[i]) fprintf(fp, "%d ", i);
							else fprintf(fp, "%d ", -i);
							j++;
						}
						else
						{
							j = 0;
							fprintf(fp, "\n");
							printf("\n");
							if (value[i]) fprintf(fp, "%d ", i);
							else fprintf(fp, "%d ", -i);
						}
					}
				}
				fclose(fp);
				fp = fopen(result, "r");
				char read[64];
				int j = 0;
				char s;
				i = 1;
				system("cls");
				show_check(check, space);
				printf("\n\n");
				fgets(read, 64, fp);
				fscanf(fp, "%c", &s);
				fgetchar();
				fscanf(fp, "%d", &j);
				while (i <= space)
				{
					solution[i] = j;
					i++;
					fscanf(fp, "%d", &j);
				}
				for (i = 1, j = 1; i <= space; i++, j++)
				{
					if (solution[i] > 0) printf("1 ");
					else printf("0 ");
					if (j == sqrt(space))
					{
						printf("\n");
						j = 0;
					}
				}
				printf("\n");
				system("pause");
				break;
			}
			case 2:
			{
				struct line* root = Read_cnf(filename, weight, &variable, &linenum);
				DPLL_better(root, value, weight, variable);
				result = strtok(filename, ".");
				result = strcat(result, ".res");
				FILE* fp = fopen(result, "w+");
				if (fp)
				{
					fprintf(fp, "s %d\nv ", i);
					int j = 0;
					for (i = 1; i <= variable; i++)
					{
						if (j < 16)
						{
							if (value[i]) fprintf(fp, "%d ", i);
							else fprintf(fp, "%d ", -i);
							j++;
						}
						else
						{
							j = 0;
							fprintf(fp, "\n");
							printf("\n");
							if (value[i]) fprintf(fp, "%d ", i);
							else fprintf(fp, "%d ", -i);
						}
					}
				}
				fclose(fp);
				fp = fopen(result, "r");
				char read[64];
				int j = 0;
				char s;
				i = 1;
				system("cls");
				show_check(check, space);
				printf("\n\n");
				fgets(read, 64, fp);
				fscanf(fp, "%c", &s);
				fgetchar();
				fscanf(fp, "%d", &j);
				while (i <= space)
				{
					solution[i] = j;
					i++;
					fscanf(fp, "%d", &j);
				}
				for (i = 1, j = 1; i <= space; i++, j++)
				{
					if (solution[i] > 0) printf("1 ");
					else printf("0 ");
					if (j == sqrt(space))
					{
						printf("\n");
						j = 0;
					}
				}
				printf("\n");
				system("pause");
			}
			}
		}
		case 3://�˳�
		{
			exit(1);
		}
		}
	}
}