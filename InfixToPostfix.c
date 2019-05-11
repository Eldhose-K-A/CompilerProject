#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char opstack[20];
int top=-1;
int priority(char ip)
{
	if(ip=='+'||ip=='-')
	{
		return(5);
	}
	else if(ip=='*'||ip=='/'||ip=='%')
	{
		return(6);
	}
	else if(ip=='^')
	{
		return(7);
	}
	else if(ip==')')
	{
		return(4);
	}
	else if(ip=='(')
	{
		return(8);
	}
	else if(ip=='=')
	{
		return(3);
	}
	else
	{
		return(-1);
	}
}

int main(int argc,char *argv[]){
	int maxindex=-1;
	int p=0;
	char ch1,ch2,ch3,ch4;
	char strtype[20];
	char string[20];
	FILE *fin,*fout,*fout2;
	
	if(argc!=3){
		printf("Wrong No of Arguments!.......\n");
		return(0);
	}
	
	fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Couldn't Open Input File!.......\n");
		return(0);
	}
	fout=fopen(argv[2],"w");
	if(fout==NULL){
		printf("Couldn't Open Output File!.......\n");
		fclose(fin);
		return(0);
	}
	fout2=fopen("log3.txt","w");
	if(fout==NULL){
		printf("Couldn't Open Log File!.......\n");
		fclose(fin);
		fclose(fout);
		return(0);
	}
	
	while(!feof(fin)){
		if(feof(fin))
			break;
		fscanf(fin," %c %s %c %s %c ",&ch1,strtype,&ch2,string,&ch3);
		printf("\n%c <-> %5s <-> %c <-> %5s <-> %c .",ch1,strtype,ch2,string,ch3);
		if(strcmp(strtype,"id")==0)
			fprintf(fout2,"String : Identifier(%s)\n",strtype);
		else if(strcmp(strtype,"op")==0)
			fprintf(fout2,"String : Operator(%s)\n",strtype);
		else if(strcmp(strtype,"di")==0)
			fprintf(fout2,"String : Digit(%d)\n",atoi(string));
		else
			fprintf(fout2,"StringERROR : %s\n",strtype);
		//----------------------------------------------------------------------------------------------------
		if(strcmp(strtype,"id")==0)
			fprintf(fout,"< id , %10s >\n",string);
		else if(strcmp(strtype,"di")==0)
			fprintf(fout,"< di , %10d >\n",atoi(string));
		else if(strcmp(strtype,"op")==0)
		{
			p = priority(string[0]);
			if(top==-1)
				opstack[++top]=string[0];
			else
			{
				if(string[0]=='(')
					opstack[++top]='(';
				else if(string[0]==')')
				{
					while(top>-1)
					{
							if(opstack[top]!='(')
								fprintf(fout,"< op , %10c >\n",opstack[top--]);
							else
								break;
					}
					if(top>-1)
						top--;
				}
				else{
					while(top>-1)
					{
						if(opstack[top]!='(')
						{
							if(priority(opstack[top])>=p)
							{
								fprintf(fout,"< op , %10c >\n",opstack[top--]);
							}
							else
								break;
						}
						else
							break;
					}
					opstack[++top]=string[0];
				}
			}
			printf("\nOpStack : ");
			for(int f=0;f<=top;++f)
				printf(" %c ",opstack[f]);
		}
		else
		{
			printf("\nERROR\n");
			break;
		}
		//----------------------------------------------------------------------------------------------------
	}
	while(top>-1)
	{
		if(opstack[top]!='('&&opstack[top]!=')')
			fprintf(fout,"< op , %10c >\n",opstack[top]);
		--top;
	}
	fclose(fin);
	fclose(fout);
	fclose(fout2);
	printf("<---\n");
	
	return(0);
}