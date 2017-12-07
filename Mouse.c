#define MouseStatusMouseOn  1    /*��MouseStatus()��ʵʱ��ʾ��� */
#define MouseStatusMouseOff 2    /*��MouseStatus()�в�ʵʱ��ʾ���*/
#define MouseDoubleClickTime 0.3    /*���˫�������ʱ����*/
int MouseHolded   =0;        /*�Ƿ�֧����깦��:0--��֧��,1--֧��*/
int MouseButtonNum=0;        /*��֧����깦��ʱ,������İ�ť��*/
int MouseX        =0;        /*�������ˮƽ�����ֵ*/
int MouseY        =0;        /*������Ĵ�ֱ�����ֵ*/
char MouseType    =1;        /*�����������:1--Ϊ��ͷ��,2--�༭��*/
clock_t LastMouseClickTime=0;    /*��һ����굥����ʱ��*/
clock_t NowMouseClickTime=0;    /*�����굥����ʱ��  */
char    MouseClickType=0;        /*��һ����굥������������Ҽ�:1--���,2--�Ҽ�*/
int arrowMousePixSave[16][10];    /*���ڱ�����꼴�����ǵ�����*/
int arrowMouseDraw[16][10]={    /*���������״,����1:��ʾ���ı߽�,2:��ʾ���߽�����Χ������,3:��ʾ������������*/
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

int qp[15][15]={0};               /*��־������ӵ�ȫ������*/
int x=399,y=239,flag=0;           /*��������Լ���Ӯ��־*/
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
void MountMouse();            /*�������*/
void UnmountMouse();        /*ж�����*/
void DrawMouseOnly(int,int);        /*�滭���,�������漴������긲�ǵ�����*/
void MouseOn(int,int);        /*��ʾ���,�����漴������긲�ǵ�����*/
void MouseOff(int,int);        /*�������*/
void SetMouseHoriBound(int,int);    /*�������ˮƽ����߽�*/
void SetMouseVertBound(int,int);    /*������괹ֱ����߽�*/
void SetMouseXY(int,int);             /*�������ĳ�ʼλ��*/
void GetMouseXY();            /*������ĵ�ǰλ��*/
void MouseSpeed(int,int);             /*���������ٶ�*/
int  MouseStatus(int);        /*�����갴��״̬*/
void  Timer(long);            /*��ʱ��*/

void  Timer(long getTime)        /*��ʱ��*/
{
    clock_t startTime=clock();
    clock_t endTime=clock();
    while((endTime-startTime)>=getTime)
    {
        endTime=clock();
    }
    return ;
}
/*�������*/
void MountMouse()
{
    _AX=0x00;        /*����00H*/
    geninterrupt(0x33);    /*0x33:����ж�����*/

    MouseHolded      =_AX;    /*_AXΪ0000H������֧����깦�ܣ�ΪFFFFH����֧����깦��*/
    MouseButtonNum=_BX;    /*��갴ť����*/
}

/*ж�����*/
void UnmountMouse()
{
    _AX=0x02;        /*����02H*/
    geninterrupt(0x33);    /*0x33:����ж�����*/
    return ;
}

/*�������ˮƽ�߽�:minXΪˮƽ�������Сֵ,maxXΪˮƽ��������ֵ*/
void SetMouseHoriBound(int minX,int maxX)
{
    _AX=0x07;
    _CX=minX;
    _DX=maxX;
    geninterrupt(0x33);
    return;
}

/*������괹ֱ�߽�:minYΪ��ֱ�������Сֵ,maxYΪ��ֱ��������ֵ*/
void SetMouseVertBound(int minY,int maxY)
{
    _AX=0x08;
    _CX=minY;
    _DX=maxY;
    geninterrupt(0x33);
    return;
}

/*�������ָ��λ��:xValueΪˮƽ����λ��,yValueΪ��ֱ�����λ��*/
void SetMouseXY(int xValue,int yValue)
{
    _AX=0x04;
    _CX=xValue;
    _DX=yValue;
    geninterrupt(0x33);
    return;
}

/*��ȡ���λ��*/
void GetMouseXY()
{
    _AX=0x03;
    geninterrupt(0x33);

    MouseX=_CX;        /*�����ˮƽ����λ�ô�ŵ�MouseX*/
    MouseY=_DX;        /*����괹ֱ����λ�ô�ŵ�MouseY*/
    return;
}

/*��������ٶ�*/
void MouseSpeed(int xSpeed,int ySpeed)
{
   _CX=xSpeed;
   _DX=ySpeed;
   _AX=0x0f;
   geninterrupt(0x33);
}

/*�滭���,�������漴������긲�ǵ�����*/
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
        else if(arrowMouseDraw[i][j]==2)    /* �����*/
        putpixel(mousex+j,mousey+i,15);
    }    
    }
    else if(MouseType==2)
    {
    for(i=0;i<15;i++)
                for(j=0;j<5;j++)
        {
        if(editMouseDraw[i][j]==1)    /*���ڱ༭�����ȵ�����������*/
                putpixel(mousex-2+j,mousey-7+i,0);
        }
     }
}

/*��ʾ���,�����漴������긲�ǵ�����*/
void MouseOn(int mousex,int mousey)
{
    int i,j;
    int color;

    if(MouseType==1)
    {
        for(i=0;i<16;i++)
    for(j=0;j<10;j++)
    {
        arrowMousePixSave[i][j]=getpixel(mousex+j,mousey+i);/* ����ԭ������ɫ*/
        if(arrowMouseDraw[i][j]==1)
        putpixel(mousex+j,mousey+i,0);
        else if(arrowMouseDraw[i][j]==2)        /* �����*/
            putpixel(mousex+j,mousey+i,15);
    }    
    }
    else if(MouseType==2)
    {
    for(i=0;i<15;i++)
            for(j=0;j<5;j++)
            {
            editMousePixSave[i][j]=getpixel(mousex-2+j,mousey-7+i);
        if(editMouseDraw[i][j]==1)            /*���ڱ༭�����ȵ�����������*/
            putpixel(mousex-2+j,mousey-7+i,0);
        }
    }
}

/*�������*/
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
        putpixel(x+j,y+i,color^color);        /*ԭλ��������*/
        putpixel(x+j,y+i,arrowMousePixSave[i][j]);/* ��ԭԭ����*/
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
        putpixel(x-2+j,y-7+i,color^color);    /*ԭλ��������*/
        putpixel(x-2+j,y-7+i,editMousePixSave[i][j]);/* ��ԭԭ����*/
    }
   }
}

/*��ȡ���״̬*/
int MouseStatus(int Mouse_On_Off)
{
  int MouseMSG=0;
  int oldMouseX,oldMouseY;
  int i,j,color;

  oldMouseX=MouseX,oldMouseY=MouseY;    /*���浱ǰ����λ��*/

  _AX=0x03;            /*��ȡ��갴ť״̬*/
  geninterrupt(0x33);        /*����33��������ж�*/

  if((_BX&1) && !(_BX&2))        /*������������ͬʱ�Ҽ�û�а���*/
    MouseMSG=4;

  if((_BX&2) && !(_BX&1))        /*����Ҽ�������ͬʱ���û�а���*/
    MouseMSG=5;

  if(_BX&1 && _BX&2)        /*���������Ҽ�ͬʱ������*/
    MouseMSG=3;

  _AX=0x06;            /*��ȡ��갴ť�ͷ���Ϣ*/
  _BX=0x00;            /*ָ����ȡ���������ͷ���Ϣ*/
  geninterrupt(0x33);        /*����33��������ж�*/
  if(_BX==1)            /*������������ͷ���Ϊ1*/
    MouseMSG=2;            /*����һ�����������Ϣ*/

  _AX=0x06;            /*��ȡ��갴ť�ͷ���Ϣ*/
  _BX=0x01;            /*ָ����ȡ����Ҽ����ͷ���Ϣ*/
  geninterrupt(0x33);        /*����33��������ж�*/
  if(_BX==1)            /*������������ͷŴ���Ϊ1*/
    MouseMSG=1;            /*����һ�������Ҽ���Ϣ*/

  GetMouseXY();            /*��õ�ǰ���λ��,�������ݸ���MouseX,MouseY*/

  if(Mouse_On_Off==MouseStatusMouseOn)    /*ʵʱ��ʾ*/
     if(oldMouseX!=MouseX || oldMouseY!=MouseY)
     {
        MouseOff(oldMouseX,oldMouseY);
        MouseOn(MouseX,MouseY);
      }

  /*���˫�����ж�*/
  if(MouseMSG==3)            /*�����ͬʱ��������������Ҽ�*/
    MouseClickType=0;        /*��һ�εİ����ǼȲ���������Ҳ��������Ҽ�*/
  else if(MouseMSG==1)        /*����ǰ��������Ҽ�*/
  {
     if(MouseClickType==2)        /*�����һ��Ҳ�ǰ��������Ҽ�*/
     {
    NowMouseClickTime=clock();/*������ڵĳ�������ʱ��*/
    /*�ж���һ�ΰ��������Ҽ�����ΰ�������Ҽ���ʱ�����ǲ���С��������˫��ʱ����*/
    if(((NowMouseClickTime-LastMouseClickTime)/CLK_TCK)<=MouseDoubleClickTime)
         MouseMSG=6;        /*�����ϢΪ�Ҽ�˫��*/
    LastMouseClickTime=NowMouseClickTime;
     }
     else
     {
    MouseClickType=2;        /*��Ϊ��һ�εİ����ж�ʱ����һ�ΰ���״̬*/
    NowMouseClickTime=clock();   /*��Ϊ��һ�εİ����ж�ʱ����һ�ΰ���ʱ��*/
    LastMouseClickTime=NowMouseClickTime;
     }
   }
   else if(MouseMSG==2)
   {
    if(MouseClickType==1)
    {
        NowMouseClickTime=clock();/*������ڵĳ�������ʱ��*/
        /*�ж���һ�ΰ��������������ΰ�����������ʱ�����ǲ���С��������˫��ʱ����*/
        if(((NowMouseClickTime-LastMouseClickTime)/CLK_TCK)<=MouseDoubleClickTime)
        MouseMSG=7;    /*�����ϢΪ���˫��*/
        LastMouseClickTime=NowMouseClickTime;
    }
    else
    {
        MouseClickType=1;            /*��Ϊ��һ�εİ����ж�ʱ����һ�ΰ���״̬*/
        NowMouseClickTime=clock();    /*��Ϊ��һ�εİ����ж�ʱ����һ�ΰ���ʱ��*/
        LastMouseClickTime=NowMouseClickTime;
    }
   }

  return MouseMSG;        /*������갴����Ϣ:0--û�а���,1--�����Ҽ�, 2--�������,3--ͬʱ����������Ҽ�,           4--��ҷ���,5--��ҷ�Ҽ�,6--˫���Ҽ�,7--˫�����*/
}
void DisplayMsg(char * msg)
{   /*
    setcolor(RED);
    floodfill(10,400,WHITE);
    */
    outtextxy(10,400,msg);

}