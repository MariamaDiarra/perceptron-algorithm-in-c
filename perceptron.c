#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E 3
#define S 1
//#define DATA_FILE "Base.csv"

//fonction de calcul de la sortie o
int calculateOutput(float w[E][S], float x[])
{
    float sum = 0.0;
    int i, j;

    for (i = 0; i < E; ++i)
    {
    	for (j = 0; j < S; ++j)
    	{
    		sum += x[i] * w[i][j];
    	}
    }
    return (sum > 0) ? 1 : 0;
}

int main(int argc, char *argv[])
{
	
	float x[E];
	float w[E][S];
	int c;
	int o;
	int i, j;

	FILE *fp = fopen("iris.csv","r");
   int count=0;
   char buff[70];
	
   printf("Base d'apprentissage\n");

   for (i = 0; i < E; ++i)
   {
    	for (j = 0; j < S; ++j)
    	{
    		w[i][j] = 1;
    	}
   }

   o = calculateOutput(w, x);
   do
	{
	 
	 	fgets(buff, 70, (FILE*)fp);
	 	count++;
	 	if(count != 1)
	 	{
	  		char *token = strtok(buff,",");
	   		int counter=0 ,i=0;
	   		while( token != NULL ) 
	   		{
		 		counter++; 
		 		if (counter !=1)
		 		{
		 		//	printf( " %s\n",token);
		 			if (counter < 5)
	 				{
				 		sscanf(token,"%f",&x[i]);
				 		printf("x[%d] = %f ",i,x[i] );
				 		i++;
				 	}
		    		else{
				    	if (counter ==6)
					 	{
					 		sscanf(token,"%d",&c);
					 		printf("c = %d \n",c);
					 		
				    		i=0;
					 	}
		    		}
		 		}
		 		token = strtok(NULL,",");
			}	  
		}
      for (i = 0; i < E; i++) 
      {
        	for (j = 0; j < S; ++j)
        	{
        		w[i][j] += (c - o) * x[i];
        	}
      }
      o = calculateOutput(w, x);

      printf("Iteration %d : sortie o = %d \n", count, o);
	 	printf("\nPerceptron : P(");
		for (i = 0; i < E; ++i)
		{
			for (j = 0; j < S; ++j)
			{
				printf("%f ", w[i][j]);
			}
		}
		printf(")");
	
	}while(!feof(fp));

    
    fclose(fp);

    printf("\n\nBase de test\n");

    while(1){
    	x[0]=1;
	    printf("\nLongueur du sépal: ");
	    scanf("%f", &x[1]);
	    printf("\nLongueur du pétal: ");
	    scanf("%f", &x[2]);
	    o = calculateOutput(w, x);
	    if (o == 0)
	    {
	    	printf("Iris-setosa\n");
	    }
	    else
	    	printf("Iris-versicolor\n");
    
    }
	return 0;
}