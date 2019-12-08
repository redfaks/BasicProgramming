#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "List.h"

void entrance()
{
    printf("Hello! You opened phone book.\n");
    printf("You have such commands to use: \n");
    printf("0 - exit \n");
    printf("1 - add new number(format: name number)\n");
    printf("2 - find phone number\n");
    printf("3 - find name\n");
    printf("4 - save data(will appear in the book after closing the program)\n");
    printf("Enter the command: ");
}

int checkInput(List* list, char* name, char* number)
{
    char *nameInTheList = findName(list, number);
    char *numberInTheList = findNumber(list, name);
    if (nameInTheList[0] != '*')
    {
        return 1;
    }
    else if (numberInTheList[0] != '*')
    {
        return 2;
    }
    return 0;
}

void executeFirstCommand(List *list, int maxInputSize)
{
    char *name = createCharArray(maxInputSize);
    char *number = createCharArray(maxInputSize);
    printf("Enter a new pair (format: name number) :  ");
    scanf("%s %s", name, number);
    int checkingAnswer = checkInput(list, name, number);
    if (checkingAnswer == 0)
    {
        printf("You added number: %s_%s \n", name, number);
        addNew(list, number, name);
        changeListSize(list, getListSize(list) + 1);
    }
    else if (checkingAnswer == 1)
    {
        printf("Number is already in the phone book.\n");
    }
    else
    {
        printf("Name is already in the phone book.\n");
    }
}

void executeSecondCommand(List *list, int maxInputSize)
{
    char *name = createCharArray(maxInputSize);
    printf("Enter a name: ");
    scanf("%s", name);
    char *answer = findNumber(list, name);
    if (answer[0] != '*')
    {
        printf("The number is: %s\n", answer);
    }
    else
    {
        printf("There is no such name in the book\n");
    }
    free(name);
}

void executeThirdCommand(List *list, int maxInputSize)
{
    char *number = createCharArray(maxInputSize);
    printf("Enter a number: ");
    scanf("%s", number);
    char *answer = findName(list, number);
    if (answer[0] != '*')
    {
        printf("The name is: %s\n", answer);
    }
    else
    {
        printf("There is no such number in the book\n");
    }
    free(number);
}

void executeFourthCommand(List *list, FILE *file, int rememberLastNumberIndex)
{
    ListElement *currentElement = getListFirst(list);
    while(getNumberIndex(currentElement) != rememberLastNumberIndex)
    {
        fprintf(file, "%s %s \n", getName(currentElement), getNumber(currentElement));
        currentElement = getNext(currentElement);
    }
}

void executeCommand(List* list, int input, int rememberLastNumberIndex, FILE* file, int maxInputSize)
{
    switch (input)
    {
        case 1:
            executeFirstCommand(list, maxInputSize);
            break;
        case 2:
            executeSecondCommand(list, maxInputSize);
            break;
        case 3:
            executeThirdCommand(list, maxInputSize);
            break;
        case 4:
            executeFourthCommand(list, file, rememberLastNumberIndex);
            break;
        default:
            printf("You entered incorrect command\n");
            scanf("%*[^\n]");
            break;
    }
}