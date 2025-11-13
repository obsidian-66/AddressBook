#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

int loadContactsFromFile(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);

int name_validation(char *str);
int number_validation(char *str);
int email_validation(char *str);

int search_name(char *str, int start, AddressBook *addressBook);
int search_number(char *str, AddressBook *addressBook);
int search_email(char *str, AddressBook *addressBook);

void display_single(int index, AddressBook *addressBook);

void edit_element(int index, AddressBook *addressBook);
void delete_element(int index, AddressBook *addressBook);

void clear_buffer();

int prompt_search_choice();
int prompt_valid_name(char *str);
int prompt_valid_number(char *str);
int prompt_valid_email(char *str);

#endif
