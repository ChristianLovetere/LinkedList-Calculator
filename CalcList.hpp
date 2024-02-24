#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <iostream>
#include <string>

class CalcNode {

    friend class CalcList; //friends so that the list functions can access and create nodes.
    public:
        FUNCTIONS node_operation;
        double node_operand;
        double node_total;
        CalcNode *next;
};


class CalcList : public CalcListInterface{ //derives function declarations from virtuals in CalcListInterface.hpp while also adding a few new functions
    public:
        double total() const;
        void newOperation(const FUNCTIONS func, const double operand);
        void removeLastOperation();
        std::string toString(unsigned short precision) const;

        CalcList();

        bool list_is_empty() const {return (number_of_operations == 0); } //simply checks if no operations currently exist

    //private:
        CalcNode* current;
    //protected:
        void addNode(const double & location);
        void delNode();
        int number_of_operations = 0; // num of operations
    };


#endif