//
// Created by turha on 2.12.2022.
//

#ifndef ASSIGNMENT3_CASHIER_H
#define ASSIGNMENT3_CASHIER_H
#include "Barista.h"
#include <fstream>
class NodeCashier{
public:
    NodeCashier* next;
    int id;
    float totalWorkTime=0;
    float lastWorkEndTime=0;
    Barista *barista;
};

class Cashier {
public:
    int que=0;
    NodeCashier* front;
    NodeCashier* rear;
    void insertCashier(int id);
    void takeOrder(float *customerArrivalTime,float *takenOrderTimeList,float *takenOrderTimeList2, float *brewTimeList, float *priceList, int *cashierId,
                   int numberOfOrders,int orderNum,int numberOfCashiers, float arrivalTime,
                   float orderTime,float brewTime, float price);
    void firstModel(std::ofstream& file,float *customerArrivalTime,int numberOfCashiers,int numberOfOrders,
                    float *takenOrderTimeList,float *brewTimeList, float *priceList);
    void secondModel(std::ofstream& file,float *customerArrivalTime,int numberOfCashiers, int numberOfOrders,
                     float *takenOrderTimeList, float *brewTimeList, float *priceList, int *cashierId);


};


#endif //ASSIGNMENT3_CASHIER_H
