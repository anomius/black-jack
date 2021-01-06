#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <ctime>
#include <string>


class Card
{
    private:      
    char m_card;         //  'A'   ,'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q','K'
    int m_value;         //1 or 11 , 2  , 3  ,  4,   5 ,  6 ,  7 ,  8 ,  9, 10,  10, 10,  10
    int m_suite;             //0 spades, 1 clubs, 2 hearts, 3 diamonds
    std::string m_nameS; 
    bool m_given;        //Check if it's been wether given or not. works as an index

    int assignValue();   

    public:
    Card(char, int);
    Card(const Card&);//copy 

    int getValue()        const;
    int getSuite()        const;
    std::string getName() const;
    bool getIfGiven()     const;
    char getCard()        const;

    void setGiven(bool x);

    void nameCard();
    //std::string Card::nameCard(char c);
};
    
    
	int Card::assignValue()
	{
		if(m_card == 'A')         return 11;
		else if (m_card == 'T' ||
				m_card == 'J' || 
				m_card == 'Q' || 
				m_card == 'K')   return 10;
		else                      return (m_card - '0');
	}

	Card::Card(char cardV, int suite)
	{
		m_card = cardV;
		m_value = assignValue();
		m_suite = suite;
		m_given = false;
	}

	Card::Card(const Card& card)
	{
		m_card = card.getCard()     ;
		m_value = card.getValue();
		m_suite = card.getSuite()   ; 
		m_nameS = card.getName()    ;
		m_given = card.getIfGiven() ; 
	}

	int Card::getValue() const
	{ return m_value; }

	int Card::getSuite() const
	{ return m_suite; }

	std::string Card::getName() const
	{ return m_nameS; }

	bool Card::getIfGiven() const
	{ return m_given; }

	char Card::getCard() const
	{ return m_card; }

	void Card::setGiven(bool x)
	{ m_given = x; }

	void Card::nameCard()
	{
		switch(m_suite)
		{
			case 0: m_nameS = "♠spades"  ; break;
			case 1: m_nameS = "♣clubs"   ; break;
			case 2: m_nameS = "♥hearts"  ; break;
			case 3: m_nameS = "♦diamonds";
		}
		if(m_card == 'A')       std::cout << "Ace"  ;
		else if (m_card == 'K') std::cout << "King";
		else if (m_card == 'J') std::cout << "Jack";
		else if (m_card == 'Q') std::cout << "Queen";
		else                    std::cout << m_value;

		std::cout << " of " << m_nameS << std::endl;
	}

  //   std::string Card::nameCard(char c)
	// {
  //       std::string temp,l;
	// 	switch(m_suite)
	// 	{
	// 		case 0: m_nameS = "spades"  ; break;
	// 		case 1: m_nameS = "clubs"   ; break;
	// 		case 2: m_nameS = "hearts"  ; break;
	// 		case 3: m_nameS = "diamonds";
	// 	}
	// 	if(m_card == 'A')       temp="Ace"  ;
	// 	else if (m_card == 'K') temp="King";
	// 	else if (m_card == 'J') temp="Joker";
	// 	else if (m_card == 'Q') temp="Queen";
	// 	else                    temp=std::to_string(m_value);

	// 	temp= temp+ " of " + m_nameS +"\n";
  //       return temp;
	// }


class Deck
{
    private:
    std::vector<Card*> m_deck;

    public:    
    Deck();

    void fillDeck();
    void shuffle() ;
    Card giveCard();
	  void f_save();
	  void print_deck();
    //void print_deck(std::ofstream &file); //polymorphism 
	
};

	Deck::Deck()
	{ 
		//Initialize the deck: 
		fillDeck();
		shuffle();
		//f_save();
	}

	void Deck::fillDeck()
	{
		for(int i = 1; i <= 13; ++i)
		{
			char c;
			switch(i){
				case 1 :  c = 'A'; break;
				case 2 :  c = '2'; break;
				case 3 :  c = '3'; break;
				case 4 :  c = '4'; break;
				case 5 :  c = '5'; break;
				case 6 :  c = '6'; break;
				case 7 :  c = '7'; break;
				case 8 :  c = '8'; break;
				case 9 :  c = '9'; break;
				case 10:  c = 'T'; break;
				case 11:  c = 'J'; break;
				case 12:  c = 'Q'; break;
				case 13:  c = 'K'; 
			}
			for(int n = 0; n <= 3; ++n)
			{
				m_deck.push_back(new Card(c,n));
			}
		}
	}

	void Deck::shuffle()
	{
		std::random_shuffle(m_deck.begin(), m_deck.end());
	}

	Card Deck::giveCard()
	{
		for(int i = 0; i < m_deck.size(); ++i)
		{
			if(!m_deck[i]->getIfGiven())
			{
				m_deck[i]->setGiven(1);
				return (*m_deck[i]);
			}
		}
	}
	
	void Deck::f_save(){
		std::fstream f;// porymophism on file system
    	f.open("deck.bi", std::ios::binary);
    	for(int i = 0; i < m_deck.size(); ++i)
		{
            m_deck[i]->nameCard();
		}
    	f.close();
	}

	void Deck::print_deck(){
        
		for(int i = 0; i < m_deck.size(); ++i)
		{
            m_deck[i]->nameCard();
		}
	}




class Hand
{

    private:
    std::vector<Card> m_hand;

    public:

    void init(Card, Card) ;
    void display()        ;
    virtual void displayAsDealer();
    void addCard(Card)    ;

    int getNumOfCards();
    int getTotalVal()  ;
};

void Hand::init(Card card1, Card card2)
{
    m_hand.push_back(card1);
    m_hand.push_back(card2);
}


// work on UI of the code 
void Hand::display()
{   
    int player=0;
    for(std::vector<Card>::iterator iter = m_hand.begin();
    iter != m_hand.end(); (++iter))
    {
        iter->nameCard();
        player+=iter->getValue(); // work on UI of the code 
    }
    std::cout<<"your total is "<<player<<"\n\n\n\n\n";
}

 void Hand::displayAsDealer()
{   int dealer=0;
    m_hand[0].nameCard();
    dealer+=m_hand[0].getValue();
    std::cout<<"Dealer total is "<<dealer<<"\n\n\n\n\n";
}

void Hand::addCard(Card card)
{
    std::cout << "\nTook out: ";
    
    card.nameCard();
    m_hand.push_back(card); 
}

int Hand::getTotalVal()
{
    int sum = 0;
    for(std::vector<Card>::iterator iter = m_hand.begin();
    iter != m_hand.end(); (++iter))
    {
        sum += iter->getValue();
    }
    return sum;
}

int Hand::getNumOfCards()
{
    return m_hand.size();
}

class Player
{
    protected:
    Deck m_deck;
    Hand m_mano;
    bool m_canGetCards;
    int score;

    public:
    Player(Deck deck);
    void plant();
    void anotherCard();
    void seeCards();

    int getScore() const;

    bool perdio();
    bool ganoFR();
 };

 Player::Player(Deck deck)
 {
    m_canGetCards = 1;
    m_deck = deck;
    m_mano.init(deck.giveCard(), deck.giveCard());
 }

 void Player::plant()
 {
    m_canGetCards = 0;
    score = m_mano.getTotalVal();
 }

 void Player::anotherCard()
 {
    if(m_canGetCards) m_mano.addCard(m_deck.giveCard());
    else std::cout << "You cannot get more cards" << std::endl;
 }

 bool Player::perdio()
 {
    if(m_mano.getTotalVal() > 21)
    {
        std::cout << "You went over 21" << std::endl;
        throw 500;
        return true;
    }
    return false;
 }

 bool Player::ganoFR()
 {
    return (m_mano.getTotalVal() == 21 && m_mano.getNumOfCards() == 2);
 }

 void Player::seeCards()
 {
    std::cout << "Your cards: \n";
    m_mano.display();
    std::cout << "-------------------------------------------\n";
 }

 int Player::getScore() const
 { return score; }

 class Dealer : public Player  //The dealer IS A player
 {
    public:
    using Player::Player;

    void seeCard()   ; 
    void game(Player);
    
 };

 void Dealer::seeCard()
 {
    std::cout << "Dealer's card: \n";
    m_mano.displayAsDealer();
    std::cout << "-------------------------------------------\n";
    std::cout << std::endl;

 }

 void Dealer::game(Player play)
 {
    while(m_mano.getTotalVal() <= 21)
    {
        std::cout << "Cards: ";
        m_mano.display();
        std::cout << std::endl;
        if(m_mano.getTotalVal() > play.getScore() && m_mano.getTotalVal() <= 21)
        {
            std::cout << "The dealer won because his score was greater than yours and it didn't exceed 21 in any form." << std::endl;
            throw 500;
            return;
        }
        if(m_mano.getTotalVal() == play.getScore())
        {
            std::cout << "A tie! " << std::endl;
            throw 501;
            return;
            
        }
        anotherCard();
    }
    if(m_mano.getTotalVal() > 21)
    {
        std::cout << "The dealer went over 21, he lost";
        throw 502;
        return;
    }
 }

class Bank{
  private:
  std::string name;
  int bal;
  int bet;
  //int amount;
  public:
  Bank(std::string name1);
  void create_bet(int bet1);
  void set_bank(int bal1);
  void calculate(int win);
  void save();
  int get_bal();
  void get_bet();

};

    Bank::Bank(std::string name1){
        name=name1;
    }
    void Bank::set_bank(int bal1){
        bal=bal1;
    }
    void Bank::create_bet(int bet1){
        if(bal>0){
            bet=bet1;
             std::cout<<bet;
        }else{
            throw 404;
        }
    }
    void Bank::calculate(int win){
            std::cout<<bal;
            bal=bal+(bet*win);
            std::cout<<"/n"<<bal;
    }
    void Bank::save(){
        std::ofstream f;
        std::string fi=this->name+".bank";
        f.open(fi);
        f<< this->name <<"\n"<<this->bal;
        f.close();
    }
    int Bank::get_bal(){
      return bal; 
    }
    void Bank::get_bet(){
        std::cout<<bet;
    }

void calculate(Bank b,int win){
    
    b.calculate(win);
}

 void start(){
    std::cout << "Welcome to \n------------------------------------- Casino Royale -------------------------------------\n"<< std::endl;
    std::cout << "lets Start of by Introducing Ourself's" << std::endl;
    std::cout << "\n\n";
    std::cout << "Have Fun!! \n\n" << std::endl;
}

std::string intro(){
    std::string name;
    std::cout << "Hey I am Decim your Dealer \n"<< std::endl;
    std::cout << "What's Your Name" << std::endl;
    std::cin >> name;
    std::cout << "you look like a familiar face 😒 \n you just got $50000 on house\n"<< std::endl;
    std::cout << "if you ever want to quit just press Q/q " << std::endl;

    return name;   
}
 
void bet(Bank b){
    int bet;
    std::cout<<"\nHow much do you wanna bet on the next Match ";
    std::cin >>bet;
    if(bet>b.get_bal()){
      throw 404;
    }
    b.create_bet(bet);
    
}

void control(){
    std::cout<<"Controls \n---------------------------------------------------\nEnter\n1 for hit \n2 for show \n";
}
void bal(Bank b){
    std::cout<<"your Balance amount is \n"<<b.get_bal()<<"\n------------------------------------------------\n";

}



int main()
{
    srand(time(0));//seed for random function

    start();

    Deck deck; 
    
    char x;
    std::string name=intro();
    Bank pp(name);
    pp.set_bank(50000);

    bool bbreak = 0;
    bool t = 1;

    while(t)
    {
        try{
            bet(pp);
            Player yo(deck);
            Dealer casino(deck);
            yo.seeCards();
            casino.seeCard();
            control();
          
            if(yo.ganoFR())//Game on flag Return
            {
                std::cout << "You won! " << std::endl;
                calculate(pp,1);
                bal(pp);
            }
            else if (casino.ganoFR())
            {
                std::cout << "The dealer won!" << std::endl;
                calculate(pp,-1);
                bal(pp);
            }
            else
            {
                  while(!yo.perdio())
                  {
                      std::cout << "What do you want to do: ";
                      std::cin >> x;
                      if(x == '1')
                      {
                          yo.anotherCard();
                      }
                      else if(x == '2')
                      {
                          yo.plant();
                          casino.game(yo);
                          break;
                      }else if(x == 'Q'||x == 'q'){
                          throw 8; 
                      }else{
                          throw 101;
                      }
                      yo.seeCards();
                      casino.seeCard();
                  }
            }
              
        }
        catch( int i ) {
            // catch block
            if(i==500){
              calculate(pp,-1);
              bal(pp);
            }else if(i==501){
              calculate(pp,0);
              bal(pp);
            }else if(i==502){
              calculate(pp,1);
              bal(pp);
            }else if(i==8){
              break;
            }else if(i==101){
              std::cout<<"enter a valid input\n"; 
            }
            else if(i==404){
              std::cout<<"There is not enough Balance left in your account\n"; 
            }

          }
          
               
    }
    pp.save();
    return 0;
}