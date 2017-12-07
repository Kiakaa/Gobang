#include "stdio.h"
#include "dos.h"
int main(void)
{
  int i, j;
  int ch;
  ch='';
  printf("Challenge yourself or Challenge yourself the computer ?\nYouselft:M\nComputer:C\nSay bye:Any other key\n");
  printf("[M] [C] [Anykey]?:");
  ch=getch();
  while(ch!='n'||ch!='N')
  {

  if(ch=='M'||ch=='m')
  system("To_Per.bat");
  if(ch=='C'||ch=='c')
  system("To_Com.bat");
  if(ch!='M'&&ch!='m'&&ch!='C'&&ch!='c')
  return 0;
    printf("\nAgain \n[M] [C] [Anykey]?:");

      ch=getch();

   }

   getch();
  return 0;
}

