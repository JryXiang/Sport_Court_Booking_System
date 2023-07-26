#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

//base class
class Sports{
	//private data members	
	double fee;
	int choice;
	int *serial_num;
	string sports_name[4];	
	
	//public member functions
	public:
	
		//constructor
		Sports(){
			sports_name[1] = "Tennis";
			sports_name[2] = "VolleyBall";
			sports_name[3] = "Badminton";
		}
		
		//define price court of the sport
		void sports_choose(){
			cout<<" Which type of sports court you will like to rent?"<<endl<<" : ";
			cin>>choice;
		//new to get serial number of court
			if(choice == 1){
				fee 	    = 23.00;
				serial_num  =  new int;
				*serial_num = 100;
			}
			else if(choice == 2){
				fee 		= 18.00;
				serial_num  =  new int;
				*serial_num = 200;
			} 
			else if(choice == 3){
				fee 		= 15.00;
				serial_num  =  new int;
				*serial_num = 300;
			}
		}		
		
		
		friend void title(Sports s);
		
		//friend class from after 1 & 2 line can access private and protected members from this class(Sports)
		friend class Display;
		friend class Calc_fee;
	
};

//base class
class Bookings{
	//private data members	
	double date, time;
	int num_court, charge, hour, i;
	string o, O;
	
	//public member functions
	public:
		//constructor
		Bookings(){
			charge = 0.00;
		}
		//ask user to type in data, get data to calculate court fee and out put data
		void court(){
			cout<<" How many court do you need to book?"<<endl<<" : ";
			cin>>num_court;			
		}
		
		void booking_date()	{	
			cout<<" When do u need to book?[DDMM]"<<endl<<" : ";
			cin>>date;
			if(date<1000){
				o = "0";
			}
			
			cout<<" What time do you need to book?[HHMM](24 hour clock)"<<endl<<" : ";
			cin>>time;
			if(time<1000){
				O = "0";//0908
			}
			
			cout<<" How many hours do you need to book for"<<endl<<" : ";
			cin>>hour;
			
			if(time>= 1800 && time<= 2300){
				charge = (num_court * hour) * 5.00;
			}
		}
		//friend class from after 1 & 2 line can access private and protected members from this class(Bookings)
		friend class Calc_fee;
		friend class Display; 	
};

//base class
class Membership{
	//private data members	
	string yn, name[20], m_n[4];
	double discount, members_fee;
	char member, apply;
	string phone_number;
	int j, players;
	
	//public member functions
	public:	
	
	Membership(){
		//m_n is member phone number
		m_n[0] = "016-7611473";
		m_n[1] = "011-16245179";
		m_n[2] = "019-2483573";
		m_n[3] = "011-13132421";
	}
		
		// ask user have member or not, then define value discount & price register fee
		void get_name(){
			cout<<" How many players will join?"<<endl<<" : ";
			cin>>players;
			
			for(j=0; j<players; j++) {
				cout<<" Enter Player "<<j+1<<" name."<<endl<<" : ";
				cin>>name[j];
			}
			
		}
		
		void get_data_membership(){
			cout<<" Do you have a membership?[Y/N]"<<endl<<" : ";
			cin>>member;
			
			if(member == 'Y' || member == 'y'){		
				fflush(stdin);
				cout<<" Enter your phone number"<<endl<<" : ";
				cin>>phone_number;
				
				//we already got list of the members, if phone num are not same with list, we will not gave customer to discount.
				if(phone_number == m_n[0] || phone_number == m_n[1] || phone_number == m_n[2] || phone_number == m_n[3]){
					yn = "  -You are our Member-";

					discount = 0.30;
					members_fee = 0.00;
				}
				else if(phone_number != m_n[0] || phone_number != m_n[1] || phone_number != m_n[2] || phone_number != m_n[3]){
					yn = "  -You are not our Member-";
					
					discount = 0;
					members_fee = 0.00;
				}
			}

			else if(member == 'N' || member == 'n'){
				cout<<" Do you want to apply our member? [Y/N]"<<endl<<" Only RM 40 to get one month 30% offer!!"<<endl<<" : ";
				cin>>apply;
				if(apply == 'Y' || apply =='y'){
					yn = "  -You are our Member-";
					
					cout<<" Enter your phone number"<<endl<<" : ";
					cin>>phone_number;
					
					discount = 0.30;
					members_fee = 40.00;
					
				} 
				else if(apply == 'N' || apply =='n'){
					yn = "  -You are not our Member-";

					cout<<" Enter your phone number"<<endl<<" : ";
					cin>>phone_number;
					
					discount = 0;
					members_fee = 0.00;
				}
	 }
	}
	//friend class from after 1 & 2 line can access private and protected members from this class(Membership)
	friend class Calc_fee;
	friend class Display;
};

//derived class
//calculate 
class Calc_fee : public Sports, public Bookings, public Membership{
	//private data members	
	double total_fee, court_fee, save, discount1;
	
	//public member functions
	public:
		//constructor
		calc_total(){
			discount1 = discount;
			court_fee = fee * num_court * hour + charge ;
			total_fee = court_fee - (court_fee * discount )+ members_fee;
		}
	friend class Display;
	friend void Cost_savings(Calc_fee c);
};

//derived class
//to create display result
class Display : public Calc_fee{
	private:
		string display_save;
		int i;
		
	public:	
		// repeat out put and +1 to get other serial number
		void serial_number(){
			for(i=0; i<num_court; i++){
				*serial_num += 1;
				cout<<" ("<<*serial_num<<")";
				//(100)(101)(102)
			}
		}
		
		//out put all data 
		display_result(){
			cout<<" ==================================================="<<endl;
			cout<<" Name    \t\t: ";
			for(j=0; j<players; j++) {
				cout<<"("<<j+1<<")"<<name[j]<<" ";
			}
			cout<<endl;
			cout<<" Phone Number   \t: "<<phone_number<<endl;
			fflush(stdin);
			cout<<" Sport of Your Choice \t: "<<sports_name[choice]<<endl;
			cout<<" Number of Booking Court: "<<num_court;
			
			//call function to output serial number
			serial_number();
			cout<<endl<<" Booking Date   \t: "<<o<<date<<endl;
			cout<<" Booking Time   \t: "<<O<<time<<endl;
			cout<<" Booking Hour   \t: "<<hour<<" hour"<<endl;
			cout<<endl;
			cout<<yn<<endl;
			cout<<"--------------------------------"<<endl;
			
			//<<fixed <<setprecision(2) is use to output decimal point & (2) is two decimal
			cout<<"   Total Price : RM "<<fixed <<setprecision(2)<<total_fee;
			delete serial_num;
	}
};
//diaplay sports title to show user
void title(Sports s){	
				cout<<endl;	
				cout<<"			*************************************"<<endl;
				cout<<"			|            Sports City            |"<<endl;
				cout<<"			|-----------------------------------|"<<endl;
				cout<<"			|          Business Hours           |"<<endl;
				cout<<"			|             0900-2300             |"<<endl;
				cout<<"			*************************************"<<endl;
				cout<<"		   	  Member will enjoy 30% offer now!!"<<endl;
				cout<<"		    (After 1800 will charge RM5 per hour & court)"<<endl<<endl;
				cout<<" [1]Tennis(RM23 per hour)  [2]Volleyball(RM18 per hour) [3]Badminton(RM15 per hour)"<<endl;			
}

//if user got members discount, output will show how much user save
//friend function
void Cost_savings(Calc_fee c){
		 c.save = c.court_fee * c.discount1;
			
		 if (c.save<=0.00){
				//less then or equal than 0.00 will not out put anything		 
			}
		 else if(c.save>0.00){
				cout<< "  (You save RM "<<c.save<<" !!)";
			}
		}

//main to call function and class
int main(){
	//create obj 
	//this way just call one obj because class Calculate_fee already derived from all the class
	//then display derived from Calculate_fee, so class Display also derived from all the class
	Sports s;// from the class sports
	Display d;
	
	//call function to make user input data
	title(s);//call friend function to make user choose sport
	d.sports_choose();//from class Sports
	d.court();//from class Bookings
	d.booking_date();//from Bookings
	d.get_name();//from class Membership
	d.get_data_membership();//from class Membership
	
	//function fflush(stdin) is used to flush the output buffer of the stream
	fflush(stdin); 
	d.calc_total();//from class Calc_fee
	
	//call funstion output result
	d.display_result();//from class Display
	Cost_savings(d);//friend function from class calc_fee
	return 0;
}

