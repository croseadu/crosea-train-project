
#define INIT_BUFFER_SIZE 20
#define INCRE_BUFFER_SIZE 10

enum TOKEN_TYPE
{
	OPERATOR,
	OPEREND,
};

typedef struct
{
	enum TOKEN_TYPE tokenType;
	union
	{
		char operator;
		int  operand;		
	}tokenValue;
}TOKEN;

STATUS getNextNumber(const char *, int *, int *);
STATUS getNextOperOrOpnd(const char *, int *, TOKEN *);
