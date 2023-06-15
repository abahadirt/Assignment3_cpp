//
// Created by turha on 2.12.2022.
//

#ifndef ASSIGNMENT3_BARISTA_H
#define ASSIGNMENT3_BARISTA_H
class NodeBarista{
public:
    NodeBarista* next;
    int id;
    float totalWorkTime=0;
    float lastWorkEndTime=0;
    int que=0; //sonradan
};

class Barista {
public:
    NodeBarista* front;
    NodeBarista* rear;
    int servedOrderCount=0;
    float minLastWorkEndTime();
    void insertBarista(int id);
    NodeBarista* brew(float takenOrderTimeList, float brewTimeList, float priceList);

};


#endif //ASSIGNMENT3_BARISTA_H
