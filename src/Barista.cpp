//
// Created by turha on 2.12.2022.
//

#include "Barista.h"
#include <iostream>

using namespace std;
void Barista::insertBarista(int id){
    NodeBarista *nodeBarista = new NodeBarista();
    nodeBarista->id=id;
    if(front == nullptr){
        front = nodeBarista;
        rear = nodeBarista;
    }
    else{
        rear->next = nodeBarista;
        rear=nodeBarista;
    }
}

NodeBarista* Barista::brew(float arrivalTime, float brewTime, float price){

        NodeBarista *temp = front;
        int check=1;
              //bostaysa eklemek
        while(temp!=nullptr){

            if(temp->lastWorkEndTime<=arrivalTime){
                break;
            }
                temp=temp->next;
            }


    //doluysa eklemek
        if(temp== nullptr){
            NodeBarista *temp2 = front;



            temp=temp2;
            float min= front->lastWorkEndTime;
            while(temp2!=nullptr){
                if(temp2->lastWorkEndTime < min){
                    temp=temp2;
                }
                temp2=temp2->next;
            }

        }

        temp->totalWorkTime+=brewTime;
        if(arrivalTime>= temp->lastWorkEndTime ){
            temp->lastWorkEndTime=arrivalTime+brewTime;
        }
        else{
            temp->que++;
            temp->lastWorkEndTime+=brewTime;
        }





    servedOrderCount++;
        return temp;
}

float Barista::minLastWorkEndTime() {

    NodeBarista *temp= front;
    float min=temp->lastWorkEndTime;

    while(temp->next!=nullptr){
        if(min>temp->lastWorkEndTime){
            min=temp->lastWorkEndTime;
        }
        temp= temp->next;
    }
    if(min>rear->lastWorkEndTime){
        min=rear->lastWorkEndTime;
    }
    return min;
}