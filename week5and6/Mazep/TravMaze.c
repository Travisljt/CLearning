#include "MazeProblem.h"
//�����㷨
void MyPath(char maze[][MAXSIZE],int moved[][MAXSIZE] ){
	int i, j, right, find, k;
	int xi=0, yi = 0;
	int top = 0;
	InterSection[top].i = xi;
	InterSection[top].j = yi;
	InterSection[top].right = -1;
	moved[xi][yi] = 1;//��ʾ�Ѿ�������
	while (top > -1) {
		i = InterSection[top].i;
		j = InterSection[top].j;
		right = InterSection[top].right+1;
		if (i == MAXSIZE-1 && j == MAXSIZE-1) {
			printf("·�����£�\n");
			for (k = 0; k <= top; k++) {
				printf("(%d,%d)\n", InterSection[k].i,InterSection[k].j);
			}
			return;
		}
		find = 0;
		while (right < 4 && find == 0) {
			
			switch (right)
			{
			case 0:i = InterSection[top].i - 1; j = InterSection[top].j; break;
			case 1:i = InterSection[top].i; j = InterSection[top].j+1; break;
			case 2:i = InterSection[top].i + 1; j = InterSection[top].j; break;
			case 3:i = InterSection[top].i; j = InterSection[top].j-1; break;
			}
			if ((maze[i][j] == ' ')&&!moved[i][j])find = 1;right++;
		}
		if (find == 1) {
			//InterSection[top].i = i;
			top++;
			InterSection[top].i = i;
			InterSection[top].j = j;
			InterSection[top].right = -1;
			moved[i][j] = 1;
		}
		else
		{
			//moved[InterSection[top].i][InterSection[top].j] = 0;
			top--;
		}
	}
	printf("��·����");
}

