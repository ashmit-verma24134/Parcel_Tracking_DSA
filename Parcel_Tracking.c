#include<stdio.h>
#include<stdlib.h>
struct node{
    int Tracking_ID;
    char Sender_name[50];
    char Receiver_name[50];
    float Weight;
    int priority;
    struct node*link;
};
struct node*top=0;
void Add_Parcel(int Tracking_ID,char Sender_name[],char Receiver_name[],float Weight,int priority){
    struct node*newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->Tracking_ID=Tracking_ID;
    newnode->Weight=Weight;
    newnode->priority=priority;
    newnode->link=0;
    /*As we cant directly assign strings in c so we will copy each character from sender name and receiver name.*/
    // Manually copy sender name
    int i=0;
    while(Sender_name[i]!='\0'&& i<49){
        newnode->Sender_name[i]=Sender_name[i];
        i++;
    }
    newnode->Sender_name[i]='\0';
    //Manually COpy the receiver name
    i=0;
    while(Receiver_name[i]!='\0' && i<49){
        newnode->Receiver_name[i]=Receiver_name[i];
        i++;
    }
    newnode->Receiver_name[i]='\0';
    if (top==0) {
        top=newnode;     //1:If stack is empty,insert at top
    }
    else if(priority==1){   //2:If the new parcel has High priority 1,insert at top
        newnode->link=top;
        top=newnode;
    }
    else {
        struct node *temp=top;       //3:If the new parcel has Medium 2 or Low 3 priority traverse it to find correct posn
        struct node *prev = NULL;
        while (temp !=NULL&& temp->priority<=priority){
            prev=temp;
            temp=temp->link;
        }
        if (prev==NULL){
            newnode->link=top;
            top=newnode;
        }else{
            prev->link=newnode;
            newnode->link=temp;
        }
    }
    printf("Parcel %d is added successfully!\n", 
        Tracking_ID);
}
void Dispatch_Parcel(){
    struct node *temp;
    temp=top;

    if(top==0){
        printf("Stack is in undeflow condition (No parcels to dispatch).\n");
    }
    else{
        printf("Dispatching Parcel...\n");
        printf("Tracking ID: %d\n",top->Tracking_ID);
        printf("Sender_Name: %s\n",top->Sender_name);
        printf("Receiver_Name: %s\n",top->Receiver_name);
        printf("Weight: %.2f kg\n",top->Weight);
        printf("Priority: %d\n",top->priority);

        top=top->link;
        free(temp);
        
    }
}
void Next_parcel(){
    if(top==0){
        printf("Stack is in underflow condition.(No parcels in the stack.)\n");
    }
    else{
        printf("\nThe next parcel details are:-\n");
        printf("Tracking ID: %d\n",top->Tracking_ID);
        printf("Sender_Name: %s\n",top->Sender_name);
        printf("Receiver_Name: %s\n",top->Receiver_name);
        printf("Weight: %.2f kg\n",top->Weight);
        printf("Priority: %d\n",top->priority);
    }
}
void Display_all_parcels(){
    if (top==0){
        printf("Stack is in underflow condition.(No parcels in the stack.)\n");
    }
    else{
        struct node* temp=top;
        printf("All parcels in order of dispatch (top to bottom) with their details.\n");
        while(temp!=0){
            printf("\nParcel details are:-\n");
            printf("Tracking ID: %d\n",temp->Tracking_ID);
            printf("Sender_Name: %s\n",temp->Sender_name);
            printf("Receiver_Name: %s\n",temp->Receiver_name);
            printf("Weight: %.2f kg\n",temp->Weight);
            printf("Priority: %d\n",temp->priority);
            temp=temp->link;
        }
    }
}
void Count_parcels_by_priority(){
    int high_priority=0;
    int medium_priority=0;
    int low_priority=0;
    struct node*temp=top;
    while (temp!=0){
        if(temp->priority==1){
            high_priority++;
        }
        else if(temp->priority==2){
            medium_priority++;
        }
        else if(temp->priority==3){
            low_priority++;
        }
        temp=temp->link;
    }
    printf("\nCount by priority level of the parcel.\n");
    printf("High priority(1): %d\n",high_priority);
    printf("Medium priority (2) : %d\n",medium_priority);
    printf("Low priority (3): %d\n",low_priority);
}
void Search(int tracking_id){
    struct node*temp=top;
    while(temp!=0){
        if(temp->Tracking_ID==tracking_id){
            printf("\nDetails of the parcel with tracking id (%d) is:-\n",tracking_id);
            printf("Tracking ID: %d\n",temp->Tracking_ID);
            printf("Sender_Name: %s\n",temp->Sender_name);
            printf("Receiver_Name: %s\n",temp->Receiver_name);
            printf("Weight: %.2f kg\n",temp->Weight);
            printf("Priority: %d\n",temp->priority);
            return;
        }
        temp=temp->link;
    }

    printf("Parcel with tracking id (%d) is not found.\n",tracking_id);

}
void Exit(){
    struct node*temp;
    while(top!=0){
        temp=top;
        top=top->link;
        free(temp);
    }
    printf("Exiting program...");
    exit(0);
}
int main() {
    int choice,Tracking_ID,priority;
    char Sender_name[50],Receiver_name[50];
    float Weight;
    while (1){
        printf("\nParcel Tracking System...\n");
        printf("1.Add Parcel\n");
        printf("2.Dispatch Parcel\n");
        printf("3.Next Parcel\n");
        printf("4.Display All Parcels\n");
        printf("5.Count Parcels by Priority\n");
        printf("6.Search Parcel by Tracking ID\n");
        printf("7.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                printf("Enter Tracking ID: ");
                scanf("%d",&Tracking_ID);
                printf("Enter Sender Name: ");
                scanf("%s",Sender_name);
                printf("Enter Receiver Name: ");
                scanf("%s",Receiver_name);
                printf("Enter Weight (kg): ");
                scanf("%f",&Weight);
                printf("Enter Priority Level (1=High, 2=Medium, 3=Low): ");
                scanf("%d",&priority);
                Add_Parcel(Tracking_ID,Sender_name,Receiver_name,Weight,priority);
                break;
            case 2:
                Dispatch_Parcel();
                break;
            case 3:
                Next_parcel();
                break;
            case 4:
                Display_all_parcels();
                break;
            case 5:
                Count_parcels_by_priority();
                break;
            case 6:
                printf("Enter Tracking ID to search: ");
                scanf("%d",&Tracking_ID);
                Search(Tracking_ID);
                break;
            case 7:
                Exit();
                return 0;
            default:
                printf("Wrong choice.\n");
        }
    }
}
