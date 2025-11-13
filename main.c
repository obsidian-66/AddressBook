#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    while(1) 
        {
            system("clear");
            printf("\nAddress Book Menu:\n");
            printf("1. Create contact\n");
            printf("2. Search contact\n");
            printf("3. Edit contact\n");
            printf("4. Delete contact\n");
            printf("5. List all contacts\n");
            printf("6. Exit\n");
            printf("\n\033[1;31m Enter your choice: \033[0m");
            scanf("%d", &choice);
            getchar();
            
            switch (choice) 
            {
                case 1:
                    createContact(&addressBook);
                    break;
                case 2:
                    searchContact(&addressBook);
                    break;
                case 3:
                    editContact(&addressBook);
                    break;
                case 4:
                    deleteContact(&addressBook);
                    break;
                case 5:          
                    listContacts(&addressBook);
                    break;
                case 6:
                    printf(" Exiting...\n");
                    saveContactsToFile(&addressBook);
                    break;
                default:
                    {
                        printf("\033[1.31m Invalid choice. Please try again.\033[0m\n");
                        clear_buffer();
                    }
            }
        }
    
    return 0;
}
