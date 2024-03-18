#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

#include "Warehouse.h"

int main () {
    int numberRobots;
    int numberRows;
    int numberColumns;
    int value;                  // store the values for every cell of map
    char commandString[30];     // store the string of command
    int robotID;
    int x;
    int y;
    int numberBoxes;
    int priority;
    char outputFunction[30];

    FILE* inputFile = fopen("robots.in", "r");
    if (inputFile == NULL) {
        printf("The input file could not be opened.\n");
        return 1;
    }

    FILE* outputFile = fopen("robots.out", "w");
    if (outputFile == NULL) {
        printf("The output file could not be opened.\n");
        return 1;
    }

    // Read the first three elements from file: N ROW COL
    fscanf(inputFile, "%d %d %d", &numberRobots, &numberRows, &numberColumns);

    // Warehouse initialization with given data from the file 
    Warehouse warehouse = Warehouse(numberRobots, numberRows, numberColumns);

    // Read all the values for the map
    for (int i = 0; i < numberRows; i++) {
        for (int j = 0; j < numberColumns; j++) {
            fscanf(inputFile, "%d", &value);
            warehouse.SetMapValue(i, j, value);
        }
    }

    // Read the rest of the file - the commands and parameters
    while (fscanf(inputFile, "%s", commandString) != EOF) {

        if (strcmp(commandString, "ADD_GET_BOX") == 0) {
            fscanf(inputFile, "%d %d %d %d %d", &robotID, &x, &y, &numberBoxes, &priority);
            warehouse.AddGetBox(robotID, x, y, numberBoxes, priority);

        } else if (strcmp(commandString, "ADD_DROP_BOX") == 0) {
            fscanf(inputFile, "%d %d %d %d %d", &robotID, &x, &y, &numberBoxes, &priority);
            warehouse.AddDropBox(robotID, x, y, numberBoxes, priority);

        } else if (strcmp(commandString, "EXECUTE") == 0) {
            fscanf(inputFile, "%d", &robotID);
            strcpy(outputFunction, warehouse.Execute(robotID).c_str());
            if (strcmp(outputFunction, "Executed") != 0) {
                fprintf(outputFile, "%s\n", outputFunction);
            }

        } else if (strcmp(commandString, "PRINT_COMMANDS") == 0) {
            fscanf(inputFile, "%d", &robotID);
            warehouse.PrintCommands(robotID);

        } else if (strcmp(commandString, "LAST_EXECUTED_COMMAND") == 0) {
            warehouse.LastExecutedCommand();

        } else if (strcmp(commandString, "UNDO") == 0) {
            strcpy(outputFunction, warehouse.Undo().c_str());
            if (strcmp(outputFunction, "Executed") != 0) {
                fprintf(outputFile, "%s\n", outputFunction);
            }

        } else if (strcmp(commandString, "HOW_MUCH_TIME") == 0) {

        } else if (strcmp(commandString, "HOW_MANY_BOXES") == 0) {
            fscanf(inputFile, "%d", &robotID);
            strcpy(outputFunction, warehouse.HowManyBoxes(robotID).c_str());
            fprintf(outputFile, "%s\n", outputFunction);

        } else {
            fprintf(outputFile, "The command is incorrect\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}