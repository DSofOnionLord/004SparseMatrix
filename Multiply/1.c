#include <stdio.h>
#include <stdlib.h>

struct Spa_mat
{
	int x;
	int y;
	int val;
};

void Transpose_matrix(struct Spa_mat *orig, struct Spa_mat *result, int mat_size, int col)
{
	int *rowT;
	int *startP;
	int i;
	rowT = (int *)malloc(sizeof(int)*col);
	startP = (int *)malloc(sizeof(int)*col);
	
	for( i = 0 ; i < col ; i ++ )
	{
		rowT[i] = 0;
	}

	for ( i = 0 ; i < mat_size ; i ++ )
	{
		rowT[orig[i].y]++;
	}
	startP[0] = 1;
	for ( i = 1 ; i < col ; i ++ )
	{
		startP[i] = rowT[i-1] + startP[i-1];
	}

	for ( i = 0 ; i < mat_size ; i ++ )
	{
		result[startP[orig[i].y]-1].x = orig[i].y;
		result[startP[orig[i].y]-1].y = orig[i].x;
		result[startP[orig[i].y]-1].val = orig[i].val;
		startP[orig[i].y]++;
	}

}


int main()
{
	FILE * inp1 = fopen("input1.txt","r");
	FILE * inp2 = fopen("input2.txt","r");
	FILE * outp = fopen("output.txt", "w");
	struct Spa_mat *mat1;
	struct Spa_mat *mat2;
	struct Spa_mat *trans_mat;
	struct Spa_mat *mult_result;
	int **result_mat;
	int i, j, k;
	int row[2], col[2];
	int mat_size[3] = { 0, 0, 0 };
	int mat_content;
	int result_point = -1;
	int n,m,temp;
	int rowBegin = 0, rowp, temp_sum = 0, colp;

//	int *mul_rowT1, *mul_rowT2;
//	int *mul_staP1, *mul_staP2;


	mat1 = (struct Spa_mat *)malloc(sizeof(struct Spa_mat)*1);
	mat2 = (struct Spa_mat *)malloc(sizeof(struct Spa_mat)*1);
	mult_result = (struct Spa_mat *)malloc(sizeof(struct Spa_mat)*1);

	

	fscanf(inp1, "%d %d", &row[0], &col[0]);
	fscanf(inp2, "%d %d", &row[1], &col[1]);
	
	if ( col[0] != row[1])
	{
		fprintf(outp,"Cannot Calculate!");
		return 0;
	}
	result_mat = (int **)malloc(sizeof(int*)*row[0]);
	for ( i = 0 ; i < row[0] ; i ++ )
	{
		result_mat[i] = (int*)malloc(sizeof(int*)*col[1]);
	}

	for ( i = 0 ; i < row[0] ; i ++ )
	{
		for ( j = 0 ; j < col[0] ; j ++ )
		{
			fscanf(inp1, "%d", &mat_content);
			if (mat_content != 0 )
			{
				mat_size[0]++;
				mat1 = (struct Spa_mat *)realloc(mat1, sizeof(struct Spa_mat) * mat_size[0]);
				mat1[mat_size[0] - 1].x = i;
				mat1[mat_size[0] - 1].y = j;
				mat1[mat_size[0] - 1].val = mat_content;
			}
		}
	}

	for ( i = 0 ; i < row[1] ; i ++ )
	{
		for ( j = 0 ; j < col[1] ; j ++ )
		{
			fscanf(inp2, "%d", &mat_content);
			if (mat_content != 0 )
			{
				mat_size[1]++;
				mat2 = (struct Spa_mat *)realloc(mat2, sizeof(struct Spa_mat) * mat_size[1]);
				mat2[mat_size[1] - 1].x = i;
				mat2[mat_size[1] - 1].y = j;
				mat2[mat_size[1] - 1].val = mat_content;
			}
		}
	}
	trans_mat = (struct Spa_mat *)malloc(sizeof(struct Spa_mat) * (mat_size[1]+1));

	Transpose_matrix(mat2, trans_mat, mat_size[1], col[1]);
	
	mat1 = (struct Spa_mat *)realloc(mat1, sizeof(struct Spa_mat) * (mat_size[0]+1));
	
	//교재 소스를 참고 하였습니다.
	rowp = mat1[0].x;
	for ( i = 0 ; i < mat_size[0] ; )
	{
		for ( j  = 0 ; j < mat_size[1]+1 ; )
		{
			if(mat1[i].x != rowp)
			{
				if(temp_sum)
				{
					//printf("sum = %d (%d,%d)\n", temp_sum, rowp, colp);
					mat_size[2]++;
					mult_result = (struct Spa_mat *)realloc(mult_result, sizeof(struct Spa_mat) * mat_size[2]);
					mult_result[mat_size[2]-1].x = rowp;
					mult_result[mat_size[2]-1].y = colp;
					mult_result[mat_size[2]-1].val = temp_sum;
					temp_sum = 0;
				}
				
				i = rowBegin;
				for(;trans_mat[j].x == colp ; j++);
				colp = trans_mat[j].x;
			}
			else if (trans_mat[j].x != colp)
			{
				if(temp_sum)
				{
					//printf("sum = %d (%d,%d)\n", temp_sum, rowp, colp);
					mat_size[2]++;
					mult_result = (struct Spa_mat *)realloc(mult_result, sizeof(struct Spa_mat) * mat_size[2]);
					mult_result[mat_size[2]-1].x = rowp;
					mult_result[mat_size[2]-1].y = colp;
					mult_result[mat_size[2]-1].val = temp_sum;
					temp_sum = 0;
				}
				temp_sum = 0;
				i = rowBegin;
				colp = trans_mat[j].x;
			}
			else
			{
				if(mat1[i].y < trans_mat[j].y)
				{
					i++;
				}
				else if(mat1[i].y == trans_mat[j].y)
				{
					temp_sum += ( mat1[i++].val * trans_mat[j++].val);
				}
				else if(mat1[i].y > trans_mat[j].y)
				{
					j++;
				}
			}
		}
		for(;mat1[i].x == rowp ; i++);

		rowBegin = i;
		rowp = mat1[i].x;
	}

	for ( i = 0 ; i < row[0] ; i ++ )
	{
		for ( j = 0 ; j < col[1] ; j ++ )
		{
			result_mat[i][j] = 0;
		}
	}

	for ( i = 0 ; i < mat_size[2] ; i ++ )
	{
		result_mat[mult_result[i].x][mult_result[i].y] = mult_result[i].val;
	}

	fprintf(outp, "%d %d\n", row[0], col[1]);
	for ( i = 0 ; i < row[0] ; i ++ )
	{
		for ( j = 0 ; j < col[1] ; j ++ )
		{
			fprintf(outp,"%-3d",result_mat[i][j]);
		}
		fprintf(outp,"\n");
	}

	
	free(mat1);
	free(mat2);
	free(trans_mat);
	fclose(inp1);
	fclose(inp2);
	fclose(outp);
	return 0;
}