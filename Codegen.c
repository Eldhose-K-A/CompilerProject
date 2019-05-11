#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
	char val[20];
	int type;
	struct stack *next;
}*top,*new,*operand1,*operand2;

int main(int argc,char *argv[]){
	
	FILE *fin,*fout,*fout2;
	top=new=NULL;
	char instruction[10];
	char ch1,ch2,ch3,strtype[20],string[20];
	
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
	fout2=fopen("log4.txt","w");
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
		{
			fprintf(fout2,"String : Identifier(%s)\n",strtype);
			new=(struct stack *)malloc(sizeof(struct stack));
			strcpy(new->val,string);
			new->type=0;
			new->next=top;
			top=new;
		}
		else if(strcmp(strtype,"op")==0)
		{
			fprintf(fout2,"String : Operator(%s)\n",strtype);
			if(strcmp(string,"+")==0)
				strcpy(instruction,"ADD");
			else if(strcmp(string,"-")==0)
				strcpy(instruction,"SUB");
			else if(strcmp(string,"*")==0)
				strcpy(instruction,"MUL");
			else if(strcmp(string,"/")==0)
				strcpy(instruction,"DIV");
			else if(strcmp(string,"%")==0)
				strcpy(instruction,"MOD");
			else if(strcmp(string,"^")==0)
				strcpy(instruction,"POW");
			else
				strcpy(instruction,"OTH");
			if(strcmp(string,"=")!=0)
			{
				if(top!=NULL)
				{
					if(top->next!=NULL)
					{
						operand2=top;
						operand1=top->next;
						if(operand1->type==1)
						{
							sprintf((operand1->val)+2,"%x",atoi(operand1->val));
							operand1->val[0]='0';
							operand1->val[1]='x';
						}
						if(operand2->type==1)
						{
							sprintf((operand2->val)+2,"%x",atoi(operand2->val));
							operand2->val[0]='0';
							operand2->val[1]='x';
						}
						top=(top->next)->next;
						if(strcmp(instruction,"MOD")==0)
							fprintf(fout,"XOR DX\n");
						if(operand1->type!=2&&operand2->type!=2)
							fprintf(fout,"MOV AX,%s\nMOV BX,%s\n",operand1->val,operand2->val);
						if(operand1->type==2&&operand2->type==2)
							fprintf(fout,"POP BX\nPOP AX\n");
						else if(operand1->type==2)
							fprintf(fout,"POP AX\nMOV BX,%s\n",operand2->val);
						else if(operand2->type==2)
							fprintf(fout,"MOV AX,%s\nPOP BX\n",operand1->val,instruction);
						
						if(strcmp(instruction,"MOD")==0)
							fprintf(fout,"DIV BX\nPUSH DX\n\n");
						else if(strcmp(instruction,"MOD")==0)
							fprintf(fout,"MUL BX\nPUSH AX\n\n");
						else
							fprintf(fout,"%s AX,BX\nPUSH AX\n\n",instruction);
					
						new=(struct stack *)malloc(sizeof(struct stack));
						new->type=2;
						new->next=top;
						top=new;
					}
					else
					{
						printf("ERROR\n");
						break;
					}
				}
				else
				{
					printf("ERROR\n");
					break;
				}
			}
			else{
				if(top!=NULL)
				{
					if(top->next!=NULL)
					{
						operand2=top;
						operand1=top->next;
						top=(top->next)->next;
						if(operand1->type==0&&operand2->type!=2)
							fprintf(fout,"MOV %s,%s\n\n",operand1->val,operand2->val);
						if(operand1->type==0&&operand2->type==2)
							fprintf(fout,"POP AX\nMOV %s,AX\n\n",operand1->val);
						else
						{
							printf("ERROR\n");
							break;
						}
					}
					else
					{
						printf("ERROR\n");
						break;
					}
				}
				else
				{
					printf("ERROR\n");
					break;
				}
			}
		}
		else if(strcmp(strtype,"di")==0)
		{
			fprintf(fout2,"String : Digit(%d)\n",atoi(string));
			new=(struct stack *)malloc(sizeof(struct stack));
			strcpy(new->val,string);
			new->type=1;
			new->next=top;
			top=new;
		}
		else
		{
			fprintf(fout2,"StringERROR : %s\n",strtype);
		}
	}
	fclose(fin);
	fclose(fout);
	fclose(fout2);
	printf("<---\n");
	
	return(0);
}