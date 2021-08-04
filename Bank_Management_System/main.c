#include<stdio.h>
#include<string.h>
#include "util7.h"
#include "util4.h"
#include "util3.h"
#include "util5.h"
#include "util2.h"
#include "util6.h"
int main()
{
	printf("\n                                   Welcome to ###### Bank Management System\n\n");
	int user,flag1 = 2,flag2 = 1,amount,flag3,flag4;
	printf("Are you an existing user or a new user\nEnter \n\n'1' If you are an existing user \n\n'2' If you are a new user : \n");
	scanf("%d",&user);
	if(user == 2)
	{
	      flag1 = create_account();
	}
	if(flag1 == 1 || flag1 == 2)
	{     
		if(flag1 == 1)
		{
			printf("Do you want to open your account details.\nEnter\n'1'for Yes\n'0'for No\n");
			scanf("%d",&flag2);
		}
		if(flag2 == 1)
		{
		char Account_number[20],Password[20];
		printf("Enter your Account Number:\n");
		scanf("%s",Account_number);
		if(check(Account_number)==1)
		{		
			while(1)
			{
				int choice;
				printf("\n1. View Profile\n\n2. Credit Money\n\n3. Withdraw Money\n\n");
				printf("4. Edit Profile\n\n5. View Transactions\n\n6. Transfer Money\n\n7. Loans\n\n8. Delete Account\n\n");
				printf("0. QUIT\n\nEnter your option : ");
				scanf("%d",&choice);
				switch(choice)
				{
					case 1:
						view(Account_number);
						break;
					case 2:
						printf("Enter the amount you want credit into your account : ");
						scanf("%d",&amount);						
						credit(Account_number,amount);
						break;
					case 3:
						printf("Enter the amount you want withdraw from your account : ");
						scanf("%d",&amount);	
						debit(Account_number,amount);
						break;
					case 4:
						edit(Account_number);
						break;
					case 5:
						printf("Enter\n'1' to show transactions with respect to date\n'2' to show transactions with respect to amount transferred\n");
						scanf("%d",&flag3);
						if(flag3==1)
						{
							sh_trans(Account_number);
						}
						if(flag3==2)
						{	
							printf("Enter\n'1' to show transactions between a given range of money\n");
							printf("'2' to view the transaction that has maximum amount transfered\n");
							printf("'3' to view the transaction that has minimum amount transferred\n.");
							printf("'0' to Go Back");
							scanf("%d",&flag4);
							switch (flag4)
							{
						         	case 1: range(Account_number);
									break;
								case 2: max(Account_number);
									break;
								case 3: min(Account_number);	
									break;
								case 0: break;
							}
						}
						break;
					case 6:
						transfer(Account_number);
						break;
					case 7:
						loans(Account_number);
						break;
					case 8:
						delete_account(Account_number);
						break;		
				}
				if(choice == 0||choice ==8)
				{
					break;
				}
			}
		}
		else
		{
			
		}
	}
	}	
	return 0;
}
