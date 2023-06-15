//
// Created by turha on 2.12.2022.
//

#include "Cashier.h"
#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>


void Cashier::firstModel(ofstream& file,float *customerArrivalTime,int numberOfCashiers,int numberOfOrders,float *takenOrderTimeList, float *brewTimeList, float *priceList){

    float *coffeDoneTime= new float[numberOfOrders-1];
    NodeCashier *temp2= front;
    Barista *baristaQue = new Barista();
    int check=1;
    while(check!=numberOfCashiers+1){
        temp2->barista=baristaQue;
        if(check%3==0){
            baristaQue->insertBarista(check/3);
        }
        if(check!=numberOfCashiers){ //n gelcek
            temp2=temp2->next;
        }
        check++;
    }

    check=1;
    while(baristaQue->servedOrderCount!=numberOfOrders){

        NodeBarista *temp = baristaQue->front;
        while(check!=(numberOfCashiers/3)+1){

//adds barista's first orders. bug warning if multiple order has same time this dont check prices
            int orderCheck=0;
            int index=0;
            float minTime=9999999;
            while(orderCheck!=numberOfOrders){
                if(minTime>takenOrderTimeList[orderCheck]&& takenOrderTimeList[orderCheck]!=0){
                    minTime=takenOrderTimeList[orderCheck];
                    index=orderCheck;
                }
                orderCheck++;
            }

            coffeDoneTime[index]= baristaQue->brew(takenOrderTimeList[index],
                                                   brewTimeList[index],
                                                   priceList[index])->lastWorkEndTime;
            takenOrderTimeList[index]=0;

            if(check!=numberOfCashiers/3){
                temp=temp->next;
            }
            check++;
        }




            int orderCheck=0;
            int index=0;
            float maxPrice=0;

            while(orderCheck!=numberOfOrders){
                if(maxPrice<priceList[orderCheck]&& takenOrderTimeList[orderCheck]!=0
                   && takenOrderTimeList[orderCheck]<=baristaQue->minLastWorkEndTime()){
                    maxPrice=priceList[orderCheck];
                    index=orderCheck;

                }

                orderCheck++;
            }

            coffeDoneTime[index]= baristaQue->brew(takenOrderTimeList[index],
                                                   brewTimeList[index],
                                                   priceList[index])->lastWorkEndTime;
            takenOrderTimeList[index]=0;

            if(check!=numberOfCashiers/3){
                temp=temp->next;
            }





    }




    //below is printing area
    NodeBarista *tempb= baristaQue->front;
    float totalRt=front->lastWorkEndTime;
    while(tempb!= nullptr){
        if(tempb->lastWorkEndTime>totalRt){
            totalRt=tempb->lastWorkEndTime;
        }
        tempb=tempb->next;
    }

    file<<totalRt<<endl;
    file<<que<<endl;
    if(baristaQue->front->que!=0){
        baristaQue->front->que--;
    }
    NodeBarista *temp29=baristaQue->front;
    int queb=0;
    while(temp29!= nullptr){
        queb +=temp29->que;
        if(temp29->que!=0){
            queb--;
        }
        temp29=temp29->next;
    }

    file<<queb<<endl;
    NodeCashier *tempc= front;
    while(tempc!= nullptr){            //<iomanip>
        file<<fixed;
        file<<setprecision(2);
        file<<tempc->totalWorkTime/totalRt<<endl;
        tempc=tempc->next;
    }
    tempb= baristaQue->front;
    while(tempb!= nullptr){
        file<<fixed;
        file<<setprecision(2);
        file<<tempb->totalWorkTime/totalRt<<endl;
        tempb=tempb->next;
    }
    for(int i=0;i<numberOfOrders;i++){
        file<<fixed;
        file<<setprecision(2);
        file<<coffeDoneTime[i]-customerArrivalTime[i]<<endl;
    }


}






void Cashier::secondModel(ofstream& file,float *customerArrivalTime,int numberOfCashiers, int numberOfOrders,float *takenOrderTimeList, float *brewTimeList, float *priceList, int *cashierId){

    float *coffeDoneTime2= new float[numberOfOrders-1];
    NodeCashier *temp2= front;
    int m2servedOrderCount=0;
    int check=1;

    while(check!=numberOfCashiers+1){
        if(check%3==1){
            Barista *baristaQue = new Barista();
            temp2->barista=baristaQue;
            temp2->next->barista= baristaQue;
            temp2->next->next->barista= baristaQue;
            baristaQue->insertBarista(check/3+1);
        }
        if(check!=numberOfCashiers){ //n gelcek
            temp2=temp2->next;
        }
        check++;
    }

    check=1;
    while(m2servedOrderCount!=numberOfOrders){

        NodeCashier *temp =front;
        while(temp!= nullptr){

//adds barista's first orders. bug warning if multiple order has same time this dont check prices
            int orderCheck=0;
            int index=-1;
            float minTime=9999999;
            while(orderCheck!=numberOfOrders){
                if(temp->barista->front->lastWorkEndTime==0 && minTime>takenOrderTimeList[orderCheck]
                && takenOrderTimeList[orderCheck]!=0 &&cashierId[orderCheck]<=3*temp->barista->front->id
                && cashierId[orderCheck]>=3*temp->barista->front->id-2){

                    minTime=takenOrderTimeList[orderCheck];
                    index=orderCheck;
                }
                orderCheck++;
            }

            if(index!=-1){
                temp->barista->brew(takenOrderTimeList[index],
                                    brewTimeList[index],priceList[index]);
                coffeDoneTime2[index]=temp->barista->front->lastWorkEndTime;
                m2servedOrderCount++;
                takenOrderTimeList[index]=0;
            }
            temp=temp->next;

        }


        temp =front;
        while(temp!= nullptr){
            int orderCheck=0;
            int index=-1;
            float maxPrice=0;
            while(orderCheck!=numberOfOrders){
                if(maxPrice<priceList[orderCheck]&& takenOrderTimeList[orderCheck]!=0
                   && takenOrderTimeList[orderCheck]<=temp->barista->front->lastWorkEndTime &&
                   cashierId[orderCheck]<=3*temp->barista->front->id && cashierId[orderCheck]>=3*temp->barista->front->id-2){
                    maxPrice=priceList[orderCheck];
                    index=orderCheck;
                }

                orderCheck++;
            }
            if(index!=-1){

                temp->barista->brew(takenOrderTimeList[index],
                                    brewTimeList[index],priceList[index]);
                coffeDoneTime2[index]=temp->barista->front->lastWorkEndTime;
                takenOrderTimeList[index]=0;
                m2servedOrderCount++;

            }
            temp=temp->next;
        }









    }


    NodeCashier *tempc= front;

    float totalRt=tempc->barista->front->lastWorkEndTime;
    while(tempc!=nullptr){
        if(tempc->barista->front->lastWorkEndTime>totalRt){
            totalRt=tempc->barista->front->lastWorkEndTime;
        }
        tempc=tempc->next;
    }

    file<<endl;
    file<<totalRt<<endl;
    file<<que<<endl;
    tempc= front;
    int printcount=1;
    int maxque=0;
    while(tempc!=nullptr){
        if(printcount%3==1){
            if(tempc->barista->front->que!=0){
                tempc->barista->front->que--;
            }
            file<<tempc->barista->front->que<<endl;
        }
        printcount++;
        tempc=tempc->next;
    }

    tempc= front;
    while(tempc!= nullptr){            //<iomanip>
        file<<fixed;
        file<<setprecision(2);
        file<<tempc->totalWorkTime/totalRt<<endl;
        tempc=tempc->next;
    }
    tempc = front;
    printcount=1;
    while(tempc!=nullptr){
        if(printcount%3==1){
            file<<fixed;
            file<<setprecision(2);
            file<<tempc->barista->front->totalWorkTime/totalRt<<endl;
        }
        tempc=tempc->next;
        printcount++;

    }


for(int i=0;i<numberOfOrders;i++){
        file<<fixed;
        file<<setprecision(2);
        file<<coffeDoneTime2[i]-customerArrivalTime[i]<<endl;
    }



}






void Cashier::insertCashier(int id){
    NodeCashier *nodeCashier = new NodeCashier();
    nodeCashier->id=id;
    if(front == nullptr){
        front = nodeCashier;
        rear = nodeCashier;
    }
    else{
        rear->next = nodeCashier;
        rear=nodeCashier;
    }
}

void Cashier::takeOrder(float *customerArrivalTime,float *takenOrderTimeList,float *takenOrderTimeList2, float *brewTimeList, float *priceList, int* cashierId,int numberOfOrders,int orderNum,int numberOfCashiers, float arrivalTime, float orderTime,float brewTime, float price) {
    NodeCashier *temp = front;


    priceList[orderNum-1]=price;
    customerArrivalTime[orderNum-1]=arrivalTime;
    brewTimeList[orderNum-1]=brewTime;

    int check=1;
    while(check!=numberOfCashiers+1){
        if(temp->lastWorkEndTime<=arrivalTime){

            break;
        }
        if(check!=numberOfCashiers){
            temp=temp->next;
        }
        check++;
    }

    if(check==numberOfCashiers+1){
        NodeCashier *temp2 = front;
        temp=temp2;
        float min= front->lastWorkEndTime;
        check=1;
        while(check!=numberOfCashiers+1){
            if(temp2->lastWorkEndTime < min){
                temp=temp2;
            }
            temp2=temp2->next;
            check++;
        }
    }

    temp->totalWorkTime+=orderTime;
    if(arrivalTime>= temp->lastWorkEndTime ){
        temp->lastWorkEndTime=arrivalTime+orderTime;
    }
    else{
        temp->lastWorkEndTime+=orderTime;
        que++;
    }



    cashierId[orderNum-1]= temp->id;
    takenOrderTimeList[orderNum-1]=temp->lastWorkEndTime;
    takenOrderTimeList2[orderNum-1]=temp->lastWorkEndTime;










    ofstream file("myoutput.txt");


   if(takenOrderTimeList[numberOfOrders-1]==temp->lastWorkEndTime){
       firstModel(file,customerArrivalTime,numberOfCashiers,numberOfOrders,takenOrderTimeList, brewTimeList, priceList);
       secondModel(file,customerArrivalTime,numberOfCashiers,numberOfOrders,takenOrderTimeList2,brewTimeList,priceList,cashierId);
   }


    file.close();
}










