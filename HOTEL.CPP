#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
class hotel
{
	int room_no;
	char name[30];
	char address[50];
	char phone[10];

	public:
	hotel() //constructor of class
	{   	cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
	}
	void menu();		//to display the main menu
	void add();	       //to book a room
	void display();        //to display the customer record
	void rooms();	       //to display alloted rooms
	void edit();			        //to edit the customer record
	int check(int);			//to check room status
	void modify(int);		        //to modify the record
	void delete_rec(int);            //to delete the record
	void spd();                      //features of super delux room
	void dlx();                     //features of delux room
	void gen();                    //features of general room
	void coupl();                  //features of couple  room
	void coupdlx();                //features of couple delux room
};
void hotel::menu()
{
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\tWANT TO CHECK FEATURES OF";
		cout<<"\n\t\t\t5.Super Delux Room";
		cout<<"\n\t\t\t6.Delux Room";
		cout<<"\n\t\t\t7.General Room";
		cout<<"\n\t\t\t8.Couple Delux Room";
		cout<<"\n\t\t\t9.Couple Delux  Room";
		cout<<"\n\t\t\t10.Exit";
		cout<<"\nEnter your choice:\n";
		int c;
		cin>>c;
		switch(c)
		{
			case 1:	add();
				break;
			case 2: display();
				break;
			case 3: rooms();
				break;
			case 4:	edit();
				break;
			case 5: spd();
				break;
			case 6: dlx();
				break;
			case 7: gen();
				break;
			case 8: coupl();
				break;
			case 9: coupdlx();
				break;
			case 10:break;
			default:
				{
					cout<<"\n\n\t\t\tWrong choice.....!!!";
					cout<<"\n\t\t\tPress any key to continue....!!";
					getch();
				}

		}
}
void hotel::add()
{
	clrscr();
	int r,flag;
	ofstream fout("Record.dat",ios::app);

	cout<<"\n Enter Customer Detalis";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);

	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";

	else
	{
		room_no=r;
		cout<<" Name: ";
		gets(name);
		cout<<" Address: ";
		gets(address);
		cout<<" Phone No: ";
		gets(phone);
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked...!!!";
	}

	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
	menu();
}

void hotel::display()
{
	clrscr();
	ifstream fin("Record.dat",ios::in);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			clrscr();
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";

	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();
	menu();

}


void hotel::rooms()
{
	clrscr();
	ifstream fin("Record.dat",ios::in);
	cout<<"\n\t\t\t    List Of Rooms Allotted";
	cout<<"\n\t\t\t    ----------------------";
	cout<<"\n\n Room No.\tName\t\tAddress\t\t\t\tPhone No.\n";

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		cout<<"\n\n "<<room_no<<"\t\t"<<name;
		cout<<"\t\t"<<address<<"\t\t"<<phone;
	}
	cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
	menu();
}

void hotel::edit()
{
	clrscr();
	int choice,r;

	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";

	cout<<"\n Enter your choice: ";
	cin>>choice;
	clrscr();
	cout<<"\n Enter room no: " ;
	cin>>r;

	switch(choice)
	{
		case 1:	modify(r);
			break;
		case 2:	delete_rec(r);
			break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
	menu();
}


int hotel::check(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			flag=1;
			break;
		}
	}

	fin.close();
	return(flag);
	menu();
}


void hotel::modify(int r)
{
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(!file.eof())
	{
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n Name: ";
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone no: ";
			gets(phone);

			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		  }
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
	menu();
}

void hotel::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Pone No: "<<phone;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;

			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}

	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
	menu();
}
void hotel::spd()
{

	clrscr();
	cout<<"\n FEATURES OF THIS ROOM";
	cout<<"\n\n Room Type >>> Sp.delux ";
	cout<<"\n\n Room charges >>> Rs.1500 per day";
	cout<<"\n\n 1. Bed >>> 2";
	cout<<"\n\n 2.Capacity >>> 5";
	cout<<"\n\n 3.Balcony available\n\n ";
	cout<<"\n ADDITIONAL FEATURES\n ";
	cout<<"\n\n 1.A/C available ";
	cout<<"\n\n 2.Geyser available";
	cout<<"\n\n 3.TV available\n\n ";
	cout<<"\n NOTE :- Extra bed will cost Rs.50 per bed ";
	cout<<"\n Press any key to continue....!!!";
	getch();
	menu();
}
void hotel::dlx()
{

	clrscr();
	cout<<"\n FEATURES OF THIS ROOM ";
	cout<<"\n\n Room Type >>> Delux ";
	cout<<"\n\n Room charges >>>Rs.1000 per day";
	cout<<"\n\n 1. Bed >>> 2";
	cout<<"\n\n 2.Capacity >>> 5\n\n";
	cout<<"\n ADDITIONAL FEATURES\n\n ";
	cout<<"\n\n 1.A/C available ";
	cout<<"\n\n 3.Geyser available";
	cout<<"\n\n 4.TV available\n\n ";
	cout<<"\n NOTE :- Extra bed will cost Rs.50 per bed ";
	cout<<"\nPress any key to continue....!!!";
	getch();
	menu();
}
void hotel::gen()
{
	clrscr();
	cout<<"\n FEATURES OF THIS ROOM ";
	cout<<"\n\n Room Type >>> General ";
	cout<<"\n\n Room charges >>>Rs.750 per day";
	cout<<"\n\n 1. Bed >>> 2";
	cout<<"\n\n 2.Capacity >>> 5\n\n";
	cout<<"\n ADDITIONAL FEATURES ";
	cout<<"\n\n 1.Geyser available";
	cout<<"\n NOTE :- Extra bed will cost Rs.50 per bed ";
	cout<<"\n Press any key to continue....!!!";
	getch();
	menu();
}
void hotel:: coupl()
{

	clrscr();
	cout<<"\n FEATURES OF THIS ROOM ";
	cout<<"\n\n Room Type >>> Couple ";
	cout<<"\n\n Room charges >>>Rs.1250 per day";
	cout<<"\n\n 1. Bed >>> 1";
	cout<<"\n\n 2. Capacity >>> 2";
	cout<<"\n\n 3.Balcony available\n\n ";
	cout<<"\n ADDITIONAL FEATURES ";
	cout<<"\n\n 2.Geyser available";
	cout<<"\n\n 3.TV available\n\n ";
	cout<<"\n NOTE :- Extra bed will cost Rs.50 per bed ";
	cout<<"\n Press any key to continue....!!!";
	getch();
	menu();

}
void hotel::coupdlx()
{
	clrscr();
	cout<<"\n FEATURES OF THIS ROOM ";
	cout<<"\n\n Room Type >>> Couple delux ";
	cout<<"\n\n Room charges >>> Rs.1500 per day";
	cout<<"\n\n 1. Bed >>> 1";
	cout<<"\n\n 2.Capacity >>> 2";
	cout<<"\n\n 3.Balcony available\n\n ";
	cout<<"\n ADDITIONAL FEATURES ";
	cout<<"\n\n 1.A/C available ";
	cout<<"\n\n 2.Geyser available";
	cout<<"\n\n 3.TV available\n\n ";
	cout<<"\n NOTE :- Extra bed will cost Rs.50 per bed ";
	cout<<"\n Press any key to continue...!!!";
	getch();
	menu();
}

void main()
{
	clrscr();
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t****************************";
	cout<<"\n\n\n\n\t\tMade By:";
	cout<<"\tPRIYANSHA SHARMA";
	cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...!!";
	cout<<"\n\n\n\n\n";
	getch();
	hotel h;
	h.menu();
}

