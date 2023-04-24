/*------------------------------------------------------*/
/* Prog    : Tp10_IFT3205.c                             */
/* Auteur  : Élie Leblanc, Justin Veilleux              */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/
// elie.leblanc@umontreal.ca justin.veilleux@umontreal.ca


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
  for (int i = 0; i < length;i++) {
      SignY[i] = 0.0;
  }

  //--------------------------------
  //Restauration  �quation R�curente
  //--------------------------------
  // 
  // y(n) = x(n) + G . x(n-Retard)
  //
  //--------------------------------

  float SamplingRate=11025;

  float f_L = 3.0;
  float η = 0.9;
  float μ = 0.5;
  float f = 1.0;

  for(int t=0;t<length;t++){
      float sum = 0.0;
      for (int n = 1;n < length;n++) {
          float k = (1 - η * sin(2 * PI * f_L * t) * sin(n * f * (2 * PI * t - μ * sin(2 * PI * f_L * t)) / f_L));
          k += (1 + η * sin(2 * PI * f_L * t) * sin(n * f * (2 * PI * t + μ * sin(2 * PI * f_L * t)) / f_L));
          sum += SignX[t] * k;
      }
      SignY[t] = sum;
  }
     
   //Sauvegarde
   SaveSignalDatWav("leslie",SignY,length,SamplingRate); 
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


