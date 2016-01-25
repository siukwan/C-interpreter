#include<stdlib>

int *text;     //text段
int *old_text; //dump text段
int *stack;    //栈
char*data;     //数据段

//4个虚拟机寄存器
int *pc, *bp, *s, ax, sycle;

//虚拟机指令集，带有参数的指令在前面
enum{LEA, IMM, JMP ,CALL ,JZ, JNZ,ENT,ADJ,LEV,LI ,LC,SI ,SC,PUSH,
		OR,XOR,AND,EQ,NE,LT,GT,LE,GE,SHL,SHR,ADD,SUB,MUL,DIV,MOD,
		OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT};
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

	if(!(stack = malloc(poolsize)))
	{
		printf("could not malloc(%d) for stack segment\n",poolsize);
	}
	//初始化
	memset(text,  0, poolsize);
	memset(data,  0, poolsize);
	memset(stack, 0, poolsize);

	//初始化寄存器
	bp = sp = (int*)((int) stack + poolsize);
	ax = 0;

}
