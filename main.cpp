/*-----------------------------------展示部分--------------------------------*/

#include "def.h"

int main()
{

	char filename[32];
	char* result;
	int choice = 1, sat = 0, sat_choice = 0;
	int i = 0;		//辅助用
	int weight[4000] = { 0 };
	int order[4000] = { 1 };
	int variable, linenum;
	int value[4000] = { 0 }; //真值表
	int solution[256] = { 0 };
	clock_t start, end;
	double runtime;
	while (choice)
	{
	start:
		system("cls");
		printf("\n1.SAT			2.数独				3.结束\n\n请选择： ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1://SAT求解CNF
		{
			system("cls");
			printf("\n1.读取cnf文件			2.返回\n\n请选择： ");
			scanf("%d", &sat);
			switch (sat)
			{
			case 1:
			{
				system("cls");
				printf("\n请输入文件地址：");
				scanf("%s", &filename);
				struct line* root = Read_cnf(filename,weight,&variable, &linenum);
				result = strtok(filename, ".");
				if (root)
				{
					printf("\n读取成功		变元数：%d		句子数：%d", variable, linenum);
				}
				else
				{
					printf("\n读取失败\n\n");
					system("pause");
					goto start;
				}
				printf("\n\n1.优化前			2.优化后		3.遍历文件数据\n\n请选择： ");
				scanf("%d", &sat_choice);			//选择优化与否的算法
				switch (sat_choice)
				{
				case 1:		//优化前
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
						printf("\n\n问题可解,运行时间为%.2f ms，结果已保存\n\n", runtime);
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
						printf("\n\n问题不可解,运行时间为%.2f ms,结果已保存\n\n", runtime);
					}
					fprintf(fp, "\nt %.2f", runtime);
					fclose(fp);
					break;
				}
				case 2:		//优化后
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
						printf("\n\n问题可解,运行时间为%.2f ms，结果已保存\n\n", runtime);
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
						printf("\n\n问题不可解,运行时间为%.2f ms,结果已保存\n\n", runtime);
					}
					fprintf(fp, "\nt %.2f", runtime);
					fclose(fp);
					break;
				}
				case 3:		//遍历读取到的文件
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
				goto start;		//仅用于返回主菜单
			}
			}
		}
		case 2://二进制数独处理
		{
			struct board check[100];
			system("cls");
			printf("\n请输入文件地址：");
			scanf("%s", &filename);
			int space = 0;
			space = Read_checkboard(filename,check);
			if (space)
			{
				printf("\n\n读取成功:\n\n");
				show_check(check,space);
			}
			else
			{
				printf("\n\n读取失败");
				printf("\n\n");
				exit(-1);
			}
			printf("\n请输入保存CNF文件的地址：");
			scanf("%s", &filename);
			check_to_cnf(check, filename, space);
			int play = 0;
			printf("\n1.求解			2.DPLL求解				\n\n请选择： ");
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
		case 3://退出
		{
			exit(1);
		}
		}
	}
}