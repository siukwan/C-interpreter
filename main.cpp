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

void eval();
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

void eval()
{
	int op,*tmp;
	while(1)
	{
		if(op == IMM) {ax = *pc++;}                    //IMM<num> ：把num放入寄存器ax中
		else if(op == LC) {ax = *(char *)ax;}          //将对应地址中的字符载入ax中，要求ax中存放地址
		else if(op == LI) {ax = *(int *)ax;}           //将对应地址中的整数载入ax中，要求ax中存放地址
		else if(op == SC) {ax = *(char *)*sp++ = ax;}  //SC将ax中的数据作为字符存放到地址中，要求栈顶存放地址
		else if(op == SI) {*(int *)*sp++ = ax;}        //SI将ax中的数据作为证书存放到地址中，要求栈顶存放地址
	}
}
