//main2.c with pthreads layer
#include "json_handler.h"
#include "validation.h"
#include "employee_ops.h"
#include<stdio.h>
#include<pthread.h>
#include<string.h>
//colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

pthread_mutex_t lock;

struct thread_args{
	struct json_object *root;
	char id[6];
	int result;
};

void *thread_add(void *arg){
	struct thread_args *data = (struct thread_args *)arg;
	data->result= add(data->root);
	return NULL;
}

void *thread_query(void *arg){
	struct thread_args *data = (struct thread_args *)arg;
        data->result=query(data->root,data->id);
        return NULL;
}

void *thread_modify(void *arg){
	struct thread_args *data =(struct thread_args *)arg;
	data->result=modify(data->root,data->id);
	return NULL;
}

void *thread_delete(void *arg){
        struct thread_args *data =(struct thread_args *)arg;
        data->result=delete_employee(data->root,data->id);
        return NULL;
}

int main(void){
	pthread_mutex_init(&lock,NULL);
	struct json_object *root = parse_json_file("employee.json");
	int choice;
	char choice_str[3];
menu_input:
	printf(CYAN"\n********Menu********\n");
	printf("----------------------\n");
	printf("1.Query\n2.Add\n3.Modify\n4.Delete\n5.Quit\n");
	printf("------------------\n"RESET);
	scanf("%2s",choice_str);
	while(getchar() !='\n');
	choice=atoi(choice_str);
	if(choice<1 || choice>5){
		printf(RED"input valid option from the menu\n"RESET);
		goto menu_input;
	}
	char choice_id[6];
	int menu_ret;
	switch (choice){
		case 1: {//query
			printf(YELLOW"Employee ID: "RESET);
query_id_input:
			scanf("%5s",choice_id);
			while(getchar() !='\n');
			if(validate_employee_id(choice_id)==-1){
				printf(YELLOW"input valid 4 digit ID: "RESET);
				goto query_id_input;
			}
			struct thread_args args;
    			args.root = root;
    			strcpy(args.id,choice_id);
    			pthread_t thread;
    			pthread_create(&thread, NULL, thread_query, (void *)&args);
    			pthread_join(thread, NULL);
    			menu_ret = args.result;
			if(menu_ret==-1){
				printf(RED"Employee id not found\n"RESET);
				goto menu_input;
			}
			else{
				goto menu_input;
			}
			}
		case 2: {//add
			struct thread_args args;
   			args.root = root;
    			pthread_t thread;
    			pthread_create(&thread, NULL, thread_add, (void *)&args);
    			pthread_join(thread, NULL);
    			menu_ret = args.result;
    			if(menu_ret == 0){
        			printf(YELLOW"Cancelled\n"RESET);
       				goto menu_input;
    			}
   			else{
        			printf(GREEN"Employee details added successfully with ID:%d"RESET, menu_ret);
        			save_json_file(root, "employee.json");
        			goto menu_input;
    			}
			}
			
		case 3: {//modify
			printf(YELLOW"Employee ID: "RESET);
modify_id_input:
			scanf("%5s",choice_id);
			while(getchar() !='\n');
			if(validate_employee_id(choice_id)==-1){
				printf(YELLOW"input valid 4 digit ID: "RESET);
				goto modify_id_input;
			}
			query(root,choice_id);
			struct thread_args args;
    			args.root = root;
    			strcpy(args.id,choice_id);
    			pthread_t thread;
    			pthread_create(&thread, NULL, thread_modify, (void *)&args);
    			pthread_join(thread, NULL);
    			menu_ret = args.result;
			if(menu_ret==-1){
				printf(RED"Employee id not found\n"RESET);
				goto menu_input;
			}
			else if(menu_ret==0){
				printf(YELLOW"Cancelled without changing\n"RESET);
				goto menu_input;
			}
			else{
				printf(GREEN"Details modified Successfully!\n"RESET);
				save_json_file(root,"employee.json");
				query(root,choice_id);
				goto menu_input;
			}
			}
		case 4: {//delete
			printf(YELLOW"Employee ID: "RESET);
delete_id_input:
                        scanf("%5s",choice_id);
			while(getchar() !='\n');
                        if(validate_employee_id(choice_id)==-1){
                                printf(YELLOW"input valid 4 digit ID: "RESET);
                                goto delete_id_input;
                        }
			struct thread_args args;
    			args.root = root;
    			strcpy(args.id,choice_id);
    			pthread_t thread;
    			pthread_create(&thread, NULL, thread_delete, (void *)&args);
    			pthread_join(thread, NULL);
    			menu_ret = args.result;
			if(menu_ret==-1){
				printf(RED"Employee id not found\n"RESET);
				goto menu_input;
			}
			if(menu_ret==0){
				printf(YELLOW"Delete cancelled\n"RESET);
				goto menu_input;
			}
			else{
				printf(GREEN"%d Deleted Successfully!\n"RESET,menu_ret);
				save_json_file(root,"employee.json");
				goto menu_input;
			}
			}
		case 5:
			json_object_put(root);
			pthread_mutex_destroy(&lock);
			return 0;
	}
	



	return 0;
}
