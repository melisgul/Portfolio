/*Melis Gülenay
  150120304*/


#include<iostream>
#include<fstream>
#include<string>

using namespace std ;

#define DECK_SIZE 10 

class Base{
private:	
	friend class HetList ;
	Base* next ;
	int value ;	// Card's status after playing 2-Win 1-Tie 0-Lose

protected:
	char type ; // D-DarkRed R-Red G-Green B-Blue
public :
	
	virtual void compare(char) = 0 ;	//	Virtual compare function is used to compare cards by their types 
	void setValue(int value){this->value = value ;}
	const int getValue() const{return value ;}
	const char getType() const{return type ;}
};


class HetList{

	Base* head ;  
	Base* traverse ;			//	Used to scan HetList
	int Wins ;					//	How many wins for a player
	int Ties ;					//	How many ties for a player. 

public:
	HetList();
	void insert(Base*) ; 
	Base* pop() ;				//	Pops head and moves traverse pointer forward 
	void headBack();			//	Is used to set traverse pointer to head pointer
	void setWinandTies();		//	Counting Wins and Ties in a player's hand
	const int getWins() const{return Wins;}
	const int getTies() const{return Ties;}
	~HetList() ;
};

class Red : public Base{

public:
	
	Red(){type = 'R' ;}
	/*
	Compare takes the opponent and define the status of current card.
	0-Lose
	1-Tie
	2-Win
	*/
	void compare(char opponent){

		switch(opponent){
		case 'R':
			setValue(1) ;
			break;
		case 'D':
			setValue(0) ;
			break;
		case 'B':
			setValue(0) ;
			break;
		case 'G':
			setValue(2) ;
			break;
		default:
			break ; 
		}
	}

};

class Blue : public Base{

public:
	
	Blue(){type = 'B' ; }
	void compare(char opponent){

		switch(opponent){
		case 'R':
			setValue(2) ;
			break;
		case 'D':
			setValue(0) ;
			break;
		case 'B':
			setValue(1) ;
			break;
		case 'G':
			setValue (0) ;
			break;	
		default:
			break ; 
		}
	}

};

class Green : public Base{

public:

	Green(){type = 'G' ;}
	void compare(char opponent){

		switch(opponent){
		case 'R':
			setValue(0) ;
			break;
		case 'D':
			setValue(2) ;
			break;
		case 'B':
			setValue (2) ;
			break;
		case 'G':
			setValue (1) ;
			break;
		default:
			break ; 
		}
	}

};

class DarkRed : public Red{

public:

	DarkRed(){ type = 'D' ; }
	void compare(char opponent){

		switch(opponent){
		case 'R':
			setValue (2) ;
			break;
		case 'D':
			setValue (1) ;
			break;
		case 'B':
			setValue (2) ;
			break;
		case 'G':
			setValue (0) ;
			break;
		default:
			break ; 
		}
	}


};


HetList :: HetList(){
	head = 0 ;
	traverse = 0 ;
	Wins = 0 ;
	Ties = 0 ;

}

void HetList :: insert (Base* t) {

	if(head)        
		t->next=head;
	else     			
		t->next=0;  
	head=t;

	//	After each insertion traverse is set to head
	traverse = head ; 
}

/*
-	If first element is going to be returned
-	If last element is going to be returned
-	Else
*/

Base* HetList :: pop () {
	
	Base* temp ;
	if(traverse == head){
		traverse = traverse->next;
		return head ;
	
	}

	else if(!traverse->next)
		return traverse ;
	
	else if(traverse){
		temp = traverse ;
		traverse = traverse->next ;
		return temp ;
	}

}
/*
headBack is used to modify traverse pointer after calling other functions changing traverse's order.
*/
void HetList :: headBack(){
	traverse = head;
}
/*
Counts win and tie values ;
*/
void HetList :: setWinandTies(){
	
	while(traverse){
		if(!traverse->next){
			if(traverse->getValue()==2)
				Wins++ ;
			else if(traverse->getValue() == 1)
				Ties++ ;
		
			return;
		}			
		else{
			if(traverse->getValue()==2)
				Wins++ ;
			else if(traverse->getValue() == 1)
				Ties++ ;

			traverse = traverse -> next ;
		}
	}
}


HetList::~HetList(){
	delete head;
}

/*
Reading deck from file
*/
void hetListsCreation(HetList& moves_1, HetList& moves_2){
 
	Base* card ;
	ifstream myFile ;
	myFile.open("deck.txt");
	string mov_1, mov_2 ;
	 
	getline(myFile,mov_1);
	getline(myFile,mov_2);


	for(int i = 0 ; i < mov_1.size() ; i++){
		
		switch(mov_1[i]){
		case 'R' :
			card = new Red();
			moves_1.insert(card);
			break;
		case 'B' :
			card = new Blue();
			moves_1.insert(card);
			break;
		case 'G' :
			card = new Green();
			moves_1.insert(card);
			break;
		case 'D' :
			card = new DarkRed();
			moves_1.insert(card);
			break;
		default:
			break;
		}
	}

	for(int i = 0 ; i < mov_2.size() ; i++){
		
		switch(mov_2[i]){
		case 'R' :
			card = new Red();
			moves_2.insert(card);
			break;
		case 'B' :
			card = new Blue();
			moves_2.insert(card);
			break;
		case 'G' :
			card = new Green();
			moves_2.insert(card);
			break;
		case 'D' :
			card = new DarkRed();
			moves_2.insert(card);
			break;
		default:
			break;
		}
	}

	myFile.close();
}

/*
Each player compares his/her hand to other player's hand
*/

void game(HetList& list1, HetList& list2){


	for (int i = 0 ; i < DECK_SIZE ; i++ )
		list1.pop()->compare(list2.pop()->getType());

	list1.headBack();
	list2.headBack();
		
	for (int i = 0 ; i < DECK_SIZE ; i++ )
		list2.pop()->compare(list1.pop()->getType());

	list1.headBack();
	list2.headBack();

	list1.setWinandTies();
	list2.setWinandTies();

	list1.headBack();
	list2.headBack();
}

/*
Passing lists which hold all required information, passing win,lose,tie,deck array,win-lose array instead
Function prints all asked info
*/
void DisplayResults(HetList& list1,HetList& list2){

	cout<<"Player 1 : " ;
	for (int i = 0 ; i < DECK_SIZE ; i++ )
		cout<<list1.pop()->getType()<<" " ;
	cout<<endl;	
	cout<<"Player 2 : " ;
	for (int i = 0 ; i < DECK_SIZE ; i++ )
		cout<<list2.pop()->getType()<<" " ;
	cout<<endl;
	list1.headBack();
	list2.headBack();

	cout<<"Score 1 : " ;
	for (int i = 0 ; i < DECK_SIZE ; i++ )
		cout<<list1.pop()->getValue()<<" " ;
	cout<<endl;
	cout<<"Score 2 : " ;
	for (int i = 0 ; i < DECK_SIZE ; i++ )
		cout<<list2.pop()->getValue()<<" " ;
	cout<<endl;
	list1.headBack();
	list2.headBack();

	
	cout<<"Total Score 1: "<<"Loses : "<<DECK_SIZE-(list1.getTies() + list1.getWins()) << "    Ties : "<<list1.getTies()<<"    Wins : " <<list1.getWins() <<endl;
	cout<<"Total Score 2: "<<"Loses : "<<DECK_SIZE-(list2.getTies() + list2.getWins()) << "    Ties : "<<list2.getTies()<<"    Wins : " <<list2.getWins() <<endl;
	cout<<"Winner: ";
	
	if(list1.getWins()>list2.getWins())
		cout<<"Player 1 Wins"<<endl;
	else if (list1.getWins() == list2.getWins())
		cout<<"Ties"<<endl;
	else
		cout<<"Player 2 Wins"<<endl;

}
		
int main(){

	HetList list1 ;
	HetList list2 ;
	hetListsCreation(list1,list2);
	game(list1,list2);
	DisplayResults(list1,list2);
	return 0 ; 
}
