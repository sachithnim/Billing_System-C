#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 void generateBillHead(char name[100], char date[20]);
 void generateBillBody(char item[20], int qty, float price);
 void generateBillfooter(float total);

	struct items{
		char item[20];
		float priceOfItem;
		int qty;
	};
	
	struct orders{
		char customer[100];
		char date[20];
		int noOfItems;
		struct items itm[50];  //structure it self to structure for items
	};

int main(){
	
	int operation, num, i;
	struct orders ord;
	struct orders order;
	float total = 0;
	
	char saveBill = 'y', conFlag = "y";
	FILE *fp;
	
	char name[50];
	
	while(conFlag == 'y'){
		float total = 0;
		int invoiceFound = 0;
		printf("Fork & Fig Bistro\n\n");
		
		printf("Select Your operation (1,2,3, or 4)\n\n");
		
		printf("1. Generate Invoice\n");
		printf("2. Show All Invoices\n");
		printf("3. Search Invoices\n");
		printf("4. Exit\n\n");
		
		printf("Enter Your Choice : ");
		scanf("%d", &operation);
		
		fgetc(stdin);
		
		switch(operation){
			case 1:
				//system("clear");
				printf("\nEnter Name of the Customer : ");
				fgets(ord.customer,50,stdin);
				ord.customer[strlen(ord.customer)-1] = 0;  //'strlen' give the actual length of string and -1 it 
														  //and that is the end possision of the string and assgnto 0
														  
				strcpy(ord.date,__DATE__);  //copy the string from one variable to another variable
			
				printf("Enter the Number of Items : ");
				scanf("%d", &num);
				
				ord.noOfItems = num;
				
				for(i = 0; i < num; i++){  // take the input for an items
					fgetc(stdin);
					printf("\n");
					
					printf("Enter the item %d Name : ", i+1);
					fgets(ord.itm[i].item,20,stdin);  //use structure in structure
					ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
					
					printf("Enter the Quantity : ");
					scanf("%d", &ord.itm[i].qty);
					
					printf("Enter the unit price : ");
					scanf("%f", &ord.itm[i].priceOfItem);
					
					total += ord.itm[i].qty * ord.itm[i].priceOfItem;
				}
				generateBillHead(ord.customer, ord.date);
				
				for(i = 0; i < ord.noOfItems; i++){
					generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].priceOfItem);
				}
				generateBillfooter(total);
				
				printf("\nDo You Want to Save the Invoice [y/n] : ");
				scanf("%s", &saveBill);
				
				if(saveBill == 'y'){
					fp = fopen("Bill.txt", "a+");  //saved bill
					
					fwrite(&ord, sizeof(struct orders), 1, fp);
					
					if(fwrite != 0){
						printf("\nBill Successfully Saved");
					}
					else{
						printf("\nError Bill Saving");
					}
					fclose(fp);
				}
				break;
			
			case 2:
				//system("clear");
				fp = fopen("Bill.dat", "r");		
				printf("\n   *****Your Previous Invoices*****");
				
				while(fread(&order, sizeof(struct orders), 1, fp)){
					
					float tot = 0;
					generateBillHead(order.customer,order.date);
					
					for(i = 0; i < order.noOfItems; i++){
						generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].priceOfItem);
						
						tot += order.itm[i].qty * order.itm[i].priceOfItem;
					}
					generateBillfooter(tot);
				}
				fclose(fp);
				break;
				
			case 3:
			
				printf("\nEnter the Name of the Customer : ");
				//fgetc(stdin);
				fgets(name, 50, stdin);
				name[strlen(name) -1] = 0;
				
				//system("clear");
				fp = fopen("Bill.dat", "r");		
				printf("\n\t   *****The Invoice of %s*****\n", name);
				
				while(fread(&order, sizeof(struct orders), 1, fp)){
					
					float tot = 0;
					
					if(!strcmp(order.customer, name)){
						generateBillHead(order.customer,order.date);
					
						for(i = 0; i < order.noOfItems; i++){
							generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].priceOfItem);
						
							tot += order.itm[i].qty * order.itm[i].priceOfItem;
						}
						generateBillfooter(tot);
						invoiceFound = 1;	
					}
				}
				if(!invoiceFound){
					printf("\nSorry Invoice for %s Does Not exists", name);
				}
				fclose(fp);
				break;
				
			case 4:
				printf("\n\t\t Good Bye..!");
				exit(0);
				break;
				
			default:
				printf("\nSorry Invalid Operation Please Select Correct One (1,2,3, or 4)");
		}
		printf("\nDo You Want Another Operation ? [y/n]\t");
		scanf("%s", &conFlag);
	}
	printf("\n\n");
	return 0;
}

void generateBillHead(char name[100], char date[20]){
	printf("\n\n");
	printf("\t    Fork & Fig Bistro");
	printf("\n\t    -----------------");
	printf("\nDate : %s", date);
	printf("\nInvoice to : %s", name);
	printf("\n");
	printf("---------------------------------------\n");
	printf("Items\t\t");
	printf("Qty\t\t");
	printf("Total\t\t");
	printf("\n---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[20], int qty, float price){
	printf("%s\t\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", qty * price);
	printf("\n");
}

void generateBillfooter(float total){
	printf("\n");
	float discount = 0.1 * total;
	float netTotal = total - discount;
	float cgst = 0.09 * netTotal,grandTotal = netTotal + 2 * cgst; //netTotal + cgst + sgst (%9)
	
	
		printf("---------------------------------------\n");
		printf("Sub Total\t\t\t %.2f\n", total);
		printf("\nDiscount @10%s\t\t\t %.2f", "%", discount);
		printf("\n\t\t\t\t-------");
		printf("\nNet Total\t\t\t %.2f", netTotal);
		printf("\nCGST @9%s\t\t\t %.2f", "%", cgst);
		printf("\nSGST @9%s\t\t\t %.2f", "%", cgst);
		printf("\n---------------------------------------");
		printf("\nGrand Total\t\t\t %.2f", grandTotal);
		printf("\n---------------------------------------\n");
}
