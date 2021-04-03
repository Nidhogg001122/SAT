#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define SOLVED 1
#define UNSOLVED 0

typedef int status;

struct data
{
	int num;
	struct data* next;
};
//���ӽṹ

struct line
{
	struct line* next;
	struct data* head;
};
//cnf�ļ��ṹ

struct board {
	int empty;
	int num;
};


struct data* Creatdata();	//�½�data
struct line* Creatline();	//�½�line
struct line* Read_cnf(char* filename, int* weight, int* variable,int* linenum);		//��ȡcnf�ļ�

struct line* single(struct line* s);	//����Ѱ�ҵ��Ӿ�
status choose(struct line* s);		//����ѡȡ���ѱ�Ԫ
status choose_better(int* weight,int variable);
struct line* add_pick(struct line* s, int pick);	//�����ѱ�Ԫ���뵽�������Ա���л���
status empty(struct line* s);		//�����ж��Ƿ���ڿ��Ӿ�
struct line* copy_data(struct line* s);		//���������������ڶ�ȡ�����ݸ����γɸ���
struct line* copy_line(struct line* s);
int change_value(int* truth, struct line* pick);	//��¼��ֵ����������������Դ������
int change_value_better(int* truth, struct line* pick, int* weight);
struct line* delete_line(struct line* s);		//ɾ��һ�����Ӿ䣬���ڱ�Ԫȡ��ʱ�Ļ���
struct line* delete_data(struct line* s, int pick);		//��ɾ�����Ԫ�෴��
struct line* simplify(struct line* s, struct line* pick);		//���滯��cnf
status DPLL(struct line* s, int* truth);		//DPLL�㷨����
status DPLL_better(struct line* s, int* truth,int* weight,int variable);

status Read_checkboard(char* filename, struct board* check);		//��ȡ����
void show_check(struct board* check,int board_num);		//չʾ����
status check_to_cnf(struct board* check, char* filename, int board_num);	//����ת��ΪCNF
void PlaySuDoKu(struct board* qipan, int board_num);		//����

