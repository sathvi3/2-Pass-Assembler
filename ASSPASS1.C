/*	
	Assembler Pass 1 of 2-Pass Assembler
	Author: PracsPedia		www.pracspedia.com
	For all the files please download source code from our site.
*/
#include<stdio.h>
#include<stdlib.h>

struct systab
{
	int no,add;
	char name[10];
};
struct littab
{
	int no,add;
	char name[10];
};
struct temptab
{
	char name[10],name1[10];
	int code;
};
struct constab
{
	int add;
	char name[10];
};

void main()
{
	FILE *in,*op,*im,*f1,*f2;

	char temp[10],t1[10],t2[10],prevt[10],prevt2[10],c,filename[15],inter[15];

	int lc,no1,n = 1,m = 1,p = 1,flag = 0,i,j,k,lc1 = 0,math,tadr = 0;
	int pool[10],l = 0,ctr = 0,t = 0,pl = 1,co = 1;
	
	struct systab sys[100];
	struct littab lit[100];
	struct temptab tab[15];
	struct constab con[10];
	
	clrscr();
	
	pool[p] = 1;

	printf("\nEnter file name : ");
	scanf("%s",filename);
	
	printf("\nEnter intermediate filename for save intermediate code :");
	scanf("%s",inter);
	
	f1 = fopen(filename,"r");
	f2 = fopen("in1.txt","w");
	
	while((c = getc(f1)) != EOF)
	{
		if(c == ',' || c == '\'')
			fprintf(f2,"");
		else if(c == '+')
			fprintf(f2," + ");
		else if(c == '=')
			fprintf(f2," = ");
		else if(c == '-')
			fprintf(f2," - ");
		else
			fprintf(f2,"%c",c);
	}
	
	fprintf(f2,"\n=");
	fclose(f2);
	fclose(f1);
	
	in = fopen("in1.txt","r");
	fscanf(in,"%s %d",temp,&lc);
	im = fopen(inter,"w");
	fprintf(im,"(AD, 1)  (c, %d)",lc);
	while(feof(in) == 0)
		{
		fscanf(in,"%s",temp);
		op = fopen("opcode.txt","r");
		while(feof(op) == 0)
			{
			fscanf(op,"%s %s %d",t1,t2,&no1);
			if(strcmp(temp,t1) == 0)
				{
				tab[t].code = no1;
				strcpy(tab[t].name1,t1);
				strcpy(tab[t].name,t2);
				t++;
				flag = 1;
				break;
				}
			}
		fclose(op);
		if(strcmp(temp,"=") == 0)
			flag = 1;
		if(strcmp(temp,"+")== 0 || strcmp(temp,"-") == 0)
			{
			flag = 1;
			strcpy(tab[t].name1,temp);
			t++;
			}
		if(strcmp(prevt,"+") == 0 || strcmp(prevt,"-") == 0
			|| strcmp(prevt,"DS") == 0)
			{
			tab[t].code = atoi(temp);
			strcpy(tab[t].name1,temp);
			strcpy(tab[t].name,"c");
			t++;
			flag = 1;
			}
		for(i = pl;i < m;i++)
			{
			if(strcmp(lit[i].name,temp) == 0)
				{
				tab[t].code = i;
				strcpy(tab[t].name1,temp);
				strcpy(tab[t].name,"l");
				t++;
				flag = 1;
				goto a;
				}
			}
		if(strcmp(prevt,"DC") == 0)
			{
			flag = 1;
			con[co].add = lc; strcpy(con[co].name,temp);
			tab[t].code = m;
			strcpy(tab[t].name1,temp);
			strcpy(tab[t].name,"c");
			t++;
			co++;
			}
		if(strcmp(prevt,"=") == 0)
			{
			flag = 1;
			lit[m].no = m; strcpy(lit[m].name,temp);
			tab[t].code = m;
			strcpy(tab[t].name1,temp);
			strcpy(tab[t].name,"l");
			t++;
			m++;
			}
a:		for(i = 1;i < n;i++)
			{
			if(strcmp(sys[i].name,temp) == 0)
				{
				tab[t].code = i;
				strcpy(tab[t].name1,temp);
				strcpy(tab[t].name,"s");
				if(t == 0)
					sys[i].add = lc;
				t++;
				flag = 1;
				break;
				}
			}
		if(flag == 0)
			{
			sys[n].no = n; strcpy(sys[n].name,temp);
			sys[n].add = lc;
			tab[t].code = n;
			strcpy(tab[t].name1,temp);
			strcpy(tab[t].name,"s");
			t++;
			n++;
			}
		if(strcmp(temp,"LTORG") == 0)
			l = 1;
		if(getc(in) == '\n')
			{
			fprintf(im,"\n");
			printf("\n");
			for(i = 0;i < t;i++)
				if(strcmp(tab[i].name,"AD") == 0)
					lc1 = 1;
			if(lc1 == 0)
				{
				fprintf(im," %d)",lc);
				printf(" %d)",lc);
				}
			for(i = 0;i < t;i++)
				{
				if(strcmp(tab[i].name1,"+") == 0)
					{
					printf(" +");
					fprintf(im," +");
					continue;
					}
				if(strcmp(tab[i].name1,"-") == 0)
					{
					printf(" -");
					fprintf(im," -");
					continue;
					}
				printf(" (%s , %d)",tab[i].name,tab[i].code);
				fprintf(im, " ( %s, %d)",tab[i].name,tab[i].code);
				}

			for(i = 0;i < t;i++)
				{
				if(strcmp(tab[i].name1,"ORIGIN") == 0)
					{
					for(j = 1;j < n;j++)
						{
						if(strcmp(tab[i+1].name1,sys[j].name) == 0)
							{
							if(strcmp(tab[i+2].name1,"+") == 0)
								{
								math = atoi(tab[i+3].name1);
								lc = sys[j].add + math;
								lc1 = 1;
								}
							if(strcmp(tab[i+2].name1,"-") == 0)
								{
								math = atoi(tab[i+3].name1);
								lc = sys[j].add - math;
								lc1 = 1;
								}
							}
						}
					}
				if(strcmp(tab[i+1].name1,"EQU") == 0)
					{
					if(t == 5)
						{
						for(j = 1;j < n;j++)
							{
							if(strcmp(tab[i+2].name1,sys[j].name) == 0)
								{
								if(strcmp(tab[i+3].name1,"+") == 0)
									{
									math = atoi(tab[i+4].name1);
									tadr = sys[j].add + math;
									}
								if(strcmp(tab[i+3].name1,"-") == 0)
									{
									math = atoi(tab[i+4].name1);
									tadr = sys[j].add - math;
									}
								}
							}
						for(j = 1;j < n;j++)
							{
							if(strcmp(tab[i].name1,sys[j].name) == 0)
								sys[j].add = tadr;
							}
						}
					 if(t == 3)
						{
						for(j = 1;j < n;j++)
							{
							if(strcmp(tab[i+2].name1,sys[j].name) == 0)
								tadr = sys[j].add;
							}
						for(j = 1;j < n;j++)
							{
							if(strcmp(tab[i].name1,sys[j].name) == 0)
								sys[j].add = tadr;
							}
						}
					}
				}
			for(i = 0;i < t;i++)
				{
				if(strcmp(prevt,"=") == 0)
					{
					for(j = pl;j < m;j++)
						{
						if(strcmp(temp,lit[j].name) == 0)
							{
							lit[j].add = lc;
							break;
							}
						}
					break;
					}
				}
			for(i = 0;i < t;i++)
				{
				if(strcmp(tab[i].name,"DL") == 0)
					{
					for(j = 0;j < n;j++)
						{
						if(strcmp(tab[i-1].name1,sys[j].name) == 0)
							{
							sys[j].add = lc;
							break;
							}
						}
					lc = lc + tab[i+1].code;
					lc1 = 1;
					break;
					}
				}
			if(l == 1)
				{
				if(strcmp(prevt,"=") == 0)
					{
					ctr++;
					if(ctr == m-p)
						{
						pool[++p] = m;
						pl = pool[p];
						l = 0;
						ctr = 0;
						}
					}
				}
			if(lc1 == 0)
				lc++;
			t = 0;
			lc1 = 0;
			}
		strcpy(prevt,temp);
		flag = 0;
		}
	printf("\n");
	fclose(in);
	in = fopen("table.txt","w");
	printf("\n--SYMBOL TABLE--");
	for(i = 1;i < n;i++)
		{
		printf("\n%d, %s, %d",sys[i].no, sys[i].name,sys[i].add);
		fprintf(in,"\ns %s %d %d",sys[i].name, sys[i].no, sys[i].add);
		}
	printf("\n--LITRAL TABLE--");
	for(i = 1;i < m;i++)
		{
		printf("\n%d, %s, %d",lit[i].no, lit[i].name,lit[i].add);
		fprintf(in,"\nl %s %d %d",lit[i].name, lit[i].no, lit[i].add);
		}
	printf("\n--POOL TABLE--");
	for(i = 1;i <= p;i++)
		printf("\n%d, %d",i,pool[i]);
	for(i = 1;i < co;i++)
		fprintf(in,"\nc %s %d",con[i].name,con[i].add);
	fclose(in);
	getch();
}