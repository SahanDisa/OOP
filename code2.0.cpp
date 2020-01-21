#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <bits/stdc++.h>
#include <string>

using namespace std;

const int MAX_ROWS = 60;//1-60
const int MAX_SEATS = 6;//A,B,C,D,E,F
//const int MAX_FLIGHT = 100;//constraint
const int MAX_SIZE = 20;//STRUCTURE size

class flight{
	
	public:
		//default constructor
		flight(){
			//cout<<"This is flight constructor"<<endl;
			flag1 = 0;
			flag2 = 0;
			fsize = 0;
		}
		//Read the file word by word
		void ReadFile(string filename){
			
			fstream file;
		   	string word;
		   	file.open(filename.c_str());
		   
		   	
		   	while(file >> word) {
		   		
				if(word[0]>='A' and word[0]<='Z'){
					data[fsize].flight_num = word;//VA301
					file >> word;
					data[fsize].dept_date = word;//date
					file >> word;
					data[fsize].dept_time = word;//time
					getline(file,word);
					getline(file,word);
					data[fsize].dept_airport = word;//departure airport
					getline(file,word);
					data[fsize].arr_airport = word;//arrival airport
					
					//----------seat graph----------//
					getline(file, word); 
  					data[fsize].seat_count[0] = 0;//declaration of count of avaliable seats
  					data[fsize].seat_count[1] = 0;
  					data[fsize].seat_count[2] = 0;
			        // Keep reading a new line while there is a blank line 
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
						  			data[fsize].rows.push_back(row_value);
									  	
								}else if(count == 2){
									//cout<<temp;
									if(temp=="B"){
										data[fsize].sclass[row_value] = 'B';
											
									}else if(temp=="E"){
										data[fsize].sclass[row_value] = 'E';
								
									}
								}else if(count == 3){
									//cout<<temp;
									for(j=0;j<temp.size();j++){
										//to remove garbage characters
										if(temp[j]>=65 and temp[j]<=70){
											data[fsize].seats[row_value][j] = temp[j];
											data[fsize].seat_count[0]++;
											if(data[fsize].sclass[row_value]=='B'){
												data[fsize].seat_count[1]++;
											}else if(data[fsize].sclass[row_value]=='E'){
												data[fsize].seat_count[2]++;
											} 
										}
										
									}
									
								}
						        //cout<<endl;
						      
							}
							temp.clear();
							count =0;	        	
			        	getline(file, word); 
					} 
					fsize++;
				}
		   	}
		   	
		   	file.close();
		}
		//print all flights in the database
		void printAllFlights(){
			
			for(i=0;i<fsize;i++){
				//The program should list all flight numbers that have at least one seat available
			
				if(data[i].seat_count[0]>=1){
					cout<<"|------------------------------------Flight "<<i+1<<"-----------------------------------|"<<endl;
					cout<<"+-------------------------------------------------------------------------------+"<<endl;
					cout<<"|Flight Number|\t"<<"Date|\t"<<"Time|\t"<<"Departure Airport|\t"<<"Arrival Airport\t\t|"<<endl;
					cout<<"+-------------------------------------------------------------------------------+"<<endl;
					cout<<"| "<<data[i].flight_num<<"\t\t"<<data[i].dept_date<<"\t"<<data[i].dept_time<<"\t"<<data[i].dept_airport<<"\t\t\t"<<data[i].arr_airport<<" |"<<endl;
					cout<<"+-------------------------------------------------------------------------------+"<<endl;
					//The program should list all number of seats available with their class
					//for further understanding to customers about count of seats
					cout<<"\n+----------------------Total Avaliable Seats for Reserve------------------------+\n";
					cout<<"|\tBusiness Class : "<<data[i].seat_count[1]<<endl;
					cout<<"|\tEconomy  Class : "<<data[i].seat_count[2]<<endl;
					cout<<"|\tTotal Seats Avaliable : "<<data[i].seat_count[0]<<endl;
					cout<<"+-------------------------------------------------------------------------------+"<<endl;
				}
				
				cout<<endl;
			}
			
			cout<<endl;
		}
		//search a particular flight
		int searchFlight(string value){
			for(i=0;i<fsize;i++){
				if(data[i].flight_num == value){
					return i;
				}
					
			}
			return -1;
		}
		//print a particular flight
		void printFlight(int ds){
			cout<<"--------------------------Flight--"<<data[ds].flight_num<<"------------------------"<<endl;
			cout<<"Flight\tDate\t\tTime\tDeparture Airport\tArrival Airport"<<endl;
			cout<<data[ds].flight_num<<"\t"<<data[ds].dept_date<<"\t"<<data[ds].dept_time<<"\t"<<data[ds].dept_airport<<"\t\t"<<data[ds].arr_airport<<endl;
			cout<<"-----------------------------------------------------------------------------------"<<endl;
			cout<<"Business Class Seats : "<<data[ds].seat_count[1]<<endl;
			cout<<"Economy Class Seats  : "<<data[ds].seat_count[2]<<endl;
			cout<<"\n\t------Avaliable Seats with more details------\n";
			for(j=0;j<data[ds].rows.size();j++){
					row = data[ds].rows[j];//row number
					cout<<row<<" "<<data[ds].sclass[row]<<" \t";
					//seats
					for(k=0;k<6;k++){
						if(data[ds].seats[row][k]>=65 and data[ds].seats[row][k]<=70)
							cout<<data[ds].seats[row][k]<<" ";
					}
					cout<<endl;
			}
			cout<<endl;
		}
		void printSeats(int ds,int n){
			//if only the number of seats are available
			if(data[ds].seat_count[0]>=n){
				cout<<"\n\t--------Avaliable Seats--------"<<endl;
				cout<<"---------------------------------------------------"<<endl;
				cout<<"Row SeatClass SeatCount  Avaliability(Yes/No)\n";
				cout<<"----------------------------------------------------"<<endl;
				for(j=0;j<data[ds].rows.size();j++){
						row = data[ds].rows[j];//row number
						cout<<row<<" \t"<<data[ds].sclass[row]<<" \t";
						//seats
						count=0;
						for(k=0;k<6;k++){
							if(data[ds].seats[row][k]>=65 and data[ds].seats[row][k]<=70){
								count++;
							}
						}
						cout<<count;
						if(count>=n){
							cout<<"\t\tYes";
						}else{
							cout<<"\t\tNo";
						}
						cout<<endl;
					}
					cout<<endl;
			}else{
				cout<<"Number of Seats are not avaliable"<<endl;
			}
			
		}
		void BookSeats(){
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			cout<<"Input the seat row (1...60) : ";
			cin>>row;
			cout<<"Input the seat location (A-F) : ";
			cin>>location;
			//flight count in the database
			count = searchFlight(flight_number);
			//search the row 
			for(i=0;i<data[count].rows.size();i++){
				if(data[count].rows[i]==row){
					flag1 = row;
					
				}
			}
			for(i=0;i<6;i++){
				if(data[count].seats[row][i]==location){
					flag2 = i;
				}
				//seat location is not avaliable
				flag2 = -1;
			}
			//if all conditions are statisfied booking has to be done
			if(flag1>=0 and flag2>=0){
				cout<<"\n\t------Booking success----------\n"<<endl;
				//remove the booked seat from the database struct
				//We named it as Z as long as it is remove by taking because seat should be in A-F
				data[count].seats[flag1][flag2] = 'Z';
				//reduce seat count by 1 
				data[count].seat_count[0]--;
				//remove from business or economy seats
				if(data[count].sclass[row]=='B'){
					data[count].seat_count[1]--;
				}else if(data[count].sclass[row]=='E'){
					data[count].seat_count[2]--;
				}
				
				//cout<<"Removed Seat : "<<count<<" "<<row<<" "<<flag2<<" "<<data[count].seats[flag1][flag2]<<endl;
				count = 0;
			}else{
				cout<<"\n\t------Booking unsuccess---------"<<endl;
				cout<<"Check again for valid flight number , Seat Row , Seat location \n"<<endl;
			}
		}
		void WriteFile(){
			ofstream outfile;
			// opens the file
			outfile.open("flights.dat"); 
			//		or
			//outfile.open(filename)
			
			// if file couldn't be opened
			if( !outfile ) { 
		      cerr << "Error: file could not be opened" << endl;
		      exit(1);
		   }else{
		   	//writing process
		   	for(i=0;i<fsize;i++){
		   		outfile<< data[i].flight_num << endl;
		   		outfile<< data[i].dept_date << "\t" << data[i].dept_time <<endl;
   				outfile<< data[i].dept_airport<<endl;
   				outfile<< data[i].arr_airport<<endl;
   				
   				//-----Seats Graph-----//
   				for(j=0;j<data[i].rows.size();j++){
					row = data[i].rows[j];//row number
					outfile<<row<<" "<<data[i].sclass[row]<<" \t";
					//seats
					for(k=0;k<6;k++){
						if(data[i].seats[row][k]>=65 and data[i].seats[row][k]<=70)
							outfile<<data[i].seats[row][k];
							count++;
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
		//destructor
		~flight(){
			
		}
		////
		private:
			string flight_number,temp;//string variables
			int row,row_value;
			int count;//count variables
			int i,j,k;//iterators
			int fsize;
			int flag1,flag2;//for booking
			char location;
			
			//structs of flights
			struct flights{
				string flight_num;
				string dept_date;
				string dept_time;
				string dept_airport;
				string arr_airport;
				vector <int> rows;
				char sclass[MAX_ROWS];
				char seats[MAX_ROWS][MAX_SEATS];
				//max seats are 6 in a particular row
				int seat_count[3];//total amount of seats avaliable for customers
				//arr[0]-> total , arr[1]-> business class seats , arr[2]-> economy class seats
			}data[MAX_SIZE];//declaration
			
			//end of struct
};

//end of class


int main(){
	int option,x,i;
	int num_of_seats;
	int flight_num;
	string flight_number;
	string data;
	string ofile;
	
	cout<<"-------------VIRGIN AIRLINE-------------"<<endl;
	cout<<"-----Flight Seat Reservation System-----"<<endl;
	
	/////////////////READ FILE////////////////////////
	flight f1;
	f1.ReadFile("flights.txt");
	//////////////////////////////////////////////////
	do{
		cout<<"\t--------OPTION MENU--------"<<endl;
		cout<<"\t1.Display Avaliable Flights"<<endl;
		cout<<"\t2.View Flight"<<endl;
		cout<<"\t3.Seat Avaliability"<<endl;
		cout<<"\t4.Seat Booking"<<endl;
		cout<<"\t5.Exit\n"<<endl;
		cout<<"Input the option : ";
		cin>>option;
		switch(option){
			
		case 1 :
			f1.printAllFlights();
			break;
		case 2 :
			cout<<"-----------Search Flight--------------"<<endl;
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			cout<<endl;
			if(f1.searchFlight(flight_number)>=0){
				f1.printFlight(f1.searchFlight(flight_number));
			}else{
				cout<<"Flight search error, Input correct Flight number"<<endl;
			}
			break;
		case 3 :
			cout<<"----------Search Avaliable Seats-----------"<<endl;
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			cout<<"Number of Seats Required : ";
			cin>>num_of_seats;
			f1.printSeats(f1.searchFlight(flight_number),num_of_seats);
			break;
		case 4:
			cout<<"----------Booking Section---------"<<endl;
			f1.BookSeats();
			break;			
		
		case 5:
			cout<<"\n-----Write to a new File------"<<endl;
			cout<<"to:- flights.dat"<<endl;
			f1.WriteFile();
			break;
		case 6:
		
		
			break;	
		default:
			cout<<"\n\tInvalid option"<<endl;
			cout<<"----Input option between (1-5)----"<<endl;
		}
		
	}while(option!=5);
	
	
	return 0;
}
