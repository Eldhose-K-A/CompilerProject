#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int maxindex=-1;
	int state=0;
	char ch;
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
	fout2=fopen("log.txt","w");
	if(fout==NULL){
		printf("Couldn't Open Log File!.......\n");
		fclose(fin);
		fclose(fout);
		return(0);
	}
	
	while((ch=fgetc(fin))!=EOF){
		if(ch==EOF)
			break;
		printf("%c",ch);
		if(ch==' ')
			fprintf(fout2,"Char : <space>\n");
		else if(ch=='\n')
			fprintf(fout2,"Char : <newline>\n");
		else if(ch==EOF)
			fprintf(fout2,"Char : <EOF>\n");
		else
			fprintf(fout2,"Char : %c\n",ch);
		//------------------------------------------------------------------------------------------
		if(state==0){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=0;
			}
			else if(ch=='+'){
				state=6;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=7;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==1){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=8;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=4;
				string[++maxindex]='\0';
				fprintf(fout,"< di , %10s >\n",string);
				maxindex=-1;
			}
			else if(ch=='+'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< di , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< di , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< di , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==2){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=4;
				string[++maxindex]='\0';
				fprintf(fout,"< id , %10s >\n",string);
				maxindex=-1;
			}
			else if(ch=='+'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< id , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< id , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< id , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==3){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=5;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
			}
			else if(ch=='+'){
				state=6;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=7;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==4){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=4;
			}
			else if(ch=='+'){
				state=3;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=3;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==5){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=5;
			}
			else if(ch=='+'){
				state=6;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=7;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==6){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=6;
			}
			else if(ch=='+'){
				state=6;
				string[maxindex]=ch;
			}
			else if(ch=='-'){
				state=7;
				string[maxindex]='-';
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==7){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=2;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=1;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=7;
			}
			else if(ch=='+'){
				state=7;
				string[maxindex]=ch;
			}
			else if(ch=='-'){
				state=6;
				string[maxindex]='+';
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< op , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		else if(state==8){
			if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')){
				state=8;
				string[++maxindex]=ch;
			}
			else if(ch>='0'&&ch<='9'){
				state=8;
				string[++maxindex]=ch;
			}
			else if(ch==' '||ch=='\n'||ch==EOF){
				state=4;
				string[++maxindex]='\0';
				fprintf(fout,"< er , %10s >\n",string);
				maxindex=-1;
			}
			else if(ch=='+'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< er , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='-'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< er , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else if(ch=='='||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='('||ch==')'){
				state=3;
				string[++maxindex]='\0';
				fprintf(fout,"< er , %10s >\n",string);
				maxindex=-1;
				string[++maxindex]=ch;
			}
			else{
				state=8;
				string[++maxindex]=ch;
			}
		}
		//------------------------------------------------------------------------------------------
	}
	if(maxindex!=-1){
		if(state==1)
			fprintf(fout,"< di ");
		else if(state==2)
			fprintf(fout,"< id ");
		else if(state==3)
			fprintf(fout,"< op ");
		else if(state==4)
			fprintf(fout,"< ne ");
		else if(state==5)
			fprintf(fout,"< on ");
		else if(state==6)
			fprintf(fout,"< ++ ");
		else if(state==7)
			fprintf(fout,"< -- ");
		else
			fprintf(fout,"< er ");
		state=0;
		string[++maxindex]='\0';
		fprintf(fout,", %10s >\n",string);
		maxindex=-1;
	}
	
	fclose(fin);
	fclose(fout);
	fclose(fout2);
	printf("<---\n");
	
	return(0);
}