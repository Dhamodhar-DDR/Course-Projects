#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util2.h"

void edit(char acc[])
{
	char str[20], change[30];

	int i, op;
	
	FILE *f1, *f2;
 
	printf("1: Change the Password\n");

	printf("2: Change the Username\n");

	printf("3: Change the Age\n");

	printf("4: Change the Gender\n");

	printf("Enter the number:");

	scanf("%d", &op);

	if(op==1)
          
          printf("Enter the New Password:");

        if(op==2)

	  printf("Enter the New username:");

	if(op==3)

	  printf("Enter the New Age:");

	if(op==4)

	  printf("Enter the New Gender:");

	f1 = fopen("file1.txt","r");

	f2 = fopen("file2.txt","a");

	while(fgets(str,20,f1) != NULL )
	{
		if(strncmp(acc,str,11) == 0)
		{
			fputs(str,f2);
			break;
		} 
		else  
		{
			fputs(str,f2);
		}		                   	
	}
	for(i=0;i<(op-1);i++)
	{
		fgets(str,20,f1);
		fputs(str,f2);
	}

	scanf("%s",change);

	fputs(change,f2);
	
	fprintf(f2,"\n");

	fgets(str,20,f1);
		
	for(i=0;i<=(3-op);i++)
	{
		fgets(str,20,f1);
		fputs(str,f2);
	}

	while(fgets(str,20,f1) != NULL )
	{
		fputs(str,f2);
	}
					   
	remove("file1.txt");		                   
	rename("file2.txt","file1.txt");
        fclose(f1);
	fclose(f2);
}
void delete_account(char acnt[])
{
  FILE *fp1,*fp2;
  char ch[20],pw[20];
  fp1=fopen("file1.txt","r");
  fp2=fopen("file3.txt","w");
  printf("As you have decided to forfeit our bank,you need to follow few basic steps\n");
  printf("enter your account password:\n");
  scanf("%s",pw);
  while(strncmp(fgets(ch,20,fp1),acnt,11))
  {
    fputs(ch,fp2);
  }
  
  fgets(ch,20,fp1); 
  
  if(!strncmp(ch,pw,strlen(pw)))
  {
   for(int i=0 ; i<5 ; i++)
   {
    fgets(ch,20,fp1);
   } 
   while(fgets(ch,20,fp1)!= NULL)
   {
	fputs(ch,fp2);	   
   }
	     fclose(fp1);
     fclose(fp2);
     remove("file1.txt");
     rename("file3.txt","file1.txt"); 

	char v;
	FILE *fp7 = fopen("file1.txt","r");
	fseek(fp7,-2,SEEK_END);
	int count = ftell(fp7);
	v = fgetc(fp7);
	fclose(fp7);
	FILE *fp5 = fopen("file1.txt","r");
	FILE *fp4 = fopen("file6.txt","a");
	if(v=='\n')
	{
		while(ftell(fp5)!=count)
		{
			v = fgetc(fp5);
			fputc(v,fp4);	
		}
		fputc('\n',fp4);
	remove("file.txt");
	rename("file6.txt","file1.txt");
	}
	else{
	fclose(fp5);
        fclose(fp4);
	remove("file6.txt");
	}
	del_trans(acnt);
	printf("Hope you enjoyed the experience in our bank!!");
  }
  else
  {
    while(strncmp(ch,pw,strlen(pw)))
    {
      printf("The entered password is incorrect.Please re-enter it:\n");
      scanf("%s",pw);
    }
  }

}

