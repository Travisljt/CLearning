#include "interpreter.h"

void parseFile(char *path, Program *p)
{
	FILE *file = fopen(path, "r");
	char str[MAXTOKENSIZE * 10];
	int i = 0;
	if (file == NULL)
	{
		printf("Can not open this file!\n");
	}
	else
	{
		while (fscanf(file, "%s", p->wds[i]) == 1 && i < MAXNUMTOKENS)
		{
			i++;
			if (strsame(p->wds[i - 1], "#"))
			{
				memset(str, '\0', sizeof(str));
				fgets(str, MAXTOKENSIZE * 10, file);
				i--;
				memset(p->wds[i], '\0', sizeof(p->wds[i]));
			}
		}
	}
	fclose(file);

	assert(i < MAXNUMTOKENS);
}

void Prog(Program *p)
{
	if (!strsame(p->wds[p->cw], "BEGIN") || !strsame(p->wds[p->cw + 1], "{"))
	{
		ERROR("No BEGIN statement ?");
	}
	p->cw = p->cw + 2;
	Insterclist(p);
}

void Insterclist(Program *p)
{
	if (strsame(p->wds[p->cw], "}"))
	{
		return;
	}
	Instrc(p);
	p->cw = p->cw + 1;
	Insterclist(p);
}

void Instrc(Program *p)
{
	if (isPrint(p))
	{
		return;
	}
	if (isSet(p))
	{
		return;
	}
	if (isCreate(p))
	{
		return;
	}

	if (isLoop(p))
	{
		Loop(p);
	}
	else
	{
		ERROR("THIS IS A WRONG GRAMMAR");
	}
}

bool isPrint(Program *p)
{
	if (!strsame(p->wds[p->cw], "PRINT"))
	{
		return false;
	}

	p->cw = p->cw + 1;

	if (isVarname(p))
	{
		printVar(vars[getVarname(p) - 'A']);
	}
	else if (isString(p))
	{
		printSring(p);
	}
	else
	{
		ERROR("THIS IS A WRONG GRAMMAR");
	}

	return true;
}

bool isSet(Program *p)
{
	if (!strsame(p->wds[p->cw], "SET"))
	{
		return false;
	}

	p->cw = p->cw + 1;
	if (isVarname(p) && strsame(p->wds[p->cw + 1], ":="))
	{
		int index = getVarname(p) - 'A';
		p->cw = p->cw + 2;
		stack *s = stack_init();
		Polishlist(p, s, index);
		stack_free(s);
		return true;
	}
	else
	{
		ERROR("THIS IS A WRONG GRAMMAR");
	}

	return false;
}

bool isCreate(Program *p)
{
	int row = 0;
	int column = 0;
	int index = 0;
	if (strsame(p->wds[p->cw], "ONES"))
	{
		p->cw = p->cw + 1;
		assert(isInteger(p));
		row = getInteger(p);
		p->cw = p->cw + 1;
		assert(isInteger(p));
		column = getInteger(p);
		p->cw = p->cw + 1;
		assert(isVarname(p));
		index = getVarname(p) - 'A';
		vars[index].row = row;
		vars[index].column = column;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				vars[index].value[i][j] = 1;
			}
		}

		vars[index].flag = 1;

		return true;
	}

	if (strsame(p->wds[p->cw], "READ"))
	{
		p->cw = p->cw + 1;
		assert(isString(p));

		char path[MAXTOKENSIZE];
		getString(p, path);

		FILE *file = fopen(path, "r");
		char str[MAXROWSIZE * MAXCOLUMNSIZE + 2][MAXLENS];
		int pro = 0;
		if (file == NULL)
		{
			printf("Can not open this file: %s!\n", p->wds[p->cw]);
		}
		else
		{
			memset(str, '\0', sizeof(str));
			while (fscanf(file, "%s", str[pro++]) > 0 && pro < MAXROWSIZE * MAXCOLUMNSIZE + 2)
				;
		}
		fclose(file);

		assert(pro < MAXROWSIZE * MAXCOLUMNSIZE + 2);

		p->cw = p->cw + 1;
		assert(isVarname(p));
		index = getVarname(p) - 'A';
		sscanf(str[0], FORMATSTR, &vars[index].row);
		sscanf(str[1], FORMATSTR, &vars[index].column);

		pro = 2;

		for (int i = 0; i < vars[index].row; i++)
		{
			for (int j = 0; j < vars[index].column; j++)
			{
				sscanf(str[pro++], FORMATSTR, &vars[index].value[i][j]);
			}
		}
		vars[index].flag = 1;

		return true;
	}

	return false;
}

bool isLoop(Program *p)
{
	if (!strsame(p->wds[p->cw], "LOOP"))
	{
		return false;
	}

	return true;
}

void Loop(Program *p)
{
	p->cw = p->cw + 1;
	assert(isVarname(p));
	int index = getVarname(p) - 'A';
	vars[index].value[0][0] = 1;
	vars[index].row = 1;
	vars[index].column = 1;
	vars[index].flag = 1;

	p->cw = p->cw + 1;
	assert(isInteger(p));
	int endValue = getInteger(p);

	p->cw = p->cw + 1;
	assert(strsame(p->wds[p->cw], "{"));

	p->cw = p->cw + 1;
	int loopIndex = p->cw;

	while (vars[index].value[0][0] <= endValue)
	{
		p->cw = loopIndex;
		Insterclist(p);
		vars[index].value[0][0] += 1;
	}
}

bool isVarname(Program *p)
{
	char ch;
	if (sscanf(p->wds[p->cw], "$%[A-Z]", &ch) == 1 && strlen(p->wds[p->cw]) == 2)
	{
		return true;
	}

	return false;
}

char getVarname(Program *p)
{
	char name = '\0';
	assert(strlen(p->wds[p->cw]) == 2);
	name = p->wds[p->cw][1];

	return name;
}

void printVar(Variable var)
{
	for (int i = 0; i < var.row; i++)
	{
		for (int j = 0; j < var.column; j++)
		{
			printf("%d ", var.value[i][j]);
		}
		printf("\n");
	}
}

bool isString(Program *p)
{
	if (p->wds[p->cw][0] != '"' || p->wds[p->cw][strlen(p->wds[p->cw]) - 1] != '"')
	{
		return false;
	}

	return true;
}

void getString(Program *p, char *string)
{
	int endIndex = MAXTOKENSIZE - 1;
	bool flag = true;
	int i = 0;
	for (i = MAXTOKENSIZE - 1; i > 0 && flag; i--)
	{
		if (p->wds[p->cw][i] == '"')
		{
			endIndex = i;
			flag = false;
		}
	}

	if (i == 0)
	{
		ERROR("THERE IS A GRAMMER ERROR");
		return;
	}

	for (i = 1; i < endIndex; i++)
	{
		string[i - 1] = p->wds[p->cw][i];
	}
	string[i - 1] = '\0';
}

void printSring(Program *p)
{
	int endIndex = MAXTOKENSIZE - 1;
	bool flag = true;
	int i = 0;
	for (i = MAXTOKENSIZE - 1; i > 0 && flag; i--)
	{
		if (p->wds[p->cw][i] == '"')
		{
			endIndex = i;
			flag = false;
		}
	}

	if (i == 0)
	{
		ERROR("THERE IS A ERROR IN GRAMMER");
		return;
	}

	for (i = 1; i < endIndex; i++)
	{
		printf("%c", p->wds[p->cw][i]);
	}
	printf("\n");
}

void Polishlist(Program *p, stack *s, int index)
{
	if (strsame(p->wds[p->cw], ";"))
	{
		Variable *v = calloc(1, sizeof(Variable));
		assert(stack_pop(s, v));
		//update data
		vars[index].row = v->row;
		vars[index].column = v->column;

		for (int i = 0; i < vars[index].row; i++)
		{
			for (int j = 0; j < vars[index].column; j++)
			{
				vars[index].value[i][j] = v->value[i][j];
			}
		}

		vars[index].flag = 1;
		return;
	}
	Polish(p, s);
	p->cw = p->cw + 1;
	Polishlist(p, s, index);
}

void Polish(Program *p, stack *s)
{

	if (Pushdown(p, s))
	{
		return;
	}

	if (UnaryOp(p, s))
	{
		return;
	}

	if (BinaryOp(p, s))
	{
		return;
	}

	ERROR("THERE IS A WRONG GRAMMAR");
}

bool UnaryOp(Program *p, stack *s)
{
	if (strsame(p->wds[p->cw], "U-NOT"))
	{
		UnOperator(s, '!');
		return true;
	}

	if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
	{
		UnOperator(s, '@');
		return true;
	}

	return false;
}

bool BinaryOp(Program *p, stack *s)
{
	if (strsame(p->wds[p->cw], "B-AND"))
	{
		BinOperator(s, '&');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-OR"))
	{
		BinOperator(s, '|');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-GREATER"))
	{
		BinOperator(s, '>');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-LESS"))
	{
		BinOperator(s, '<');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-ADD"))
	{
		BinOperator(s, '+');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-TIMES"))
	{
		BinOperator(s, '*');
		return true;
	}

	if (strsame(p->wds[p->cw], "B-EQUALS"))
	{
		BinOperator(s, '=');
		return true;
	}

	return false;
}

bool Pushdown(Program *p, stack *s)
{
	if (isVarname(p))
	{
		int index = getVarname(p) - 'A';
		if (vars[index].flag == 1) //we can find it from vars array
		{
			stack_push(s, vars[index]);
		}
		else
		{
			ERROR("THERE IS AN ERROR: THE VARIABLE IS UNDEFINED!");
		}
		return true;
	}

	if (isInteger(p))
	{
		int var_value;
		sscanf(p->wds[p->cw], FORMATSTR, &var_value);
		Variable v;
		v.value[0][0] = var_value;
		v.row = 1;
		v.column = 1;
		v.flag = 0;
		stack_push(s, v);

		return true;
	}

	return false;
}

bool isInteger(Program *p)
{
	int d;
	if (sscanf(p->wds[p->cw], FORMATSTR, &d) == 1)
	{
		if (d >= 0)
		{
			return true;
		}
		else
		{
			ERROR("THIS IS A NEGATIVE INTEGER!");
		}
	}

	return false;
}

int getInteger(Program *p)
{
	int value = 0;
	sscanf(p->wds[p->cw], FORMATSTR, &value);

	return value;
}

void BinOperator(stack *s, char op)
{
	Variable *v2 = (Variable*)calloc(1, sizeof(Variable));
	Variable *v1 = (Variable*)calloc(1, sizeof(Variable));
	Variable result;
	assert(stack_pop(s, v2));
	assert(stack_pop(s, v1));

	if ((v1->row == 1 && v1->column == 1) && (v2->row == 1 && v2->column == 1))
	{

		if (op == '&')
		{
			result.value[0][0] = v1->value[0][0] & v2->value[0][0];
		}
		else if (op == '|')
		{
			result.value[0][0] = v1->value[0][0] | v2->value[0][0];
		}
		else if (op == '>')
		{
			result.value[0][0] = v1->value[0][0] > v2->value[0][0] ? 1 : 0;
		}
		else if (op == '<')
		{
			result.value[0][0] = v1->value[0][0] < v2->value[0][0] ? 1 : 0;
		}
		else if (op == '+')
		{
			result.value[0][0] = v1->value[0][0] + v2->value[0][0];
		}
		else if (op == '*')
		{
			result.value[0][0] = v1->value[0][0] * v2->value[0][0];
		}
		else if (op == '=')
		{
			result.value[0][0] = v1->value[0][0] == v2->value[0][0] ? 1 : 0;
		}
		else
		{
			ERROR("THIS IS AN OPERATOR ERROR!");
			return;
		}

		result.row = 1;
		result.column = 1;
	}
	else if ((v1->row == 1 && v1->column == 1) && (v2->row > 1 || v2->column > 1))
	{
		if (op == '&')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] & v2->value[i][j];
				}
			}
		}
		else if (op == '|')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] | v2->value[i][j];
				}
			}
		}
		else if (op == '>')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] > v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else if (op == '<')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] < v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else if (op == '+')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] + v2->value[i][j];
				}
			}
		}
		else if (op == '*')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] * v2->value[i][j];
				}
			}
		}
		else if (op == '=')
		{
			for (int i = 0; i < v2->row; i++)
			{
				for (int j = 0; j < v2->column; j++)
				{
					result.value[i][j] = v1->value[0][0] == v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else
		{
			ERROR("THIS IS AN OPERATOR ERROR!");
			return;
		}

		result.row = v2->row;
		result.column = v2->column;
	}
	else if ((v1->row > 1 || v1->column > 1) && (v2->row == 1 || v2->column == 1))
	{
		if (op == '&')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] & v2->value[0][0];
				}
			}
		}
		else if (op == '|')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] | v2->value[0][0];
				}
			}
		}
		else if (op == '>')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] > v2->value[0][0] ? 1 : 0;
				}
			}
		}
		else if (op == '<')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] < v2->value[0][0] ? 1 : 0;
				}
			}
		}
		else if (op == '+')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] + v2->value[0][0];
				}
			}
		}
		else if (op == '*')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] * v2->value[0][0];
				}
			}
		}
		else if (op == '=')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] == v2->value[0][0] ? 1 : 0;
				}
			}
		}
		else
		{
			ERROR("THIS IS AN OPERATOR ERROR!");
			return;
		}

		result.row = v1->row;
		result.column = v1->column;
	}
	else if ((v1->row > 1 || v1->column > 1) && (v2->row > 1 || v2->column > 1) && (v1->row == v2->row && v1->column == v2->column))
	{
		if (op == '&')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] & v2->value[i][j];
				}
			}
		}
		else if (op == '|')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] | v2->value[i][j];
				}
			}
		}
		else if (op == '>')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] > v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else if (op == '<')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] < v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else if (op == '+')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] + v2->value[i][j];
				}
			}
		}
		else if (op == '*')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] * v2->value[i][j];
				}
			}
		}
		else if (op == '=')
		{
			for (int i = 0; i < v1->row; i++)
			{
				for (int j = 0; j < v1->column; j++)
				{
					result.value[i][j] = v1->value[i][j] == v2->value[i][j] ? 1 : 0;
				}
			}
		}
		else
		{
			ERROR("THIS IS AN OPERATOR ERROR!");
			return;
		}

		result.row = v1->row;
		result.column = v1->column;
	}
	else
	{
		ERROR("THERE ARE SOME ERRORS: WRONG ROWS OR COLUMNS!");
		free(v1);
		free(v2);
		return;
	}

	result.flag = 0;
	stack_push(s, result);

	free(v1);
	free(v2);
}

void UnOperator(stack *s, char op)
{

	Variable *v = (Variable*)calloc(1, sizeof(Variable));
	Variable result;
	assert(stack_pop(s, v));

	for (int i = 0; i < v->row; i++)
	{
		for (int j = 0; j < v->column; j++)
		{
			if (v->value[i][j] != 0 && v->value[i][j] != 1)
			{
				ERROR("THIS IS NOT A BINARY ARRAY!");
				free(v);
				return;
			}
		}
	}

	for (int i = 0; i < v->row; i++)
	{
		for (int j = 0; j < v->column; j++)
		{
			result.value[i][j] = 0;
		}
	}

	if (op == '!')
	{
		for (int i = 0; i < v->row; i++)
		{
			for (int j = 0; j < v->column; j++)
			{
				result.value[i][j] = !v->value[i][j];
			}
		}
	}
	else if (op == '@')
	{
		for (int i = 0; i < v->row; i++)
		{
			for (int j = 0; j < v->column; j++)
			{
				if (i - 1 >= 0)
				{
					result.value[i][j] += v->value[i - 1][j];
					if (j - 1 > 0)
					{
						result.value[i][j] += v->value[i - 1][j - 1];
					}

					if (j + 1 < v->column)
					{
						result.value[i][j] += v->value[i - 1][j + 1];
					}
				}

				if (i + 1 < v->column)
				{
					result.value[i][j] = v->value[i + 1][j];
					if (j - 1 > 0)
					{
						result.value[i][j] += v->value[i + 1][j - 1];
					}

					if (j + 1 < v->column)
					{
						result.value[i][j] += v->value[i + 1][j + 1];
					}
				}

				if (j - 1 > 0)
				{
					result.value[i][j] += v->value[i][j - 1];
				}

				if (j + 1 < v->column)
				{
					result.value[i][j] += v->value[i][j + 1];
				}
			}
		}
	}
	else
	{
		ERROR("THIS IS AN ERROR OPERATOR!");
		free(v);
		return;
	}

	result.row = v->row;
	result.column = v->column;
	result.flag = 0;
	stack_push(s, result);

	free(v);
}
