#include "json_handler.h"
#include "validation.h"
#include "employee_ops.h"
#include<stdio.h>
//colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

int main(void){
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
		case 1: //query
			printf(YELLOW"Employee ID: "RESET);
query_id_input:
			scanf("%5s",choice_id);
			while(getchar() !='\n');
			if(validate_employee_id(choice_id)==-1){
				printf(YELLOW"input valid 4 digit ID: "RESET);
				goto query_id_input;
			}
			menu_ret=query(root,choice_id);
			if(menu_ret==-1){
				printf(RED"Employee id not found\n"RESET);
				goto menu_input;
			}
			else{
				goto menu_input;
			}
		case 2: //add
			menu_ret=add(root);
			if(menu_ret==0){
				printf(YELLOW"Cancelled\n"RESET);
				goto menu_input;
			}
			else{
				printf(GREEN"Employee details added successfully with ID:%d"RESET,menu_ret);
				save_json_file(root,"employee.json");
				goto menu_input;
			}
		case 3: //modify
			printf(YELLOW"Employee ID: "RESET);
modify_id_input:
			scanf("%5s",choice_id);
			while(getchar() !='\n');
			if(validate_employee_id(choice_id)==-1){
				printf(YELLOW"input valid 4 digit ID: "RESET);
				goto modify_id_input;
			}
			query(root,choice_id);
			menu_ret=modify(root,choice_id);
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
		case 4: //delete
			printf(YELLOW"Employee ID: "RESET);
delete_id_input:
                        scanf("%5s",choice_id);
			while(getchar() !='\n');
                        if(validate_employee_id(choice_id)==-1){
                                printf(YELLOW"input valid 4 digit ID: "RESET);
                                goto delete_id_input;
                        }
			menu_ret=delete_employee(root,choice_id);
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
		case 5:
			json_object_put(root);
			return 0;
	}
	



	return 0;
}
