/*-----------------------------------DPLL处理部分--------------------------------*/
#include "def.h"
//用于寻找单子句
struct line* single(struct line* s)
{
	struct line* temp = s;
	while (temp)
	{
		if (temp->head && !temp->head->next) return temp;
		temp = temp->next;
	}
	return NULL;
}

//用于选取分裂变元
int choose(struct line* s)
{
	int pick = s->head->num;
	return pick;
}

int choose_better(int* weight,int variable)
{
	int i = 1,j=1,k=0, max = weight[1];
	for (; i <= variable; i++)
	{
		k = weight[i];
		if (max < k)
		{
			max = k;
			j = i;
		}
	}
	weight[j] = 0;
	return j;
}

//将分裂变元加入到数据中以便进行化简
struct line* add_pick(struct line* s, int pick)
{
	struct line* front = (struct line*)malloc(sizeof(struct line));
	front->head = (struct data*)malloc(sizeof(struct data));
	front->head->next = NULL;
	front->head->num = pick;
	front->next = s;
	return front;
}

//用于判断是否存在空子句
int empty(struct line* s)
{
	struct line* temp = s;
	while (temp)
	{
		if (!temp->head) return 1;
		temp = temp->next;
	}
	return 0;
}

//下列两个函数用于读取后数据复制形成副本
struct line* copy_data(struct line* s)
{
	struct data* temp = s->head, * current;
	struct line* copy_single = (struct line*)malloc(sizeof(struct line*));
	copy_single->head = NULL;
	copy_single->next = NULL;
	if (temp)
	{
		current = (struct data*)malloc(sizeof(struct data));
		current->num = temp->num;
		current->next = NULL;
		copy_single->head = current;
		temp = temp->next;
		while (temp)
		{
			current->next = (struct data*)malloc(sizeof(struct data));
			current->next->num = temp->num;
			current->next->next = NULL;
			current = current->next;
			temp = temp->next;
		}
	}
	return copy_single;
}

struct line* copy_line(struct line* s)
{
	struct line* s_copy, * temp, * current = s->next;
	s_copy = (struct line*)malloc(sizeof(struct line*));
	s_copy = copy_data(s);
	temp = s_copy;
	while (current)
	{
		temp->next = (struct line*)malloc(sizeof(struct line));
		temp->next = copy_data(current);
		current = current->next;
		temp = temp->next;
	}
	return s_copy;
}

//记录真值表，若最终求出解则以此输出答案
int change_value(int* truth, struct line* pick)
{
	int judge = pick->head->num;
	if (judge > 0)
	{
		truth[judge] = 1;
	}
	else
	{
		truth[-judge] = 0;
	}
	return 1;
}

int change_value_better(int* truth, struct line* pick,int* weight)
{
	int judge = pick->head->num;
	if (judge > 0)
	{
		truth[judge] = 1;
		weight[judge] = 0;
	}
	else
	{
		truth[-judge] = 0;
		weight[-judge] = 0;
	}
	return 1;
}

//删除一整个子句，用于变元取真时的化简
struct line* delete_line(struct line* s)
{
	struct data* q = s->head;
	struct line* p = (struct line*)malloc(sizeof(struct line));
	p->next = s;
	while (q)
	{
		s->head = s->head->next;
		free(q);
		q = s->head;
	}
	s = s->next;
	free(p);
	return s;
}

//仅删除与变元相反项
struct line* delete_data(struct line* s, int pick)
{
	struct data* front, * last;
	if (s->head) last = s->head;
	else return s;
	if (s->head->num == pick) return NULL;
	if (s->head->num == -pick)
	{
		s->head = s->head->next;
		free(last);
		return s;
	}
	while (last)
	{
		if (last->next && last->next->num == pick) return NULL;
		if (last->next && last->next->num == -pick)
		{
			front = last->next;
			last->next = last->next->next;
			free(front);
			return s;
		}
		last = last->next;
	}
	return s;
}

//交替化简cnf
struct line* simplify(struct line* s, struct line* pick)
{
	struct line* head = (struct line*)malloc(sizeof(struct line*));
	head->head = NULL;
	head->next = s;
	struct line* front = head;
	int var = pick->head->num;
	struct line* current = head->next;
	while (current)
	{
		current = delete_data(current, var); //删除相反变元
		if (!current)			//发现相同值变元，删除子句
		{
			current = delete_line(front->next);
			front->next = current;
			continue;
		}
		if (current == NULL) break;
		front = current;
		current = current->next;
	}
	return head->next;
}

//DPLL算法过程
int DPLL(struct line* s, int* truth)
{
	struct line* single_line = NULL;
	single_line = single(s);

	while (single_line)
	{
		change_value(truth, single_line);		//记录真值
		s = simplify(s, single_line);

		if (!s) return SOLVED;		//子集全为空，问题可解
		else if (empty(s))	return UNSOLVED;	//存在空子集，问题不可解
		single_line = single(s);
	}

	//分裂选择
	int pick = choose(s);
	if (DPLL(add_pick(copy_line(s), pick), truth))	return SOLVED;
	return DPLL(add_pick(copy_line(s), -pick), truth);
}

int DPLL_better(struct line* s, int* truth, int* weight,int variable)
{
	struct line* single_line = NULL;
	single_line = single(s);

	while (single_line)
	{
		change_value_better(truth, single_line,weight);		//记录真值
		s = simplify(s, single_line);

		if (!s)	return SOLVED;		//子集全为空，问题可解
		else if (empty(s))	return UNSOLVED;		//存在空子集，问题不可解
		single_line = single(s);
	}

	//分裂选择
	int pick = choose_better(weight,variable);
	if (DPLL(add_pick(copy_line(s), pick), truth)) return SOLVED;
	return DPLL(add_pick(copy_line(s), -pick), truth);
}


