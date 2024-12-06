#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) //do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); printf("\n"); } while (0)
#undef OUT_TO_BUFFER
#define USE_EXAMPLE_FILE
#ifdef USE_EXAMPLE_FILE
#include <dirent.h>
#endif
const char *reserved[30] = {
    "const", "int", "float", "double",
    "long", "static", "void", "char",
    "extern", "return", "break", "enum",
    "struct", "typedef", "union", "goto"
};

const char *oper[11] = {
    "+", "-", "*", "/",
    "=", "==", "!=", ">=",
    "<=", ">", "<"
};

/*
int isdigit(char ch){
	return ('0' <= ch && ch <= '9'); 
}
*/
int ischar(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

int in_reserved(char *str) {
    for (int i = 0; i < 16; ++i) {
        if (!strcmp(str, reserved[i])) {
            return 1;
        }
    }
    return 0;
}

int in_operator(char *str) {
    for (int i = 0; i < 11; ++i) {
        if (!strcmp(str, oper[i])) {
            return 1;
        }
    }
    return 0;
}
int isInterger(char *str){
	char *s=str;
	while(*s){
		if(!isdigit(*s)){
			return 0;
		}
		s++;
	}
	return 1;
}
int isFloat(char *str){
	char *s=str;
	int dot=0;
	while(*s){
		if((dot==0)&&(*s=='.')){
			dot=1;
			s++;
			continue;			
		}
		if(!isdigit(*s)){
			return 0;
		}
		s++;
	}
	return 1;
}
int isVariable(char *str){
	char *s=str;
	if(isdigit(*s)){
			return 0;
	}
	while(*s){
		if(isdigit(*s)||(*s=='_')||ischar(*s)){
		}else{
			return 0;
		}
		s++;
	}
	return 1;
}
void trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    if (len == 0) return; 
    for (int i = len - 1; i >= 0; --i) {
        if (!isspace(str[i]) && str[i] != '\r' && str[i] != '\n') {
            break;
        }
        str[i] = '\0';
    }
}
char str[4096]={0};
#ifdef OUT_TO_BUFFER
char outstr[4096]={0};
#endif
int compile_error = 0;
void redirectOut(char *s){
#ifdef 	OUT_TO_BUFFER
	strcat(outstr,s);
#else
	printf("%s",s);
#endif
}
void handleToken(char* token){
	if(in_operator(token))
		redirectOut("operator ");
	else if(in_reserved(token))
		redirectOut("reserved ");
	else if(isInterger(token))
		redirectOut("integer ");
	else if(isFloat(token))
		redirectOut("float ");
	else if(isVariable(token)){	
		redirectOut("variable ");		
	}else{
		redirectOut("Compile Error\n");
		compile_error=1;
	}
}
void _process(char* str){

    char *token;
    const char *delim = " "; 

    token = strtok(str, delim);
    if (token != NULL) {
        //printf("%s\n", token);
        handleToken(token); 
    }

    while ((token = strtok(NULL, delim)) != NULL) {
        //printf("%s\n", token);
        handleToken(token); 
    }

} 
void process(char* s){	
	if(strlen(s)==0){
		redirectOut("\n");
	}
	else{
#ifndef OUT_TO_BUFFER		
		log("%s",s);
#endif		
		_process(s);
		redirectOut("\n");
	}
}
int main() {
#ifdef USE_EXAMPLE_FILE   
     FILE *file;
	 DIR *d;
     struct dirent *dir;
	 char path[1024]={0};
     d = opendir("data");
	if(d){
		 while ((dir = readdir(d)) != NULL) {             
			snprintf(path, sizeof(path), "%s/%s", "data", dir->d_name);
			if(!strcmp(dir->d_name,".")||!strcmp(dir->d_name,".."))
				continue;
			printf("#########try to open %s ", path); 
#if 0			
            if (dir->d_type != DT_REG) {
                continue;
            }			
#endif			
			file = fopen(path, "r"); 
			if (file == NULL) {
				perror("open file failure");
				continue;
			}else{
				printf(":\n");
			}
#else
	FILE *file=stdin;
#endif
    while ((compile_error==0)&&(fgets(str, sizeof(str), file) != NULL)) {
		trim_trailing_whitespace(str);
#ifndef OUT_TO_BUFFER 	
        log("read string: %s", str);
#endif        
        char *begin=str; 
		int len=strlen(str);       
        char *end=begin;
        while((compile_error==0)&&(begin<(str+len))){
			log("begin=%s",begin);
	        char *s = strchr(begin, ';');
		    if (s == NULL) {
				if(!isblank(*begin)&&(*begin!='\r')&&(*begin!='\n')){
					redirectOut("Compile Error\n");
					compile_error=1;
					break;
				}else{
					begin+=1;
					continue;
				}
		    }else{
		    	log("s=%s",s);
		    	*s='\0'; 
			    process(begin); 
			}
			begin=s+1;
			log("begin=%s",begin);
		}
	    
    } 
#ifdef USE_EXAMPLE_FILE    
			fclose(file);
		}
		closedir(d);
	}
#endif   
#ifdef 	OUT_TO_BUFFER 
	if(compile_error==0)
		printf("%s",outstr);
	else
		printf("Compile Error");
#endif		
    return 0;
}
