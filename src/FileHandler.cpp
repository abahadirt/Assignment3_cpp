//
// Created by turha on 2.12.2022.
//

#include <iostream>
#include <sstream>
#include "FileHandler.h"
#include "Barista.h"
#include "Cashier.h"
void FileHandler::handle(string input, string output){


    float *customerArrivalTime;
    float *takenOrderTimeList;
    float *takenOrderTimeList2;
    float *brewTimeList;
    float *priceList;
    int *cashierId;

    int orderNum=1;
    Cashier *cashier = new Cashier();
    ifstream inputFile(input);
    string myText;
    int temp=0;
    int numberOfCashier;
    int numberOfOrder;
    while (getline (inputFile, myText)) {
        stringstream stream;

        if(temp==0){
            stream << myText;
            stream >> numberOfCashier;





            for(int i=0; numberOfCashier>i;i++){
                cashier->insertCashier(i+1);
            }

        }
        else if(temp==1){

            stream << myText;
            stream >> numberOfOrder;
            float *customerArrivalTim = new float[numberOfOrder];
            float *takenOrderTimeLis=new float[numberOfOrder];
            float *brewTimeLis=new float[numberOfOrder];
            float *priceLis=new float[numberOfOrder];
            int *cashierI=new int[numberOfOrder];
            float *takenOrderTimeLis2=new float[numberOfOrder];
            cashierId=cashierI;
            takenOrderTimeList=takenOrderTimeLis;
            brewTimeList=brewTimeLis;
            priceList=priceLis;
            customerArrivalTime=customerArrivalTim;
            takenOrderTimeList2=takenOrderTimeLis2;
        }
        else{
            float arrivalTime,orderTime,brewTime,price;
            stream << myText;
            stream >> arrivalTime;

            stream >> orderTime;
            stream >> brewTime;
            stream >> price;

cashier->takeOrder(customerArrivalTime,takenOrderTimeList,takenOrderTimeList2,brewTimeList,priceList,cashierId,numberOfOrder,orderNum,numberOfCashier,arrivalTime,orderTime,brewTime,price);

            orderNum++;

        }
        temp++;
    }
}