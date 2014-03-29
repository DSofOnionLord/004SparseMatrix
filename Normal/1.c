#include<stdio.h>
#include<stdlib.h>

struct Objects
{
	int x;
	int y;
	int val;
};

void fast_trans ( struct Objects *orig_arr,struct Objects *res, int size_arr, int size_mat)
{
	int *rowTerms;
	int *startPos;
	int i, j;

	rowTerms = (int *) malloc ( sizeof(int) * size_mat);
	startPos = (int *) malloc ( sizeof(int) * size_mat);

	for ( i = 0 ; i < size_mat ; i ++ )
	{
		rowTerms[i] = 0;
		//printf("%5d %5d %5d\n", orig_arr[i].x, orig_arr[i].y, orig_arr[i].val);
	}

	for ( i = 0 ; i < size_arr ; i ++ ) //O(n^2)
	{
		rowTerms[orig_arr[i].y]++;
	}
	startPos[0] = 1;
	for ( i = 1 ; i < size_mat ; i ++ ) //O(n)
	{
		startPos[i] = startPos[i-1] + rowTerms[i-1];
	}
	
	for ( i = 0 ; i < size_arr ; i ++ )//O(n^2)
	{
		res[startPos[orig_arr[i].y]-1].x = orig_arr[i].y;
		res[startPos[orig_arr[i].y]-1].y = orig_arr[i].x;
		res[startPos[orig_arr[i].y]-1].val = orig_arr[i].val;
		startPos[orig_arr[i].y]++;
	}
	free(rowTerms);
	free(startPos);
}

int main()
{
	FILE * fin = fopen("input.txt", "r");
	FILE * fout = fopen("output.txt", "w");
	struct Objects *arr;
	struct Objects *result;

	int mat_size;
	int count = 0;
	int mat_content;
	int i, j;

	fscanf(fin, "%d", &mat_size);
	
	arr = (struct Objects *)malloc(sizeof(struct Objects));
	result = (struct Objects *)malloc(sizeof(struct Objects));
	
	for ( i = 0 ; i < mat_size ; i ++ )
	{
		for ( j = 0 ; j < mat_size ; j ++ )
		{
			fscanf(fin,"%d",&mat_content);
			
			if(mat_content != 0 )
			{
				count++;
				arr = (struct Objects *)realloc(arr, sizeof(struct Objects) * count);
				result = (struct Objects *)realloc(result, sizeof(struct Objects) * count);
				arr[count-1].x = i;
				arr[count-1].y = j;
				arr[count-1].val = mat_content;
			}
		}
	}
	
	fast_trans(arr,result, count, mat_size);

	
	fprintf(fout, "%d\n", count);
	for ( i = 0 ; i < count ; i ++ )
	{
		fprintf(fout, "%5d %5d %5d\n", result[i].x, result[i].y, result[i].val);
	}

	free(arr);
	free(result);
	fclose(fin);
	fclose(fout);
	/*
	while(fscanf(fin, "%d %d %d", &a[c].x, &a[c].y, &a[c].val) != EOF)
	{
		rowTerm[a[c].y]++;
		c++;
	}
	startP[0] = 1;
	for ( i = 1 ; i < 20 ; i ++ )
	{
		startP[i] = startP[i-1] + rowTerm[i-1];
	}
	
	for ( i = 0 ; i < 20 ; i ++ )
	{
		printf("%d ", rowTerm[i]);
	}
	printf("\n");
	for ( i = 0 ; i < 20 ; i ++ )
	{
		printf("%d ", startP[i]);
	}

	for ( i = 0 ; i < 20 ; i ++ )
	{
		
	}
	*/
}