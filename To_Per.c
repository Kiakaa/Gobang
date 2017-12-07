#include "graphics.h"
#include "stdio.h"
#include "dos.h"
#include "time.h"
#define ESC 0X11b
#include "graphics.h"            /*图形系统头文件*/
#include <conio.h>
#define closegr closegraph

#include "Mouse.c"
#include "doit.c"

#include "drawmat.c"
void main()
{
    int i=0;
    int key=0,p=2,q=3;
    int black=0,white=0;
    char * blac;
    char * whit;
    char * str="";
    char * bl;
    char * wh;
    int gdriver=DETECT,gmode,tempx,tempy,mouseMsg;
    initgraph(&gdriver,&gmode,"");

     drawmat(f64Y + i * 32, 64,45 , 20, 6);
    for(i = 0; i < 6; i++)
     drawmat(f16S, 16,10+32*i, 90, i+1);
    for(i = 0; i < 3; i++)
    drawmat(sm16S + i * 32, 16,10 + i * 15, 120, 6);
    for(i = 0; i < 5; i++)
    drawmat(sm16S + (i+3) * 32, 16,10 + i * 15, 150, 6);
    for(i = 0; i < 5; i++)
    drawmat(sm16S + (i+8) * 32, 16,10 + i * 15, 180, 6);

    for(i = 0; i < 4; i++)
    drawmat(xie64S+i*512 ,64,45, 210+i*64, 6);

    MountMouse();
    SetMouseHoriBound(0,600);
    SetMouseVertBound(0,450);

    SetMouseXY(150,3);
    tempx=150;
    tempy=3;
    MouseOff(tempx,tempy);

            setbkcolor(0);
      drawqp();
    while(1)
    {

        GetMouseXY();
         if(tempx!=MouseX||tempy!=MouseY)
        {
            MouseOff(tempx,tempy);
            MouseOn(MouseX,MouseY);
            tempx=MouseX;
            tempy=MouseY;
            DisplayMsg("                    ");
        }

        mouseMsg=MouseStatus(!MouseStatusMouseOn);
       /*
    play();
         */


        if(mouseMsg!=0)
        {
         if(tempx!=MouseX||tempy!=MouseY)
        {
            MouseOff(tempx,tempy);
            MouseOn(MouseX,MouseY);
            tempx=MouseX;
            tempy=MouseY;
            DisplayMsg("                    ");
        }

            switch(mouseMsg)
            {

                case 1:
                setcolor(0);
               for(pi=0;pi<15;pi++){
                  for(pj=0;pj<15;pj++)
                {
                    if ((MouseX>rel[pi][pj].lr)&&(MouseX<rel[pi][pj].rr)&&(MouseY>rel[pi][pj].ur)&&(MouseY<rel[pi][pj].dr))
                    {
                    MouseOff(MouseX,MouseY);
                        if ((qp[(pos[pi][pj].y-29)/30][(pos[pi][pj].x-189)/30]!=1)&&(p%2!=0))

                        {
                        downzi(pos[pi][pj].x,pos[pi][pj].y,p);
                        qp[(pos[pi][pj].y-29)/30][(pos[pi][pj].x-189)/30]=2;
                        p++;

                        black++;

                        flag=panying();
                        key=0;
                        }
                    MouseOn(MouseX,MouseY);
                     }
                  }
               }       if(2==flag)
                {
                setcolor(4);
                 settextstyle(0,0,3);
                 outtextxy(240,220,"The black win");
                 outtextxy(160,260,"Press anykey to quit");

                 UnmountMouse();
                 getch();
                 goto end;
                /*
                 return ;
                 */
                }
                    break;

                case 2:
                setcolor(15);
                for(pi=0;pi<15;pi++){
                  for(pj=0;pj<15;pj++)
                {
                    if ((MouseX>rel[pi][pj].lr)&&(MouseX<rel[pi][pj].rr)&&(MouseY>rel[pi][pj].ur)&&(MouseY<rel[pi][pj].dr))
                    {
                    MouseOff(MouseX,MouseY);
                         if ((qp[(pos[pi][pj].y-29)/30][(pos[pi][pj].x-189)/30]!=2)&&(p%2==0))
                        {
                        downzi(pos[pi][pj].x,pos[pi][pj].y,p);
                        qp[(pos[pi][pj].y-29)/30][(pos[pi][pj].x-189)/30]=1;
                         p++;

                        white++;

                        flag=panying();
                        key=0;
                        }
                    MouseOn(MouseX,MouseY);
                     }
                  }
               }

                     if(1==flag)
                {
                setcolor(4);
                 settextstyle(0,0,3);
                 outtextxy(240,220,"The white win");
                 outtextxy(160,260,"Press anykey to quit");
                 UnmountMouse();
                 getch();
                 goto end;
                 /*
                 return ;
                 */
                 }

                /*
                 gotoxy(10,400);
                  printf("Black:%d White:%d",black,white);
                  */
                  /*
                  strcat(str,"Black");
                  bl=itoa(black,blac,10);
                  strcat(str,bl);
                  wh=itoa(white,whit,10);
                  strcat(str,wh);
                  moveto(10,400);

                  outtext(str);
                  */
                    /*

                    DisplayMsg("Left Button Clicked!");
                    */
                    break;
               /*
                case 3:
                    DisplayMsg("Both Buttons Down!");
                    break;
                case 4:
                    DisplayMsg("Left Button Dragging!");
                    break;
                case 5:
                    DisplayMsg("Right Button Dragging!");
                    break;
                case 6:
                    DisplayMsg("Right Button Double Clicked!");
                    break;
                case 7:
                    DisplayMsg("Left Button Double Clicked!");
                    break;
                    */

            }

                  /*
                  DisplayMsg(str);
                  */

        }

        Timer(1000);


    }

end:    UnmountMouse();
    closegraph();
}

