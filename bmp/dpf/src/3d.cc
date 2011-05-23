/* Note:Your choice is C IDE */
#include <stdio.h>
#include "graphics.h"
#include  <math.h>
void hua(int T[8][3])
{
   moveto(T[0][0]/T[0][2],T[0][1]/T[0][2]);
   lineto(T[1][0]/T[1][2],T[1][1]/T[1][2]);
   lineto(T[2][0]/T[2][2],T[2][1]/T[2][2]);
   lineto(T[3][0]/T[3][2],T[3][1]/T[3][2]);
   lineto(T[0][0]/T[0][2],T[0][1]/T[0][2]);
   moveto(T[4][0]/T[4][2],T[4][1]/T[4][2]);
   lineto(T[5][0]/T[5][2],T[5][1]/T[5][2]);
   lineto(T[6][0]/T[6][2],T[6][1]/T[6][2]);
   lineto(T[7][0]/T[7][2],T[7][1]/T[7][2]);
   lineto(T[4][0]/T[4][2],T[4][1]/T[4][2]);
   moveto(T[0][0]/T[0][2],T[0][1]/T[0][2]);
   lineto(T[4][0]/T[4][2],T[4][1]/T[4][2]);
   moveto(T[1][0]/T[1][2],T[1][1]/T[1][2]);
   lineto(T[5][0]/T[5][2],T[5][1]/T[5][2]);
   moveto(T[2][0]/T[2][2],T[2][1]/T[2][2]);
   lineto(T[6][0]/T[6][2],T[6][1]/T[6][2]);
   moveto(T[3][0]/T[3][2],T[3][1]/T[3][2]);
   lineto(T[7][0]/T[7][2],T[7][1]/T[7][2]);
}
/*/////////////////////////////////////////////////////////////////////////*/
void x(int T[8][3],float af)
{   int i;
    float theta   =0.00017* af;

   for(i=0;i<8;i++)
             {

                    T[i][0]=T[i][0];
                    T[i][1]=T[i][0]*0+T[i][1]*cos(theta)+T[i][2]*(-sin(theta));
                    T[i][2]=T[i][0]*0+T[i][1]*sin(theta)+T[i][2]*cos(theta);
             }
   hua(T);
}
/*//////////////////////////////////////////////////////////////////////*/
void y(int T[8][3],float af)
{   int i;
    float theta   =0.00017* af;

   for(i=0;i<8;i++)
          {

                T[i][0]=T[i][0]*cos(theta)+T[i][2]*sin(theta);
                T[i][1]=T[i][1];
                T[i][2]=T[i][0]*(-sin(theta))+T[i][2]*cos(theta);
          }
   hua(T);
}
/*/////////////////////////////////////////////////////////////////////////*/
void z(int T[8][3],float af)
{   int i;
    float theta   =0.00017* af;

   for(i=0;i<8;i++)
              {
                     T[i][0]=T[i][0]*cos(theta)+T[i][1]*(-sin(theta));
                     T[i][1]=T[i][1]*sin(theta)+T[i][1]*cos(theta);
                     T[i][2]=T[i][2];
              }
  hua(T);
}
/*//////////////////////////////////////////////////////////////*/
void projection(int T[8][3],float af,float af1)
{
  int i;
  float theta   =0.017* af;
  float theta1   =0.017* af1;

  for(i=0;i<8;i++)
           {

               T[i][0]=T[i][0]*cos(theta)+T[i][1]*(-sin(theta));
               T[i][1]=0;
               T[i][2]=T[i][0]*(-sin(theta)*sin(theta1))+T[i][1]*(-cos(theta)*sin(theta1))+T[i][2]*cos(theta1);
           }
 hua(T);
}
/*////////////////////////////////////////////////////////////////////*/
void perspective(int T[8][4],float af,float af1,float q)
{
  int i;
  float theta   =0.017* af;
  float theta1   =0.017* af1;

  for(i=0;i<8;i++)
        {

                T[i][0]=T[i][0]*cos(theta)+T[i][1]*(-sin(theta));
                T[i][1]=0;
                T[i][2]=T[i][0]*(-sin(theta)*sin(theta1))+T[i][1]*(-cos(theta)*sin(theta1))+T[i][2]*cos(theta1);
                T[i][3]=T[i][0]*q*sin(theta)*cos(theta1)+T[i][1]*q*cos(theta)*cos(theta1)+T[i][2]*q*sin(theta1)+T[i][3];
         }
 hua(T);
}
/*//////////////////////////////////////////////////////////////////////*/
void Zperspective(int T[8][3])
{
  int i;

  for(i=0;i<8;i++)
       {
              T[i][0]=T[i][0]*0.707+T[i][1]*(-0.707);
              T[i][1]=0;
              T[i][2]=T[i][0]*(-0.408)+T[i][1]*(-0.408)+T[i][2]*(0.816);
        }
  hua(T);
}
/*==============================================================================================================*/
int three()
{

 int gdriver=DETECT,gmode;
 int T[8][3]={530,390,1,500,420,1,560,420,1,590,390,1,530,450,1,500,480,1,560,480,1,590,450,1};
 int TT[8][3]={80,50,1,50,80,1,110,80,1,140,50,1,80,110,50,140,110,140,140,110,80,110,1};
 float af,af1,q;


 initgraph(&gdriver,&gmode,"");
 cleardevice();
 setbkcolor(9);setcolor(4);
 hua(T);

             printf("input af:");
             scanf("%f",&af);
             x(T,af);
 /*****************************/
             printf("input af:");
             scanf("%f",&af);
             x(T,af);
 /*****************************/
             printf("input af:");
             scanf("%f",&af);
             x(T,af);
 /*****************************/
             printf("input af:");
             scanf("%f",&af);
             y(T,af);
 /*****************************/
             printf("input af:");
             scanf("%f",&af);
             z(T,af);
 /*****************************/
     /*
            printf("input af,af1:");
            scanf("%f%f",&af,&af1);
            projection(T,af,af1);
            printf("input af,af1,q:");
            scanf("%f%f%f",&af,&af1,&q);
            perspective(T,af,af1,q);
            Zperspective(T);
       */     
 getch();
 closegraph(); 
 return 0;
}
