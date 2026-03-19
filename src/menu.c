#include<stdio.h>
#include<stdlib.h>
void show_menu();
void back_menu();
int main()
{
    back_menu();
    return 0;
}
void show_menu()
{
    char op;
do {
        printf("-----------------------------------------------\n");
    printf("                MAIN MENU                     \n");
    printf("Select an option from the menu below:\n");
    printf("1. Run a system diagnosis\n");
    printf("2. Check logs\n");
    printf("3. Risk list\n");
    printf("4. About\n");
    printf("5. Exit\n");
    printf("-----------------------------------------------\n");
    printf("Enter your choice[1/2/3/4/5] \n");
    scanf(" %c",&op);
    switch(op)
    {
        case '1':
            printf("Running system diagnosis...\n");
            //run_diagnosis();
            break;
        case '2':
            printf("Checking logs...\n");
            //check_logs();
            break;
        case '3':
            printf("Displaying risk list...\n");
            //show_risk_list();
            break;
        case '4':
            printf("About: This is a system utility program.\n");
            //about();
            break;
        case '5':
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid option selected. Please try again.\n");
    }
}while (op!='5');
    
}
void back_menu()
{
    char op2;
    while(1)
    {
        printf("\nEnter 'M for Main Menu or 'E' to Exit\n");
        printf("Enter M/E: ");
        scanf(" %c",&op2);

        if(op2=='m' || op2=='M')
        {
            return;
        }
        else if (op2=='e' || op2=='E')
        {
            printf("Exiting Program, Goodbye.");
            exit(0);
        }
        else
        {
            printf("Invalid input!\n");
        }
        
    }
}