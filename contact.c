#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"

void clear_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int prompt_search_choice()
{
    int choice;
    while(1)
        {
            system("clear");
            printf("Search by: \n1. Name \n2. Number \n3. Email \nEnter Choice : ");
            scanf("%d", &choice);
            clear_buffer();

            if(choice>=1 && choice<=3)
                return choice;
            else
                printf("\033[1;31mError! Enter a valid choice!\033[0m");

            clear_buffer();
        }
}

int prompt_valid_name(char *str)
{
    while(1)
        {
            system("clear");
            printf("Enter name : ");
            scanf("%[^\n]", str);
            clear_buffer();

            if(name_validation(str))
                return 1;
            else   
                printf("\033[1;31mError: Invalid Name! Use only letters and spaces.\033[0m\n");

            clear_buffer();
        }
}

int prompt_valid_number(char *str)
{
    while(1)
        {
            system("clear");
            printf("Enter phone number: ");
            scanf("%[^\n]", str);
            clear_buffer();
            
            int valid = number_validation(str);
            if(valid == 1)
                return 1;
            else if(valid == -1)
                printf("\033[1;31mError: Number must be only 10 digits.\033[0m\n");
            else if(valid == 0)
                printf("\033[1;31mError: Number must contain only digits.\033[0m\n");

            clear_buffer();
        }
}

int prompt_valid_email(char *str)
{
    while(1)
        {
            system("clear");
            printf("Enter email: ");
            scanf("%[^\n]", str);
            clear_buffer();

            int valid = email_validation(str);
            if(valid == 1)
                return 1;
            else if(valid == 0)
                printf("\033[1;31mError! Missing '@'\033[0m\n");
            else if(valid == -1)
                printf("\033[1;31mError! Missing or invalid .com\033[0m\n");
            else if(valid == -2)
                printf("\033[1;31mError! User name must be only lowercase letters.\033[0m\n");
            else if(valid == -3)
                printf("\033[1;31mError! Missing domain name.\033[0m\n");
            else if(valid == -4)
                printf("\033[1;31mError! Domain name must be lowercase letters.\033[0m\n");

            clear_buffer();
        }
}

void listContacts(AddressBook *addressBook)
{
    system("clear");
	int index = addressBook->contactCount;
    printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Number", "Email ID");
    for(int i=0; i<index; i++)
        {
            printf("%-5d %-20s %-15s %-30s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    clear_buffer();
}

void display_single(int index, AddressBook *addressBook)
{
    printf("%-20s %-15s %-30s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    int file_check = loadContactsFromFile(addressBook);

    if (file_check == 0)
        {
            populateAddressBook(addressBook);
        }
}

int loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");
    if(fp == NULL)
        {
            return 0;
        }
    else    
        {
            fscanf(fp, "%d\n", &addressBook->contactCount);
            int count = addressBook->contactCount;

            for(int i=0; i<count; i++)
                {
                    fscanf(fp, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            fclose(fp);
            return 1;
        }
}

void saveContactsToFile(AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    FILE *fp = fopen("contacts.csv", "w");

    fprintf(fp, "%d\n", addressBook->contactCount);
    for(int i=0; i<count; i++)
        {
            fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    fclose(fp);

    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    char name[50], num[20], email[50];
    int index = addressBook->contactCount;

    //Name entry and validation
    while(1)
        {
            system("clear");
            printf("Enter Name : ");
            scanf("%[^\n]", name);
            clear_buffer();

            if(name_validation(name))               //break if validation is true
                {
                    strcpy(addressBook->contacts[index].name, name);
                    break;
                }
            else
                printf("\033[1;31mError! Enter a valid name.\033[0m\n");

            clear_buffer();
        }

    //Number entry and validation
    while(1)                            
        {
            system("clear");
            printf("Enter number : ");
            scanf("%[^\n]", num);
            clear_buffer();
            
            int valid = number_validation(num);
            if(valid == 1)
                {
                    if(search_number(num, addressBook) != -1)
                        {
                            printf("\033[1;31mError! Duplicate entry detected. Enter unique phone number.\033[0m");
                        }
                    else
                        {
                            strcpy(addressBook->contacts[index].phone, num);
                            break;
                        }
                }
                
            else if(valid == -1)
                printf("\033[1;31mError! Number should contain 10 digits\033[0m\n");
            else if(valid == 0)
                printf("\033[1;31mError! Number should contain only digits\033[0m\n");
            
            clear_buffer();
        }

    //Email entry and validation
    while(1)                            
        {
            system("clear");
            printf("Enter Email : ");
            scanf("%[^\n]", email);
            clear_buffer();
            
            int valid = email_validation(email);
            if(valid == 1)
                {
                    if(search_email(email, addressBook) != -1)
                        {
                            printf("\033[1;31mError! Duplicate entry detected. Enter unique email.\033[0m");
                        }
                    else
                        {
                            strcpy(addressBook->contacts[index].email, email);
                            break;
                        }
                }
            else if(valid == 0)
                printf("\033[1;31mError, no @ present.\033[0m\n");
            else if(valid == -1)
                printf("\033[1;31mError, no .com present.\033[0m\n");
            else if(valid == -2)
                printf("\033[1;31mError, username should be lower case.\033[0m\n");
            else if(valid == -3)
                printf("\033[1;31mError, no domain name present.\033[0m\n");
            else if(valid == -4)
                printf("\033[1;31mError, domain name should be lower case.\033[0m\n");

            clear_buffer();
        }
    
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook)
{
    int choice, index = addressBook->contactCount;
    choice = prompt_search_choice();
    
    switch(choice)              
        {
            case 1:
                {
                    char name[50];
                    prompt_valid_name(name);
                    
                    int indices[index];                                  //store name indices in case of repeating names
                    for(int i=0; i<index; i++)
                        indices[i] = -1;

                    int found = 0;
                    for(int i=0; i<index; i++)
                        {
                            int val = search_name(name, i, addressBook);
                            if(val!=-1)
                                {
                                    indices[found++] = val;
                                    i = val;
                                }
                        }

                    if(found == 0)
                        printf("\033[1;31mNo contact found with the given name. \033[0m");
                    else
                        {
                            printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Number", "Email ID");
                            for(int i=0; i<found; i++)
                                {
                                    printf("%-5d ", i+1);
                                    display_single(indices[i], addressBook);
                                }
                        }
                    break;
                }
            case 2:
                {
                    char number[50];
                    prompt_valid_number(number);
                    
                    int val = search_number(number, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given number.\033[0m");
                    else
                        {
                            printf("%-5s %-20s %-15s %-30s\n", "1.", "Name", "Number", "Email ID");
                            display_single(val, addressBook);
                        }
                    break;
                }
            case 3:
                {
                    char email[50];
                    prompt_valid_email(email);
                    
                    int val = search_email(email, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given email.\033[0m");
                    else
                        {
                            printf("%-5s %-20s %-15s %-30s\n", "1.", "Name", "Number", "Email ID");
                            display_single(val, addressBook);
                        }
                    break;
                }
        }
    clear_buffer();
}

void editContact(AddressBook *addressBook)
{
    int choice, index = addressBook->contactCount;
    choice = prompt_search_choice();                                    //search by
    
    switch(choice)                           
        {
            case 1:
                {
                    char name[50];
                    prompt_valid_name(name);
                    
                    int indices[index];                                 //store name indices in case of repeating names
                    for(int i=0; i<index; i++)
                        indices[i] = -1;

                    int found = 0;
                    for(int i=0; i<index; i++)
                        {
                            int val = search_name(name, i, addressBook);
                            if(val!=-1)
                                {
                                    indices[found++] = val;
                                    i = val;
                                }
                        }
                    
                    if(found == 0)
                        {
                            printf("\033[1;31mNo contact found with the given name.\033[0m");
                        }
                    else
                        {
                            printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Number", "Email ID");
                            for(int i=0; i<found; i++)
                                {
                                    printf("%-5d ", i+1);
                                    display_single(indices[i], addressBook);
                                }

                            printf("\nEnter the contact Sl. No. to edit: ");
                            int num;
                            while(1)
                                {
                                    scanf("%d", &num);
                                    clear_buffer();
                                    if(num<=found && num>=1)
                                        {   
                                            edit_element(indices[num-1], addressBook);
                                            break;
                                        }
                                    else    
                                        printf("\033[1;31mError! Enter a valid number.\033[0m");
                                }
                        }
                    break;
                }
            case 2:
                {
                    char number[50];
                    prompt_valid_number(number);
                    
                    int val = search_number(number, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given number.\033[0m");
                    else
                        {
                            edit_element(val, addressBook);
                        }
                    break;
                }
            case 3:
                {
                    char email[50];
                    prompt_valid_email(email);
                    
                    int val = search_email(email, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given email.\033[0m");
                    else
                        {
                            edit_element(val, addressBook);
                        }
                    break;
                }
        }
    clear_buffer();
}

void edit_element(int index, AddressBook *addressBook)
{
    char name[50], num[20], email[50];

    //Name entry and validation
    while(1)
        {
            system("clear");
            printf("Enter Name (Enter x to skip) : ");
            scanf("%[^\n]", name);
            clear_buffer();

            if(strcmp(name, "x") == 0)
                break;
            else
                {
                    if(name_validation(name))                //break if validation is true
                        {
                            strcpy(addressBook->contacts[index].name, name);
                            break;
                        }
                    else
                        printf("\033[1;31mError, Invalid Name. Try again.\033[0m\n");
                }

            clear_buffer();
        }

    //Number entry and validation
    while(1)                            
        {
            system("clear");
            printf("Enter number (Enter x to skip) : ");
            scanf("%[^\n]", num);
            clear_buffer();

            if(strcmp(num, "x") == 0)
                break;
            else
                {
                    int valid = number_validation(num);
                    if(valid == 1)
                        {
                            if(search_number(num, addressBook) != -1 && search_number(num, addressBook) != index)
                                {
                                    printf("\033[1;31mError! Duplicate entry detected. Enter unique phone number.\033[0m");
                                }
                            else
                                {
                                    strcpy(addressBook->contacts[index].phone, num);
                                    break;
                                }
                        }
                    else if(valid == -1)
                        printf("\033[1;31mError, enter number should contain 10 digits.\033[0m\n");
                    else if(valid == 0)
                        printf("\033[1;31mError, enter number should contain only digits.\033[0m\n");
                }
            
            clear_buffer();
        }

    //Email entry and validation
    while(1)                            
        {
            system("clear");
            printf("Enter Email (Enter x to skip) : ");
            scanf("%[^\n]", email);
            clear_buffer();

            if(strcmp(email, "x") == 0)
                break;
            else
                {
                    int valid = email_validation(email);
                    if(valid == 1)
                        {
                            if(search_email(email, addressBook) != -1 && search_email(email, addressBook) != index)
                                {
                                    printf("\033[1;31mError! Duplicate entry detected. Enter unique email.\033[0m");
                                }
                            else
                                {
                                    strcpy(addressBook->contacts[index].email, email);
                                    break;
                                }
                        }
                    else if(valid == 0)
                        printf("\033[1;31mError, no @ present.\033[0m\n");
                    else if(valid == -1)
                        printf("\033[1;31mError, no .com present.\033[0m\n");
                    else if(valid == -2)
                        printf("\033[1;31mError, username should be lower case.\033[0m\n");
                    else if(valid == -3)
                        printf("\033[1;31mError, no domain name present.\033[0m\n");
                    else if(valid == -4)
                        printf("\033[1;31mError, domain name should be lower case.\033[0m\n");
                }

            clear_buffer();
        }
}

void deleteContact(AddressBook *addressBook)
{
    int choice, index = addressBook->contactCount;
    choice = prompt_search_choice();
    
    switch(choice)              
        {
            case 1:
                {
                    char name[50];
                    prompt_valid_name(name);
                    
                    int indices[index];                                  //store name indices in case of repeating names
                    for(int i=0; i<index; i++)
                        indices[i] = -1;

                    int found = 0;
                    for(int i=0; i<index; i++)
                        {
                            int val = search_name(name, i, addressBook);
                            if(val!=-1)
                                {
                                    indices[found++] = val;
                                    i = val;
                                }
                        }
                    
                    if(found == 0)
                        printf("\033[1;31mNo contact found with the given name.\033[0m");
                    else
                        {
                            printf("%-5s %-20s %-15s %-30s\n", "Sl.No", "Name", "Number", "Email ID");
                            for(int i=0; i<found; i++)
                                {
                                    printf("%-5d ", i+1);
                                    display_single(indices[i], addressBook);
                                }
                            
                            printf("\nEnter the contact Sl. No. to delete: ");
                            int num;
                            while(1)
                                {
                                    scanf("%d", &num);
                                    clear_buffer();
                                    if(num<=found && num>=1)
                                        {   
                                            delete_element(indices[num-1], addressBook);
                                            break;
                                        }
                                    else    
                                        printf("\033[1;31mEntry invalid! Try again.\033[0m");
                                }
                        }
                    break;
                }
            case 2:
                {
                    char number[50];
                    prompt_valid_number(number);
                    
                    int val = search_number(number, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given number.\033[0m");
                    else
                        {
                            delete_element(val, addressBook);
                        }
                    break;
                }
            case 3:
                {
                    char email[50];
                    prompt_valid_email(email);
                    
                    int val = search_email(email, addressBook);

                    if(val == -1)
                        printf("\033[1;31mNo contact found with the given email.\033[0m");
                    else
                        {
                            delete_element(val, addressBook);
                        }
                    break;
                }
        }
    clear_buffer();
}

void delete_element(int index, AddressBook *addressBook)
{
    int len = addressBook->contactCount;

    for(int i=index; i<len-1; i++)
        {
            strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
            strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
            strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email);
        }
    addressBook->contactCount--;
    
    printf("\nContact Deleted.");
    clear_buffer();
}

int name_validation(char *str)         //ret 0 if error
{
    int len = strlen(str);
    for(int i=0; i<len; i++)
        {
            if(!isalpha((unsigned int)str[i]) && str[i] != ' ')         //check if alphabet
                return 0;
            else
                {
                    if(i == 0 || (i>0 && (str[i-1] == ' ')))            //convert first letter to upper case
                        str[i] = toupper((unsigned char)(str[i]));
                    else   
                        str[i] = tolower((unsigned char)(str[i]));      //else all to lowercase
                }
        }

    for(int i=0; i<len; i++)                                            //remove consecutive spaces and leading space
        {
            if(str[0] == ' ' || (str[i]==' ' && str[i+1] == ' '))
                {
                    for(int j=i; j<len; j++)
                        {
                            str[j] = str[j+1];
                        }
                    len--;                                              //\0 is left shifted, so len decreases
                    i--;                                                //check from the last occurance of space
                }
        }
    return 1;
}

int number_validation(char *str)       //ret -1 if len!=10; 0 if not digit
{
    int len = strlen(str);
    
    if(len!=10)                                         //len==10
        return -1;

    for(int i=0; i<len; i++)                        
        {
            if(!isdigit((unsigned int)str[i]))         //check if digit
                return 0;
        }
    return 1;
}

int email_validation(char *str)        //ret; 0: no @;; -1: no .com;; -2: upper/characters present;; -3: no domain;; -4: domain case error
{
    int len = strlen(str);
    int at_loc, dot_loc;
    
    if(strchr(str,'@'))                         //returns a pointer to the first occurance of the char
        at_loc = strchr(str,'@') - str;     
    else
        return 0;

    if(strrchr(str,'.'))                        //check the last occurance of .
        {   
            dot_loc = strrchr(str,'.') -str;

            if (len < dot_loc + 4 || strcmp(&str[dot_loc], ".com") != 0)
                return -1;

        }
    else
        return -1;

    for(int i=0; i<at_loc; i++)                 //check for alphabets
        if(!islower((unsigned char)str[i]) && !isdigit((unsigned char)str[i]))
            return -2;

    if((at_loc>dot_loc)||(dot_loc == at_loc+1))
        return -3;                               //check domain between @ and .
    else
        for(int i=at_loc+1; i<dot_loc; i++)            //check domain is only lowercase
            if(!islower((unsigned char)str[i]))
                return -4;

    return 1;
}

int search_name(char *str, int start, AddressBook *addressBook)    //start value is the beginning of search
{
    int index = addressBook->contactCount;
    for(int i=start; i<index; i++)
        {
            if(strstr(addressBook->contacts[i].name, str) != NULL)          //strcasecmp does case insensitive comparison
                return i;
        }
    return -1;
}

int search_number(char *str, AddressBook *addressBook)                 //ret index if true, -1 false  
{
    int index = addressBook->contactCount;
    for(int i=0; i<index; i++)
        {
            if(strcmp(str,addressBook->contacts[i].phone) == 0)
                return i;
        }
    return -1;
}

int search_email(char *str, AddressBook *addressBook)                 //ret index if true, -1 false     
{
    int index = addressBook->contactCount;
    for(int i=0; i<index; i++)
        {
            if(strcmp(str,addressBook->contacts[i].email) == 0)
                return i;
        }
    return -1;
}