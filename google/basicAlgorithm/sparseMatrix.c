#include "../include/common.h"

typedef struct
{
  int i;
  int j;
  int value;
}TRIPLE;


#define MAX_ELEMENT 50
#define MAX_RC 30
#define MAX_CO 30

typedef struct
{
  TRIPLE data[MAX_ELEMENT];
  int rops[MAX_RC+1];
  int mu, nu, tu;
}SPARSE_MATRIX;

void reverseMatrixV1(SPARSE_MATRIX *dstMatrix, SPARSE_MATRIX *srcMatrix);
void reverseMatrixV2(SPARSE_MATRIX *dstMatrix, SPARSE_MATRIX *srcMatrix);
void multiplyMatrix (SPARSE_MATRIX **dstMatrix, 
		     SPARSE_MATRIX *firstMatrix, 
		     SPARSE_MATRIX *secondMatrix);
STATUS getMatrix(SPARSE_MATRIX **dstMatrix, 
		 FILE *fp, 
		 unsigned int row, 
		 unsigned int column);

void getNext(FILE *fp, char *pC)
{
  while (!feof(fp))
      {
	*pC = fgetc(fp); 
	if (*pC != ' ' && *pC != '\t' && *pC != '\n' && *pC != '\r')
	  break;
      }
}

#define VALID_NODE_DATA(c) (c != EOF && c != ',' && c != ')' && c != '(')
#define VALID_EDGE_START(c) (c == '(')
#define VALID_EDGE_SEPARATOR(c) (c == ',')
#define VALID_EDGE_END(c) (c == ')')

int main()
{
  FILE *fp;
  char c;
  SPARSE_MATRIX *pMatrix = NULL, *dMatrix, *firstMatrix, *secondMatrix;
  int row, column, value;
  int curIndex, i;
  STATUS status;


  /****************** Start Reverse Matrix *********************/

  fp = fopen("input/inputDataForSparseMatrix.txt", "r");
  if (NULL == fp)
    {
      printf("Cannot Open File:inputDataForSpareMatrix.txt\n");
      exit(-1);

    }

  status = getMatrix(&pMatrix, fp, MAX_RC, MAX_CO);
  if (status == ERROR)
    {
      fclose(fp);
      exit(-1);
    }

  printf("\n Triple:\n");
  for (i = 0; i < pMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   pMatrix->data[i].i,
	   pMatrix->data[i].j,
	   pMatrix->data[i].value);
  putchar('\n');

  dMatrix = (SPARSE_MATRIX *)malloc(sizeof(SPARSE_MATRIX));
  if (NULL == dMatrix)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }
  
  reverseMatrixV1(dMatrix, pMatrix);
  //reverseMatrixV2(dMatrix, pMatrix);
  printf("\n New Triple After ReverseV1:\n");
  for (i = 0; i < dMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   dMatrix->data[i].i,
	   dMatrix->data[i].j,
	   dMatrix->data[i].value);
  putchar('\n');

  memset(dMatrix, 0, sizeof(SPARSE_MATRIX));
  reverseMatrixV2(dMatrix, pMatrix);
  printf("\n New Triple After ReverseV2:\n");
  for (i = 0; i < dMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   dMatrix->data[i].i,
	   dMatrix->data[i].j,
	   dMatrix->data[i].value);
  putchar('\n');

  fclose(fp);
  free(pMatrix);
  free(dMatrix);
  /********************** End Of Reverse Matrix *************************/

  /********************** Start Multiply Matrix *************************/
   fp = fopen("input/matrix1.txt", "r");
  if (NULL == fp)
    {
      printf("Cannot Open File:matrix1.txt\n");
      exit(-1);

    }
  status = getMatrix(&firstMatrix, fp, 5, 3);
  if (status == ERROR)
    {
      printf("Create First Matrix Failed\n");
      exit(-1);
    }
  fclose(fp);

  fp = fopen("input/matrix2.txt", "r");
  if (NULL == fp)
    {
      printf("Cannot Open File:matrix2.txt\n");
      exit(-1);

    }
  status = getMatrix(&secondMatrix, fp, 3, 4);
  if (status == ERROR)
    {
      printf("Create Second Matrix Failed\n");
      exit(-1);
    }
  fclose(fp);
  printf("\nFirst:");
  for (i = 0; i < firstMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   firstMatrix->data[i].i,
	   firstMatrix->data[i].j,
	   firstMatrix->data[i].value);
  printf("\nSecond:");
  for (i = 0; i < secondMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   secondMatrix->data[i].i,
	   secondMatrix->data[i].j,
	   secondMatrix->data[i].value);
  putchar('\n');
  
  multiplyMatrix(&dMatrix, firstMatrix, secondMatrix);
  if (dMatrix == NULL)
    exit(OVERFLOW);
  for (i = 0; i < dMatrix->tu; i++)
    printf("[(%d, %d) %d] ", 
	   dMatrix->data[i].i,
	   dMatrix->data[i].j,
	   dMatrix->data[i].value);
  putchar('\n');
  //verifyResult(dMatrix, firstMatrix, secondMatrix);

  free(firstMatrix);
  free(secondMatrix);
  free(dMatrix);
  return 0;
}


void reverseMatrixV1(SPARSE_MATRIX *dstMatrix, SPARSE_MATRIX *srcMatrix)
{
  int i,j;
  TRIPLE *pData;
  int curIndex;

  dstMatrix->mu = srcMatrix->nu;
  dstMatrix->nu = srcMatrix->mu;
  dstMatrix->tu = srcMatrix->tu;

  curIndex = 0;
  for (i = 1; i <= srcMatrix->nu; i++)
    for (j = 0; j < srcMatrix->tu; j++)
      {
	pData = &srcMatrix->data[j];
	
	if (pData->j == i)
	  {
	    TRIPLE *newData = &dstMatrix->data[curIndex];
	    curIndex++;
	    newData->i = pData->j;
	    newData->j = pData->i;
	    newData->value = pData->value;
	  }
      }
}

void reverseMatrixV2(SPARSE_MATRIX *dstMatrix, SPARSE_MATRIX *srcMatrix)
{
  int i;
  TRIPLE *pData;
  int numPerColumn[MAX_CO+1];
  int columnStart[MAX_CO+1];

  memset(numPerColumn, 0, sizeof(numPerColumn));

  for (i = 0; i < srcMatrix->tu; i++)
    {
      pData = &srcMatrix->data[i];
      numPerColumn[srcMatrix->data[i].j]++;      
    }
  columnStart[1] = 0;
  for (i = 2; i <= srcMatrix->nu; i++)
    columnStart[i] = columnStart[i-1] + numPerColumn[i-1];


  dstMatrix->mu = srcMatrix->nu;
  dstMatrix->nu = srcMatrix->mu;
  dstMatrix->tu = srcMatrix->tu;

  for (i = 0; i < srcMatrix->tu; i++)
    {
      int newRow;
      TRIPLE *dstTriple;
      
      newRow = srcMatrix->data[i].j;
      dstTriple = &dstMatrix->data[columnStart[newRow]];
      columnStart[newRow]++;
      dstTriple->i = srcMatrix->data[i].j;
      dstTriple->j = srcMatrix->data[i].i;
      dstTriple->value = srcMatrix->data[i].value;
    }
}



void multiplyMatrix (SPARSE_MATRIX **dstMatrix, 
		     SPARSE_MATRIX *firstMatrix, 
		     SPARSE_MATRIX *secondMatrix)
{
  int i, j, k;
  int t1, t2;
  int preRow = 0;
  int *aac = NULL;
  SPARSE_MATRIX *pMatrix;
  int curIndex;

  // Calculate First rops
  for (i = 0; i < firstMatrix->tu; i++)
    if (firstMatrix->data[i].i != preRow)
      {
	preRow = firstMatrix->data[i].i;
	firstMatrix->rops[firstMatrix->data[i].i] = i;
      }

  // Calculate Second rops
  preRow = 0;
  for (i = 0; i < secondMatrix->tu; i++)
    if (secondMatrix->data[i].i != preRow)
      {
	preRow = secondMatrix->data[i].i;
	secondMatrix->rops[secondMatrix->data[i].i] = i;
      }

  aac = (int *)malloc(sizeof(int)*(secondMatrix->nu+1));
  if (NULL == aac)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return;
    }

  pMatrix = (SPARSE_MATRIX *)malloc(sizeof(SPARSE_MATRIX));
  if (NULL == pMatrix)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      return;
    }
  pMatrix->mu = firstMatrix->mu;
  pMatrix->nu = secondMatrix->nu;
  pMatrix->tu = 0;
  curIndex = 0;


  for (i = 1; i <= firstMatrix->mu; i++)
    {
      int firstStart, firstEnd;
 
      memset(aac, 0 ,sizeof(int)*(secondMatrix->nu+1));

      firstStart = firstMatrix->rops[i];
      if (i >= firstMatrix->mu)
	firstEnd = firstMatrix->tu;
      else
	firstEnd = firstMatrix->rops[i+1];

      for (t1 = firstStart; t1 < firstEnd; t1++)
	{
	  int secondStart, secondEnd;
	  k = firstMatrix->data[t1].j;

	  secondStart = secondMatrix->rops[k];
	  if (k >= secondMatrix->mu)
	    secondEnd = secondMatrix->tu;
	  else
	    secondEnd = secondMatrix->rops[k+1];
	  
	  for (t2 = secondStart; t2 < secondEnd; t2++)
	    {
	      assert(firstMatrix->data[t1].j == secondMatrix->data[t2].i);
	      aac[secondMatrix->data[t2].j] += 
		firstMatrix->data[t1].value * secondMatrix->data[t2].value;
	    }
	}

      for (j = 1; j <= secondMatrix->nu; j++)
	{
	  if (curIndex >= MAX_ELEMENT)
	    {
	      printf ("Too Many Elements, not a sparse matrix for Result\n");
	      exit(OVERFLOW);
	    }
	  if (aac[j] == 0)
	    continue;
	  pMatrix->data[curIndex].i = i;
	  pMatrix->data[curIndex].j = j;
	  pMatrix->data[curIndex].value = aac[j];
	  pMatrix->tu++;
	  curIndex++;
	}
    }
  *dstMatrix = pMatrix;
}

STATUS getMatrix(SPARSE_MATRIX **dstMatrix, FILE *fp, unsigned int m, unsigned int n)
{
  STATUS status = OK;
  char c;
  int curIndex;
  int row, column, value;
  SPARSE_MATRIX *pMatrix;

  pMatrix = (SPARSE_MATRIX *)malloc(sizeof(SPARSE_MATRIX));
  if (NULL == pMatrix)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }
  pMatrix->mu = m;
  pMatrix->nu = n;
  pMatrix->tu = 0;

  curIndex = 0;
  getNext(fp, &c);
  while (!feof(fp))
    {
       if (!VALID_EDGE_START(c))
	{
	  status = ERROR;
	  break;
	}

      if (fscanf(fp, "%d", &row))
	{
	  if (row < 0)
	    {
	      printf("Invalid row\n");
	      status = ERROR; 
	      break;
	    }
	}
      else
	{
	  printf("Invalid Input for Edge\n");
	  status = ERROR;
	  break;
	}

      getNext(fp, &c);
      if (!VALID_EDGE_SEPARATOR(c))
	{
	  status = ERROR;
	  break;
	}

      if (fscanf(fp, "%d", &column))
	{
	  if (column < 0)
	    {
	      printf("Invalid column\n");
	      status = ERROR; 
	      break;
	    }
	}
      else
	{
	  printf("Invalid Input for Edge\n");
	  status = ERROR;
	  break;
	}

      getNext(fp, &c);
      if (!VALID_EDGE_SEPARATOR(c))
	{
	  status = ERROR;
	  break;
	}

      if (fscanf(fp, "%d", &value))
	{
	}
      else
	{
	  printf("Invalid Input for Edge\n");
	  status = ERROR;
	  break;
	}

      getNext(fp, &c);
      if (!VALID_EDGE_END(c))
	{
	  status = ERROR;
	  break;
	}

      if (row > MAX_RC 
	  || column > MAX_CO
	  || value == 0
	  || curIndex >= MAX_ELEMENT)
	{
	  status = ERROR;
	  break;
	}
          
      pMatrix->data[curIndex].i = row;
      pMatrix->data[curIndex].j = column;
      pMatrix->data[curIndex].value = value;
      curIndex++;
      pMatrix->tu++;
	   
      getNext(fp, &c);
    }

  *dstMatrix = pMatrix;
  return status;
}
