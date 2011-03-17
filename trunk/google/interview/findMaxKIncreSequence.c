
//int a[] = {1,5,2,8,7,6,11};
int a[] = {7,6,5,4,3,2,1};
int main()
{
	int d0[7];
	int d1[7];
	int d2[7];
	int i, j, max;
	
	for (i = 0; i < 7; i++)
		d0[i] = 0;

	for (i = 0; i < 7; i++)
	{
		d1[i] = 0;
		for (j = i+1; j< 7; j++)
		{
			if (a[j] > a[i] && d1[i] < a[j] + d0[j])
				d1[i] = a[j] + d0[j];
		}
	}

	for (i = 0; i < 7; i++)
	{
		d2[i] = 0;
		for (j = i+1; j< 7; j++)
		{
			if (a[j] > a[i] && d2[i] < a[j] + d1[j])
				d2[i] = a[j] + d1[j];
		}
	}

	max = 0;
	for (i = 0; i < 7; i++)
	{
		if (a[i] + d2[i] > max)
		{
			max = a[i] + d2[i];
		}
	}
	
	printf ("\nMax K increse order sequence is %d\n", max);
}
