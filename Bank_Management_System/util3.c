#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"util2.h"
int create_account()
{
  FILE *fp;
  char nm[20],pw[15],gd[6],r[2],a[2],am[15],ch[20],dp[20],ag[3];
  int i;
  long int amnt,acnt;

  fp=fopen("file1.txt","r");
	  
  printf("Enter your user name (not more than 20 characters,spaces not allowed) : \n");

  scanf("%s",nm);

  printf("Enter the password(not more than 15 characters,spaces not allowed) : \n");
  
  scanf("%s",pw);
  
  printf("Please enter your gender : \n");
  
  scanf("%s",gd);
  
  printf("Please enter your age : \n");
  
  scanf("%s",ag);
  
  printf("You are one step away from opening account in our bank!!\n");
  
  printf("In order to open an account in our bank the minimum bank balance is 5,000 Rupees \n");
  
  printf("Do you still wish to continue?(Enter Y/N):\n");
  
  scanf("%s",r);  

  if(strcmp(r,"Y")==0 || strcmp(r,"y")==0)
  {
    printf("Enter the amount you want to credit to open the account:\n");
    scanf("%ld",&amnt);
    while(amnt<5000)
    {
      printf("The entered amount is less than the required amount\n");
      printf("Please re-enter the amount:\n");
      scanf("%ld",&amnt);
    }  
    while(fgets(ch,20,fp)!=NULL) 
    {
     if(strcmp(ch,"\n")==0)
     {
	     fgets(ch,20,fp);
     }
     
     for(i=0; i<11 ; i++)
     {
       dp[i]=ch[i];
     }
     dp[i]='\n';
     
     for(i=0 ; i < 5 ; i++)
     {
       fgets(ch,20,fp);
     }        
    }
    
    acnt=atol(dp)+1;
    sprintf(ch,"%ld",acnt); 
    printf("Your bank account number is %s \n",ch);
    fp=fopen("file1.txt","a");
    fprintf(fp,"\n");
    fprintf(fp,"%s\n",ch);
    fprintf(fp,"%s\n",pw);
    fprintf(fp,"%s\n",nm);
    fprintf(fp,"%s\n",ag);
    fprintf(fp,"%s\n",gd);
    fprintf(fp,"%ld\n",amnt); 
    fclose(fp);	
    newst_trans(ch,nm);
    printf("Thanks for crediting the amount\n");
    printf("Your account has been created,CONGRATULATIONS!!\n");
    return 1;
  }
  
  else
  {
    printf("As you have decided to discontinue, your account is NOT created\n");
    printf("We wish to see you some other day in our bank,THANK YOU!!");
    return 0;
  }
	
}
void view (char acc[])
{
	char det[20], str[15];

	int i;
	
	FILE *fp;
 
	fp = fopen("file1.txt","r");

	while(fgets(str,15,fp) != NULL )
	{
		if(strncmp(acc,str,11) == 0)
		{
			break;
		}                      
	}
	printf("\nYour Profile :-\n");
	printf("\nAccount Number  : %s\n\n",acc);

	fgets(str,15,fp);
	
		fgets(det,100,fp);

		printf("Name            : %s\n",det);
		fgets(det,100,fp);	

		printf("Age             : %s\n",det);
		fgets(det,100,fp);

		printf("Gender          : %s\n",det);
		fgets(det,100,fp);

		printf("Account Balance : Rs.%s\n",det);
	fclose(fp);
}


