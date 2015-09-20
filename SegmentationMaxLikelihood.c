#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Function.h"

int main(int argc, char *argv[])
{
  int i,j,NB;
  int seuilMV;
  float mean0,mean1,var0,var1,sum0,sum1,count0,count1,k,l;
  float mean0new,mean1new,var0new,var1new; 
  float prob0,prob1;
  int length,width;

  float** y;  
  float** x;  
  
  y=LoadImagePgm(argv[1],&length,&width);
  x=fmatrix_allocate_2d(length,width);
 
  /*k-means */
  mean0=90; mean1=100; NB=0;

  do{
  	sum1=0;sum0=0;
	count1=0;count0=0;

	k=mean0; l=mean1;
	for(i=0;i<length;i++){
		for(j=0;j<width;j++){
			if(powf(y[i][j]-mean0,2)>powf(y[i][j]-mean1,2)){
				x[i][j]=1;
			}
			else if(powf(y[i][j]-mean0,2)<powf(y[i][j]-mean1,2)){
				x[i][j]=0;
			}
			else{
				x[i][j]=(0||1);
			}
		}
 	}		
		
	for(i=0;i<length;i++){
		for(j=0;j<width;j++){
			if(x[i][j]==1){
				sum1=sum1+y[i][j];
				count1++;
			}
			else {
				sum0=sum0+y[i][j];
				count0++;
			}
		}
	}

	NB++;
	mean0=sum0/count0; mean1=sum1/count1;
	printf("%d\tmean0=%f\tmean1=%f\t\n",NB,mean0,mean1);

    }while(mean1!=l||mean0!=k);

    sum1=0;sum0=0;count1=0;count0=0; 

    for(i=0;i<length;i++){
	 for(j=0;j<width;j++){
	      if(x[i][j]==1){
		    sum1=sum1+powf(y[i][j]-mean1,2);
		    count1++;
	      }
	      if(x[i][j]==0){
		    sum0=sum0+powf(y[i][j]-mean0,2);
		    count0++;
	      }
	 }
    }	

    var1=sum1/count1; var0=sum0/count0;
	    
    /*Maximum Likelihood*/
    for(i=0;i<length;i++){
 	for(j=0;j<width;j++){
	     prob0 = prob(y[i][j],mean0,var0);	
	     prob1 = prob(y[i][j],mean1,var1);
     
	     if(prob0<prob1) x[i][j]=1;
	     else x[i][j]=0;
	}
    }

    for(i=0;i<length;i++){
 	for(j=0;j<width;j++){
	     if(x[i][j]==1) x[i][j]=255;
	     else x[i][j]=0;
	}
    }

    Recal(x,length,width);
    SaveImagePgm("image_name",x,length,width);
    
    free_fmatrix_2d(x);
    free_fmatrix_2d(y);
  
    system("display image_name.pgm&"); 
  
    printf("\n Ending ... \n\n\n");
    return 0; 	 
}

