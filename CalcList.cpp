//Christian Lovetere U46489387 (solo)
//This code uses a circular linked list to create and maintain a calculator.
//New functions can be added, the most recent function can be removed (acts as
//an undo feature) and the entire list of currently maintained operations can
//be returned as a formatted string in order to view the calculator's 'history'.
//alternatively, the total() function can be used at any time to simply view
//the current total. 

#include "CalcList.hpp"
#include <sstream>
#include <iomanip>
#include "catch.hpp"

CalcList::CalcList() { //Constructor function, creates a list with just a default node.
    current = new CalcNode;
    current->node_operation = ADDITION;
    current->node_operand = 0;
    current->node_total = 0;
    current->next = current;
}

void CalcList::addNode(const double & starting_val) {
    ++number_of_operations;
    CalcNode *previous = new CalcNode; //temp node

    previous->node_operation = ADDITION;
    previous->node_operand = 0;
    previous->node_total = 0;
    previous->next = NULL;

    if(current == NULL){ //if no node exists, create a node with provided total
        previous->node_total = starting_val;
        current = previous; 
        current->next = current; //one and only node points to itself
    }

    else { //else just add node to the linked list, between the 'current' node and the node that current previously pointed to.
        previous->next = current->next;
        previous->node_total = current->next->node_total;
        current->next = previous;
    }
}

void CalcList::delNode() {
    if (list_is_empty()){
        throw("Cannot remove function, no functions are present.");
    }
    else {
        --number_of_operations; //decrement operations counter
        CalcNode *doomed = current->next; //create temporary pointer node, set it equal to next node
        if (doomed == current){ //if the node to be deleted is the current node, just set current node to NULL
            current = NULL;
        }
        else {  //otherwise, get rid of the doomed node and connect the 'current' node to the node after the doomed node, to keep the circular linked list complete.
            current->next = doomed->next;
        }
        delete doomed; //clear temp node pointer
    }
}

double CalcList::total() const{
    if( current != NULL){
        return current->next->node_total; //returns the total of the last node
    }
    else {
        return 0;
    }
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) { //creates a new operation based on what operation and operand are passed in. Can do +, -, *, and /.

    addNode(0); //create new default node that will have its attributes assigned below

    switch (func) { //assign the node's operation and operand based on what was passed into the function. Assigns total based on this as well as the previous total.
        case ADDITION: //this node's total = number requested + old total
            current->next->node_operation = func;
            current->next->node_operand = operand;
            current->next->node_total += operand;
            break;
                
        case SUBTRACTION: //this node's total = number requested - old total
            current->next->node_operation = func;
            current->next->node_operand = operand;
            current->next->node_total -= operand;
            break;

        case MULTIPLICATION: //this node's total = number requested * old total
            current->next->node_operation = func;
            current->next->node_operand = operand;
            current->next->node_total *= operand;
            break;
                
        case DIVISION: //this node's total = number requested / old total
            if(operand != 0.0) {
            current->next->node_operation = func;
            current->next->node_operand = operand;
            current->next->node_total /= operand;
            }

            else { //prevent attempts to divide by zero by throwing an error.
                throw("Cannot divide by zero.");
            }
            break;
            
        default: //if user did not provide a proper operation, throw an error.
            throw("Undefined arithmetic function. Please use addition, subtraction, multiplication, or division only.");
    }
}
void CalcList::removeLastOperation(){ //removes most recent op by deleting its respective node.
    delNode();
}

std::string CalcList::toString(unsigned short precision) const{ //print the calculator's history in newest to oldest order.

    std::stringstream s_stream; //create a string stream to store all of the steps' information in
    std::string list_contents = ""; //this empty string will be filled with s_stream's contents at the end.

    CalcNode *p = new CalcNode; //pointer calcnode that will hold current->next's info
    p = current->next;
    int step_back = number_of_operations; //copies value of number_of_operations. Lets the function use this value without tampering with it.

    s_stream.precision(precision); //incorporate user-requested decimal precision.

    while(p->node_total != 0){ //while statement will run until we have reached the 0 total node, marking the beginning of operations.

        s_stream << step_back << ": "; //append string with current operation #.

        s_stream << std::fixed << p->next->node_total; //append string with current operation total.

        if(p->node_operation == ADDITION){ //append string with current operation.
            s_stream << "+";
        }
        else if (p->node_operation == SUBTRACTION){
            s_stream << "-";
        }
        else if (p->node_operation == MULTIPLICATION){
            s_stream << "*";
        }
        else if (p->node_operation == DIVISION){
            s_stream << "/";
        }

        s_stream << p->node_operand; //append string with current operand.
        s_stream << "="; //append string with an equals sign.
        s_stream << p->node_total; //append string with the new (next) total.
        s_stream << std::endl; //finish up with an endline.

        p = p->next; //move pointer forward.
        --step_back; //decrement current operation #.
        
    }
    list_contents = s_stream.str(); //dump string stream's contents into the list.
    return list_contents;
}