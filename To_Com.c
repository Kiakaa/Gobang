#include "graphics.h"
#include "stdio.h"
#include "dos.h"
#include "time.h"
#include <conio.h>
#define closegr closegraph

#include "Mouse.c"
#include "doit.c"

#include "drawmat.c"

void main()
{
    int i=0;
    int key=0,p=0;
    int black=0,white=0;
    char * blac;
    char * whit;
    char * str="";
    char * bl;
    char * wh;
    int gdriver=DETECT,gmode,tempx,tempy,mouseMsg;
    initgraph(&gdriver,&gmode,"");

    for(i = 0; i < 4; i++)
    drawmat(xie64S+i*512 ,64,45, 100+i*80, 6);

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
        }

        mouseMsg=MouseStatus(!MouseStatusMouseOn);
       /*
    play();
         */


        if(mouseMsg!=0)
        {

            switch(mouseMsg)
            {


            /*

                case 1:
                    DisplayMsg("Right Button Clicked!");
                    break;
              */
                case 2:   for(pi=0;pi<15;pi++){
                  for(pj=0;pj<15;pj++)
                {
                    if ((MouseX>rel[pi][pj].lr)&&(MouseX<rel[pi][pj].rr)&&(MouseY>rel[pi][pj].ur)&&(MouseY<rel[pi][pj].dr))
                    {
                    MouseOff(MouseX,MouseY);
                        if(p%2==0)
                        {
                        downzi(pos[pi][pj].x,pos[pi][pj].y,p);
                        qp[(pos[pi][pj].y-29)/30][(pos[pi][pj].x-189)/30]=1;
                        white++;
                        flag=panying();
                        key=0;
                        p++;
                        }
                    MouseOn(MouseX,MouseY);
                     }
                  }
               }

              if(p%2==1)
                {

             cpuai();
             downzi(x,y,p);
             qp[(y-29)/30][(x-189)/30]=2;
             flag=panying();
             black++;
             p++;
               }

                     if(1==flag)
                {
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
                    if(2==flag)
                {
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

