#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"util5.h"
#include"util2.h"
void transfer(char accu[])
{
	FILE *fp;
	fp = fopen("t_file.txt","r");				//Opening the database that we have stored.
	int validity(char *acc,FILE *fp)			//Creating a function inorder to check the validity of the use entered account number.
	{
		char check[12];		
		while(fgets(check,12,fp)!=NULL)
		{
			if(strncmp(check,acc,11)==0)
			{
				fseek(fp,0,SEEK_SET);
				return 1;
			}
		}
		return 0;
	}
	char acct[13];			
	int amount,flag;		
	puts("Enter the account number to which you want to transfer money : ");
	scanf("%s",acct);		// Input of the account number of the person for whom the money should be transfered.
	while(validity(acct,fp)!=1)
	{
		puts("--No account found--\n ");
		printf("Do you want to try again ?\nEnter\n'1' for Yes\n'2' for No\n");
		scanf("%d",&flag);
		if(flag==0)
		{
			break;
		}
		printf("Enter the account number to which you want to transfer money : ");
		scanf("%s",acct);
		fseek(fp,0,SEEK_SET);
	}
	if(validity(acct,fp)==1 && strlen(acct)==11)
	{
		puts("Enter the amount you want to transfer:");
	        scanf("%d",&amount);
		printf("Amount is transferred to %s successfully",acct);
	}
        fclose(fp);
	debit(accu,amount);
	credit(acct,amount);
	st_trans(accu,acct,amount);
}
void range(char a[])
{
	int no_of_digits(int n)
	{
		int count;
		while(n!=0)
		{
			n = n/10;
			count++;
		}
		return count;
	}
	FILE *fp;
	int a1,a2;
	int fa1,fa2;
	char check[200],c='d';
	fp = fopen("t_file.txt","r");
	printf("Enter the range of amount you want to see\n");
	printf("Minimum : ");
	scanf("%d",&a1);
	printf("Maximum : ");
	scanf("%d",&a2);
	a[11]='A';
	a[12]='\0';
                while(fgets(check,200,fp)!=NULL)
                {
                        if(strncmp(check,a,12)==0)
			{
				
				while(fgets(check,200,fp)!=NULL)
				{
					unsigned k = ftell(fp);
                                        fgets(check,200,fp);
					if(strcmp(check,"\n")!=0)
					{	
						fseek(fp,k,SEEK_SET);
						k = ftell(fp);
						fseek(fp,21,SEEK_CUR);
						fscanf(fp,"%d",&fa1);
						fseek(fp,k,SEEK_SET);
						fgets(check,80,fp);
						if(fa1>=a1 && fa1<=a2 && check[0]=='1') 
						{
							printf("\n%s",check);	
						}
					}
					else
					{
						break;
					}
				}
			}

		}
	fclose(fp);
}
