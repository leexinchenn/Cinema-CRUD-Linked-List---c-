//Group 21
//Chin Hui Xin 1181203506
//Lee Xin Chen 1181203295
//Lim Jia Min 1181203267

#include <iostream>
#include <ctime>	//for time 
#include <cstdlib>	//for srand & rand (random number)
#include <iomanip>	//for setw() 

using namespace std;

//to get movie id
//5 digit auto generate number
int getid()
{
	int id;
	//program for auto generated numbers
	//this  function must write before the 'rand' function
	unsigned seed = time(0);
	srand(seed);
	
	id = rand()%90000+10000; 
	//random number between 10000 to 99999
	
	return id;
}

struct movie
{
	int id;
	string name;
	double price;
	movie *next;
};

class Movie
{
	private:
		movie *head, *temp, *tail;
		char yn;
		string m_name;
		double m_price;
		
	public:
		Movie()
		{
			head = NULL;
		}
		
		//create the first node(movie) - LINKED LIST
		void addFirst()
		{
			cout<<"Enter Movie Name: ";
			cin.ignore();
			getline(cin,m_name);
			
			cout<<"Enter Movie Ticket Price: RM ";
			cin>>m_price;
			
			head = new movie; 
			head->id = getid();
			head->name = m_name; 
			head->price = m_price;
			head->next = NULL; 
			tail = head;
		}
		
		//add at the back if movie list not empty - LINKED LIST
		int addBack(int mov) 
		{ 	
			int yes, check=0;
			movie m[mov];
			
			cout<<"Enter Movie Name: ";
			cin.ignore();
			getline(cin,m_name);
			
			yes = checkList(mov, m_name);
			
			if(yes!=0)
			{
				cout<<"Enter Movie Ticket Price: RM ";
				cin>>m_price;
				
				temp = new movie;
				temp->id = getid();	
				temp->name = m_name;
				temp->price = m_price;
				temp->next = NULL;
				tail->next = temp;
				tail = temp;
				check=1;
			}
			
			return check;
		}
		
		//check the previous movie name has been added or not
		int checkList(int mov, string m_name)
		{
			movie m[mov];
			int yes=1;
			
			temp = head;
			for(int i=0; i<mov; i++)
			{	
				m[i].id = temp->id;
				m[i].name = temp->name;
				m[i].price = temp->price;
				
				int comp = m[i].name.compare(m_name);
				if(comp==0) //if found
				{
					cout<<endl<<"MOVIE HAS ADDED"<<endl<<endl;
					yes=0;
					break;
				}
				else
					temp = temp->next; 
			}
			
			return yes;
		}
		
		//check whether movie list is empty
		int empty()
		{
			if(head==NULL)
				return 1;
			else
				return 0;
		}
		
		//edit movie name and price - LINKED LIST & BINARY SEARCH
		void editMov(int mov)
		{
			if(!empty())
			{
				movie m[mov];
				int editID, find;
				
				temp = head;
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					temp = temp->next; 		
				}
				
				cout<<"Enter Movie ID to Edit: ";
				cin>>editID;
				cout<<endl;
				
				find=searchEditID(m, mov, editID);
				
				if(find!=-1) //if movie id is found
					edit(editID);
				else //movie id not found
					cout<<"----- MOVIE ID NOT FOUND -----"<<endl<<endl<<endl;
			}
			else //no movie data
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl<<endl;
		}
		
		int searchEditID(movie m[], int mov, int editid)
		{
			int first, last, mid;
			
			first=0;
			last=mov-1;
			
			while(first<=last)
			{
				mid=(first+last)/2;
				
				if(editid==m[mid].id)
					return mid;
				else if(editid>m[mid].id)
					first=mid+1;
				else
					last=mid-1;
			}
			
			return -1;
		}
		
		int edit(int editID)
		{
			string editName;
			double editPrice;
			
			if(!empty())
			{
				temp=head;
				while(temp->next!=NULL && temp->id!=editID)
				{
					temp=temp->next;
				}
				if(temp!=NULL) // if movie id is found
				{
					cout<<"Enter New Movie Name: ";
					cin.ignore();
					getline(cin, editName);
					
					cout<<"Enter New Movie Ticket Price : RM ";
					cin>>editPrice;
					cout<<endl;
					
					temp->name=editName; //replace old movie name to new movie name
					temp->price=editPrice; //replace old movie price to new movie price
					
					cout<<"EDITED SUCCESSFULLY"<<endl<<endl<<endl;
				}
				else
				{
					cout<<"FAIL TO EDIT"<<endl<<endl<<endl;
				}
			}
		}
		
		//delete movie - LINKED LIST & lINEAR SEARCH
		int dltMov(int mov)
		{
			int check=0; //to check whether data has been deleted successfully
			if(!empty())
			{
				movie m[mov];
				int dltID, find;
				
				temp = head;
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					temp = temp->next;
				}
				
				cout<<"Enter Movie ID to Delete: ";
				cin>>dltID;
				cout<<endl;
				
				find = searchDltID(m, mov, dltID);
				
				if(find!=-1) //if movie id is found
				{
					dltDltID(dltID);
				    check=1; //movie data is deleted
				    mov--;
				    if(mov==0) //if there is no movie data anymore
				    {
				    	head=NULL;
					}
				}
				else //movie id not found
				{
					cout<<"----- MOVIE ID NOT FOUND -----"<<endl<<endl<<endl; 
					check=2; //movie data not deleted
				}
			}
			else //no movie data
			{
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl<<endl;
				check=2; //movie data not deleted
			}
			return check;
		}
		
		int searchDltID(movie m[], int mov, int dltID)
		{
			for(int i=0; i<mov; i++)
			{
				if(m[i].id==dltID)
					return i;
			}
			
			return -1;
		}
		
		int dltDltID(int dltid)
		{
			if(!empty())
			{
				temp=head;
				tail->next=head; //link tail->next to head first
				while(temp!=NULL && temp->id!=dltid)
				{
					tail=temp; //let tail always infront of temp
					temp=temp->next;
				}
				if(temp!=NULL) //if movie id is found
				{
					head=temp->next; //let head behind of temp
					tail->next=NULL; //let tail->next become NULL
					temp->next=NULL;
					delete temp;
					temp=tail;
					cout<<"DELETED SUCCESSFULLY"<<endl<<endl<<endl;
				}
				else //movie id not found
				{
					cout<<"FAIL TO DELETE"<<endl<<endl<<endl;
				}
			}
		}
		
		//Printing out the linked list without sort - LINKED LIST
		void displayAll() 
		{
			if(!empty())
			{
				temp = head;
				//display all
				cout<<left<<setw(15)<<"MOVIE ID"<<setw(40)<<"MOVIE NAME"<<"MOVIE PRICE"<<endl;
		        while(temp != NULL)
				{	
					cout<<left<<setw(15)<<temp->id<<setw(40)<<temp->name<<temp->price<<endl;
					temp = temp->next; 
				}
					
				cout<<endl<<"----- NO MORE MOVIE LIST -----"<<endl<<endl;	
			}
			else
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl;
		}
		
		//display with name sorting - INSERTION SORT
		void displaySort_Name(int mov)
		{
			if(!empty())
			{
				movie m[mov];
				movie Mtemp;
				
				temp = head;
				
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					temp = temp->next; 		
				}
				
				int j=0;
				for(int i=1; i<mov; i++)
				{
					Mtemp = m[i]; //temp = m[1]
					j=i; //j=1
					while(j>0 && Mtemp.name<m[j-1].name) //j>0 && temp.name<m[0].name
					{
						m[j] = m[j-1]; //m[1] = m[0]
						j--; //j-1=0
						m[j]=Mtemp; //m[0] = temp = m[1]
					}
				}
				
				cout<<left<<setw(15)<<"MOVIE ID"<<setw(40)<<"MOVIE NAME"<<"MOVIE PRICE"<<endl;
				for(int i=0; i<mov; i++)
				{
					cout<<left<<setw(15)<<m[i].id <<setw(40) <<m[i].name <<m[i].price <<endl;
				}
				cout<<endl<<"----- NO MORE MOVIE LIST -----"<<endl<<endl;
			}
			else
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl;
		}
		
		//display with price sorting - INSERTION SORT
		void displaySort_Price(int mov)
		{
			if(!empty())
			{
				movie m[mov];
				movie Mtemp;
				
				temp = head;
				
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					temp = temp->next; 		
				}
				
				int j=0;
				for(int i=1; i<mov; i++)
				{
					Mtemp = m[i]; //temp = m[1]
					j=i; //j=1
					while(j>0 && Mtemp.price<m[j-1].price) //j>0 && temp.name<m[0].name
					{
						m[j] = m[j-1]; //m[1] = m[0]
						j--; //j-1=0
						m[j]=Mtemp; //m[0] = temp = m[1]
					}
				}
				
				cout<<left<<setw(15)<<"MOVIE ID"<<setw(40)<<"MOVIE NAME"<<"MOVIE PRICE"<<endl;
				for(int i=0; i<mov; i++)
				{
					cout<<left<<setw(15)<<m[i].id <<setw(40) <<m[i].name <<m[i].price <<endl;
				}
				cout<<endl<<"----- NO MORE MOVIE LIST -----"<<endl<<endl;
			}
			else
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl;
		}
		
		//search movie ID - BINARY SEARCH
		void searchMov_ID(int mov)
		{
			if(!empty())
			{
				movie m[mov];
				movie Mtemp;
				temp = head;
				
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					temp = temp->next; 		
				}
				
				//arrange id in ascending order before search
				int j=0;
				for(int i=1; i<mov; i++)
				{
					Mtemp = m[i]; //temp = m[1]
					j=i; //j=1
					while(j>0 && Mtemp.id<m[j-1].id) //j>0 && temp.name<m[0].name
					{
						m[j] = m[j-1]; //m[1] = m[0]
						j--; //j-1=0
						m[j]=Mtemp; //m[0] = temp = m[1]
					}
				}
				
				int value; 
				int found;
				cout<<"Enter Movie ID to Search: ";
				cin>>value;
				
				found = IdSearch(m, mov, value);
				cout<<endl;
				if(found==-1)
				{
					cout<<"----- MOVIE ID NOT FOUND -----"<<endl<<endl; 
				}
				else
				{
					cout<<left<<setw(15)<<"MOVIE ID"<<setw(40)<<"MOVIE NAME"<<"MOVIE PRICE"<<endl;
					int i = found;
					cout<<left<<setw(15)<<m[i].id <<setw(40) <<m[i].name <<m[i].price <<endl<<endl;
				}
			}
			else
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl;
		}
		
		int IdSearch(movie m[], int numElems, int value)	// function heading
		{
			int first = 0;				// First element of list
			int last = numElems - 1;	// last element of the list
			int middle;					// variable containing the current middle value of the list
		
			while (first <= last)
			{
				middle = (first + last) / 2;
		
				if (m[middle].id == value)
					return middle;		// if value is in the middle, we have found the searched element
		
				else if (m[middle].id > value)
					last = middle - 1;	// toss out the second remaining half of
					                    // the array and search the first
				else
					first = middle + 1;	// toss out the first remaining half of
										// the array and search the second
			}
		
			return -1;	// indicates that value is not in the array
		}	
		
		//search movie name
		void searchMov_Name(int mov)
		{
			if(!empty())
			{
				movie m[mov];
				temp = head;
				string value;
				 
				cout<<"Enter Movie Name to Search: ";
				cin.ignore();
				getline(cin,value);
				
				int j=0;
				int yes=1;
				for(int i=0; i<mov; i++)
				{	
					m[i].id = temp->id;
					m[i].name = temp->name;
					m[i].price = temp->price;
					
					int comp = m[i].name.compare(value);
					if(comp==0) //if found
					{
						j=i;
						yes=0;
						break;
					}
					else
						temp = temp->next; 		
				}
				
				cout<<endl;
				if (yes==0)
				{
					cout<<left<<setw(15)<<"MOVIE ID"<<setw(40)<<"MOVIE NAME"<<"MOVIE PRICE"<<endl;
					cout<<left<<setw(15)<<m[j].id <<setw(40) <<m[j].name <<m[j].price <<endl<<endl;
				}
				else
				{
					cout<<"----- MOVIE NAME NOT FOUND -----"<<endl<<endl; 
				}
			}
			else
				cout<<"----- NO MOVIE LIST -----"<<endl<<endl;
		}
};

int main()
{
	Movie M;
	int action, condD, condS;
	int mov=0;
	char yn;
	
	cout<<"+++++++++++++++++++++++++++++++++"<<endl;
	cout<<"              MOVIE              "<<endl;
	cout<<"+++++++++++++++++++++++++++++++++"<<endl<<endl;
	
	do
	{
		cout<<"================================="<<endl;
		cout<<"\tAction"<<endl;
		cout<<"1. Add New Movie"<<endl;
		cout<<"2. Edit Movie"<<endl;
		cout<<"3. Delete Movie"<<endl;
		cout<<"4. Display Movie List"<<endl;
		cout<<"5. Search Movie"<<endl;
		cout<<"6. Exit program"<<endl<<endl;
		
		cout<<"Choose Action : ";
		cin>>action;
		cout<<"================================="<<endl;
		cout<<endl;
		
		if(action==1)
		{
			//ADD MOVIE
			int checkM;
			cout<<"-------------------------------"<<endl;
			cout<<"         ADD NEW MOVIE         "<<endl;
			cout<<"-------------------------------"<<endl;
			if(mov==0)
			{
				M.addFirst();
				mov++;
				
				cout<<"Do you want to continue add ? [Y-Yes N-No] :";
				cin>>yn;
				cout<<endl;
				
				while(yn=='y' || yn=='Y')
				{	
					checkM=M.addBack(mov);
					if(checkM==1)
						mov++;
					
					cout<<"Do you want to continue add ? [Y-Yes N-No] :";
					cin>>yn;
					cout<<endl;
				}
				
				cout<<endl;
			}
			else
			{
				do
				{
					checkM=M.addBack(mov);
					if(checkM==1)
						mov++;
					
					cout<<"Do you want to continue add ? [Y-Yes N-No] :";
					cin>>yn;
					cout<<endl;
				}
				while(yn=='y' || yn=='Y');
				
				cout<<endl;
			}
		}
		else if(action==2)
		{
			//EDIT MOVIE
			do
			{
				cout<<"------------------------------"<<endl;
				cout<<"          EDIT MOVIE          "<<endl;
				cout<<"------------------------------"<<endl;
				M.editMov(mov);
				
				cout<<"Do you want to continue edit ? [Y-Yes N-No] :";
				cin>>yn;
				cout<<endl;
			}
			while(yn=='y' || yn=='Y');
			
			cout<<endl;
		}
		else if(action==3)
		{
			//DELETE MOVIE
			do
			{
				int check;
				cout<<"------------------------------"<<endl;
				cout<<"         DELETE MOVIE         "<<endl;
				cout<<"------------------------------"<<endl;
				check=M.dltMov(mov);
				if(mov>0 && check==1)
					mov--;
				
				cout<<"Do you want to continue delete ? [Y-Yes N-No] :";
				cin>>yn;
				cout<<endl;
			}
			while(yn=='y' || yn=='Y');
			
			cout<<endl;
		}
		else if(action==4)
		{
			//DISPLAY MOVIE
			do
			{
				cout<<"-------------------------------"<<endl;
				cout<<"       Display Condition       "<<endl;
				cout<<"-------------------------------"<<endl;
				cout<<"1. Display Without Sort"<<endl;
				cout<<"2. Display With Sort Movie Name"<<endl;
				cout<<"3. Display With Sort Movie Price"<<endl<<endl;
				
				cout<<"Choose Display Condition: ";
				cin>>condD;
				cout<<endl;
				if(condD==1)
					M.displayAll();
				else if(condD==2)
					M.displaySort_Name(mov);
				else if(condD==3)
					M.displaySort_Price(mov);		
				else
					cout<<endl<<"***INVALID INPUT***"<<endl<<endl;
			}
			while(condD!=1 && condD!=2 && condD!=3);
		}
		else if(action==5)
		{
			//SEARCH MOVIE
			do
			{
				cout<<"------------------------------"<<endl;
				cout<<"       Search Condition       "<<endl;
				cout<<"------------------------------"<<endl;
				cout<<"1. Search With Movie ID"<<endl;
				cout<<"2. Search With Movie Name"<<endl<<endl;
				
				cout<<"Choose Search Condition: ";
				cin>>condS;
				cout<<endl;
				if(condS==1)
					M.searchMov_ID(mov);
				else if(condS==2)
					M.searchMov_Name(mov);
				else
					cout<<endl<<"***INVALID INPUT***"<<endl<<endl;
			}
			while(condS!=1 && condS!=2);
		}
		else if(action!=1 && action!=2 && action!=3 && action!=4 && action!=5 && action!=6)
		{
			//INVALID INPUT
			cout<<endl<<"*** INVALID INPUT ***"<<endl<<endl<<endl;
		}
	}
	while(action!=6);
	
	//EXIT PROGRAM
	cout<<endl<<"Thank you for using our program!"<<endl;
	
	return 0;
}
