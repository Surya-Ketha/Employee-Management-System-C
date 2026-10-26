#include"employee_ops.h"
#include"validation.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define true 1
#define false 0

int query(struct json_object *root, const char *id){
	
	struct json_object *arr = json_object_object_get(root, "employees");
	int query_id = atoi(id);
	int len=json_object_array_length(arr);
	for(int i=0; i<len; i++){
		struct json_object *emp= json_object_array_get_idx(arr,i);
		struct json_object *id_obj=json_object_object_get(emp,"employee_ID");
		int json_id= json_object_get_int(id_obj);
		if(json_id == query_id){
			struct json_object *emp_details=json_object_object_get(emp,"employee_details");
			struct json_object *name_obj=json_object_object_get(emp_details,"name");
			printf("Name: %s\n",json_object_get_string(name_obj));

			struct json_object *age_obj=json_object_object_get(emp_details,"age");
			printf("Age: %d\n",json_object_get_int(age_obj));

			struct json_object *cont_details=json_object_object_get(emp_details,"contact_details");
			struct json_object *emp_mobile=json_object_object_get(cont_details,"mobile_number");

			printf("Mobile: %s\n",json_object_get_string(emp_mobile));
			struct json_object *emp_email=json_object_object_get(cont_details,"email");
			printf("email: %s\n",json_object_get_string(emp_email));
			struct json_object *emp_add=json_object_object_get(cont_details,"address");
			printf("Address: %s\n",json_object_get_string(emp_add));
			return 0;
		}
	}
	return -1;
}

int delete_employee(struct json_object *root, const char *id){
	struct json_object *arr= json_object_object_get(root,"employees");
	int delete_id=atoi(id);
	int len=json_object_array_length(arr);

	for(int i=0; i<len; i++){
		struct json_object *emp=json_object_array_get_idx(arr,i);
		struct json_object *id_obj=json_object_object_get(emp,"employee_ID");
		int json_id=json_object_get_int(id_obj);
		char confirm;
		if(json_id==delete_id){
			printf("Press Y/N to confirm or cancel delete: ");
confirm_input:
			scanf("%c",&confirm);
			if(confirm=='Y' || confirm =='y'){	
				json_object_array_del_idx(arr,i,1);
				return delete_id;
			}
			else if(confirm=='n' || confirm == 'N'){
				return 0;
			}
			else{
				printf("choose only from Y/N: ");
				goto confirm_input;
			}
		}
	}
	return -1;
}

int modify(struct json_object *root, const char *id){
	struct json_object *arr=json_object_object_get(root,"employees");
	int modify_id=atoi(id);
	int len=json_object_array_length(arr);

	for(int i=0; i<len; i++){
		struct json_object *emp=json_object_array_get_idx(arr,i);
		struct json_object *id_obj=json_object_object_get(emp,"employee_ID");
		int json_id = json_object_get_int(id_obj);

		if(json_id==modify_id){
			int choice;	int is_modified=false;
input:
			printf("Choose the field to modify:\n1.Name\n2.Age\n3.Mobile\n4.Address\n5.Quit\n");
			scanf("%d",&choice);
			if(choice>5 || choice<1){
				printf("input valid field: ");
				goto input;
			}
			struct json_object *emp_details=json_object_object_get(emp,"employee_details");
			struct json_object *cont_details=json_object_object_get(emp_details,"contact_details");
			int mod_ret;
			char confirm; 
			switch(choice){
				case 1:{
					char new_name[100];
					printf("Input new Name: ");
input_mod_name:
					scanf(" %[^\n]",new_name);
					mod_ret=validate_name(new_name);
					if(mod_ret==-1){
						printf("input valid name: ");
						goto input_mod_name;
					}
input_name_confirm:
					printf("press Y/N to confirm or cancel changes: ");
					scanf(" %c",&confirm);
					if(confirm=='Y' || confirm =='y'){
						char name_email[100];
						int l;
						for(l=0; new_name[l]!='\0'; l++){
							name_email[l]=tolower(new_name[l]);
							if(name_email[l]==' '){
								name_email[l]='-';
							}
						}
						name_email[l]='\0';
						char new_email[119];
						sprintf(new_email,"%s@maven-silicon.com",name_email);
						json_object_object_add(cont_details,"email",json_object_new_string(new_email));
						json_object_object_add(emp_details,"name",json_object_new_string(new_name));
						is_modified=true;
						goto input;
					}
					else if(confirm == 'n' || confirm == 'N'){
						printf("Cancelled\n");
						goto input;
					}
					else{
						goto input_name_confirm;
					}
					}
				case 2:{
					char new_age_str[5];
					printf("input new Age: ");
input_mod_age:
					scanf(" %s",new_age_str);
					mod_ret=validate_age(new_age_str);
					if(mod_ret==-1){
						printf("input age between 18-100: ");
						goto input_mod_age;
					}
					int new_age=atoi(new_age_str);	
input_age_confirm:
					printf("press Y/N to confirm or cancel changes: ");
					scanf(" %c",&confirm);
					if(confirm=='Y' || confirm == 'y'){
						json_object_object_add(emp_details, "age",json_object_new_int(new_age));
						is_modified=true;
						goto input;
					}
					else if(confirm =='N' || confirm == 'n'){
						printf("Cancelled\n");
						goto input;
					}
					else{
						goto input_age_confirm;
					}
					}
				case 3:{
					char new_mobile[11];
					printf("Input new Mobile number: ");
input_mod_mobile:
					scanf(" %s",new_mobile);
					mod_ret=validate_mobile(new_mobile);
					if(mod_ret==-1){
						printf("enter valid mobile number: ");
						goto input_mod_mobile;
					}
input_mobile_confirm:
					printf("press Y/N to confirm or cancel changes: ");
					scanf(" %c",&confirm);
					if(confirm=='y' || confirm == 'Y'){
						json_object_object_add(cont_details,"mobile_number",json_object_new_string(new_mobile));
						is_modified=true;
						goto input;
					}
					else if(confirm=='N' || confirm == 'n'){
						printf("Cancelled\n");
						goto input;
					}
					else{
						goto input_mobile_confirm;
					}

					}
				/*case 4:{
					char new_email[25];
					printf("input new email: ");
					scanf("%s",new_email);
input_email_confirm:
					printf("press Y/N to confirm or cancel changes: ");
					scanf(" %c",&confirm);
					if(confirm=='Y' || confirm =='y'){
						json_object_object_add(cont_details,"email",json_object_new_string(new_email));
						goto input;
					}
					else if(confirm =='n' || confirm =='N'){
						printf("Cancelled\n");
						goto input;
					}
					else{
						goto input_email_confirm;
					}
				       }*/
				case 4:{
					char new_add[100];
					printf("input new address: ");
					scanf(" %[^\n]",new_add);
input_add_confirm:
					printf("press Y/N to confirm or cancel changes: ");
					scanf(" %c",&confirm);
					if(confirm=='y' || confirm =='Y'){
						json_object_object_add(cont_details, "address",json_object_new_string(new_add));
						is_modified=true;
						goto input;
					}
					else if(confirm == 'n' || confirm == 'N'){
						printf("Cancelled\n");
						goto input;
					}
					else{
						goto input_add_confirm;
					}
					}

				 case 5:
				 	if(is_modified){
				 		return modify_id;
				 	}
				 	else
				       		return 0;

			} //switch
			
		} //if

	} //for
	return -1;
} //function 

int add(struct json_object *root){
	struct json_object *arr=json_object_object_get(root,"employees");
	int len=json_object_array_length(arr);
	int new_id; char confirm;
	if(len==0){
		new_id=1000;
	}
	else{
		struct json_object *last_emp = json_object_array_get_idx(arr,len-1);
		struct json_object *last_id_obj=json_object_object_get(last_emp,"employee_ID");
		//id
		new_id=json_object_get_int(last_id_obj) + 1;
	}
	
	printf("***New employee details***\n");
	//name
	char name[100];
	printf("Name: ");
input_name:
	scanf(" %[^\n]",name);
	int val_name=validate_name(name);
	if(val_name==-1){
		printf("Input valid user Name: ");
		goto input_name;
	}
	//age
	char age_str[4];
	printf("Age: ");
input_age:
	scanf("%3s",age_str);
	int val_age=validate_age(age_str);
	if(val_age==-1){
		printf("Input valid Age between 18-100: ");
		goto input_age;
	}
	int age=atoi(age_str);
	
	//mobile number
	char mobile[12];
	printf("Mobile: ");
input_mobile:
	scanf("%11s",mobile);
	int val_mobile=validate_mobile(mobile);
	if(val_mobile==-1){
		printf("Input Valid mobile number: ");
		goto input_mobile;
	}

	//email
	char email[119];
	int l;
	char name_email[100];
	for(l=0; name[l]!='\0'; l++){
		name_email[l]=tolower(name[l]);
		if(name_email[l]==' '){
			name_email[l]='-';
		}
	}
	name_email[l]='\0';
	sprintf(email,"%s@maven-silicon.com",name_email);

	//address
	char address[100];
	printf("Address: ");
	scanf(" %[^\n]",address);
	
	printf("Name: %s\n",name);
	printf("Age: %d\n",age);
	printf("Mobile: %s\n",mobile);
	printf("Email: %s\n",email);
	printf("Address: %s\n",address);
input_confirm:
	printf("input Y/N to confirm or cancell Add: ");
	scanf(" %c",&confirm);
	if(confirm =='N' || confirm =='n'){
		printf("Cancelled");
		return 0;
	}
	else if( confirm == 'Y' || confirm == 'y'){
	//object creations
	struct json_object *new_contact_obj=json_object_new_object();
	struct json_object *new_emp_details_obj=json_object_new_object();
	struct json_object *new_emp_obj=json_object_new_object();	
	
	//contact insertion
	json_object_object_add(new_contact_obj, "mobile_number", json_object_new_string(mobile));
	json_object_object_add(new_contact_obj, "email",json_object_new_string(email));
	json_object_object_add(new_contact_obj, "address", json_object_new_string(address));

	//details insertion
	json_object_object_add(new_emp_details_obj, "name",json_object_new_string(name));
	json_object_object_add(new_emp_details_obj, "age",json_object_new_int(age));
	json_object_object_add(new_emp_details_obj,"contact_details",new_contact_obj);

	//employee insertion
	json_object_object_add(new_emp_obj,"employee_ID",json_object_new_int(new_id));
	json_object_object_add(new_emp_obj,"employee_details",new_emp_details_obj);

	//inserting to array
	json_object_array_add(arr,new_emp_obj);
	
	return new_id;
	}
	else{
		goto input_confirm;
	}

}	



