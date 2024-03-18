#ifndef __WAREHOUSE_H__
#define __WAREHOUSE_H__

#include <assert.h>
#include <iostream>
#include <vector>
#include <tuple> 
#include <string>
#include <cassert>

#include "DoublyLinkedList.h"
#include "ResizableArray.h"

enum CommandType { GET, DROP };   

struct Robot {
    int ID;
    int numberBoxes;
    /**
        The command queue for a specific robot 
        Contains only "GET" and "DROP" types of commands
        
        The tuple contains the informations about the command: 
        CommandType, x, y, numberBoxes
    */
    DoublyLinkedList<std::tuple<CommandType, int, int, int>> commandsQueue;

    Robot() : numberBoxes(0), commandsQueue() {}
};

class Warehouse {
private:
    int numberRobots;
    int numberRows;
    int numberColumns;
    int **map;              // the map of the warehouse
    std::vector<struct Robot> robots;
    /**
        The stack with the history of executed commands
        Contains the history of commands given by robots, only GET and DROP type
        
        The tuple contains the informations about the command: 
        robotID, CommandType, x, y, numberBoxes
    */
    ResizableArray<std::tuple<int, CommandType, int, int, int>> commandsHistory;
    

public:
    Warehouse(int numberRobots, int numberRows, int numberColumns) {
        this->numberRobots = numberRobots;
        this->numberRows = numberRows;
        this->numberColumns = numberColumns;

        // Instantiate commandsHistory stack
        commandsHistory = ResizableArray<std::tuple<int, CommandType, int, int, int>>();

        // Initializing vector of robots and setting their IDs and numberBoxes
        robots.resize(numberRobots);     
        for (int i = 0 ; i < numberRobots; i++) {
            robots[i].ID = i;
        }

        // Dynamic allocation for map
        map = new int*[numberRows];
        for (int i = 0; i < numberRows; i++) {
            map[i] = new int[numberColumns];
        }
    }

    ~Warehouse() {
        // Freeing dynamically allocated memory for map
        for (int i = 0; i < numberRows; i++) {
            delete[] map[i];
        }
        delete[] map;
    }

    // Setter function for a specific element of the map
    void SetMapValue(int x, int y, int value) {
        map[x][y] = value;
    }

    // Getter function for a specific element of the map
    int GetMapValue(int x, int y) {
        return map[x][y];
    }

    /**
    * AddGetBox() and AddDropBox() functions
    *
    * Depending on the priority of the command, it will be added to the 
    * beginning or end of the commands queue of the robot with the given ID
    */
    void AddGetBox(int robotID, int x, int y, int numberBoxes, int priority) {
        auto commandTuple = std::make_tuple(CommandType::GET, x, y, numberBoxes);
        if (priority == 1) {
            robots[robotID].commandsQueue.addLast(commandTuple);
        } else {
            robots[robotID].commandsQueue.addFirst(commandTuple);
        }
    }

    void AddDropBox(int robotID, int x, int y, int numberBoxes, int priority) {
        auto commandTuple = std::make_tuple(CommandType::DROP, x, y, numberBoxes);

        if (priority ==  1) {
            robots[robotID].commandsQueue.addLast(commandTuple);
        } else {
            robots[robotID].commandsQueue.addFirst(commandTuple);
        }
    }

    /**
        Executes the first command from the queue of a robot with the given ID
    */
    std::string Execute(int robotID) {
        std::string outputString;

        // If there is no command in the queue for execution
        if (robots[robotID].commandsQueue.isEmpty()) {
            outputString = "EXECUTE: No command to execute";

        } else {
            // take the first command from the queue of the robot with the given ID
            auto commandNode = robots[robotID].commandsQueue.getHead();
            auto commandTuple = commandNode->data; // Accessing the tuple from the node
            auto currentType = std::get<0>(commandTuple);
            int x = std::get<1>(commandTuple);
            int y = std::get<2>(commandTuple);
            int firstNumberBoxes = std::get<3>(commandTuple);
            int currentNumberBoxes = firstNumberBoxes; // Added value in the commands stack

            // Case 1: GET type command
            if (currentType == CommandType::GET) {
                /* 
                if the number of boxes to be taken is greater than the
                number of boxes in the cell -> will take all existing boxes
                */
                if (firstNumberBoxes >= map[x][y]) {

                    currentNumberBoxes = map[x][y];
                    robots[robotID].numberBoxes += map[x][y];
                    map[x][y] = 0;


                } else {
                    // else the robot will take the given number of boxes
                    robots[robotID].numberBoxes += firstNumberBoxes;
                    map[x][y] -= firstNumberBoxes;

                }

            // Case 2: DROP type command
            } else {
                /* 
                if the number of boxes to be dropped is greater than the 
                number of boxes of the robot -> will drop all its boxes
                */
                if (robots[robotID].numberBoxes <= firstNumberBoxes) {

                    currentNumberBoxes = robots[robotID].numberBoxes;
                    map[x][y] = robots[robotID].numberBoxes;
                    robots[robotID].numberBoxes = 0;

                } else {
                    // else the robot will drop the given number of boxes
                    map[x][y] += firstNumberBoxes;
                    robots[robotID].numberBoxes -= firstNumberBoxes;

                }
            }
            // The executed command is added to the history stack
            std::tuple<int, CommandType, int, int, int> commandTupleStack = std::make_tuple(robotID, currentType, x, y, currentNumberBoxes);
            commandsHistory.addLast(commandTupleStack);

            outputString = "Executed";
        }
        return outputString;
    }

    /**
        * Print the commands from the queue of the given robot
        *
        * @param outputString Constructs the string to be displayed
        * 
    */
    std::string PrintCommands(int robotID) {
        std::string outputString;
        outputString += "PRINT_COMMANDS: ";

        // Case 1 - if there are no commands in the robot's queue
        if (robots[robotID].commandsQueue.isEmpty()) {
            outputString =  "No command found";

        // Case 2 - else print the commands
        } else {
            outputString += std::to_string(robotID) + ": ";

            // displays the first (size - 1) commands
            for (int i = 0; i < robots[robotID].commandsQueue.size() - 1; i++) {
                auto currentNode = robots[robotID].commandsQueue.goToPos(i);
                auto currentTuple = currentNode->data; // Accessing the tuple from the node

                auto currentType = std::get<0>(currentTuple);
                int x = std::get<1>(currentTuple);
                int y = std::get<2>(currentTuple);
                int numberBoxes = std::get<3>(currentTuple);

                outputString += std::to_string(currentType) + " ";
                outputString += std::to_string(x) + " ";
                outputString += std::to_string(y) + " ";
                outputString += std::to_string(numberBoxes) + "; ";
            }
            // displays the last command 
            int size = robots[robotID].commandsQueue.size();
            auto currentNode = robots[robotID].commandsQueue.goToPos(size - 1);
            auto currentTuple = currentNode->data; // Accessing the tuple from the node

            auto currentType = std::get<0>(currentTuple);
            int x = std::get<1>(currentTuple);
            int y = std::get<2>(currentTuple);
            int numberBoxes = std::get<3>(currentTuple);

            outputString += std::to_string(currentType) + " ";
            outputString += std::to_string(x) + " ";
            outputString += std::to_string(y) + " ";
            outputString += std::to_string(numberBoxes);
        }

        return outputString;
    }

    /**
        * Print the last added command in the stack of commands history
        *
        * @param outputString Constructs the string to be displayed
        * 
    */
    std::string LastExecutedCommand() {
        std::string outputString;
        outputString += "LAST_EXECUTED_COMMAND: ";

        // Case 1 - if there are no commands in the stack history
        if (commandsHistory.isEmpty()) {
            outputString += "No command was executed";

        // Case 2 - else print the last executed command     
        } else {
            auto lastCommand = commandsHistory.getLast();
            int robotID = std::get<0>(lastCommand);
            CommandType commandType = std::get<1>(lastCommand);
            int x = std::get<2>(lastCommand);
            int y = std::get<3>(lastCommand);
            int numberBoxes = std::get<4>(lastCommand);

            outputString += std::to_string(robotID) + ": ";
            outputString += std::to_string(commandType) + " ";
            outputString += std::to_string(x) + " ";
            outputString += std::to_string(y) + " ";
            outputString += std::to_string(numberBoxes);
        }

        return outputString;
    }

    /**
        * Remove the last executed command from the stack history
        * Put command back in the robot's command queue
        * Perform the reverse operation for the command found
        *
        * @param outputString Constructs the string to be displayed
        * 
    */
    std::string Undo() {
        std::string outputString;

        // Case 1 - if there are no commands in the stack history
        if (commandsHistory.isEmpty()) {
            outputString += "UNDO: No History";

        // Case 2 - else execute UNDO implementation 
        } else {
            // Take the atributes from the last command in stack history
            auto lastCommand = commandsHistory.getLast();
            int robotID = std::get<0>(lastCommand);
            CommandType commandType = std::get<1>(lastCommand);
            int x = std::get<2>(lastCommand);
            int y = std::get<3>(lastCommand);
            int numberBoxes = std::get<4>(lastCommand);

            // Delete the command from history stack
            commandsHistory.removeLast();

            // Add command to the queue of the robot with given ID
            robots[robotID].commandsQueue.addFirst(std::make_tuple(commandType, x, y, numberBoxes));

            /**
                UNDO execution
                Perform the reverse operation of the extracted one
            */

            //Case 1: for DROP type command - execute GET
            if (commandType == CommandType::DROP) {
                /* 
                if the number of boxes to be taken is greater than the
                number of boxes in the cell -> will take all existing boxes
                */
                if (numberBoxes >= map[x][y]) {

                    numberBoxes = map[x][y];
                    robots[robotID].numberBoxes += map[x][y];
                    map[x][y] = 0;


                } else {
                    // else the robot will take the given number of boxes
                    robots[robotID].numberBoxes += numberBoxes;
                    map[x][y] -= numberBoxes;

                }

            // Case 2: for GET type command - execute DROP
            } else {
                /* 
                if the number of boxes to be dropped is greater than the 
                number of boxes of the robot -> will drop all its boxes
                */
                if (robots[robotID].numberBoxes <= numberBoxes) {

                    numberBoxes = robots[robotID].numberBoxes;
                    map[x][y] = robots[robotID].numberBoxes;
                    robots[robotID].numberBoxes = 0;

                } else {
                    // else the robot will drop the given number of boxes
                    map[x][y] += numberBoxes;
                    robots[robotID].numberBoxes -= numberBoxes;

                }
            }

            outputString += "Executed";
        }
        return outputString;
    }

    /**
        * Returns the number of boxes that the robot with the given ID has
        * at that time
        *
        * @param outputString Constructs the string to be displayed
        * 
    */
    std::string HowManyBoxes(int robotID) {
        std::string outputString;
        outputString += "HOW_MANY_BOXES: ";

        int currentBoxes = robots[robotID].numberBoxes;
        outputString += std::to_string(currentBoxes);

        return outputString;
    }

};


#endif // __WAREHOUSE_H__