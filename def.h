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
//句子结构

struct line
{
	struct line* next;
	struct data* head;
};
//cnf文件结构

struct board {
	int empty;
	int num;
};


struct data* Creatdata();	//新建data
struct line* Creatline();	//新建line
struct line* Read_cnf(char* filename, int* weight, int* variable,int* linenum);		//读取cnf文件

struct line* single(struct line* s);	//用于寻找单子句
status choose(struct line* s);		//用于选取分裂变元
status choose_better(int* weight,int variable);
struct line* add_pick(struct line* s, int pick);	//将分裂变元加入到数据中以便进行化简
status empty(struct line* s);		//用于判断是否存在空子句
struct line* copy_data(struct line* s);		//下列两个函数用于读取后数据复制形成副本
struct line* copy_line(struct line* s);
int change_value(int* truth, struct line* pick);	//记录真值表，若最终求出解则以此输出答案
int change_value_better(int* truth, struct line* pick, int* weight);
struct line* delete_line(struct line* s);		//删除一整个子句，用于变元取真时的化简
struct line* delete_data(struct line* s, int pick);		//仅删除与变元相反项
struct line* simplify(struct line* s, struct line* pick);		//交替化简cnf
status DPLL(struct line* s, int* truth);		//DPLL算法过程
status DPLL_better(struct line* s, int* truth,int* weight,int variable);

status Read_checkboard(char* filename, struct board* check);		//读取棋盘
void show_check(struct board* check,int board_num);		//展示棋盘
status check_to_cnf(struct board* check, char* filename, int board_num);	//棋盘转化为CNF
void PlaySuDoKu(struct board* qipan, int board_num);		//交互

