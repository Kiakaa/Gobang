#define MouseStatusMouseOn  1    /*在MouseStatus()中实时显示鼠标 */
#define MouseStatusMouseOff 2    /*在MouseStatus()中不实时显示鼠标*/
#define MouseDoubleClickTime 0.3    /*鼠标双击的最大时间间隔*/
int MouseHolded   =0;        /*是否支持鼠标功能:0--不支持,1--支持*/
int MouseButtonNum=0;        /*当支持鼠标功能时,存放鼠标的按钮数*/
int MouseX        =0;        /*存放鼠标的水平方向的值*/
int MouseY        =0;        /*存放鼠标的垂直方向的值*/
char MouseType    =1;        /*设置鼠标类型:1--为箭头型,2--编辑型*/
clock_t LastMouseClickTime=0;    /*上一次鼠标单击的时间*/
clock_t NowMouseClickTime=0;    /*这次鼠标单击的时间  */
char    MouseClickType=0;        /*上一次鼠标单击是左键还是右键:1--左键,2--右键*/
int arrowMousePixSave[16][10];    /*用于保存鼠标即将覆盖的区域*/
int arrowMouseDraw[16][10]={    /*设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域*/
    {1,1,3,3,3,3,3,3,3,3},
    {1,2,1,3,3,3,3,3,3,3},
    {1,2,2,1,3,3,3,3,3,3},
    {1,2,2,2,1,3,3,3,3,3},
    {1,2,2,2,2,1,3,3,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,2,2,1,3},
    {1,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,1,3,1,2,2,1,3,3},
    {1,1,3,3,1,2,2,1,3,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,3,1,2,2,1} };
int editMousePixSave[15][5];
int editMouseDraw[15][5]={
    {1,1,3,1,1},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {3,3,1,3,3},
    {1,1,3,1,1}    };

int qp[15][15]={0};               /*标志棋局棋子的全局数组*/
int x=399,y=239,flag=0;           /*光标坐标以及输赢标志*/
struct posi
{
 int x;
 int y;
}pos[15][15];
struct rela
{
 int lr;
 int rr;
 int ur;
 int dr;
}rel[15][15];
int pi,pj;
void MountMouse();            /*加载鼠标*/
void UnmountMouse();        /*卸载鼠标*/
void DrawMouseOnly(int,int);        /*绘画鼠标,但不保存即将被鼠标覆盖的区域*/
void MouseOn(int,int);        /*显示鼠标,但保存即将被鼠标覆盖的区域*/
void MouseOff(int,int);        /*隐藏鼠标*/
void SetMouseHoriBound(int,int);    /*设置鼠标水平方向边界*/
void SetMouseVertBound(int,int);    /*设置鼠标垂直方向边界*/
void SetMouseXY(int,int);             /*设置鼠标的初始位置*/
void GetMouseXY();            /*获得鼠标的当前位置*/
void MouseSpeed(int,int);             /*设置鼠标的速度*/
int  MouseStatus(int);        /*获得鼠标按键状态*/
void  Timer(long);            /*计时器*/

void  Timer(long getTime)        /*计时器*/
{
    clock_t startTime=clock();
    clock_t endTime=clock();
    while((endTime-startTime)>=getTime)
    {
        endTime=clock();
    }
    return ;
}
/*加载鼠标*/
void MountMouse()
{
    _AX=0x00;        /*功能00H*/
    geninterrupt(0x33);    /*0x33:鼠标中断类型*/

    MouseHolded      =_AX;    /*_AX为0000H——不支持鼠标功能，为FFFFH——支持鼠标功能*/
    MouseButtonNum=_BX;    /*鼠标按钮个数*/
}

/*卸载鼠标*/
void UnmountMouse()
{
    _AX=0x02;        /*功能02H*/
    geninterrupt(0x33);    /*0x33:鼠标中断类型*/
    return ;
}

/*设置鼠标水平边界:minX为水平方向的最小值,maxX为水平方向的最大值*/
void SetMouseHoriBound(int minX,int maxX)
{
    _AX=0x07;
    _CX=minX;
    _DX=maxX;
    geninterrupt(0x33);
    return;
}

/*设置鼠标垂直边界:minY为垂直方向的最小值,maxY为垂直方向的最大值*/
void SetMouseVertBound(int minY,int maxY)
{
    _AX=0x08;
    _CX=minY;
    _DX=maxY;
    geninterrupt(0x33);
    return;
}

/*设置鼠标指针位置:xValue为水平方向位置,yValue为垂直方向的位置*/
void SetMouseXY(int xValue,int yValue)
{
    _AX=0x04;
    _CX=xValue;
    _DX=yValue;
    geninterrupt(0x33);
    return;
}

/*读取鼠标位置*/
void GetMouseXY()
{
    _AX=0x03;
    geninterrupt(0x33);

    MouseX=_CX;        /*将鼠标水平方向位置存放到MouseX*/
    MouseY=_DX;        /*将鼠标垂直方向位置存放到MouseY*/
    return;
}

/*设置鼠标速度*/
void MouseSpeed(int xSpeed,int ySpeed)
{
   _CX=xSpeed;
   _DX=ySpeed;
   _AX=0x0f;
   geninterrupt(0x33);
}

/*绘画鼠标,但不保存即将被鼠标覆盖的区域*/
void DrawMouseOnly(int mousex,int mousey)
{
    int i,j;
    int color;

    if(MouseType==1)
    {
        for(i=0;i<16;i++)
    for(j=0;j<10;j++)
    {                
        if(arrowMouseDraw[i][j]==1)
        putpixel(mousex+j,mousey+i,0);
        else if(arrowMouseDraw[i][j]==2)    /* 画鼠标*/
        putpixel(mousex+j,mousey+i,15);
    }    
    }
    else if(MouseType==2)
    {
    for(i=0;i<15;i++)
                for(j=0;j<5;j++)
        {
        if(editMouseDraw[i][j]==1)    /*由于编辑鼠标的热点在鼠标的中心*/
                putpixel(mousex-2+j,mousey-7+i,0);
        }
     }
}

/*显示鼠标,但保存即将被鼠标覆盖的区域*/
void MouseOn(int mousex,int mousey)
{
    int i,j;
    int color;

    if(MouseType==1)
    {
        for(i=0;i<16;i++)
    for(j=0;j<10;j++)
    {
        arrowMousePixSave[i][j]=getpixel(mousex+j,mousey+i);/* 保存原来的颜色*/
        if(arrowMouseDraw[i][j]==1)
        putpixel(mousex+j,mousey+i,0);
        else if(arrowMouseDraw[i][j]==2)        /* 画鼠标*/
            putpixel(mousex+j,mousey+i,15);
    }    
    }
    else if(MouseType==2)
    {
    for(i=0;i<15;i++)
            for(j=0;j<5;j++)
            {
            editMousePixSave[i][j]=getpixel(mousex-2+j,mousey-7+i);
        if(editMouseDraw[i][j]==1)            /*由于编辑鼠标的热点在鼠标的中心*/
            putpixel(mousex-2+j,mousey-7+i,0);
        }
    }
}

/*隐藏鼠标*/
void MouseOff(int mousex,int mousey)
{
   int i,j,x,y,color;
   x=mousex;
   y=mousey;

   if(MouseType==1)
   {
    for(i=0;i<16;i++)
    for(j=0;j<10;j++)
    {
        if(arrowMouseDraw[i][j]==3)
        continue;
        color=getpixel(x+j,y+i);
        putpixel(x+j,y+i,color^color);        /*原位置异或清除*/
        putpixel(x+j,y+i,arrowMousePixSave[i][j]);/* 还原原背景*/
    }
   }
   else if(MouseType==2)
   {
        for(i=0;i<15;i++)
    for(j=0;j<5;j++)
    {
        if(editMouseDraw[i][j]==3)
            continue;
        color=getpixel(x-2+j,y-7+i);
        putpixel(x-2+j,y-7+i,color^color);    /*原位置异或清除*/
        putpixel(x-2+j,y-7+i,editMousePixSave[i][j]);/* 还原原背景*/
    }
   }
}

/*获取鼠标状态*/
int MouseStatus(int Mouse_On_Off)
{
  int MouseMSG=0;
  int oldMouseX,oldMouseY;
  int i,j,color;

  oldMouseX=MouseX,oldMouseY=MouseY;    /*保存当前鼠标的位置*/

  _AX=0x03;            /*读取鼠标按钮状态*/
  geninterrupt(0x33);        /*产生33号鼠标软中断*/

  if((_BX&1) && !(_BX&2))        /*鼠标左键被按下同时右键没有按下*/
    MouseMSG=4;

  if((_BX&2) && !(_BX&1))        /*鼠标右键被按下同时左键没有按下*/
    MouseMSG=5;

  if(_BX&1 && _BX&2)        /*鼠标左键和右键同时被按下*/
    MouseMSG=3;

  _AX=0x06;            /*读取鼠标按钮释放信息*/
  _BX=0x00;            /*指定读取鼠标左键的释放信息*/
  geninterrupt(0x33);        /*产生33号鼠标软中断*/
  if(_BX==1)            /*如果鼠标左键的释放数为1*/
    MouseMSG=2;            /*产生一个单击左键信息*/

  _AX=0x06;            /*读取鼠标按钮释放信息*/
  _BX=0x01;            /*指定读取鼠标右键的释放信息*/
  geninterrupt(0x33);        /*产生33号鼠标软中断*/
  if(_BX==1)            /*如果鼠标左键的释放次数为1*/
    MouseMSG=1;            /*产生一个单击右键信息*/

  GetMouseXY();            /*获得当前鼠标位置,并把数据赋给MouseX,MouseY*/

  if(Mouse_On_Off==MouseStatusMouseOn)    /*实时显示*/
     if(oldMouseX!=MouseX || oldMouseY!=MouseY)
     {
        MouseOff(oldMouseX,oldMouseY);
        MouseOn(MouseX,MouseY);
      }

  /*鼠标双击的判断*/
  if(MouseMSG==3)            /*如果是同时按下鼠标的左键和右键*/
    MouseClickType=0;        /*上一次的按键是既不是鼠标左键也不是鼠标右键*/
  else if(MouseMSG==1)        /*如果是按下鼠标的右键*/
  {
     if(MouseClickType==2)        /*如果上一次也是按下鼠标的右键*/
     {
    NowMouseClickTime=clock();/*获得现在的程序运行时间*/
    /*判断上一次按下鼠标的右键到这次按下鼠标右键的时间间隔是不是小于最大鼠标双击时间间隔*/
    if(((NowMouseClickTime-LastMouseClickTime)/CLK_TCK)<=MouseDoubleClickTime)
         MouseMSG=6;        /*鼠标消息为右键双击*/
    LastMouseClickTime=NowMouseClickTime;
     }
     else
     {
    MouseClickType=2;        /*作为下一次的按键判断时的上一次按键状态*/
    NowMouseClickTime=clock();   /*作为下一次的按键判断时的上一次按键时间*/
    LastMouseClickTime=NowMouseClickTime;
     }
   }
   else if(MouseMSG==2)
   {
    if(MouseClickType==1)
    {
        NowMouseClickTime=clock();/*获得现在的程序运行时间*/
        /*判断上一次按下鼠标的左键到这次按下鼠标左键的时间间隔是不是小于最大鼠标双击时间间隔*/
        if(((NowMouseClickTime-LastMouseClickTime)/CLK_TCK)<=MouseDoubleClickTime)
        MouseMSG=7;    /*鼠标消息为左键双击*/
        LastMouseClickTime=NowMouseClickTime;
    }
    else
    {
        MouseClickType=1;            /*作为下一次的按键判断时的上一次按键状态*/
        NowMouseClickTime=clock();    /*作为下一次的按键判断时的上一次按键时间*/
        LastMouseClickTime=NowMouseClickTime;
    }
   }

  return MouseMSG;        /*返回鼠标按键消息:0--没有按键,1--单击右键, 2--单击左键,3--同时按下左键和右键,           4--拖曳左键,5--拖曳右键,6--双击右键,7--双击左键*/
}
void DisplayMsg(char * msg)
{   /*
    setcolor(RED);
    floodfill(10,400,WHITE);
    */
    outtextxy(10,400,msg);

}