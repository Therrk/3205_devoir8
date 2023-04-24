/*------------------------------------------------------*/
/* Prog    : Tp10_IFT3205.c                             */
/* Auteur  : Élie Leblanc, Justin Veilleux              */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/
// elie.leblanc@umontreal.ca


/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo10.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER_IMG "./display "
#define NAME_VISUALISER     "./ViewSig.sh "

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/

/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
 {
  int i,j,n;
  char BufSystVisuSig[100];
  int length;

  //=================================================
  //Question 2.1
  //------------
  //
  // Sample Rate = 11025 ech/sec
  // Frequence �chant= 11025
  //
  //  
  //=================================================

  float*  SignX=LoadSignalDat("SOUND_GoodMorningVietnam",&length);
  float*  SignY=fmatrix_allocate_1d(length);
  float  fm,fb,c,c_inter,d;


  //--------------------------------
  //Restauration  �quation R�curente
  //--------------------------------
  // 
  // y(n) = x(n) + G . x(n-Retard)
  //
  //--------------------------------

  float SamplingRate=11025;
  for(n=0;n<length;n++){
    fm=2000+1000*sin(2*PI*(((float)n)/SamplingRate));
    fb=fm/10;
    d=-cos(2*PI*fm/SamplingRate);
    c_inter = tan(PI*fb/SamplingRate);
    c=(c_inter-1)/(c_inter+1);
    switch (n) {
	    case 0:
	      SignY[n]=SignX[n]*(1+c)/2;
		  break;
      case 1:
	      SignY[n]=(SignX[n]*(1+c)/2)-d*(1-c)*SignY[n-1];
	    break;
	    default:
	      SignY[n]=((SignX[n]-SignX[n-2])*(1+c)/2)-(d*(1-c)*SignY[n-1])+(c*SignY[n-2]);
		  break;
    }
  }
     
   //Sauvegarde
   SaveSignalDatWav("passe_bande",SignY,length,SamplingRate); 
   //SaveSignalDat("SOUND_GoodMorningVietnam1",SignY,length);
 
   //Visu
   //strcpy(BufSystVisuSig,NAME_VISUALISER);
   //strcat(BufSystVisuSig,"SOUND_GoodMorningVietnam1.dat&");
   //printf(" %s",BufSystVisuSig);
   //system(BufSystVisuSig);
       
 
  //==End=========================================================

  //retour sans probleme
  printf("\n C'est fini ... \n\n");
  return 0; 	 
}


