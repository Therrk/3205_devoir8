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
  float fm = 500.0;
  float fe = 11025.0;
  float fb = 1.0;
  float d=-cos(2*PI*fm/fe);
  float c_inter = tan(PI*fb/fe);
  float c = (c_inter-1)/(c_inter+1);

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

  // on veut trouver le n0 pour que la différence de fréquence soit de
  // 784 Hz, comme on as 11025 échantillons par seconde, 11025/784 = 14

  float SamplingRate=11025;
  SignY[0] = SignX[0]*(1+c)/2;
  SignY[1] = (SignX[1]*(1+c)/2)-d*(1-c)*SignY[0];
  for(n=2;n<length;n++){
    SignY[n] = ((SignX[n]-SignX[n-1])*(1+c)/2)-(d*(1-c)*SignY[n-1])+(c*SignY[n-2]);
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


