#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"util5.h"
int check(char *Account_Number)
{
 char Password[100];
 char z[100];
 int i=1,op;
 FILE *fp;
 fp=fopen("file1.txt","r");
 fgets(z,100,fp);
 while(1)
 {
 	if(feof(fp) || strlen(Account_Number)!=11)
 	{
                printf("Incorrect Account Number\nEnter\n");
  		printf("'1' to RETRY\n");
  		printf("'2' to QUIT : ");
  		scanf("%d",&op);
  		if (op==1)
  		{
     			printf("Enter your Account Number");
     			scanf("%s",Account_Number);
     			fseek(fp,0,SEEK_SET);
			fgets(z,100,fp);
     		}
	        if (op==2)
                {
                 printf("Exiting\n");
		 fclose(fp);
                 return 0;
                }
 	}	 
 	if(strncmp(Account_Number,z,11)!=0)
 	{
  		for(i=0;i<7;i++)
  		{
  			fgets(z,100,fp);
  		}		
 	}
        else if (strncmp(Account_Number,z,11)==0 && strlen(Account_Number)==11)
        {
          break;
        }
 }
        if (strncmp(Account_Number,z,11)==0)
 	{
    		printf("Password : \n");
  		scanf("%s",Password);
  		fgets(z,100,fp);
 		while (strncmp(Password,z,strlen(Password))!=0)
		{
			printf("The password you have entered is incorrect\n");
  			printf("'1' to RETRY\n");
  			printf("'2' to QUIT : ");
	   		scanf("%d",&op);
  			if (op==1)
  			{
   				printf("Enter you Password:");
	   			scanf("%s",Password);
  			}
			if(op==2)
			{
				printf("Exiting\n");
				fclose(fp);
				return 0;
			}
 		}
		fclose(fp);
		return 1;
 	}
}
void loans(char Account_Number[])

{

 printf("Select option for loan\n");

 printf("1.EDUCATION LOAN\n");

 printf("2.HEALTH LOAN\n");

 printf("3.HOME LOAN\n");

 printf("4.CAR LOAN\n");

 int p,q;


 scanf("%d",&p);

 printf("INTEREST:10.25PERCENT\n");

 printf("CHOOSE OPTION\n");

 printf("1.ACCEPTED  ");

 printf("2.NOT ACCEPTED\n");

 scanf("%d",&q);
 
 if (q!=1)

 {

  printf("YOUR LOAN IS NOT GRANTED\n");
  
 }

 if(q==1)

 {

  int AMOUNT;

  printf("AMOUNT:");

 scanf("%d",&AMOUNT);

  switch(p)

  {

   case 1:

    printf ("YOUR EDUCATION LOAN IS GRANTED\n");

    break;

   case 2:

    printf ("YOUR HEALTH LOAN IS GRANTED\n");

    break;

   case 3:

    printf ("YOUR HOAM LOAN IS GRANTED\n");

    break;

   case 4:

    printf ("YOUR CAR LOAN LOAN IS GRANTED\n");

    break;

  }
  credit(Account_Number,AMOUNT);
 }

}
  



