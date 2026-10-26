/* validation.c - Input validation implementations */

#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include"validation.h"
int validate_employee_id(const char *id){
	//not empty
	if(strlen(id)!=4)
		return -1;
	//all are digits only
	for(int i=0; id[i]!='\0'; i++){
		if(!isdigit(id[i]))
			return -1;
	}
	return 0;	
}

int validate_name(const char *name){
	//not empty
	if(strlen(name)<1)
		return -1;
	//only alphabets and spaces
	for(int i=0; name[i]!='\0'; i++){
		if(!isalpha(name[i])){
			if(name[i]==' ')
				continue;
			else
				return -1;
		}
	}
	return 0;

}

int validate_mobile(const char *mobile){
	//should exactly 10 not less not more
	if(strlen(mobile)!=10)
		return -1;

	//all are digits
	for(int i=0; mobile[i]!='\0'; i++){
		if(!isdigit(mobile[i]))
			return -1;
	}
	return 0;

}

int validate_age(const char *age){
	//not empty
	if(strlen(age)<1)
		return -1;

	//all digits
	for(int i=0; age[i]!='\0'; i++){
		if(!isdigit(age[i]))
			return -1;
	}
	//in between 18 and 100
	int age_int = atoi(age);
	if(age_int>100 || age_int<18){
		return -1;
	}
	return 0;
}
