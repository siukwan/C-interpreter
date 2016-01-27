#include<stdlib>

int *text;     //text段
int *old_text; //dump text段
int *stack;    //栈
char*data;     //数据段

//4个虚拟机寄存器
int *pc,   //程序计数器
	 *bp,   //基址指针寄存器
    *sp,   //指针寄存器
	 ax,    //通用寄存器
	 cycle;

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
		if(op == IMM)      {ax = *pc++;}                //IMM<num> ：把num放入寄存器ax中
		else if(op == LC)  {ax = *(char *)ax;}          //将对应地址中的字符载入ax中，要求ax中存放地址
		else if(op == LI)  {ax = *(int *)ax;}           //将对应地址中的整数载入ax中，要求ax中存放地址
		else if(op == SC)  {ax = *(char *)*sp++ = ax;}  //SC将ax中的数据作为字符存放到地址中，要求栈顶存放地址
		else if(op == SI)  {*(int *)*sp++ = ax;}        //SI将ax中的数据作为证书存放到地址中，要求栈顶存放地址，栈的地址是从高地址扩展到低地址，所以sp++回归高地址是出栈的意思
		else if(op== PUSH) {*--sp = ax;}                //把ax的值放入栈中
		else if(op == JMP) {pc = (int*)*pc;}            //JMP<addr>，无条件地将当前的PC寄存器设置为指定的<addr>
		else if(op == JZ)  {pc = ax?pc+1:(int*)*pc;}    //ax为0时进行跳转
		else if(op == JNZ) {pc = ax?(int*)*pc:pc+1;}    //ax不为0时跳转
		else if(op == CALL)
			{*--sp = (int)(pc+1); pc = (int *)*pc;}      //子函数调用
		else if(op == ENT) {*--sp = (int)bp; bp = sp; sp = sp - *pc++;}//ENT <size>指的时enter,用于实现make new call frame功能，即保存当前的栈指针，同时在栈上保留一定的空间，用以存放局部变量
		else if(op == ADJ) {sp = sp + *pc++;}           //ADJ<size>用于实现remove arguments from frame。在将调用子函数时雅如栈中的数据清除，本质上时因为我们的ADD指令功能有限。
	}
}
