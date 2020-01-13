#include<iostream>
#include<fstream>
#include<vector>
#include <sstream> 
#include <bits/stdc++.h>
#include<string>

using namespace std;

const int MAX_ROWS = 60;//1-60
const int MAX_SEATS = 6;//A,B,C,D,E,F
const int MAX_FLIGHT = 100;//constraint
const int MAX_SIZE = 20;//STRUCTURE size

class flight{
	
	public:
		//default constructor
		flight(){
			cout<<"This is flight constructor"<<endl;
			flag1 = 0;
			flag2 = 0;
			i=0;
		}
		//Read the file word by word
		void ReadFile(string filename){
			
			fstream file;
		   	string word;
		   	file.open(filename.c_str());
		   
		   	
		   	while(file >> word) {
		   		
				if(word[0]>='A' and word[0]<='Z'){
					data[i].flight_num = word;//VA301
					file >> word;
					data[i].dept_date = word;//date
					file >> word;
					data[i].dept_time = word;//time
					getline(file,word);
					getline(file,word);
					data[i].dept_airport = word;//departure airport
					getline(file,word);
					data[i].arr_airport = word;//arrival airport
					
					//----------seat graph----------//
					getline(file, word); 
  					
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
						  			data[i].rows.push_back(row_value);
									  	
								}else if(count == 2){
									//cout<<temp;
									if(temp=="B"){
										data[i].sclass[row_value] = 'B';
									}else if(temp=="E"){
										data[i].sclass[row_value] = 'E';
									}
								}else if(count == 3){
									//cout<<temp;
									for(j=0;j<temp.size();j++){
										data[i].seats[row_value][j] = temp[j]; 
									}
									
								}
						        //cout<<endl;
						      
							}
							temp.clear();
							count =0;	        	
			        	getline(file, word); 
					} 
					i++;
				}
		   	}
		   	
		   	file.close();
		}
		//print all flights in the database
		void printAllFlights(){
			size = i;
			for(i=0;i<size;i++){
				cout<<"-----Flight "<<i+1<<"-----"<<endl;
				cout<<data[i].flight_num<<"\t"<<data[i].dept_date<<"\t"<<data[i].dept_time<<"\t"<<data[i].dept_airport<<"\t"<<data[i].arr_airport<<endl;
				cout<<"\n-----Avaliable Seats for Reserve------\n";
				for(j=0;j<data[i].rows.size();j++){
					row = data[i].rows[j];//row number
					cout<<row<<" "<<data[i].sclass[row]<<" \t";
					//seats
					for(k=0;k<6;k++){
						if(data[i].seats[row][k]>=65 and data[i].seats[row][k]<=70)
							cout<<data[i].seats[row][k]<<" ";
					}
					cout<<endl;
				}
				cout<<endl;
			}
			cout<<endl;
		}
		//search a particular flight
		int searchFlight(string value){
			for(i=0;i<size;i++){
				if(data[i].flight_num == value){
					return i;
				}
					
			}
			return -1;
		}
		//print a particular flight
		void printFlight(int ds){
			cout<<"Flight\tDate\tTime\tDeparture Airport\tArrival Airport"<<endl;
			cout<<data[ds].flight_num<<"\t"<<data[ds].dept_date<<"\t"<<data[ds].dept_time<<"\t"<<data[ds].dept_airport<<"\t\t"<<data[ds].arr_airport<<endl;
			////
			cout<<"\n\t------Avaliable Seats------\n";
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
			cout<<"\n\t------Avaliable Seats------\n";
			cout<<"\nRow\tclass\tSeat Count  Avaliability(Yes/No)\n";
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
						cout<<"\tYes";
					}else{
						cout<<"\tNo";
					}
					cout<<endl;
				}
				cout<<endl;
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
					flag1 = 1;
				}
			}
			for(i=0;i<6;i++){
				if(data[count].seats[row][i]==location){
					flag2 = 1;
				}
			}
			//if all conditions are statisfied booking has to be done
			if(flag1==1 and flag2==1){
				cout<<"\n\t------Booking success----------\n"<<endl;
				//remove the booked seat from the database
			}else{
				cout<<"Booking unsuccess"<<endl;
				cout<<"Check again with flight number , Seat Row , Seat location "<<endl;
			}
		}
		void WriteFile(string filename){
			ofstream outfile;
			outfile.open("flight.dat"); // opens the file
			//or
			//outfile.open(filename
			if( !outfile ) { // file couldn't be opened
		      cerr << "Error: file could not be opened" << endl;
		      exit(1);
		   }else{
		   	//writing process
		   	for(i=0;i<5;i++){
		   		outfile << num[i] << endl;
   
			   }
		   }
		   //close the file
		   outdata.close();
		}
		////
		private:
			string flight_number;
			int row_value;
			int row;
			int count;
			int i,j,k;//iterators
			int size;
			int flag1,flag2;//for booking
			string temp;
			char location;
			//struct of flights
			struct flights{
				string flight_num;
				string dept_date;
				string dept_time;
				string dept_airport;
				string arr_airport;
				vector <int> rows;
				char sclass[MAX_ROWS];
				char seats[MAX_ROWS][MAX_SEATS];//max seats are 6 in a particular row
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
	
	cout<<"-----Flight Seat Reservation System-----\n";
	cout<<"\t1.Display Avaliable Flights\n\t2.View Flight\n\t3.Seat Avaliability\n\t4.Seat Booking\n\t5.Exit\n";

	
	/////////////////READ FILE////////////////////////
	flight f1;
	f1.ReadFile("flights.txt");
	//////////////////////////////////////////////////
	do{
		cout<<"Input the option : ";
		cin>>option;
		switch(option){
			
		case 1 :
			cout<<"---------Flights---------\n";
			f1.printAllFlights();
	
			break;
		case 2 :
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
			cout<<"Input the Flight Number : ";
			cin>>flight_number;
			cout<<"Number of Seats Required : ";
			cin>>num_of_seats;
			f1.printSeats(f1.searchFlight(flight_number),num_of_seats);
			break;
		case 4:
			cout<<"----------Booking---------"<<endl;
			f1.BookSeats();
			break;			
		
		case 5:
			cout<<"\n-----Write to a new File------"<<endl;
			cout<<"Input the file name to write : ";
			cin>>ofile;
			f1.WriteFile(ofile);
			break;
		}
	}while(option!=5);
	
	
	return 0;
}
