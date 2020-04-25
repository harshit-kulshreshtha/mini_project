#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<ctime>
using namespace std;

void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
time_t now, later;
 
void sleep(int delay)
{
 now=time(NULL);
 later=now+delay;
 while(now<=later)
 	now=time(NULL);
}
class PersonDetail
{
	char cus_name[30];
	char cus_phno[11];
	public:
		int get()
		{
			cout<<"Enter the customer name: \n";
			cin>>cus_name;
			cout<<"Enter the customer phone number:\n";
			cin>>cus_phno;
		}
		int put()
		{
			cout<<"\n..................................................................................\n";
		 	cout<<"CUSTOMER'S NAME: "<<cus_name<<"\t\t"<<"CUSTOMER'S PHONE NO.: "<<cus_phno<<endl<<endl;
		}
};
class medicine : public PersonDetail
{
	int med_id;
	char med_name[30];
	int cost;
	int quan;
	
	struct dates
	{
		int date;
		char mon[5];
		int year;
	}var1,var2;
	public:
		int getdata()
		{
			cout<<"ENTER MED_ID\t";
			cin>>med_id;
			cout<<"ENTER MED_NAME\t";
			cin>>med_name;
			cout<<"ENTER UNIT COST\t";
			cin>>cost;
			cout<<"ENTER QUANTITY\t";
			cin>>quan;
			cout<<"ENTER DATE OF manufacturing(04-may-2000)\n";
			cin>>var1.date>>var1.mon>>var1.year;
			cout<<"ENTER DATE OF EXPIRY(04-05-2001)\n";
			cin>>var2.date>>var2.mon>>var2.year;
		 } 
		 int putdata()
		 {
		 	cout<<"MEDICINE ID:     "<<med_id<<"\t\t"<<"MEDICINE NAME:          "<<med_name<<endl<<endl;
		 	cout<<"UNIT cOST:       "<<cost<<"\t\t"<<"QUANTITY:                 "<<quan<<endl<<endl;
		 	cout<<"MANUFACTURING DATE: "<<var1.date<<"-"<<var1.mon<<"-"<<var1.year<<"\t";
		 	cout<<"EXPIRY DATE:     "<<var2.date<<"-"<<var2.mon<<"-"<<var2.year<<endl<<endl;
		 	cout<<"TOTAL COST:      "<<cost*quan<<endl<<endl;
		 	cout<<"\n..................................................................................\n";
		}
		int compare()
		{
			return med_id;
		}
		int update()
		{
			int Q;
			cout<<"Enter the additional quantity of that medicine Customer is purchasing\n";
				cin>>Q;
				quan+=Q;
		}
};
int main()
{

	
	medicine ob;
	int num,medid;
	char ch;
	system("color 70");
	/*ifstream printout;
	printout.open("banner.txt");
	while(!printout.eof()==0)
	{
		printout>>ch;
		cout<<ch;
	};*/
	system("pause");
	system("cls");
	cout<<"\t***********~~~~~~~MEDICAL STORE MANAGEMENT SYSTEM~~~~~~~~~*************\n";
	cout<<"\n\t\t\t\t  WELCOME \n";
	cout<<"\n\t\t\t\t  TO our\n";
	cout<<"\n\t\t\t\t   SHOP\n";
	system("pause");
	//system("cls");
	for(int i=21;i<35;i++)
	{
		gotoxy(0,15);
		cout<<"OPENING THE DOCUMENT";
		gotoxy(i,15);
		cout<<"...";
		sleep(0.25);
		system("cls");
	}
	
while(1)
{	
	system("color 70");
	fstream fout("medicine.txt");
	fstream fin("medicine.txt",ios::in);
	ofstream fout1("temp.txt",ios::out);
	cout<<"........................................................................................................\n";
	cout<<"\t\t1) SALE ANY MEDICINE:\n";
	cout<<"\t\t2) DETAILS OF ALL SALED MEDICINE:\n";
	cout<<"\t\t3) SEARCH ANY MEDICINE:\n";
	cout<<"\t\t4) MODIFY ANY DETAIL OF MEDICINE:\n";
	cout<<"\t\t5) DELETE ANY RECORD OF MEDICINE:\n";
	cout<<"\t\t6) TO EXIT:\n";
	cout<<"ENTER YOUR choice:\n";
	cin>>num;
	system("cls");
	switch(num)
	{
		case 1:
			ob.get();
			ob.getdata();
			fout.seekp(0,ios::end);
			fout.write((char*) &ob, sizeof(ob));
			fout.close();
			system("cls");
			break;
		case 2:
			fin.seekg(0);
			while(fin.read((char*) &ob, sizeof(ob)))
			{
				ob.put();
				ob.putdata();
			}
				fin.close();
				system("pause");
				system("cls");
			break;
		case 3:
			cout<<"Enter the medicine id of the medicine you want to search:\n";
			cin>>medid;
			
			while(fin.read((char*) &ob, sizeof(ob)))
			{
				
				if(medid==ob.compare())
					ob.putdata();					

			}
			fin.close();
			system("pause");
			system("cls");
			break;
		case 4:
			cout<<"Enter the medicine id of the medicine whose detail you want to modify: \n";
			cin>>medid;
			while(fin.read((char*) &ob, sizeof(ob)))
			{
				if(medid==ob.compare())
				{
					ob.update();
					int pos=(-1)*sizeof(ob);
					fin.seekg(pos,ios::cur);
					int x=fin.tellg();
					fout.seekp(x,ios::beg);
					fout.write((char*) &ob, sizeof(ob));
					break;
				}	
			}
			fin.close();
			fout.close();
			system("cls");
			break;
		case 5:
			cout<<"Want to delete record of any sale, therefore enter the medicine id :\n";
			cin>>medid;
			fin.seekg(0);
			while(fin.read((char*) &ob, sizeof(ob)))
			{
				if(ob.compare()!=medid)
				{
					fout1.seekp(0,ios::end);
					fout1.write((char*) &ob, sizeof(ob));
				}
			}
			remove("medicine.txt");
			rename("temp.txt","medicine.txt");
			remove("temp.txt");
			fin.close();
			fout1.close();
			system("pause");
			system("cls");
			break;
		case 6:
			return 0;	
	}
	system("pause");
	system("cls");
}		
}
