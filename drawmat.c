void drawmat(char *mat,int matsize,int x,int y,int color)
/*���Σ���ģָ�롢�����С����ʼ����(x,y)����ɫ*/
{
  int i, j, k, n;
  n = (matsize - 1) / 8 + 1;
  for(j = 0; j < matsize; j++)
    for(i = 0; i < n; i++)
      for(k = 0;k < 8; k++)
        if(mat[j * n + i] & (0x80 >> k))  /*����Ϊ1��λ����ʾ*/
          putpixel(x + i * 8 + k, y + j, color);
}


/*
drawmat(matarray16k + i * 32, 16, 200 + i * 15, 200, WHITE);
*/
#include "fivesta.c"
#include "shuom.c"
#include "thanks.c"