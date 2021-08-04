#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
void st_trans(char acc1[],char acc2[],int money)
{
	acc1[11]='A';
        time_t t;
	time(&t);
	struct tm *mytime = localtime(&t);
        char s[20];
	char type[10];
        FILE *fp1,*fp2;
        fp1 = fopen("t_file.txt","r");
        fp2 = fopen("n.txt","a");
        while(fgets(s,20,fp1)!=NULL)
        {
                fputs(s,fp2);
                if(strncmp(s,acc1,12)==0)
                {
                        fgets(s,20,fp1);
                        fputs(s,fp2);
                        break;
                }
        }
        fprintf(fp2,"%s   -   Rs.%d  -  DEBITED  -  %s",acc2,money,ctime(&t));
	fprintf(fp2,"%d %d %d\n",(mytime->tm_mday),(mytime->tm_mon)+1,(mytime->tm_year)-100);
        while(fgets(s,20,fp1)!=NULL)
        {
                fputs(s,fp2);
        }
	acc2[11]='A';
	acc1[11]='\0';
	fseek(fp2,0,SEEK_SET);
	remove("t_file.txt");
        rename("n.txt","t_file.txt");
        fp1 = fopen("t_file.txt","r");
        fp2 = fopen("n.txt","a");
	while(fgets(s,20,fp1)!=NULL)
        {
                	fputs(s,fp2);
                	if(strncmp(s,acc2,12)==0)
                	{
                        	fgets(s,20,fp1);
                        	fputs(s,fp2);
                        	break;
                	}
        }
	fprintf(fp2,"%s   -   Rs.%d  -  CREDITED  -  %s",acc1,money,ctime(&t));
        fprintf(fp2,"%d %d %d\n",(mytime->tm_mday),(mytime->tm_mon)+1,(mytime->tm_year)-100);
        while(fgets(s,20,fp1)!=NULL)
        {
                fputs(s,fp2);
       	}
	remove("t_file.txt");
        rename("n.txt","t_file.txt");
        fclose(fp1);
	fclose(fp2);
}


void newst_trans(char acc[],char name[])
{
	FILE *fp = fopen("t_file.txt","a");
	fprintf(fp,"\n%sA\n",acc);
	fprintf(fp,"%s\n",name);
	fclose(fp);
}

void del_trans(char acc[])
{
	acc[11]='A';
	char a[300];
	FILE *fp = fopen("t_file.txt","r");
	FILE *fp2 = fopen("n.txt","a");
	while(fgets(a,300,fp)!=NULL)
	{
		if(strncmp(a,acc,12)==0)
		{
			break;
		}
		fputs(a,fp2);
	}
	while(fgets(a,300,fp)!=NULL)
	{
		if(strcmp(a,"\n")==0)
		{
			break;
		}
	}
	while(fgets(a,300,fp)!=NULL)
	{
		fputs(a,fp2);
	}
	fclose(fp);
        fclose(fp2);
	remove("t_file.txt");
	rename("n.txt","t_file.txt");
	char v;
	FILE *fp3 = fopen("t_file.txt","r");
	fseek(fp3,-2,SEEK_END);
	int count = ftell(fp3);
	v = fgetc(fp3);
	fclose(fp3);
	FILE *fp1 = fopen("t_file.txt","r");
	FILE *fp4 = fopen("file4.txt","a");
	if(v=='\n')
	{
		while(ftell(fp1)!=count)
		{
			v = fgetc(fp1);
			fputc(v,fp4);
		}
		fputc('\n',fp4);
		fclose(fp1);
        	fclose(fp4);
		remove("t_file.txt");
		rename("file4.txt","t_file.txt");
	}
	else{
	fclose(fp1);
        fclose(fp4);
	remove("file4.txt");
	}
}
void sh_trans(char acc[])
{
int comp(int date1, int date2,int month1,int month2,int year1,int year2)
{
    if (year1 < year2)
    {
       return -1;
    }
    else if (year1 > year2)
    {
	    return 1;
    }
    if (year1 == year2)
    {
         if (month1<month2)
	 {
              return -1;
	 }
         else if (month1>month2)
	 {
              return 1;
	 }
         else if (date1<date2)
	 {
              return -1;
	 }
         else if(date1>date2)
	 {
              return 1;
	 }
         else
	 {
              return 1;
	 }
    }
}
int opt,flag1=0,m=0,count,h=1,flag4;
char s[12],z[1000];
FILE *fp;
fp = fopen("t_file.txt","r");
acc[11]='A';
while(1)
{
	flag1=0;
	flag4 = 0;
	fseek(fp,0,SEEK_SET);
	while(fgets(z,1000,fp)!=NULL)
        {
        	if(strncmp(z,acc,12)==0)
      		{
                  	flag1 = 2;
			fgets(z,1000,fp);
                        if(fgets(z,1000,fp)==NULL || strcmp(z,"\n")==0)
                        {
                            	printf("OOPS! You have no transactions to be displayed!");
                	        flag1 = 1;
                               	break;
                       	}
			break;
               	}
	}
	if(flag1==1)
	{
		break;
	}
	if(flag1==2)
	{
		m =0;
		count = 0;
		flag4 =0;
		printf("Enter\n1 to view the last 10 transactions\n2 to view all the transactions before a specific date\n3 to view all the transactions after a specific date\n");
		scanf("%d",&opt);
		if(opt==1)
		{
			while(m<10 && strcmp(z,"\n")!=0)
			{	
				printf("%s\n",z);
				fgets(z,1000,fp);
				m++;
				count++;
				if(fgets(z,1000,fp)==NULL)
				{
					break;
				}
			}
		}
		if(opt == 3 || opt == 2)
		{
			int dt,mn,yr,date[3];
			if(opt==2)
			{
				printf("Enter that specific date to view the transactions before that (in dd/mm/yy format) : ");
			}
			else
			{
				printf("Enter that specific date to view the transactions after that (in dd/mm/yy format) : ");
			}
			scanf("%d/%d/%d",&dt,&mn,&yr);	
			char b[3];
			if(dt>=31 ||dt<0 || mn>12 || mn<1 || yr<=0)
			{
					flag4 = 1;
					printf("Enter a valid date!\n");	
			}	
			if(flag4==0)
			{
				while(strcmp(z,"\n")!=0)
				{
			        	for(int i=0;i<3;i++)
					{
						b[0]=fgetc(fp);
						b[1]=fgetc(fp);
						b[2]='\0';
						fgetc(fp);
						date[i] = atoi(b);
					}
					
					if(opt == 3 && comp(dt,date[0],mn,date[1],yr,date[2])==-1) 	
					{
						printf("\n%s\n",z);
						count++;
					}
					else if(opt==2 && comp(dt,date[0],mn,date[1],yr,date[2])==1) 
					{
						printf("\n%s\n",z);
						count++;
					}
					if(fgets(z,1000,fp)==NULL)
					{	
						break;
					}	
				}
			}
	}
			if((opt ==1 ||opt ==2||opt ==3))
			{	
				if(count == 0)
				{
					printf("\n---No transactions to be displayed---\n\n");
					system("sleep 1");
				}
				printf("Do you want to check other transactions?\nEnter\n1 for YES\n0 to QUIT\n");
				scanf("%d",&h);
			}	
			if((opt !=1 && opt !=2 && opt !=3))
                	{
                       		printf("Please enter a valid option\n");
				system("sleep 1");
                	}
			while(h!=0 && h!=1)
			{	printf("Enter a valid option");
				scanf("%d",&h);
			}
			if(h==0)
			{
				break;
			}
		}
		
	}
	fclose(fp);
}
