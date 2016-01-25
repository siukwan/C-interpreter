#include<stdlib>

int *text;     //text段
int *old_text; //dump text段
int *stack;    //栈
char*data;     //数据段

int main()
{

	//为虚拟机分配内存
	if(!(text = old_text = malloc(poolsize)))
	{
		printf("could not malloc(%d) for text segment\n",poolsize);
		return -1;
	}

	if(!(data = malloc(poolsize)))
	{
		printf("could not malloc(%d) for data segment\n",poolsize);
		return -1;
	}

}
