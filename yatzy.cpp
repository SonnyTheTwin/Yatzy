#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding the random number generator

#define FgC1 "\033[38;5;67m" // "Forground Color 1"
#define FgC2 "\033[38;5;31m" 
#define FgC3 "\033[38;5;181m"
#define FgC4 "\033[38;5;161m"


// fuction to handle game

//function to handle die


class Scoreboard 
{
private:
    bool crossed_out = false;
    int points = 0;
    std::string name;

public:
    Scoreboard()
    {}
    ~Scoreboard(){}

    void setName(std::string name){
        this->name=name;
    }
    std::string getName()
    {
        return name;
    }

    void setBoolCrossedOut()
    {
        crossed_out = true;
    }

    bool getBool()
    {
        return crossed_out;
    }

    void setPoint(int value)
    {
        points = value;
    }

    int getPoint()
    {
        return points;
    }
};


class Player : Scoreboard
{
private:
    std::string name;
    //std::vector<Scoreboard> scoreboard;
public:
    std::vector<Scoreboard> scoreboard;

    std::string getName(){
        return name;
    }

    bool getCrossedOutBool(){
        return getBool();
    }

    void crossedOut(){
        setBoolCrossedOut();
    }

    int getScore(int index)
    {
        return scoreboard[index].getPoint();
    }

    void setScore(int index, int value)
    {
        scoreboard[index].setPoint(value);
    }


    

    Player(std::string name)
    {
        this->name = name;
        for (int i = 0; i < 18; i++)
        {
            Scoreboard insert;
            scoreboard.push_back(insert);
        }
        
    }
    ~Player(){}
};


class Dice
{
private:

    int value;
    
public:
    std::vector<std::string>dice_one;
    std::vector<std::string>dice_two;
    std::vector<std::string>dice_three;
    std::vector<std::string>dice_four;
    std::vector<std::string>dice_five;
    std::vector<std::string>dice_six;
    Dice(/* args */){}
    ~Dice(){}



    int rollDice()
    {
        value = rand() % 6 + 1;
        return value;
    }

    void setValue(int value){
        this->value=value;
    }

    int getValue(){
        return value;
    }

    void initilazeDice()
    {
        dice_one.push_back(" -------- ");
        dice_one.push_back("|        |");
        dice_one.push_back("|   *    |");
        dice_one.push_back("|        |");
        dice_one.push_back(" -------- ");

        dice_two.push_back(" -------- ");
        dice_two.push_back("| *      |");
        dice_two.push_back("|        |");
        dice_two.push_back("|      * |");
        dice_two.push_back(" -------- ");

        dice_three.push_back(" -------- ");
        dice_three.push_back("| *      |");
        dice_three.push_back("|   *    |");
        dice_three.push_back("|     *  |");
        dice_three.push_back(" -------- ");

        dice_four.push_back(" -------- ");
        dice_four.push_back("| *    * |");
        dice_four.push_back("|        |");
        dice_four.push_back("| *    * |");
        dice_four.push_back(" -------- ");

        dice_five.push_back(" -------- ");
        dice_five.push_back("| *    * |");
        dice_five.push_back("|   *    |");
        dice_five.push_back("| *    * |");
        dice_five.push_back(" -------- ");

        dice_six.push_back(" --------");
        dice_six.push_back("| *    * |");
        dice_six.push_back("| *    * |");
        dice_six.push_back("| *    * |");
        dice_six.push_back(" --------");

    }

    
};


std::vector<std::string> scoreBoard()
{
    std::vector<std::string> score_board;
    score_board.push_back(FgC1 "|" FgC2 "      1:or      ");
    score_board.push_back(FgC1 "|" FgC2 "      2:or      ");
    score_board.push_back(FgC1 "|" FgC2 "      3:or      ");
    score_board.push_back(FgC1 "|" FgC2 "      4:or      ");
    score_board.push_back(FgC1 "|" FgC2 "      5:or      ");
    score_board.push_back(FgC1 "|" FgC2 "      6:or      ");
    score_board.push_back(FgC1 "|" FgC3 "     Total:     ");
    score_board.push_back(FgC1 "|" FgC2 "     Bonus      ");
    score_board.push_back(FgC1 "|" FgC2 "     1 pair     ");
    score_board.push_back(FgC1 "|" FgC2 "     2 pair     ");
    score_board.push_back(FgC1 "|" FgC2 "   3 of a kind  ");
    score_board.push_back(FgC1 "|" FgC2 "   4 of a kind  ");
    score_board.push_back(FgC1 "|" FgC2 " Small straight ");
    score_board.push_back(FgC1 "|" FgC2 " Large straight ");
    score_board.push_back(FgC1 "|" FgC2 "   Full house   ");
    score_board.push_back(FgC1 "|" FgC2 "     Chance     ");
    score_board.push_back(FgC1 "|" FgC2 "     Yatzy      ");
    score_board.push_back(FgC1 "|" FgC3 "     Total:     ");
    return score_board;
}

void getScore(int index, std::vector<Player>&players)
{
    std::cout << FgC1 << "|";
    int check = 0;

    for (Player x : players)
    {
        //std::cout << "|";
        
        int score = x.getScore(index);

        if (index == 6) // checks if we are at "Total:" on scoreboard, if so, tally up total
        {
            score = 0;
            for (int i = 0; i < 6; i++)
            {
                score += x.getScore(i);
                if (score >= 63)
                {
                    players[check].setScore(7,50);
                }
            }
            players[check].setScore(6,score);
        }
        if (index == 17) // checks if we are at end "total", if so tally up whole board!
        {
            score = 0;
            for (int y = 6; y < 17; y++)
            {
                score += x.getScore(y);
            }
            players[check].setScore(17,score);
            
        }
        


        check++;


        // Handels padding depending on size of score. 
        if (x.scoreboard[index].getBool() == true)
        {
            std::cout << "  "<< FgC4 << "X"<< FgC1 <<" |";
        }
        else if (score <= 9)
        {
            if (index == 6 || index == 17)
            {
                std::cout << "  " << FgC3 << score << FgC1 << " |";
            }
            else
            {
                std::cout << "  " << FgC2 << score << FgC1 << " |";
            }
        }
        else if (score >= 10 && score <= 99)
        {
            if (index == 6 || index == 17)
            {
                std::cout << " " << FgC3 << score << FgC1 << " |";
            }
            else
            {
                std::cout << " " << FgC2 << score << FgC1 << " |";
            }
        }
        else if (score > 99)
        {
            if (index == 6 || index == 17)
            {
                std::cout << "" << FgC3 << score << FgC1 << " |";
            }
            else
            {
                std::cout << "" << FgC2 << score << FgC1 << " |";
            }
        }
        
        
    }
    
}


void printScoreBoard(std::vector<Player>&players)
{
    std::vector<std::string> score_board;
    score_board = scoreBoard();

    std::cout <<"\n"<< FgC1 << "Row "<< FgC1 << "|"<< FgC2 <<" Option"<<FgC1<<"/"<< FgC3 <<"Player  "<< FgC1"|";

    for (Player x : players)
    {
        std::string name = x.getName();

        std::cout << "  " << FgC3 <<name[0] << FgC1 << " |";
    }

    int y = 1;
    for (int i = 0; i < 18; i++)
    {
    
        if (i <= 9 && y < 10)
        {
            std::cout<< "\n"<< FgC2 << y << FgC1 << ".  " << score_board[i];
            getScore(i,players);
        }
        else
        {
            std::cout<< "\n"<< FgC2 << y << FgC1 << ". " << score_board[i];
            getScore(i,players);
        }
        y++;
    }
}

void print_dice(std::vector<Dice>&dice)
{
    for (int i = 0; i < 5; i++)
    {
        int y = 0;
        for (Dice x : dice)
        {
            y ++;
            if (i==0)
            {
                
                std::cout<< FgC2 <<"   D"<< y <<": " << FgC1;
            }
            else
            {
                std::cout<< FgC1<<"       ";
            }
            
            
            switch (x.getValue())
            {
            case 1:
                std::cout << x.dice_one[i];
                break;
            case 2:
                std::cout << x.dice_two[i];
                break;
            case 3:
                std::cout << x.dice_three[i];
                break;
            case 4:
                std::cout << x.dice_four[i];
                break;
            case 5:
                std::cout << x.dice_five[i];
                break;
            case 6:
                std::cout << x.dice_six[i];
                break;
            
            default:
                break;
            }
        }
        std::cout<<std::endl;
        
    }
    

}

void game_loop_own_dice(std::vector<Player>&players)
{
    int rolled, position, user_input;
    std::vector<Dice>dice;
    for (int i = 0; i < 5; i++)
    {   
        Dice new_dice;
        new_dice.initilazeDice();
        dice.push_back(new_dice);
    }
    

    for (int i = 0; i < players.size(); i++)
    {
        system("clear");
        printScoreBoard(players); // printar hela scoreboarden med allas poäng
        std::cout<< FgC1 <<"\n\nIts " << FgC3 << players[i].getName() << FgC1 <<" turn to roll their dice" << std::endl;

        std::cout<< FgC1 << "Options:\n"
                 << FgC2 << "1"<< FgC1 <<". Add score\n"
                 << FgC2 << "2"<< FgC1 <<". Cross out\n"
                 << "Input: "<<FgC2;
        std::cin>>user_input;
        if (user_input == 1)
        {
            std::cout<< FgC1 <<"Enter what you rolled then enter what row in the scoreboard!\nRolled: "<< FgC2;
            std::cin>>rolled;
            std::cout<< FgC1 <<"Row: "<< FgC2;
            std::cin>>position;
            players[i].setScore(position-1,rolled);
        }
        else if (user_input == 2)
        {
            std::cout<< FgC1 <<"Enter what row you wanna crossout in the scoreboard!\nRow: "<< FgC2;
            std::cin>>position;
            players[i].scoreboard[position-1].setBoolCrossedOut();
            players[i].setScore(position-1,0);
        }


    

    }
}

void game_loop_computer_dice(std::vector<Player>&players)
{
    int rolled, position, user_input;
    std::vector<Dice>dice;
    for (int i = 0; i < 5; i++)
    {   
        Dice new_dice;
        new_dice.initilazeDice();
        dice.push_back(new_dice);
    }
    

    for (int i = 0; i < players.size(); i++)
    {
        system("clear");
        printScoreBoard(players); // printar hela scoreboarden med allas poäng
        std::cout<< FgC1 <<"\n\nIts " << FgC3 <<players[i].getName() << FgC1 <<" turn to roll their dice" << std::endl;


        // FIRST ALL 5 DICE GETS ROLLED AND PRINTED
        for (int i = 0; i < 5; i++)
        {
            int dice_value = dice[i].rollDice();
            dice[i].setValue(dice_value);
        }

        std::cout<< FgC1 <<"\nYour "<< FgC2 <<"1"<< FgC1 <<" roll: " << std::endl;
        print_dice(dice);


        for (int y = 0; y < 2; y++)
        {
            for (int i = 0; i < 5; i++)
            {
                std::cout<< FgC1 <<"Do y wanna save "<< FgC2 <<"D" << i+1 << FgC1 << "?\n"
                    << FgC2 <<"1"<< FgC1 <<". Yes "<< FgC2 << "2"<< FgC1 <<". No  , Input: "<<FgC2;
                std::cin>>user_input;
                if (user_input == 2)
                {
                    dice[i].setValue(dice[i].rollDice());
                }
            }
            system("clear");
            printScoreBoard(players);
            std::cout<< FgC1 <<"\nYour "<< FgC2 << y+2 << FgC1 <<" roll: " << std::endl;
            print_dice(dice);
        }

        std::cout<< FgC1 << "Options:\n"
                 << FgC2 << "1"<< FgC1 <<". Add score\n"
                 << FgC2 <<"2"<< FgC1 <<". Cross out\n"
                 << "Input: " << FgC2;
        std::cin>>user_input;
        if (user_input == 1)
        {
            std::cout<< FgC1 <<"Enter what you rolled then enter what row in the scoreboard!\nRolled: "<< FgC2;
            std::cin>>rolled;
            std::cout<< FgC1 <<"Row: "<<FgC2;
            std::cin>>position;
            players[i].setScore(position-1,rolled);
        }
        else if (user_input == 2)
        {
            std::cout<< FgC1 <<"Enter what row you wanna crossout in the scoreboard!\nRow: "<<FgC2;
            std::cin>>position;
            players[i].scoreboard[position-1].setBoolCrossedOut();
            players[i].setScore(position-1,0);
        }
    }
}


int main()
{
    std::vector<Player>Players;
    int user_input;

    do
    {
        /* code */    
    std::cout << FgC1 << "\nWelcome to Yatzy!\n"
              << FgC2 <<"1"<< FgC1 <<". New Game\n"
              << FgC2 <<"2"<<FgC1<<". Exit Game\n"
              << FgC1 <<"Input: "<<FgC2;
    std::cin>> user_input;
    
    if (user_input == 1)
    {
        std::cout << FgC1 << "How Many players?\n"
                  << "Input: "<<FgC2;
        std::cin >> user_input;
        for (int i = 0; i < user_input; i++)
        {
            std::string name;
            std::cout << FgC1 << "Name of Player " << FgC2 << i+1 << FgC1 << ": "<<FgC2;
            std::cin>>name;
            Players.push_back(Player(name));
        }
        std::cout << FgC1 << "What dice do you wanna use?\n"
                  << FgC2 << "1"<<FgC1<<". My own Dice\n"
                  << FgC2 << "2"<<FgC1<<". Computers Dice\n"
                  << "Input: "<<FgC2;
        std::cin>>user_input;
        if (user_input == 1)
        {
            for (int i = 0; i < 2; i++)
            {
                game_loop_own_dice(Players);
            }
            printScoreBoard(Players);
        }
        else if (user_input == 2)
        {
            for (int i = 0; i < 15; i++)
            {
                game_loop_computer_dice(Players);
            }
        }

        std::cout << FgC1 << "\n\nEnd Result:\n";
        for (Player x : Players)
        {
            std::cout << "Player: " << x.getName() << ", Total score: " << x.getScore(17) << "\n";
        }
        std::cout<<"\n\n<Press Enter to Continue";
        
    }
    else if (user_input == 2)
    {
        /* EXIT PROGRAM */
    }
    else
    {
        std::cout << "Invalid Input!" << std::endl;
    }
    } while (user_input != 2);

    return 0;
}