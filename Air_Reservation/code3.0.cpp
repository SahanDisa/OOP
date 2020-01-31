#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <bits/stdc++.h>
#include <string>

using namespace std;

const int MAX_ROWS = 60;//1-60
const int MAX_SEATS = 6;//A,B,C,D,E,F
const int MAX_SIZE = 20;//STRUCTURE size



//flight class;
class flight{
	//private data members
	private:
		string flight_num;
		string dept_date;
		string dept_airport;
		string arr_airport;
		int seat_count[3];
		vector <int> rows;
		char sclass[MAX_ROWS];
		char seats[MAX_ROWS][MAX_SEATS];
		
		
		int count;
	//public data members and member functions	
	public:	
		//default constructor
		flight(){
			count = 0;
			seat_count[0] = 0;
			seat_count[1] = 0;
			seat_count[2] = 0;
			
		}
		//setters for private members(ENCAPSULATION)
		void Setflight_num(string val){
			flight_num = val;
		}
		void Setdept_date(string val){
			dept_date = val;
		}
		void Setdept_airport(string val){
			dept_airport = val;
		}
		void Setarr_airport(string val){
			arr_airport = val;
		}
		void SetRows(int value){
			rows.push_back(value);
		}
		void SetClass(char seatclass,int row){
			sclass[row] = seatclass;
			
		}
		void SetSeatCount(int type){
			seat_count[type]++;
		}
		void SetSeat(char seat,int location,int row){
			seats[row][location] = seat;	
			if(sclass[row] == 'B'){
				seat_count[1]++;
			}else if(sclass[row] == 'E'){
				seat_count[2]++;
			}
		}
		//getters for private members
		string GetFlight_Num(){
			return flight_num;
		}
		string GetDateAndTime(){
			return dept_date;
		}
		string GetDeptAirport(){
			return dept_airport;
		}
		string GetArrAirport(){
			return arr_airport;
		}
		int GetSeatCount(int type){
			if(type==0){
				return seat_count[0];
			}else if(type == 1){
				return seat_count[1];
			}else if(type == 2){
				return seat_count[2];
			}
		}
		int GetRows(){
			return rows.size();
		}
		int GetRow(int pos){
			int value = rows[pos];
			return value;
		}
		char GetSeatClass(int pos){
			return sclass[pos];
		}
		int RowCount(int pos){
			int count;
			for(int i =0; i<6;i++){
				if(seats[pos][i]>='A' and seats[pos][i]<='F'){
					count++;
				}
			}
			return count;
		}
		char GetSeat(int row,int location){
			return seats[row][location];
		}
		
		//MEMBER FUNCTIONS
		//print a flight	
		void printFlight();
		//check avaliablity of seats
		void CheckSeats(int amount,char type);
		//Book a Seat
		void BookSeats(int location,char seat);
		
		//reset functions	
		void ResetRows(){
			rows.clear();
		}
		void ResetCount(){
			seat_count[0]=0;
			seat_count[1]=0;
			seat_count[2]=0;
		}
		void ResetSeats(){
			for(int i=0;i<MAX_ROWS;i++){
				for(int j=0;j<MAX_SEATS;j++){
					seats[i][j] = 'Z';
				}
			}
		}
		void RemoveSeat(int row,int loc){
			seats[row][loc] = 'Z';
			//cout<<"Removed success"<<endl;
		}
		void RemoveRow(int value_of_row){
			int res = 0;
			for(int i =0; i< rows.size();i++){
				if(rows[i]==value_of_row){
					res = i;
				}
			}
			rows.erase(rows.begin() + res);
		}
};


void flight::printFlight(){
	cout<<"-------------------------------------Flight--"<<GetFlight_Num()<<"-----------------------------------"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"| Flight |    Date & Time     | Depature Airport | Arrival Airport | B Class | E Class | Total Seats |"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
	
	cout<<GetFlight_Num()<<"   "<< GetDateAndTime()<<"\t"<<GetDeptAirport()<<"\t\t"<<GetArrAirport()<<"\t\t";
	cout<<GetSeatCount(1)<<"\t"<<GetSeatCount(2)<<"\t"<<GetSeatCount(0)<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
	//----------seat graph---------//
	int row;
	cout<<"+-----+-------+------------------------+"<<endl;
	cout<<"| Row | Class |         Seats          |"<<endl;
	cout<<"+-----+-------+------------------------+"<<endl;
	for(int i = 0;i <rows.size();i++){
		cout<<"| "<<rows[i]<<"\t"<<sclass[rows[i]]<<"\t";
		row = rows[i];
		for(int j =0; j < 6; j++){
			if(seats[row][j]>='A' and seats[row][j]<='F'){
				cout<<seats[row][j]<<" ";
			}
		}
		cout<<endl;
	}
	cout<<"+-----+-------+------------------------+"<<endl;
	cout<<endl;

}
void flight::BookSeats(int location,char seat){
	//we set the seat for 'Z' when booked a seat
	
	int flag1=0,flag2=0;
	int row_count;
	
	//check row
	for(int i =0; i<rows.size();i++){
		if(rows[i]==location){
			flag1 = 1 ;
		}
	}
	//check seat
	for(int j=0;j<6;j++){
		if(seats[location][j]==seat){
			flag2 = j;
		}
		//flag2 = -1;
	}
	//double check( critical section of the program )
	if(flag1 == 1 and flag2>=0){
		//check for valid seat
		if(seats[location][flag2]>='A' and seats[location][flag2]<='F' ){
			cout<<"\t-----Booking success------"<<endl;
			cout<<"You have booked row : "<<location<<" seat : "<<seat<<" from class : "<<GetSeatClass(location)<<endl;
			
			//remove the seat
			RemoveSeat(location,flag2);
			//reduce the total count
			seat_count[0]--;
			//reduce seat class count
			if(GetSeatClass(location)=='B'){
				seat_count[1]--;
			}else if(GetSeatClass(location)=='E'){
				seat_count[2]--;
			}
			
			//if no longer seats are not avaliable in a particular row delete it from the database
			if(!RowCount(location)){
				RemoveRow(location);
			}
		}
		
	}else{
			cout<<"\tBooking unsucess"<<endl;
			cout<<"Check for valid row number and seat number again!"<<endl;
		}
	cout<<endl;
}

void flight::CheckSeats(int amount,char type){
	//cout<<amount<<"  "<<type<<endl;
	if(type == 'E'){
		if(amount <= GetSeatCount(2)){
			cout<<"-------------Seats are avaliable------------"<<endl;
			cout<<"------You can book seats(Go to Option 4)----\n"<<endl;
		}else{
			cout<<"Sorry!...Seats are not avaliable"<<endl;
		}
	}else if(type == 'B'){
		if(amount <= GetSeatCount(1)){
			cout<<"-------------Seats are avaliable------------"<<endl;
			cout<<"------You can book seats(Go to Option 4)----\n"<<endl;
		}else{
			cout<<"Sorry!...Seats are not avaliable"<<endl;
		}
	}
}


//vector of flights to store array of object(instances of classes)
vector <flight> records;
//read file
void ReadFile(string filename){
	int row_value,j;
	int count = 0,temp_count=0;
	int flag = 0;
			
	flight f1;
	fstream file;
	string word,temp;
	file.open(filename.c_str());
	
	//one by one add to the vector of flight	   
	while(getline(file, word)) {
		if(word[0]>='A' and word[0]<='Z'){
			temp_count++;
			flag = 1;
			f1.Setflight_num(word);
			getline(file,word);
			f1.Setdept_date(word);
			getline(file,word);
			f1.Setdept_airport(word);
			getline(file,word);
			f1.Setarr_airport(word);
			
			//----------seat graph----------//
			getline(file, word); 
			
			//Keep reading a new line while there is a blank line 
			while (word.length()!=0){
			    // Used to split string around spaces. 
				istringstream ss(word); 
				count = 0;
						  	
				while (count++<3){
					ss >> temp; 
					if(count == 1){
						//cout<<temp;
						istringstream sss(temp);
						sss >> row_value;
						f1.SetRows(row_value);
									  	
						}else if(count == 2){
							//cout<<temp;
							if(temp=="B"){
								f1.SetClass('B',row_value);
											
							}else if(temp=="E"){
								f1.SetClass('E',row_value);
							}
						}else if(count == 3){
							//cout<<temp<<endl;
							
							for(j=0;j<temp.size();j++){
							//to remove garbage characters
								if(temp[j]>=65 and temp[j]<=70){
									//cout<<temp[j]<<" "<<j<<" "<<row_value<<" "; 
									f1.SetSeat(temp[j],j,row_value);
									f1.SetSeatCount(0);
								}				
							}
							//cout<<endl;
						}
					//cout<<endl;
				}
				temp.clear();
				count =0;	        	
			    getline(file, word);
						 
			} 
		}
		records.push_back(f1);
		f1.ResetRows();
		f1.ResetCount();
		f1.ResetSeats();
	}
	file.close();
}
//end of read file

//search a particular flight
int searchFlight(string value){
	
	for(int i=0;i<records.size();i++){
		if(records[i].GetFlight_Num()==value){
			//cout<<"success";
			return i;
		}
					
	}
	return -1;
}

//print all flights in the file with avaliable seat counts
void printAllFlights(){
	int i;
	cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"|Flight Number|  Date & Time  | Depature Airport | Arrival Airport | B Class | E Class | Total Seats |"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
	for(i=0;i<records.size();i++){
		//The program should list all flight numbers that have at least one seat available
		
		if(records[i].GetSeatCount(0)>=1){
			cout<<"|"<<records[i].GetFlight_Num()<<"\t"<<records[i].GetDateAndTime()<<"\t"<<records[i].GetDeptAirport()<<"\t\t"<<records[i].GetArrAirport();
			cout<<"\t\t"<<records[i].GetSeatCount(1)<<"\t"<<records[i].GetSeatCount(2)<<"\t\t"<<records[i].GetSeatCount(0)<<"   |"<<endl;
			//The program should list all number of seats available with their class
			//for further understanding to customers about count of seats
			cout<<"+----------------------------------------------------------------------------------------------------+"<<endl;
		}
		
	}
}

//write to the file
void WriteFile(){
	ofstream outfile;
	int row;
	// opens the file
	outfile.open("flights.dat"); 

	// if file couldn't be opened
	if( !outfile ) { 
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}else{
		//writing process
		for(int i=0;i<records.size();i++){
		   		outfile<< records[i].GetFlight_Num() << endl;
		   		outfile<< records[i].GetDateAndTime() <<endl;
   				outfile<< records[i].GetDeptAirport()<<endl;
   				outfile<< records[i].GetArrAirport()<<endl;
   				
   				//-----Seats Graph-----//
   				for(int j=0;j<records[i].GetRows();j++){
					row = records[i].GetRow(j);//row number
					outfile<<row<<" "<<records[i].GetSeatClass(row)<<" \t";
					//seats
					for(int k=0;k<6;k++){
						if(records[i].GetSeat(row,k)>=65 and records[i].GetSeat(row,k)<=70)
							outfile<<records[i].GetSeat(row,k);
							
					}
					outfile<<endl;
				}
				outfile<<endl;
		   	}
		   //close the file
		outfile.close();
	}
	cout<<"Successfully write to flights.dat the modified data"<<endl;

}

int main(){
	int option,x,i;
	int num_of_seats,row;
	int flight_num;
	string flight_number;
	string data;
	string ofile;
	char seat_class,location;
	
	cout<<"-------------VIRGIN AIRLINE-------------"<<endl;
	cout<<"-----Flight Seat Reservation System-----"<<endl;
	
	/////////////////READ FILE////////////////////////
	ReadFile("flights.txt");
	//////////////////////////////////////////////////
	do{
		cout<<"\t+--------OPTION MENU--------+"<<endl;
		cout<<"\t|1.Display Avaliable Flights|"<<endl;
		cout<<"\t|2.View a Flight            |"<<endl;
		cout<<"\t|3.Seat Avaliability        |"<<endl;
		cout<<"\t|4.Seat Booking             |"<<endl;
		cout<<"\t|5.Exit                     |"<<endl;
		cout<<"\t+---------------------------+"<<endl;
		cout<<"Input the option : ";
		
		cin>>option;
		switch(option){
			
		case 1 :
			printAllFlights();
			break;
		case 2 :
			cout<<"-----------Search Flight--------------"<<endl;
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			
			cout<<endl;
			x = searchFlight(flight_number);
			if(x>=0){
				records[x].printFlight();
			}else{
				cout<<"Flight search error, Input correct Flight number\n"<<endl;
			}
			break;
		case 3 :
			cout<<"----------Search Avaliable Seats-----------"<<endl;
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			cout<<"Number of Seats Required : ";
			cin>>num_of_seats;
			cout<<"Input the Seat Class(Input E or B) : ";
			cin>>seat_class;
			x = searchFlight(flight_number);
			if(x>=0){
				records[x].CheckSeats(num_of_seats,seat_class);
			}else{
				cout<<"Flight search error, Input correct Flight number\n"<<endl;
			}
			
			break;
		case 4:
			cout<<"----------Booking Section---------"<<endl;
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			x = searchFlight(flight_number);
			if(x>=0){
				cout<<"Input the seat row (1...60) : ";
				cin>>row;
				cout<<"Input the seat location (A-F) : ";
				cin>>location;
				records[x].BookSeats(row,location);
			}else{
				cout<<"Flight search error, Input correct Flight number\n"<<endl;
			}
			
			break;			
		
		case 5:
			cout<<"\n-----Write to a new File------"<<endl;
			cout<<"to:- flights.dat"<<endl;
			WriteFile();
			break;
			
		default:
			cout<<"\n---------Invalid option---------"<<endl;
			cout<<"----Input option between (1-5)----"<<endl;
		}
		
	}while(option!=5);
	
	return 0;
}
