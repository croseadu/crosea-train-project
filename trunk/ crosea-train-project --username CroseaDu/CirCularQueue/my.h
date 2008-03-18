
typedef struct
{
	int *base;
	int front;
	int end;
	int length;
}CIRCULARQUEUE,*LPCIRCULARQUEUE;

int	initCircularQueue();
int destroyCircularQueue();
int getLengthOfCircularQueue();
int insertCircularQueue();
int	deleteCircularQueue();


 