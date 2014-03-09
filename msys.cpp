/*
Copyright (c) 2014 Vinayak Mehta <vmehta94@gmail.com>

This file is licensed under the MIT License.
*/
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
//--------------------------------CLASSES------------------------------------
class product
{
	int pno;                     //product no.
	char pname[50];              //product name
	float price,qty,tax,dis;     //price,quantity,tax and discount

	public:
	void create_product()        //FUNCTION-to input the product details
	{                            //from administrator
		cout<<"\nPLEASE ENTER THE PRODUCT NO. OF THE PRODUCT :-  ";
		cin>>pno;
		cout<<"\n\nPLEASE ENTER THE NAME OF THE PRODUCT :- ";
		gets(pname);
		cout<<"\nPLEASE ENTER THE PRICE OF THE PRODUCT :- ";
		cin>>price;
		cout<<"\nPLEASE ENTER THE DISCOUNT (%) :-";
		cin>>dis;
	 }

	void show_product()          //FUNCTION-to display the product details
	{
		cout<<"\nTHE PRODUCT NO. OF THE PRODUCT :- "<<pno;
		cout<<"\nTHE NAME OF THE PRODUCT:- ";
		puts(pname);
		cout<<"\nTHE PRICE OF THE PRODUCT :- Rs.  "<<price;
		cout<<"\nDISCOUNT : "<<dis<<"%";
	}

	int  retpno()                //FUNCTION-to return product number
	{
		return pno;
	}

	float retprice()             //FUNCTION-to return product price
	{
		return price;
	}

	char* retname()              //FUNCTION-to return product name
	{
		return pname;
	}

	int retdis()                 //FUNCTION-to return discount on product
	{
		return dis;
	}

};

class cust
{
	char name[20];               //customer name
	char add[40];                //customer address
	char tel[11];                //contact no. of customer
	int id;                      //ID no. of customer

	public:
	void enter(int idno)         //FUNCTION-to input customer details
	{
		id=idno;
		cout<<"\nID NO. :";
		cout<<id<<endl;
		cout<<"\nENTER THE NAME OF THE CUSTOMER :";
		gets(name);
		cout<<"\nENTER THE ADDRESS OF THE CUSTOMER :";
		gets(add);
		cout<<"\nENTER THE TELEPHONE NO. OF THE CUSTOMER:";
		gets(tel);
		cout<<endl;
	}

	void display()               //FUNCTION-to display customer details
	{
		cout<<"\t\t\tCUSTOMER RECORDS";
		cout<<"===========================================================\n";
		cout<<"ID No.\t"<<id<<"NAME\t ";
		puts(name);
		cout<<"ADDRESS\t";
		puts(add);
		cout<<"TELEPHONE NO.\t";
		puts(tel);
	}
	int idno()                   //FUNCTION-to return ID no.
	{
		return id;
	}
	char* ret_name()             //FUNCTION-to return customer's name
	{
		return name;
	}
	char* ret_add()              //FUNCTION-to return customer's address
	{
		return add;
	}
	char* ret_tel()              //FUNCTION-to return customer's contact no.
	{
		return tel;
	}
}c;     //object of class customer

fstream fp;         //object of class fstream
product pr;         //object of class product
//--------------------------------CLASSES------------------------------------

int generate_id()                    //FUNCTION-to return and increment ID no.
{
	int idn=0;
	fp.open("Customer.txt",ios::in|ios::binary);
	fp.read((char*)&c,sizeof(c));
	while(fp.read((char*)&c,sizeof(c)))
	{
		idn=c.idno();
		fp.read((char*)&c,sizeof(c));
	}
	fp.close();
	return idn;
}

void write_product()                 //FUNCTION-to write product details
{                                    //into the text file
	fp.open("Store.txt",ios::out|ios::app);
	pr.create_product();
	fp.write((char*)&pr,sizeof(pr));
	fp.close();
	cout<<"\n\nTHE PRODUCT HAS BEEN CREATED. ";
	
}

void enter_cust()                    //FUNCTION-enter customer details
{
	
	cout<<"\n============================";
	cout<<"\n     CUSTOMER DETAILS";
	cout<<"\n============================\n";
	fp.open("Customer.txt",ios::out|ios::app);
	cout<<"ENTER THE INFO OF CUSTOMER: ";
	int id=100;
	id=generate_id();
	c.enter(id);
	fp.write((char*)&c,sizeof(cust));
	fp.close();
}

void search_product(int n)           //FUNCTION-to search the product details
{
	int flag=0;
	fp.open("Store.txt",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()==n)
		{
			
			pr.show_product();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
		cout<<"\n\nRECORD DOES NOT EXIST.";
	
}

void modify_product()                //FUNCTION-to modify product details
{
	int no,found=0;
	
	cout<<"\n\n\tTO MODIFY ";
	cout<<"\n\n\tPLEASE ENTER THE PRODUCT NO. OF THE PRODUCT :- ";
	cin>>no;
	fp.open("Store.txt",ios::in|ios::out);
	while(fp.read((char*)&pr,sizeof(product)) && found==0)
	{
		if(pr.retpno()==no)
		{
			pr.show_product();
			cout<<"\nPLEASE ENTER THE NEW DETAILS OF THE PRODUCT :- "<<endl;
			pr.create_product();
			int pos=-1*sizeof(pr);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&pr,sizeof(product));
			cout<<"\n\n\t RECORD UPDATED.";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n\n RECORD NOT FOUND. ";
	
}

void delete_product()                //FUNCTION-to delete product details
{
	int no;
	
	cout<<"\n\n\n\tDELETE RECORD";
	cout<<"\n\nPLEASE ENTER THE PRODUCT NO. OF THE PRODUCT YOU WANT TO DELETE:- ";
	cin>>no;
	fp.open("Store.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()!=no)
		{
			fp2.write((char*)&pr,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("Store.txt");
	rename("Temp.txt","Store.txt");
	cout<<"\n\n\tRECORD DELETED ..";
	
}

void menu()                          //FUNCTION-product menu
{
	
	fp.open("Store.txt",ios::in);
	if(!fp)
	{
		cout<<"\tTHE STORE IS OUT OF STOCK.";
		cout<<"\n\n\n Program is closing ....";
		
		exit(0);
	}

	cout<<"\n\n\t\tPRODUCT MENU\n\n";
	cout<<"===========================================================\n";
	cout<<"P.NO.\t\t\tNAME\t\t\tPRICE\n";
	cout<<"===========================================================\n";

	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t\t"<<pr.retname()<<"\t\tRs. "<<pr.retprice()<<endl;
	}
	fp.close();
}

void cust_record()                   //FUNCTION-to display customer records
{
	
	fp.open("Customer.txt",ios::in);
	if(!fp)
	{
		cout<<"\tTHE SHOP HAS JUST OPENED.";
		cout<<"\n\n\n Wait for the Customers to buy some Products ....";
		
		exit(0);
	}
	cout<<"\n\n\t\tCUSTOMER RECORDS\n\n";
	cout<<"===========================================================\n";
	cout<<"ID.NO.\t\tNAME\t\tADDRESS\t\tCONTACT NO.\n";
	cout<<"===========================================================\n";

	while(fp.read((char*)&c,sizeof(product)))
	{
		cout<<"\t\t"<<c.ret_name()<<"\t\t"<<c.ret_add()<<"\t\t"<<c.ret_tel()<<endl;
	}
	
	fp.close();

}


void place_order()                   //FUNCTION-to place order
{
	cust c;
	int  order_arr[50],quan[50],t=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"\n============================";
	cout<<"\n    PLACE YOUR ORDER";
	cout<<"\n============================\n";
	do
	{
		cout<<"\n\nENTER THE PRODUCT NO. OF THE PRODUCT :- ";
		cin>>order_arr[t];
		cout<<"\nQUANTITY IN NO. :- ";
		cin>>quan[t];
		t++;
		cout<<"\nDO YOU WANT TO ORDER ANOTHER PRODUCT ? (y/n)";
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
	cout<<"\n\nTHANK YOU FOR THE TRANSACTION!";
	
	
	enter_cust();
	
	

	cout<<"\n\n************************************INVOICE*************************************\n";
	cout<<"\nPr No.\tPr NAME\t\tQUANTITY\tPRICE\tAMOUNT\tAMOUNT(AFTER DISCOUNT)\n";
	for(int x=0;x<=t;x++)
	{
		 fp.open("Store.txt",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		 while(!fp.eof())
		 {
			if(pr.retpno()==order_arr[x])
			{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"   "<<quan[x]<<"\tRs."<<pr.retprice()<<"\tRs."<<amt<<"\tRs."<<damt;
				 total+=damt;
			}
			fp.read((char*)&pr,sizeof(product));
		 }

		 fp.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	cout<<"\n\n\n================================================================================\n";
	cout<<"\n\nCUSTOMER DETAILS :-";
	cout<<"\nNAME :- \tADDRESS :- \tCONTACT NO. :- \n";
	cout<<c.ret_name()<<"/t"<<c.ret_add()<<"/t"<<c.ret_tel();
	
}

/*void intro()                         //MAIN SCREEN
{
	
	gotoxy(31,11);
	cout<<"  SPORTS STORE";
	gotoxy(35,14);
	cout<<" BILLING";
	gotoxy(35,17);
	cout<<" PROJECT";
	gotoxy(35,40);
	cout<<"\n\tMADE BY : VINAYAK MEHTA AND RUDRAKSH";
	cout<<"\n\n\tSCHOOL : ST. CECILIA'S PUBLIC SCHOOL";
	

}*/

void admin_menu()                    //ADMINISTRATOR MENU
{
	
	char ch2;
	cout<<"\n\n\n\tADMIN MENU";
	cout<<"\n\n\t1.CREATE PRODUCT";
	cout<<"\n\n\t2.SEARCH ";
	cout<<"\n\n\t3.MODIFY PRODUCT";
	cout<<"\n\n\t4.DELETE PRODUCT";
	cout<<"\n\n\t5.VIEW PRODUCT MENU";
	cout<<"\n\n\t6.VIEW CUSTOMER RECORDS";
	cout<<"\n\n\t7.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
	ch2=
	switch(ch2)
	{
		case '1': 	
				write_product();
				break;
		case '2':
				int num;
				
				cout<<"\n\n\tPlease Enter The Product No. ";
				cin>>num;
				search_product(num);
				break;
		case '3': 	modify_product();
				break;
		case '4': 	delete_product();
				break;
		case '5': 	menu();
				
		case '6':  	cust_record();
		case '7': 	break;
		default:	cout<<"\a";admin_menu();
	}
}

void main()
{

	char ch;
	//intro();
	do
	{
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CUSTOMER";
		cout<<"\n\n\t02. ADMINISTRATOR";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		ch=
		switch(ch)
		{
			case '1': 	
					place_order();
					
					break;
			case '2':       //password protected admin menu
					int ch,k=0,p=0;
					char password[10];
					do
					{
						
						cout<<"\n\ENTER PASSWORD :  ";
						gets(password);
						if(strcmp(password,"EINSTEIN")!=0)
						{
							k++;
							cout<<"WRONG PASSWORD. ACCESS DENIED."<<endl;
							cout<<"YOU HAVE "<<3-k<<" MORE CHANCES LEFT.";
							

						}
						else
						{
							p=1;
						}
					}while(k<3&&p!=1);
					if(strcmp(password,"EINSTEIN")!=0)
					{
						
						cout<<"PROGRAM IS BEING TERMINATED.";
						
						exit(0);
					}
					if(strcmp(password,"EINSTEIN")==0)
						admin_menu();
					break;
			case '3':	exit(0);
			default :	cout<<"\a";
		}
	}while(ch!='3');
}

