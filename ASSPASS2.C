/*
	Assembler Pass 2 of 2-Pass Assembler
	Author: PracsPedia		www.pracspedia.com
	For all the files please download source code from our site.
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct tabb
{
	char name[10];
} tab[300];
main()
{
	FILE *f1,*f2,*f3;
	char c,temp[10],tname[10],type[3],filename[10],output[15];
	int i,j,k,t = 0,nl = 0,t1,t2,t3;
	clrscr();
	printf("\nEnter intermediate file name: ");
	scanf("%s",filename);
	printf("\nEnter output file name for save final output : ");
	scanf("%s",output);
	f1 = fopen(filename,"r");
	f2 = fopen("out1.txt","w");
	while((c = getc(f1)) != EOF)
		{
		if(c == ',' || c == '(' || c == ')' || c == '+')
			fprintf(f2,"");
		else if(c == '-')
			fprintf(f2,"-");
		else if(c == '\n')
			fprintf(f2,"\n");
		else
			fprintf(f2,"%c",c);
		}
	fprintf(f2,"\n");
	fclose(f2);
	fclose(f1);
	f1 = fopen("out1.txt","r");
	f2 = fopen(output,"w");
	while(feof(f1) == 0)
		{
		fscanf(f1,"%s",temp);
		strcpy(tab[t].name,temp);
		t++;
		if(getc(f1) == '\n')
			{
			printf("\n");
			fprintf(f2,"\n");
			for(i = 0;i < t;i++)
				{
				if(strcmp(tab[i].name,"AD") == 0)
								nl = 1;
				if(strcmp(tab[i].name,"DL") == 0 && strcmp(tab[i+1].name,"0") != 0)
					{
					printf(" %s)",tab[0].name);
					fprintf(f2," %s)",tab[0].name);
					nl = 1;
					}
				if(strcmp(tab[i].name,"DL") == 0 && strcmp(tab[i+1].name,"0") == 0)
					{
					f3 = fopen("table.txt","r");
					while(feof(f3) == 0)
						{
						fscanf(f3,"\n%s %s %d %d",type,tname,&t1,&t2);
						t3 = atoi(tab[0].name);
						if(strcmp(type,"c") == 0 && t3 == t1)
							{
							printf(" %s) 0 0 %s",tab[0].name,tname);
							fprintf(f2," %s) 0 0 %s",tab[0].name,tname);
							}
						}
					close(f3);
					nl = 1;
					}
				}
			for(i = 0;i < t;i++)
					{
					if(strcmp(tab[i].name,"DL") == 0 && strcmp(tab[i+1].name,"1") == 0)
						{
						if(strcmp(tab[i+2].name,"l") == 0)
							{
							f3 = fopen("table.txt","r");
							while(feof(f3) == 0)
								{
								fscanf(f3,"\n%s %s %d %d",type,tname,&t1,&t2);
								if(strcmp(type,"l") == 0
										&& atoi(tab[i+3].name) == t1)
									{
									printf(" 0 0 %s",tname);
									fprintf(f2," 0 0 %s",tname);
									nl = 1;
									break;
									}
								}
							fclose(f3);
							}
						}
					}
			if(nl != 1)
				{
				for(i = 0;i < t;i++)
					{
					if(i == 0 && strcmp(tab[1].name,"s") == 0)
						{
						printf(" %s)",tab[i].name);
						fprintf(f2," %s)",tab[i].name);
						i = i + 2;
						}
					else if(strcmp(tab[i].name,"IS") == 0 ||strcmp(tab[i].name,"-") == 0
					|| strcmp(tab[i].name,"R") == 0 )
							printf("");
					else if(strcmp(tab[i].name,"s") == 0)
						{
						f3 = fopen("table.txt","r");
						while(feof(f3) == 0)
							{
							fscanf(f3,"\n%s %s %d %d",type,tname,&t1,&t2);
							if(strcmp(type,"s") == 0
									&& atoi(tab[i+1].name) == t1)
									{
									printf(" %d",t2);
									fprintf(f2," %d",t2);
									i = i + 1;
									}
							}
							fclose(f3);
						}
				else if(strcmp(tab[i].name,"l") == 0)
						{
						f3 = fopen("table.txt","r");
						while(feof(f3) == 0)
							{
							fscanf(f3,"\n%s %s %d %d",type,tname,&t1,&t2);
							if(strcmp(type,"l") == 0
									&& atoi(tab[i+1].name) == t1)
									{
									if(i != 1)
										{
										printf(" %d",t2);
										fprintf(f2," %d",t2);
										}
									else
										{
										printf(" 0 0 %s",tname);
										fprintf(f2," 0 0 %s",tname);
										}
										i = i + 1;
									}
							}
							fclose(f3);
						}
					else if(i == 0)
						{
						printf(" %s)",tab[i].name);
						fprintf(f2," %s)",tab[i].name);
						}
					else
						{
						printf(" %s",tab[i].name);
						fprintf(f2," %s",tab[i].name);
						}
					}
				}
			t = 0;
			nl = 0;
			}
		}
	fclose(f2);
	getch();
	return 0;
}