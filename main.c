#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_ACCOUNTS 100

typedef struct
{
    char name[30];
    char password[30];
} user;
typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char acc_number[30];
    char name[30];
    char mobile[12];
    char email_address[60];
    double balance;
    date date_opened;
} account;

int login()
{
    user user_check, user_input;
    FILE *users=fopen("users.txt","r");
    if(users == NULL)
    {
        printf("Sorry,No users found!\n");
        return 0;
    }
    else do
        {
            printf("Enter Username:\n");
            gets(user_input.name);
            printf("Enter Password:\n");
            gets(user_input.password);
            while(!feof(users))
            {
                fscanf(users,"%s %s", user_check.name, user_check.password);
                if(strcmp(user_input.name, user_check.name)==0 && strcmp(user_input.password, user_check.password)==0)
                {
                    fclose(users);
                    printf("Logged In Successfully\n");
                    printf("-----------------------\n");
                    return 1;
                }
            }
            printf("User doesn't exist,please try again\n");
            rewind(users);
        }
        while(1);
}

void load_accounts(account x[], int *i)
{
    char temp[150];
    char *dlim = ",-";
    FILE *accounts = fopen("accounts.txt", "r");
    if (accounts != NULL)
    {
        while (fgets(temp, 149, accounts) != NULL)
        {
            char *token = strtok(temp, dlim);;
            if (token != NULL) strcpy(x[*i].acc_number, token);
            token = strtok(NULL, dlim);
            if (token != NULL) strcpy(x[*i].name, token);
            token = strtok(NULL, dlim);
            if (token != NULL) strcpy(x[*i].email_address, token);
            token = strtok(NULL, dlim);
            if (token != NULL) x[*i].balance = atof(token);
            token = strtok(NULL, dlim);
            if (token != NULL) strcpy(x[*i].mobile, token);
            token = strtok(NULL, dlim);
            if (token != NULL) x[*i].date_opened.month = atoi(token);
            token = strtok(NULL, dlim);
            if (token != NULL) x[*i].date_opened.year = atoi(token);


            (*i)++;
        }
        fclose(accounts);
    }
    else
        printf("There are no accounts! You can add some.\n");
}
//Validations

int validate_email(char* str)
{
    int i, at_position = -1, dot_position = -1, count =0;
    int length = strlen(str);

    for (i = 0; i < length ; i++)
        if (str[i] == '@')
        {
            count++;
            at_position = i;
        }
    if (count != 1 || at_position < 1)
        return 0;

    for (i = 0; i < at_position ; i++)
        if (!(isalnum(str[i]) || str[i] == '.' || str[i] == '_' ))
            return 0;
    count =0; //for dots
    for (i = at_position+1 ; i < length; i++)
        if (str[i] == '.')
        {
            count++;
            dot_position=i;
        }
    if (count != 1 || dot_position == at_position+1)
        return 0;
    for (i = at_position+1 ; i < dot_position; i++)
        if (!isalpha(str[i]))
            return 0;

    if(str[dot_position + 1] !='c' || str[dot_position + 2] !='o' || str[dot_position + 3] !='m')
        return 0;
    return 1;
}

int validate_mobile_number(char* str)
{
    if (str==NULL)
        return -1;
    int i,len=strlen(str);
    if (len !=11)
        return -1;
    for (i=0; i<len; i++)
    {
        if (isdigit(str[i]) != 1)
            return -1;
    }
    if( !(  str[0]=='0' && str[1]=='1' &&  (str[2]=='0' || str[2]=='1' || str[2]=='2' || str[2]=='5')  ) )
        return -1;
    return 1;
}

double validate_withamount(char *str)
{
    if (str==NULL)
        return -1.0;
    int i,len = strlen (str);
    int num_dot=0;
    for (i=0; i<len; i++)
    {

        if (isdigit(str[i]) !=1 && str[i] != '.')
            return -1.0;
        else if (str[i] == '.')
            num_dot++;
    }
    if (num_dot>1 )
        return -1.0;
    return atof(str);
}
void Save(account x[],int *i)
{
    int j;
    FILE *accounts=fopen("accounts.txt","w");
    if (accounts != NULL)
    {
        for(j=0 ; j<*i-1 ; j++)
        {
            fprintf(accounts,"%s,%s,%s,", x[j].acc_number, x[j].name, x[j].email_address);
            fprintf(accounts,"%.2lf,%s,%d-%d\n",x[j].balance, x[j].mobile,x[j].date_opened.month, x[j].date_opened.year);
        }
        fprintf(accounts,"%s,%s,%s,", x[j].acc_number, x[j].name, x[j].email_address);
        fprintf(accounts,"%.2lf,%s,%d-%d",x[j].balance, x[j].mobile,x[j].date_opened.month, x[j].date_opened.year);
        fclose(accounts);
    }
    else
        printf("Error while opening accounts' file !\n");
}
void Print_Account(account x[],int i)
{
    char month[11];
    switch(x[i].date_opened.month)
    {
    case 1:
        strcpy (month,"January");
        break;
    case 2:
        strcpy (month,"February");
        break;
    case 3:
        strcpy (month,"March");
        break;
    case 4:
        strcpy (month,"April");
        break;
    case 5:
        strcpy (month,"May");
        break;
    case 6:
        strcpy (month,"June");
        break;
    case 7:
        strcpy (month,"July");
        break;
    case 8:
        strcpy (month,"August");
        break;
    case 9:
        strcpy (month,"September");
        break;
    case 10:
        strcpy (month,"October");
        break;
    case 11:
        strcpy (month,"November");
        break;
    case 12:
        strcpy (month,"December");
        break;
    }
    printf ("Account Number : %s\n",x[i].acc_number);
    printf ("Name : %s\n",x[i].name);
    printf ("Email : %s\n",x[i].email_address);
    printf ("Balance : %.2f\n",x[i].balance);
    printf ("Mobile : %s\n",x[i].mobile);
    printf ("Opened : %s %d\n\n",month,x[i].date_opened.year);
}
//1
void ADD(account x[],int *i)
{
    int j;
    do
    {
        printf("Enter Account number: ");
        gets(x[(*i)].acc_number);
        for(j=0; j<10 ; j++)
        {
            if (!isdigit(x[*i].acc_number[j]))
                break;
        }
    }
    while (strlen(x[(*i)].acc_number) != 10 || j!=10);

    for(j=0; j<*i; j++)
        if(strcmp(x[*i].acc_number, x[j].acc_number)==0)
        {
            printf("Sorry,Account number exists!\n");
            return;
        }
    printf("Enter Name: ");
    gets(x[(*i)].name);
    do
    {
        printf("Enter Email address: ");
        gets(x[(*i)].email_address);
    }
    while(validate_email(x[(*i)].email_address)==0);

    char temp_balance[15];
    do
    {
        printf("Enter Balance: ");
        gets(temp_balance);
        x[(*i)].balance=validate_withamount(temp_balance);
    }
    while(x[(*i)].balance == -1.0);

    do
    {
        printf("Enter Mobile: ");
        gets(x[(*i)].mobile);
    }
    while(validate_mobile_number(x[(*i)].mobile) == -1);

    time_t current=time(NULL);
    struct tm *DOD=localtime(&current);
    x[(*i)].date_opened.month =(DOD->tm_mon)+1;
    x[(*i)].date_opened.year =(DOD->tm_year)+1900;

    char temp[30]; //for file name
    strcpy(temp,x[*i].acc_number);
    char selection[15];
    do
    {
        printf("Pick(1:2):\n1-  SAVE \n2-  DISCARD\n");
        gets(selection);
        if (strcmp(selection, "1")==0)
        {
            (*i)++;
            if(*i==1)
                Save(x,i);
            else
            {
                FILE *accounts=fopen("accounts.txt","a");
                if(accounts !=NULL)
                {
                    fprintf(accounts,"\n%s,%s,%s,", x[j].acc_number, x[j].name, x[j].email_address);
                    fprintf(accounts,"%.2lf,%s,%d-%d",x[j].balance, x[j].mobile,x[j].date_opened.month, x[j].date_opened.year);
                    fclose(accounts);
                }
                else
                    printf("Error while opening accounts' file !\n");
            }
            strcat(temp,".txt");
            FILE *new_acc=fopen(temp,"w");
            fclose(new_acc);
            printf("New account has been added successfully!\n");
            return;
        }
        else if (strcmp(selection, "2")==0)
        {
            printf("DISCARDED!\n");
            return;
        }
        else
            printf("Invalid selection.\n");
    }
    while (1);
}
//2
void DELETE(account x[],int *i)
{
    char Account_number[30];
    int j,index = -1;
    printf("Enter Account number : ");
    gets(Account_number);
    for(j=0; j<(*i); j++)
        if(strcmp(Account_number, x[j].acc_number ) ==0)
        {
            index = j;
            if(x[j].balance !=0)
            {
                printf("Sorry,You can't delete this account (Balance is not empty)\n");
                return;
            }
        }
    if(index<0)
    {
        printf("Account doesn't exist!\n");
        return;
    }
    char selection[15];
    do
    {
        printf("Pick(1:2):\n1-  SAVE \n2-  DISCARD\n");
        gets(selection);
        if (strcmp(selection, "1")==0)
        {
            (*i)--;
            strcpy(x[index].acc_number, x[*i].acc_number);
            strcpy(x[index].name, x[*i].name);
            strcpy(x[index].email_address, x[*i].email_address);
            strcpy(x[index].mobile, x[*i].mobile);
            x[index].balance=x[(*i-1)].balance;
            x[index].date_opened.month = x[*i].date_opened.month;
            x[index].date_opened.year = x[*i].date_opened.year;
            Save(x,i);

            strcat(Account_number,".txt");
            remove(Account_number);
            printf("Account deleted successfully!\n");
            return;
        }
        else if(strcmp(selection, "2")==0)
        {
            printf("DISCARDED\n");
            return;
        }
        else
            printf("Invalid selection.\n");
    }
    while (1);
}
//3
void MODIFY(account x[],int *i)
{
    int index,j,found=0,check_name=0,check_address=0,check_mobile=0;
    char accnumber[20],NAME[30],NUM[12],ADDRESS[60];
    char selection[15];
    printf("Enter Account number : ");
    gets(accnumber);
    for(j=0; j<*i; j++)
        if(strcmp(x[j].acc_number,accnumber)==0)
        {
            found=1;
            break;
        }
    if(found==1)
        index=j;
    else
    {
        printf("Account doesn't exist.\n");
        return;
    }
    do
    {
        printf("Do you want to update your username? Pick(1:2): \n1-   YES \n2-   NO\n");
        gets(selection);
        if (strcmp(selection, "1")==0)
        {
            printf("Enter your new username : ");
            gets(NAME);
            check_name=1;
            break;
        }
        else if(strcmp(selection, "2")==0)
            break;
        else
            printf("Invalid selection.\n");
    }
    while (1);
    do
    {
        printf("Do you want to update your mobile? Pick(1:2): \n1-   YES \n2-   NO\n");
        gets(selection);
        if (strcmp(selection, "1")==0)
        {
            do
            {
                printf("Enter your new mobile number : ");
                gets(NUM);
            }
            while(validate_mobile_number(NUM) == -1);
            check_mobile=1;
            break;
        }
        else if(strcmp(selection, "2")==0)
            break;
        else
            printf("Invalid selection.\n");
    }
    while (1);

    do
    {
        printf("Do you want to update your email address? Pick(1:2): \n1-   YES \n2-   NO\n");
        gets(selection);
        if (strcmp(selection, "1")==0)
        {
            do
            {
                printf("Enter your new email address: ");
                gets(ADDRESS);
            }
            while(validate_email(ADDRESS) == 0);
            check_address =1;
            break;
        }
        else if(strcmp(selection, "2")==0)
            break;
        else
            printf("Invalid selection.\n");
    }
    while (1);

    do
    {
        printf("Pick(1:2) : \n1-   SAVE \n2-   DISCARD\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
        {
            printf("Data Updated Successfully.");
            if(check_name)
                strcpy(x[index].name, NAME);
            if(check_address)
                strcpy(x[index].email_address, ADDRESS);
            if(check_mobile)
                strcpy(x[index].mobile, NUM);
            Save(x,i);
            return;
        }
        else if(strcmp(selection, "2")==0)
        {
            printf("DISCARDED\n");
            return;
        }
        else
            printf("Invalid selection.\n");

    }
    while(1);
}
//4
void SEARCH(account x[],int *actual_accounts)
{
    int check=1;
    char acc_num[30];
    printf("Enter Account Number To Find : ");
    gets(acc_num);
    for(int i=0; i<*actual_accounts; i++)
    {
        if (strcmp(acc_num,x[i].acc_number)==0)
        {
            Print_Account(x,i);
            check=0;
            break;
        }
    }
    if(check)
        printf("Account doesn't exist.\n\n");
}
//5
void ADVANCED_SEARCH(account x[],int *actual_accounts)
{
    char key[30];
    int flag=0;
    char a_search[*actual_accounts][30];
    for (int k=0;k<*actual_accounts;k++)
    {
        strcpy(a_search[k],x[k].name);
    }
    printf ("Enter Keyword : ");
    gets (key);
    char *del=" ";
    char *token = strtok(a_search[0], del);
    for (int i=0; i<*actual_accounts;)
    {
        while (token)
        {
            int len =strlen(token);
            if (len == strlen(key))
            {
                for (int i=0; i<len; i++)
                {

                    key[i] = toupper(key[i]);
                    token [i]= toupper(token[i]);
                }
                if (!strcmp(key,token))
                {
                    printf ("Search Results:\n\n");
                    Print_Account(x,i);
                    flag=1;
                }
            }
            token = strtok(NULL, del);
        }
        token = strtok(a_search[++i], del);
    }
    if (!flag)
        printf ("There is no account with entered keyword.\n");
}

//6
void WITHDRAW(account x[],int *i)
{
    double withamount;
    int index,j,found=0;
    char NUM[20];
    printf("Enter Account number : ");
    gets(NUM);
    for(j=0; j<*i; j++)
        if(strcmp(x[j].acc_number,NUM)==0)
        {
            found=1;
            break;
        }
    if(found==1)
    {
        index=j;
    }
    else
    {
        printf("Account doesn't exist.\n");
        return;
    }
    char temp_withamount[15];
    do
    {
        printf("Enter the amount you want to withdraw (the maximum amount to withdraw is 10,000 $): ");
        gets(temp_withamount);
        withamount=validate_withamount(temp_withamount);
    }
    while(withamount>10000 || withamount> x[index].balance || withamount<=0 );

    char selection[15];
    do
    {
        printf("Pick(1:2) : \n1-   SAVE \n2-   DISCARD\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
        {
            printf("Successful Withdrawal.\n");
            x[index].balance -= withamount;
            printf("Your new balance is %.2lf $\n",x[index].balance);
            strcat(NUM,".txt");
            FILE *accnumber = fopen(NUM,"a");
            fprintf(accnumber,"%s withdrawed %.2lf $ \n",x[index].acc_number,withamount);
            fclose(accnumber);
            Save(x,i);
            return;
        }
        else if(strcmp(selection, "2")==0)
        {
            printf("DISCARDED\n");
            return;
        }
        else
            printf("Invalid selection.\n");
    }
    while(1);
}
//7
void DEPOSIT(account x[],int *actual_accounts)
{
    int index=-1;
    double amount;
    char acc_num[20];
    printf("Enter Account number:");
    gets(acc_num);
    for(int i=0; i<*actual_accounts; i++)
    {
        if (strcmp(acc_num,x[i].acc_number)==0)
        {
            index=i;
            break;
        }
    }
    if(index == -1)
    {
        printf("Account doesn't exist.\n");
        return;
    }
    char temp_withamount[15];

    do
    {
        printf("Enter amount to deposit (the maximum amount to deposit is 10,000 $): ");
        gets(temp_withamount);
        amount=validate_withamount(temp_withamount);
    }
    while(amount>10000 || amount<=0 );

    char selection[15];
    do
    {
        printf("Pick(1:2):\n1-   SAVE\n2-   DISCARD\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
        {
            x[index].balance+=amount;
            strcat(acc_num,".txt");
            FILE *acc_numm = fopen(acc_num,"a");
            if (acc_numm == NULL)
            {
                printf("Error opening file.\n");
                return;
            }
            fprintf(acc_numm,"%s Deposited %.2lf $\n",x[index].acc_number,amount);
            fclose(acc_numm);
            printf("Successful Deposit.\n");
            printf("Your new balance is %.2lf $\n",x[index].balance);
            Save(x,actual_accounts);
            return;
        }
        else if(strcmp(selection, "2")==0)
        {
            printf("DISCARDED.\n");
            return;
        }
        else
            printf("Invalid Selection.\n");
    }
    while(1);
}
//8
void TRANSFER(account x[],int *actual_accounts)
{
    int i,index1,index2,flag=0;
    char account_number1[30];
    char account_number2[30];
    double amount=0;
    printf("Enter Account Number of Sender :");
    gets(account_number1);
    for(i=0; i<*actual_accounts; i++)
    {
        if(strcmp(account_number1,x[i].acc_number)==0)
        {
            flag=1;
            index1=i;
            break;
        }

    }
    if(!flag)
    {
        printf("Account with account number %s doesn't exist.\n",account_number1);
        return;
    }
    printf("Enter Account Number of Receiver :");
    gets(account_number2);
    flag=0;
    for(i=0; i<*actual_accounts; i++)
    {
        if(strcmp(account_number2,x[i].acc_number)==0)
        {
            flag=1;
            index2=i;
            break;
        }
    }
    if(!flag)
    {

        printf("Account with account number %s doesn't exist.\n",account_number2);
        return;
    }

    if(strcmp(account_number1,account_number2)==0)
    {
        printf("Invalid transfer process\n");
        return;
    }

    char temp_withamount[15];
    do
    {
        printf("Enter amount to be transferred(the maximum amount to transfer is 10,000 $):");
        gets(temp_withamount);
        amount = validate_withamount(temp_withamount);
    }
    while(amount>10000 || amount<=0 );

    char selection[15];
    printf("Transferred %.2lf $ from account with number %s to account with number %s.",amount,account_number1,account_number2);
    do
    {
        printf("Pick(1:2):\n1-   SAVE\n2-   DISCARD\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
        {
            strcat(account_number1,".txt");
            x[index1].balance=x[index1].balance - amount;
            x[index2].balance=x[index2].balance + amount;
            FILE*accnum=fopen(account_number1,"a");
            if(accnum==NULL)
            {
                printf("Error in opening file.\n");
                return;
            }
            fprintf(accnum,"Transferred %.2lf $ from %s to %s\n",amount,x[index1].acc_number,x[index2].acc_number);
            fclose(accnum);
            strcat(account_number2,".txt");
            accnum=fopen(account_number2,"a");
            if(accnum==NULL)
            {
                printf("Error in opening file.\n");
                return;
            }
            fprintf(accnum,"%s Received %.2lf $ from %s\n",x[index2].acc_number,amount,x[index1].acc_number );
            fclose(accnum);
            printf("Successful Transfer.\n");
            Save(x,actual_accounts);
            return;
        }
        else if(strcmp(selection, "2")==0)
        {
            printf("DISCARDED.\n");
            return;
        }
        else
            printf("Invalid Selection.\n");

    }
    while(1);

}
//9
void REPORT(account x[],int *actual_accounts)
{
    char acc_num[20];
    printf ("Enter Account number: ");
    gets(acc_num);
    int len=strlen(acc_num);
    for (int j=0; j<len; j++)
    {
        if (!isdigit(acc_num[j]))
        {
            printf ("Invalid account number.\n");
            return;
        }
    }
    strcat(acc_num,".txt");
    FILE *f=fopen(acc_num,"r");
    if (f == NULL)
    {
        printf ("Account doesn't exist.\n");
        return;
    }

    char trans[100][100];
    int i=0;
    while (!feof(f))
    {
        fgets(trans[i],100,f);
        if (strlen(trans[i])==0)
        {
            i--;
            break;
        }
        i++;
    }
    fclose(f);
    if (i<0)
        printf ("This account didn't make any transactions.\n");
    else if (i<4)
    {
        printf ("This account only did %d transactions:\n",i+1);
        for (int j=0; j<=i; j++)
        {
            printf ("%s",trans[j]);
        }
    }
    else
    {
        printf ("Account's last five transactions:\n");
        for (int j = (i-4); j<=i; j++)
        {
            printf ("%s",trans[j]);
        }
    }
    for (; i>=0; i--)
        strcpy(trans[i],"");
}

//10
void sortByName(account x[],int *actual_accounts)
{
    int i,j,tempdate=0;
    char temp[65];
    double tempbalance=0.0;
    for(i=0; i<*actual_accounts; i++)
        for(j=i+1; j<*actual_accounts; j++)
            if(strcmp(x[i].name, x[j].name)>0)
            {
                //Swapping Account number
                strcpy(temp, x[i].acc_number);
                strcpy(x[i].acc_number, x[j].acc_number);
                strcpy(x[j].acc_number, temp);
                //Swapping Name
                strcpy(temp, x[i].name);
                strcpy(x[i].name, x[j].name);
                strcpy(x[j].name, temp);
                //Swapping Mobile
                strcpy(temp, x[i].mobile);
                strcpy(x[i].mobile, x[j].mobile);
                strcpy(x[j].mobile, temp);
                //Swapping Email
                strcpy(temp, x[i].email_address);
                strcpy(x[i].email_address, x[j].email_address);
                strcpy(x[j].email_address, temp);
                //Swapping Balance
                tempbalance=x[i].balance;
                x[i].balance=x[j].balance;
                x[j].balance=tempbalance;
                //Swapping Month
                tempdate=x[i].date_opened.month;
                x[i].date_opened.month=x[j].date_opened.month;
                x[j].date_opened.month=tempdate;
                //Swapping Year
                tempdate=x[i].date_opened.year;
                x[i].date_opened.year=x[j].date_opened.year;
                x[j].date_opened.year=tempdate;
            }
}
void sortByDate(account x[],int *actual_accounts) //OLDEST-->LATEST
{
    int i,j,tempdate;
    char temp[65];
    double tempbalance;
    for(i=0; i<*actual_accounts; i++)
        for(j=i+1; j<*actual_accounts; j++)
            if(x[i].date_opened.year>x[j].date_opened.year)
            {
                //Swapping Account number
                strcpy(temp,x[i].acc_number);
                strcpy(x[i].acc_number,x[j].acc_number);
                strcpy(x[j].acc_number,temp);
                //Swapping Name
                strcpy(temp,x[i].name);
                strcpy(x[i].name,x[j].name);
                strcpy(x[j].name,temp);
                //Swapping Mobile
                strcpy(temp,x[i].mobile);
                strcpy(x[i].mobile,x[j].mobile);
                strcpy(x[j].mobile,temp);
                //Swapping Email
                strcpy(temp,x[i].email_address);
                strcpy(x[i].email_address,x[j].email_address);
                strcpy(x[j].email_address,temp);
                //Swapping Balance
                tempbalance=x[i].balance;
                x[i].balance=x[j].balance;
                x[j].balance=tempbalance;
                //Swapping Month
                tempdate=x[i].date_opened.month;
                x[i].date_opened.month=x[j].date_opened.month;
                x[j].date_opened.month=tempdate;
                //Swapping Year
                tempdate=x[i].date_opened.year;
                x[i].date_opened.year=x[j].date_opened.year;
                x[j].date_opened.year=tempdate;
            }
            else if(x[i].date_opened.year==x[j].date_opened.year)
                if(x[i].date_opened.month>x[j].date_opened.month)
                {
                    //Swapping Account number
                    strcpy(temp,x[i].acc_number);
                    strcpy(x[i].acc_number,x[j].acc_number);
                    strcpy(x[j].acc_number,temp);
                    //Swapping Name
                    strcpy(temp,x[i].name);
                    strcpy(x[i].name,x[j].name);
                    strcpy(x[j].name,temp);
                    //Swapping Mobile
                    strcpy(temp,x[i].mobile);
                    strcpy(x[i].mobile,x[j].mobile);
                    strcpy(x[j].mobile,temp);
                    //Swapping Email
                    strcpy(temp,x[i].email_address);
                    strcpy(x[i].email_address,x[j].email_address);
                    strcpy(x[j].email_address,temp);
                    //Swapping Balance
                    tempbalance=x[i].balance;
                    x[i].balance=x[j].balance;
                    x[j].balance=tempbalance;
                    //Swapping Month
                    tempdate=x[i].date_opened.month;
                    x[i].date_opened.month=x[j].date_opened.month;
                    x[j].date_opened.month=tempdate;
                    //Swapping Year
                    tempdate=x[i].date_opened.year;
                    x[i].date_opened.year=x[j].date_opened.year;
                    x[j].date_opened.year=tempdate;
                }
}

void sortByBalance(account x[],int* actual_acounts) //HIGH -->LOW
{
    int i,j,tempdate;
    char temp[65];
    double tempbalance;
    for(i=0; i<*actual_acounts; i++)
        for(j=i+1; j<*actual_acounts; j++)
            if(x[i].balance<x[j].balance)
            {
                //Swapping Account number
                strcpy(temp,x[i].acc_number);
                strcpy(x[i].acc_number,x[j].acc_number);
                strcpy(x[j].acc_number,temp);
                //Swapping Name
                strcpy(temp,x[i].name);
                strcpy(x[i].name,x[j].name);
                strcpy(x[j].name,temp);
                //Swapping Mobile
                strcpy(temp,x[i].mobile);
                strcpy(x[i].mobile,x[j].mobile);
                strcpy(x[j].mobile,temp);
                //Swapping Email
                strcpy(temp,x[i].email_address);
                strcpy(x[i].email_address,x[j].email_address);
                strcpy(x[j].email_address,temp);
                //Swapping Balance
                tempbalance=x[i].balance;
                x[i].balance=x[j].balance;
                x[j].balance=tempbalance;
                //Swapping Month
                tempdate=x[i].date_opened.month;
                x[i].date_opened.month=x[j].date_opened.month;
                x[j].date_opened.month=tempdate;
                //Swapping Year
                tempdate=x[i].date_opened.year;
                x[i].date_opened.year=x[j].date_opened.year;
                x[j].date_opened.year=tempdate;
            }
}
void PRINT(account x[],int *actual_accounts)
{
    char selection [15],same[15];
    int i;
    do
    {
        printf("Pick(1:3):\n1-   SORT BY NAME\n2-   SORT BY DATE\n3-   SORT BY BALANCE\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
        {
            sortByName(x,actual_accounts);
            strcpy(same,"1");
            break;
        }
        else if(strcmp(selection, "2")==0)
        {
            sortByDate(x,actual_accounts);
            do
            {
                printf("Pick(1:2):\n1-   OLDEST-->LATEST  \n2-   LATEST-->OLDEST\n");
                gets(same);
                if(strcmp(same,"1")==0 || strcmp(same,"2")==0)
                    break;
            }
            while(1);
            break;

        }
        else if(strcmp(selection, "3")==0)
        {
            sortByBalance(x,actual_accounts);
            do
            {
                printf("Pick(1:2):\n1-   DESCENDING ORDER\n2-   ASCENDING ORDER\n");
                gets(same);
                if(strcmp(same, "1")==0 || strcmp(same, "2")==0)
                    break;
            }
            while(1);
            break;
        }
    }
    while(1);
    int j=0;
    if(strcmp(same, "1")==0)
        for(i=0; i<*actual_accounts; i++)
        {
            printf("Account %d:\n",i+1);
            Print_Account(x,i);
            printf("-----------------------\n");

        }
    else if(strcmp(same, "2")==0)
        for(i=*actual_accounts-1 ; i>=0 ; i--)
        {
            printf("Account %d:\n",++j);
            Print_Account(x,i);
            printf("-----------------------\n");

        }
}
int main()
{
    //login or quit
    char selection[10]; //for login and menu
    do
    {
        printf("Pick(1:2): \n1-   LOGIN \n2-   QUIT\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
            break;
        else if(strcmp(selection, "2")==0)
            return 0;
        else
            printf("Invalid input, Please try again.\n");
    }
    while(1);

    if(login()==0)//check log In
        return 0;

    account x[MAX_ACCOUNTS];
    int actual_accounts=0;
    load_accounts(x,&actual_accounts);

    //menu

    do
    {
        printf("Pick(1:11): \n1-   ADD \n2-   DELETE \n3-   MODIFY \n4-   SEARCH \n5-   ADVANCED SEARCH \n6-   WITHDRAW \n7-   DEPOSIT \n8-   TRANSFER \n9-   REPORT \n10-  PRINT \n11-  QUIT\n");
        gets(selection);
        if(strcmp(selection, "1")==0)
            ADD(x,&actual_accounts);
        else if(strcmp(selection, "2")==0)
            DELETE(x,&actual_accounts);
        else if(strcmp(selection, "3")==0)
            MODIFY(x,&actual_accounts);
        else if(strcmp(selection, "4")==0)
            SEARCH(x,&actual_accounts);
        else if(strcmp(selection, "5")==0)
            ADVANCED_SEARCH(x,&actual_accounts);
        else if(strcmp(selection, "6")==0)
            WITHDRAW(x,&actual_accounts);
        else if(strcmp(selection, "7")==0)
            DEPOSIT(x,&actual_accounts);
        else if(strcmp(selection, "8")==0)
            TRANSFER(x,&actual_accounts);
        else if(strcmp(selection, "9")==0)
            REPORT(x,&actual_accounts);
        else if(strcmp(selection, "10")==0)
            PRINT(x,&actual_accounts);
        else if(strcmp(selection, "11")==0)
            return 0;
        else
            printf("Invalid input, Please try again.\n");
    }
    while (1);


    return 0;
}
