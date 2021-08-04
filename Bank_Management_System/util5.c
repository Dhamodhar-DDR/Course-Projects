#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void credit(char accnumber[],int amount)
{
   char str[15],am[15]="\n",pwd[15];
   FILE *f1,*f2;
   int i,j,m;
   f1=fopen("file1.txt","r");
   f2=fopen("file2.txt","a");
   while(1)
   {  
      fgets(str,15,f1);
      fputs(str,f2);      
      if(feof(f1))
      {
	 printf("Account number not found");  	 
         break;
      }
      else
      {
	if(!strncmp(accnumber,str,11))
	{		
	      j=0;
              while(j<5)
              {
                fgets(str,15,f1);
	        if(j<4)
	        {
	           fputs(str,f2);
	        }	
	        j++;
	      }  
              m=atoi(str);
              m=m+amount;
	      sprintf(str,"%d",m);
	      fputs(str,f2);
	      fputs(am,f2);
	      printf("\nAmount credited"); 
	      break;
	}
        else
	{		
           i=0;		
	   while(i<6)
	   {
	     fgets(str,15,f1);
	     fputs(str,f2);
	     i++;
           }
        }
      }
   }
   while(fgets(str,15,f1)!=NULL)
   {	   
      fputs(str,f2);      
   } 
   remove("file1.txt");
   rename("file2.txt","file1.txt"); 
   fclose(f1);
   fclose(f2);
}   

void debit(char accnumber[],int amount)
{
   char str[15],am[15]="\n",pwd[15];
   FILE *f1,*f2;
   int i,j,m;
   f1=fopen("file1.txt","r");
   f2=fopen("file2.txt","a");
   while(1)
   {
      fgets(str,15,f1);
      fputs(str,f2);
      if(feof(f1))
      {
         printf("Account number not found");
         break;
      }
      else
      {
        if(!strncmp(accnumber,str,11))
        {
              j=0;
              while(j<5)
              {
                fgets(str,15,f1);
                if(j<4)
                {
                   fputs(str,f2);
                }
                j++;
              }
              m=atoi(str);
              m=m-amount;
	      if(m>0)
	      {	      
                 sprintf(str,"%d",m);
	         fputs(str,f2);
                 fputs(am,f2);
                 printf("Amount debited");
                 break;
	      }
	      else
	      {
	         printf("No Sufficient Funds");
                 break;
              }		 
        }
        else
        {
           i=0;
           while(i<6)
           {
             fgets(str,15,f1);
             fputs(str,f2);
             i++;
           }
        }
      }
   }
   while(fgets(str,15,f1)!=NULL)
   {
     fputs(str,f2);
   }
   remove("file1.txt");
   rename("file2.txt","file1.txt");
   fclose(f1);
   fclose(f2);
}          

void max(char acc[])
{  
char str[150];
   int n,p=0,g,k,count=0;   
   acc[11]='A';
   acc[12]='\0';
   FILE *f1;
   char a;
   f1=fopen("t_file.txt","r");
   while(fgets(str,150,f1)!=NULL)
   {	   	
	   if(strncmp(acc,str,12)==0)
	   {
	   while(fgets(str,150,f1)!=NULL)
           {	
		g = ftell(f1);
		fgets(str,150,f1);
		if(strcmp(str,"\n")!=0)
		{	
			fseek(f1,g,SEEK_SET);
              		fseek(f1,21,SEEK_CUR);
              		fscanf(f1,"%d",&n);
			fseek(f1,g,SEEK_SET);
			fgets(str,150,f1);
              		if(n>p)
              		{
				k = g;
                 		p=n;
				count++;
              		}	
		}
		else if(strcmp(str,"\n")==0)
		{
			break;
		}
           }
	}	   
   }       
	fseek(f1,k,SEEK_SET);
	fgets(str,150,f1);	
	if(count!=0)
	{
	printf("Maximum Amount transferred\n%s",str);
	}
	else
	{
		printf("No Transactions to be displayed\n");
	}
}

void min(char acc[])
{  
   char str[150];
   int n,p=10000000,m=0,k,g,count=0;   
   acc[11]='A';
   acc[12]='\0';
   FILE *f1;
   char a;
   f1=fopen("t_file.txt","r");
   while(fgets(str,150,f1)!=NULL)
   {	   	
	   if(strncmp(acc,str,12)==0)
	   {
	   while(fgets(str,150,f1)!=NULL)
           {			   
		g = ftell(f1);
		fgets(str,150,f1);
		if(strcmp(str,"\n")!=0)
		{
              		fseek(f1,g,SEEK_SET);
              		fseek(f1,21,SEEK_CUR);
              		fscanf(f1,"%d",&n);
			fseek(f1,g,SEEK_SET);
			fgets(str,150,f1);
			if(n<p)
			{
			   p=n;
			   k = g;
			   count++;
		        }	   
		}
		else if(strcmp(str,"\n")==0)
		{
			break;
		}
           }
	}	   
   }       
   fseek(f1,k,SEEK_SET);
   fgets(str,150,f1);	
   if(count!=0)
{	
   printf("Minumum amount transferred\n\n%s",str);
	}
  else
{
printf("No Transactions to be displayed");
}	
}

