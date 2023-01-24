#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include "windows.h"

typedef struct User{
    int age;
    char name[100];
    double salary;
    struct User* next;
} User;

void print(User* user){
    printf("\t%s\t|\t%d\t|\t%.2f\t|\n" , user->name, user->age, user->salary);
}

User* User_Create(char* name, int age, double salary){
    User* user = malloc(sizeof(User));
    strcpy(user->name, name);
    user->age = age;
    user->salary = salary;
    user->next = NULL;
    return user;
}

User* List_push(User* root, User* newUser){
    if(root == NULL){
        return newUser;
    }
    User* tmpUser = root;
    while(tmpUser->next != NULL){
        tmpUser = tmpUser->next;
    }
    tmpUser->next = newUser;
    return root;
}

User* First_step(User* root) {


    FILE *file = NULL;
    file = fopen("base1.txt", "r");
    if(!file){
        printf("Cant open file\n");
        fclose(file);
        return 0;
    }
    else{
        int age;
        char name[100];
        double salary;
        while(fscanf(file, "%s%d%lf", &name, &age, &salary) !=EOF){
            User tmp;
            strcpy(tmp.name, name);
            tmp.age = age;
            tmp.salary = salary;
            root = List_push(root, User_Create(tmp.name, tmp.age, tmp.salary));
        }
        return root;
        fclose(file);
    }

   /* FILE *file = NULL;
    file = fopen("base.csv", "r");
    if (!file) {
        printf("Cant open file\n");
        fclose(file);
        return 0;
    } else {
        printf("file opened\n");
        int age;
        char name[100];
        double salary;

        char buffer[1024];
        int row = 0;
        int column = 0;

        while (fgets(buffer,
                     sizeof(buffer), file)) {
            User tmp;
            column = 0;
            row++;



            // Splitting the data
            char* value = strtok(buffer, ";");

            while (value) {
                // Column 1
                if (column == 0) {
                    strcpy(tmp.name, value);
                }

                // Column 2
                if (column == 1) {
                    tmp.age = atoi(value);
                }

                // Column 3
                if (column == 2) {
                    tmp.salary = atoi(value);
                }

                value = strtok(NULL, ";");
                column++;
            }
            root = List_push(root, User_Create(tmp.name, tmp.age, tmp.salary));

        }
        fclose(file);
        return root;
    }*/
}
int Size_of_struct(User* root){
    int struct_size = 0;
    if (root == 0){
        struct_size = 0;
    }
    else{
        while(root!=0){
            root = root->next;
            struct_size ++;
        }
    }
    return struct_size;
}

User* List_show(User* root){
    if(root == NULL){
        printf("List is empty!\n");
    }
    int i = 0;
    //print("");
    printf("|-------------------------------------------------------------------------------|\n");
    printf("|\tId\t|\tFull name\t|\tAge\t|\tSalary\t\t|\n");
    printf("|-------------------------------------------------------------------------------|\n");
    while(root != NULL){
        printf("|\t[%d]\t|", i);
        print(root);
        root = root->next;
        i++;
    }
    return root;
}


void User_delete(User* user){
    free(user);
}

User* List_remove(User* root, int ind){
    if(root == NULL){
        return root;
    }
    if(ind == 0){
        User* next = root->next;
        User_delete(root);
        return next;
    }
    User* prev = root;
    User* current = root;
    int i = 0;
    while(current != NULL){
        if(ind == i){
            prev->next = current->next;
            User_delete(current);
            break;
        }
        prev = current;
        current = current->next;
        i++;
    }
    return root;

}


User* Menu_createUser(User* root){
    User tmp;
    printf("Input name:");
    scanf("%s", &tmp.name);
    printf("Input age:");
    scanf("%d", &tmp.age);
    printf("Input salary:");
    scanf("%lf", &tmp.salary);
    root = List_push(root, User_Create(tmp.name, tmp.age, tmp.salary));
    return root;
}


int Show_menu(){
    printf("MENU:\n");
    printf("1. Show all users from file\n");
    printf("2. Add new user\n");
    printf("3. Delete exist user\n");
    printf("4. Sort data by salary\n");
    printf("5. Sort data by full name\n");
    printf("6. Find data\n");
    printf("7. Exit\n");
    printf("Input action [1-6]:\n");
    int actionId;
    scanf("%d", &actionId);
    return actionId;
}

User* Sort_salary_inc(User* root){

    User* result_root = NULL;
    while (root != NULL){
        User* temp = root;
        root = root->next;

        if (result_root == NULL || temp->salary < result_root->salary){
            temp->next = result_root;
            result_root = temp;
        }
        else{
            User* current = result_root;
            while (current->next != NULL && !(temp->salary < current->next->salary)){
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    return result_root;
}


User* Sort_salary_desc(User* root){

    User* result_root = NULL;
    while (root != NULL){
        User* temp = root;
        root = root->next;
        if (result_root == NULL || temp->salary > result_root->salary){
            temp->next = result_root;
            result_root = temp;
        }
        else{
            User* current = result_root;
            while (current->next != NULL && (temp->salary > current->next->salary)){
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    return result_root;
}

User* Sort_names_inc(User* root){

    User* result_root = NULL;
    while (root != NULL){
        User* temp = root;
        root = root->next;

        if (result_root == NULL || (strcmp(temp->name,result_root->name) < 0) ){
            temp->next = result_root;
            result_root = temp;
        }
        else{
            User* current = result_root;
            while (current->next != NULL && !(strcmp(temp->name,current->next->name) < 0)){
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    return result_root;
}

User* Sort_names_desc(User* root){

    User* result_root = NULL;
    while (root != NULL){
        User* temp = root;
        root = root->next;

        if (result_root == NULL || (strcmp(temp->name,result_root->name) > 0) ){
            temp->next = result_root;
            result_root = temp;
        }
        else{
            User* current = result_root;
            while (current->next != NULL && strcmp(temp->name, current->next->name) <= 0){
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    return result_root;
}

User* Find_name(User* root, char* substr){
    char *search_str;
    int i = 0;

    printf("|-------------------------------------------------------------------------------|\n");
    printf("|\tId\t|\tFull name\t|\tAge\t|\tSalary\t\t|\n");
    printf("|-------------------------------------------------------------------------------|\n");

    while(root != NULL){
        search_str = strstr(root->name, substr);
        if(search_str != NULL){
            printf("|\t[%d]\t|", i);
            print(root);
            i++;
        }
        root = root->next;
    }
    return root;
}

User* Find_salary(User* root, int first_num, int last_num){
    int i = 0;

    printf("|-------------------------------------------------------------------------------|\n");
    printf("|\tId\t|\tFull name\t|\tAge\t|\tSalary\t\t|\n");
    printf("|-------------------------------------------------------------------------------|\n");

    while(root != NULL){
        if(root->salary >= first_num && root->salary <= last_num){
            printf("|\t[%d]\t|", i);
            print(root);
            i++;
        }
        root = root->next;
    }
    return root;
}

int Rewrite_file(User* root) {
    FILE *file = NULL;
    int size = Size_of_struct(root);
    file = fopen("base.csv", "w");
    if (!file) {
        printf("File was deleted or removed: check file\n");
        fclose(file);
        return 0;
    } else {
        printf("file opened\n");
        for (int i = 0; i < size; i++) {
            fprintf(file, "%s;%d;%lf\n", root->name, root->age, root->salary);
            root = root->next;
        }

        fclose(file);
    }
}


    int main() {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        setlocale(LC_ALL, "Ru");

        User *rootUser = NULL;
        rootUser = First_step(rootUser);
        User *sorted_data = NULL;
        int t = 1;
        while (t) {
            int action = Show_menu();

            switch (action) {
                case 1: {
                    List_show(rootUser);
                }
                    break;
                case 2: {
                    rootUser = Menu_createUser(rootUser);
                }
                    break;
                case 3: {
                    printf("Enter user index: \n");
                    int index = 0;
                    scanf("%d", &index);
                    rootUser = List_remove(rootUser, index);
                }
                    break;


                case 4: {
                    //Sort data
                    //int sort_item = 1;
                    int sort_flag = 0;
                    printf("Sort parameters: 0 - inc, 1 - desc: \n");
                    scanf("%d", &sort_flag);
                    printf("Enter the last number of the range in salary: \n");
                    /*printf("Enter 1 for sort by salary or 2 for sort by full name: ");
                    scanf("%d", &sort_item);*/
                        if (sort_flag == 0) {
                            sorted_data = Sort_salary_inc(rootUser);
                        }
                        else if (sort_flag == 1){
                            sorted_data = Sort_salary_desc(rootUser);
                        }
                    List_show(sorted_data);



                }
                    break;
                case 5:{
                    int sort_flag = 0;
                        printf("Sort parameters: 0 - inc, 1 - desc: \n");
                        scanf("%d", &sort_flag);
                        if (sort_flag == 0) {
                            sorted_data = Sort_names_inc(rootUser);
                        }
                        else if (sort_flag == 1) {
                            sorted_data = Sort_names_desc(rootUser);
                        }

                    List_show(sorted_data);


                } break;
                case 6: {
                    int find_item = 1;
                    printf("Choose 1 for find by name or 2 for find by salary: \n");
                    scanf("%d", &find_item);
                    if (find_item == 1) {
                        char str_name[100];
                        printf("Enter name for search: \n");
                        scanf("%s", str_name);
                        Find_name(rootUser, str_name);
                    } else if (find_item == 2) {
                        int first_num = 0;
                        int last_num = 0;
                        printf("Enter the first number of the range: \n");
                        scanf("%d", &first_num);
                        printf("Enter the last number of the range:\n");
                        scanf("%d", &last_num);
                        Find_salary(rootUser, first_num, last_num);
                    }

                }
                    break;
                case 7: {
                    Rewrite_file(rootUser);
                    printf("Good Bye!");
                    t = 0;
                }
                    break;
            }
        }
        return 0;
    }

