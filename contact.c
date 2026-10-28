#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    switch(sortCriteria)
    {
        case 1:printf("Sorting by name : \n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index No\tName\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
    
        case 2:printf("Sorting by phone : \n");
            for(int i=0;i<addressBook->contactCount-1;i++)
            {
                for(int j=0;j<addressBook->contactCount-i-1;j++)
                {
                    if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index No\tName\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;

    case 3:printf("Sorting by email : \n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index No\tName\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        default:
        printf("Invalid choice\n");
        return;
    }
    
}

void initialize(AddressBook *addressBook) {
    
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	Contact newContact;
    int i,valid;

    while(1)
    {
        printf("Enter Name : ");
        scanf(" %[^\n]",newContact.name);

        valid=1;

        for(i=0;newContact.name[i]!='\0';i++)
        {
            if(!(isalpha(newContact.name[i] )||newContact.name[i]==' '))
            {
                valid=0;
                break;
            }
        }
        if(valid)
            break;

        printf("Invalid Name!Use only alphabets.\n");
    }

    while(1)
    {
        printf("Enter Phone : ");
        scanf("%s",newContact.phone);

        valid=1;

        if(strlen(newContact.phone)!=10)
            valid=0;
        
        for(i=0;newContact.phone[i]!='\0' && valid;i++)
        {
            if(!isdigit(newContact.phone[i]))
            {
                valid=0;
                break;
            
            }
        }
        if(valid)
        {
            if(newContact.phone[0]<'6'||newContact.phone[0]>'9')
                valid=0;
        }

        if(valid)
        {
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(newContact.phone,
                        addressBook->contacts[i].phone)==0)
                {
                    printf("Phone number already exists!\n");
                    valid=0;
                    break;
                }

            }
        }
        if(valid)
            break;
        
            printf("Invalid Phone Number!\n");

    }
    while(1)
    {
        int at=0;
        printf("Enter Email : ");
        scanf("%s",newContact.email);

        valid=1;

        if(isdigit(newContact.email[0]))
            valid=0;

        for(i=0;newContact.email[i]!='\0';i++)
        {
            if(newContact.email[i]=='@')
                at++;
        }
        if(at!=1)
            valid=0;

        if(valid)
        {
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(newContact.email,
                            addressBook->contacts[i].email)==0)
                {
                    printf("Email already exists!\n");
                    valid=0;
                    break;
                }
            }
        }
        if(valid)
            break;

        printf("Invalid Email!\n");
    }
    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;

    printf("\nContact Added Successfully.\n");
}

int searchContact(AddressBook *addressBook)
{
    int choice, i;
    char key[100];

    while(1)
    {
        
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int matchedIndex[addressBook->contactCount];
                int count = 0, option;

                printf("Enter Name : ");
                scanf(" %[^\n]", key);

                printf("\nMatching Contacts:\n");

                for(i = 0; i < addressBook->contactCount; i++)
                {
                    // Partial match (starts with entered characters)
                    if(strncmp(addressBook->contacts[i].name, key, strlen(key)) == 0)
                    {
                        matchedIndex[count] = i;

                        printf("%d. %s\n", count + 1, addressBook->contacts[i].name);
                        printf("   Phone : %s\n", addressBook->contacts[i].phone);
                        printf("   Email : %s\n\n", addressBook->contacts[i].email);

                        count++;
                    }
                }

                if(count == 0)
                {
                    printf("Contact Not Found.\n");
                    break;
                }

                if(count == 1)
                {
                    return matchedIndex[0];
                }

                printf("Enter your choice (1-%d): ", count);
                scanf("%d", &option);

                if(option >= 1 && option <= count)
                {
                    return matchedIndex[option - 1];
                }
                else
                {
                    printf("Invalid Choice\n");
                    return -1;
                }
            }

            case 2:
            {
                int matchedIndex[addressBook->contactCount];
                int count = 0, option;

                printf("Enter Phone Number : ");
                scanf("%s", key);

                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, key) == 0)
                    {
                        matchedIndex[count] = i;

                        printf("%d. %s\n", count + 1, addressBook->contacts[i].name);
                        printf("   Phone : %s\n", addressBook->contacts[i].phone);
                        printf("   Email : %s\n\n", addressBook->contacts[i].email);

                        count++;
                    }
                }

                if(count == 0)
                {
                    printf("Contact Not Found.\n");
                    break;
                }

                if(count == 1)
                {
                    return matchedIndex[0];
                }

                printf("Enter your choice (1-%d): ", count);
                scanf("%d", &option);

                if(option >= 1 && option <= count)
                {
                    return matchedIndex[option - 1];
                }
                else
                {
                    printf("Invalid Choice\n");
                    return -1;
                }
            }

            case 3:
            {
                int matchedIndex[addressBook->contactCount];
                int count = 0, option;

                printf("Enter Email ID : ");
                scanf("%s", key);

                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].email, key) == 0)
                    {
                        matchedIndex[count] = i;

                        printf("%d. %s\n", count + 1, addressBook->contacts[i].name);
                        printf("   Phone : %s\n", addressBook->contacts[i].phone);
                        printf("   Email : %s\n\n", addressBook->contacts[i].email);

                        count++;
                    }
                }

                if(count == 0)
                {
                    printf("Contact Not Found.\n");
                    break;
                }

                if(count == 1)
                {
                    return matchedIndex[0];
                }

                printf("Enter your choice (1-%d): ", count);
                scanf("%d", &option);

                if(option >= 1 && option <= count)
                {
                    return matchedIndex[option - 1];
                }
                else
                {
                    printf("Invalid Choice\n");
                    return -1;
                }
            }

            case 4:
                printf("Exiting Search...\n");
                return -1;

            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int index, choice;

    index = searchContact(addressBook);

    if(index == -1)
        return;

    while(1)
    {
        printf("\n------ Edit Menu ------\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter New Name : ");
                scanf(" %[^\n]", addressBook->contacts[index].name);
                printf("Name Updated Successfully.\n");
                return;

            case 2:
                printf("Enter New Phone Number : ");
                scanf("%s", addressBook->contacts[index].phone);
                printf("Phone Number Updated Successfully.\n");
                return;

            case 3:
                printf("Enter New Email ID : ");
                scanf("%s", addressBook->contacts[index].email);
                printf("Email Updated Successfully.\n");
                return;

            case 4:
                printf("Exiting Edit Menu...\n");
                return;

            default:
                printf("Invalid Choice!\n");
        }
    }
}



    



void deleteContact(AddressBook *addressBook)
{
    int index, i;
    char ch;

    index = searchContact(addressBook);

    if(index == -1)
    {
        return;
    }

    printf("\nDo you want to delete this contact? (Y/N): ");
    scanf(" %c", &ch);

    if(ch == 'Y' || ch == 'y')
    {
        for(i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact Deleted Successfully.\n");
    }
    else
    {
        printf("Deletion Cancelled.\n");
    }
}
 




