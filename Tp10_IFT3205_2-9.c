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


  //--------------------------------
  //Restauration  �quation R�curente
  //--------------------------------
  // 
  // y(n) = x(n) + G . x(n-Retard)
  //
  //--------------------------------

  float SamplingRate=11025;

  for(n=0;n<length;n++){

      float k = 0;
      float alpha[3] = {1, 3, 4};
      for (int m = 0;m < 3;m++) {
          k += alpha[m] * sin(2 * PI * m * 440 * n / SamplingRate + 7 * sqrt((float)m) * sin(2 * PI * 5 * n / SamplingRate));
      }

      SignY[n] = SignX[n] * k;
    
  }
     
   //Sauvegarde
   SaveSignalDatWav("vibrato",SignY,length,SamplingRate); 
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


