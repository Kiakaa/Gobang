void drawqp()
{
    int i;
    setcolor(1);
    /*
    函数名: setcolor
    功  能: 设置当前画线颜色
    用  法: void far setcolor(int color);
    */
    setlinestyle(SOLID_LINE,0,3);
    /*
    函数名: setlinestyle
    功  能: 设置当前画线宽度和类型
    用  法: void far setlinestyle(int linestype, unsigned upattern);
    */
    setfillstyle(SOLID_FILL,6);
    /*
    函数名: setfillstyle
    功  能: 设置填充模式和颜色
    */
    bar(163,4,635,475);
    rectangle(163,3,635,475);
    setlinestyle(SOLID_LINE,0,1);
    for(i=0;i<15;i++)
        {line(189+30*i,3,189+30*i,475);
         line(163,29+30*i,635,29+30*i);
        }
    for (pi=0;pi<15;pi++)
     {
       for (pj=0;pj<15;pj++)
       {
         pos[pi][pj].x=189+30*pj;
         pos[pi][pj].y=29+30*pi;

         rel[pi][pj].lr=pos[pi][pj].x-14;
         rel[pi][pj].rr=pos[pi][pj].x+14;
         rel[pi][pj].ur=pos[pi][pj].y-14;
         rel[pi][pj].dr=pos[pi][pj].y+14;
       }

     }
/*

   printf("\n");
   printf("Wlcome to the game!\n");
   printf("smart wuzi qi!\n\n\n");
   printf("ver: 1.0\n");
   printf("author:\n");
   printf("wangmaohai\n\n");
   printf("control key:\n");
   printf("up--up\n");
   printf("down--down\n");
   printf("left--left\n");
   printf("right--right\n");
   printf("Yes--Enter\n");
   printf("EXIT--ESC\n\n\n");
   printf("contact me:\n");
   printf("QQ:\n");
   printf("874655551\n");
   printf("EMAIL:\n");
   printf("wanglui1990@.163 \n");
*/

}
/*人机对战*/
void play()
{
     /*
    int key=0,p=0;
    */

    /*
    int *mapbuf1,*mapbuf2;
    int size;


    line(387,237,397,237);
    line(397,227,397,237);
    line(401,227,401,237);
    line(401,237,411,237);
    line(387,241,397,241);
    line(397,241,397,251);
    line(401,241,401,251);
    line(401,241,411,241);
    size=imagesize(387,227,411,251);
    mapbuf1=malloc(size);
    mapbuf2=malloc(size);
    getimage(387,227,411,251,mapbuf1);
    getimage(207,47,231,71,mapbuf2);


    while(!kbhit())
    {      /
      key=bioskey(0);
        if(key==LEFT&&x>189)
        {
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf2,COPY_PUT);
            x-=30;key=0;
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf1,COPY_PUT);
        }
        if(key==RIGHT&&x<609)
        { 
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf2,COPY_PUT);
            x+=30;key=0;
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf1,COPY_PUT);
        }
        if(key==DOWN&&y<449)
        { 
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf2,COPY_PUT);
            y+=30;key=0;
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf1,COPY_PUT);
        }
        if(key==UP&&y>29)
        {
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf2,COPY_PUT);
            y-=30; key=0;
            if(qp[(y-29)/30][(x-189)/30]==0)
            putimage(x-12,y-12,mapbuf1,COPY_PUT);
        }
          */
          /*
        if(key==ENTER&&qp[(y-29)/30][(x-189)/30]==0)
        {
        */  /*
            if(p%2==0)
            { downzi(x,y,p);
             qp[(y-29)/30][(x-189)/30]=1;

            p++;
            flag=panying();
            key=0;
            }
             if(p%2==1)
            {cpuai();
             downzi(x,y,p);
             qp[(y-29)/30][(x-189)/30]=2;
             flag=panying();
             p++;
            }
            */
         /*
        }
          */
          /*
        if(1==flag)
        {
            settextstyle(0,0,4);
            outtextxy(190,240,"The white win");
            return;
        }
        if(2==flag)
        {
            settextstyle(0,0,4);
            outtextxy(190,240,"The black win");
            return;
        }

    }*/
}
void downzi(x,y,p)
{
    if(p%2==0)
        setfillstyle(SOLID_FILL,WHITE);
    else
        setfillstyle(SOLID_FILL,BLACK);
    fillellipse(x,y,15,15);
    /*
    函数名: fillellipse
    功  能: 画出并填充一椭圆
    用  法: void far fillellipse(int x, int y, int xradius, int yradius);
    */
}
 /*判断输赢*/
int panying()
{
    int p1=0,p2=0,i,j,k;
/****************判行**********************/
    for(i=0;i<15;i++)
        for(j=0;j<10;j++)
        {
            for(k=0;k<5;k++)
            {
                if(qp[i][j+k]==1)                     /*qp[15][15]={0}标志棋局棋子的全局数组*/
                    p1++;
                if(qp[i][j+k]==2)
                    p2++;
            }
            if(p1==5) return 1;
            if(p2==5) return 2;
            p1=p2=0;
        }
/**************判列*******************/
          for(j=0;j<15;j++)
            for(i=0;i<10;i++)
            {
                for(k=0;k<5;k++)
                {
                    if(qp[i+k][j]==1)
                        p1++;
                    if(qp[i+k][j]==2)
                        p2++;
                }
                if(p1==5) return 1;
                if(p2==5) return 2;
                p1=p2=0;
            }
/**************右斜******************/
            for(i=0;i<10;i++)
                for(j=0;j<10;j++)
                {
                    for(k=0;k<5;k++)
                    {
                        if(qp[i+k][j+k]==1)
                            p1++;
                        if(qp[i+k][j+k]==2)
                            p2++;
                    }
                    if(p1==5) return 1;
                    if(p2==5) return 2;
                    p1=p2=0;
                }
/***************左斜*****************/
                for(i=0;i<10;i++)
                    for(j=4;j<15;j++)
                    {
                        for(k=0;k<5;k++)
                        {
                            if(qp[i+k][j-k]==1)
                                p1++;
                            if(qp[i+k][j-k]==2)
                                p2++;
                        }
                        if(p1==5) return 1;
                        if(p2==5) return 2;
                        p1=p2=0;
                    }
}
/*五子棋AI*/
void cpuai()
{
int qiju[2][15][15][8][2]={0};     /* 棋型数组*/
int k,i,j,q,b=0,a=1,d,y1=0,y2=0,x1=0,x2=0;
int a1[15][15]={0},a2[15][15]={0};
/****************为双方填写棋型表************/
for(k=0;k<2;k++)
for(i=0;i<15;i++)
for(j=0;j<15;j++)
{
  if(qp[i][j]==0)
  {
   for(q=0;q<8;q++)
   {
    if(k==0) d=1;
    else d=2;
    if(q==0&&j>0)
    {
     for(;;)
     {
      if(qp[i][j-a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i][j-a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==1&&i>0&&j>0)
    {
     for(;;)
     {
      if(qp[i-a][j-a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i-a][j-a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==2&&i>0)
    {
     for(;;)
     {
      if(qp[i-a][j]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i-a][j]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==3&&i>0&&j<14)
    {
     for(;;)
     {
      if(qp[i-a][j+a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i-a][j+a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
     if(q==4&&j<14)
    {
     for(;;)
     {
      if(qp[i][j+a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i][j+a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==5&&i<14&&j<14)
    {
     for(;;)
     {
      if(qp[i+a][j+a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i+a][j+a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==6&&i<14)
    {
     for(;;)
     {
      if(qp[i+a][j]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i+a][j]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
    if(q==7&&j>0&&i<14)
    {
     for(;;)
     {
      if(qp[i+a][j-a]==d){b++;a++;continue;}
      else break;
     }
     qiju[k][i][j][q][0]=b;b=0;
     if(qp[i+a][j-a]==0){qiju[k][i][j][q][1]=1;a=1;}
     else {qiju[k][i][j][q][1]=0;a=1;}
    }
   }
  }
}
/******************根据评分规则对每一个空格评分***************/
for(k=0;k<2;k++)
for(i=0;i<15;i++)
for(j=0;j<15;j++)
{
  if(k==0) /*为白棋评分*/
  {
   for(q=0;q<4;q++)
   {
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=7000;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=301;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=43;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=11;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=7000;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=63;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=6;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=1;

   }
    if(b==126||b==189||b==252) b=1500;
    if(b==106) b=1000;

   a1[i][j]=b;b=0;
  }
  if(k==1)  /*为黑棋评分*/
  {
   for(q=0;q<4;q++)
   {
    
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=30000;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=1500;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=51;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
    &&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
    b+=16;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=30000;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=71;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=7;
    if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
    &&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
    ||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
    b+=2;
   }
   if(b==142||b==213||b==284) b=1500;
   if(b==122) b=1300;

   a2[i][j]=b;b=0;
  }
}
/****************算出分数最高的空位，填写坐标*********************/
for(i=0;i<15;i++)
for(j=0;j<15;j++)
{
  if(a1[y1][x1]<a1[i][j]) {y1=i;x1=j;}
}
for(i=0;i<15;i++)
for(j=0;j<15;j++)
{
  if(a2[y2][x2]<a2[i][j]) {y2=i;x2=j;}
}
if(a2[y2][x2]>=a1[y1][x1]){x=189+30*x2;y=29+30*y2;}
else {x=189+30*x1;y=29+30*y1;}
}
