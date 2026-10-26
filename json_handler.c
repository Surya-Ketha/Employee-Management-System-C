#include"json_handler.h"
#include<stdlib.h>
#include<stdio.h>

struct json_object *parse_json_file(const char *filename){
	FILE *fp=fopen(filename,"r");
	if(fp==NULL){
		printf("file open failed\n");
		return NULL;
	}

	fseek(fp,0,SEEK_END);
	long size = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char *buffer = malloc(size+1);
	if(buffer==NULL){
		fclose(fp);
		return NULL;
	}

	fread(buffer,1,size,fp);
	buffer[size]='\0';

	fclose(fp);
	
	struct json_object *root = json_tokener_parse(buffer); //converts raw text into
							       //structured text

	free(buffer);
	return root; //must call json_object_put(root); after using this function.
}

int save_json_file(struct json_object *root, const char *filename){

	const char *json_string=json_object_to_json_string_ext(root,JSON_C_TO_STRING_PRETTY);

	FILE *fp=fopen(filename, "w");
	if(fp==NULL){
		printf("open failed\n");
		return -1;
	}
	fprintf(fp,"%s\n", json_string);

	fclose(fp);

	return 0;
}


