/* 
 * Solution: Project #1 - Yahtzee
 * Version 1.1
 * File:   main.cpp
 * Author: Jay Blakeborough
 * Created on July 31, 2023
 * Purpose: Play the game of Yahtzee (Lite edition)
 *      This edition will only have eight rounds instead of thirteen as is normal
 *      for the full game. The small and large straights, full house, and three
 *      and four of a kind will be eliminated.
 */

/*
 * VERSION HISTORY
 * 
 * v0.1 - Build and test menu system
 * v0.2 - Build in random number generator w/ random seed based on time of day
 *          and also build dice roll logic.
 * v0.3 - Build logic for user to select dice to keep for the role and flow logic to
 *          proceed to the end of the round.
 * v0.4 - Build scoring logic:  allow player to select what scoring option that
 *          they would like to use as long as it applies and it hasn't been used
 *          to score previously.
 * v0,5 - Build logic for displaying score card
 * v0.6 - Build in logic to save game and to load saved game
 * v1.0 - Start of Project 2 build - replace individual variables to arrays
 *          examples:(dice, keeper flags, markers), move dice roll to a function
 * v1.1 - use arrays for the scoring system and move various logic into functions
 *          where appropriate
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>  //to get randmon number generstor
#include <ctime>  // use system time for seed
#include <fstream> //library to stream I/O files
using namespace std;

//User Libraries

//Global Constants


//Function Prototypes
void rollDie(short int[], bool[], char); //arguments: dice array, keeper array, array size
bool scr1to6(short int[], bool[], short int[], char, char, string[]); //arguments: scoring array, score flag array, dice array, 

//Execution Begins Here
int main(int argc, char** argv)
{
    //Local constants
    const char ROUNDS = 8; //ROUNDS will be 8 for lite version. change to 13 once logic is built for full version 
    const char DICE = 5; //number of die
    const unsigned RSEED = time(0);  //use system time for seed
    
    //seed the random number generator
    srand(RSEED);
    
    //Declare Variables/Data Types
    
    short int die[DICE];
    bool keep[DICE];
    char mark[DICE];
    bool sFlg[ROUNDS];
    short int score[ROUNDS];
    char mChoice;  //input the Main Menu choice
    char pChoice;  //input the Play Option choice
    short int choice; //cin input variable - will cast to mChoice
    short int round;  // round counter x of 8
    short int roll; // role counter x of 3
    string pName = "";
    string dName[6] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes"};
    
    //Initialize Variables
    mChoice = '0';
    pChoice = '0';
    
    
    //Process Inputs
    
    cout << "\t\tPlay the Game of Yahtzee" << endl << endl;
    
    do //repeat main menu until Exit(9) is chosen
    {
        cout << "Choose one of the following..." << endl;
        cout << "\t1. New Game" << endl
             << "\t2. Continue Saved Game" << endl
             << "\t9. Exit" << endl;
        
        cin >> choice; //input the menu choice
        
        mChoice = static_cast<char>(choice) + 48; //casting for credit
    
        switch (mChoice)
        {
            case '1': //Play a new game
            {
                cout << endl << "New Game" << endl << endl;
                
                cout << "Enter you name: "; //Get the Player's name
                cin >> pName;
                cout << endl << endl;
                
                //reset games variables for new game
                for (int i=0; i < DICE; i++)
                    die[i]=0, keep[i]=false, mark[i]=' ';
                
                for (int i=0; i < ROUNDS; i++)
                    score[i]=0, sFlg[i] = false;
                
                round = 1;
                roll = 1;
                
                do //loop until 9 is selected to return to Main Menu
                {
                    cout << endl << "Player: " << pName << "\tRound: " << round
                         << "\tRoll: " << roll << endl << endl; //player name, round and roll
                    
                    cout << "Choose one of the following play options..." << endl;
                    cout << "\t1. Roll the Dice" << endl
                         << "\t2. Select Dice to Keep" << endl
                         << "\t3. End Round and Select Scoring Choice" << endl //if you want to end round before third roll
                         << "\t4. View Score Card" << endl
                         << "\t5. Save Game and Exit to Main Menu" << endl
                         << "\t9. Exit to Main Menu" << endl;
                    
                    cin >> pChoice;
                    
                    switch (pChoice) //case will execute based on option selected
                    {
                        case '1': //Game Play - Roll the dice
                        {
                            rollDie(die, keep, DICE); //execute the roll die function
                            //Display the dice roll and any previously marked die that were kept
                            cout << endl << "Dice roll...";
                            cout << "\t\tDie #1\tDie #2\tDie #3\tDie #4\tDie #5" << endl;
                            cout << "\t\t\t------\t------\t------\t------\t------" << endl;
                            
                            cout << "\t\t";
                            for (int i=0; i < DICE; i++)
                                cout << "\t  " << die[i];
                            cout << endl;
                            
                            cout << "Marked to keep = X";
                                for (int i=0; i < DICE; i++)
                                    cout << "\t  " << mark[i];
                            cout << endl;
                                       
                            roll++; //increment the dice roll by 1
                                    //roll variable will be 1 ahead of actual roll
                                    // at this point in order to allow for pass through
                                    // to next case
                                
                            //pass through to next case
                        }
                        
                        case '2': //Game Play - Select die to keep from roll
                        {
                            if (roll <= 3) //only allow selections on first two roles
                                           //third roll will automatically flow to scoring
                            {
                            char ans; // local variable for answer to question
                            cout << endl << "Select the Dice to keep..." << endl;
                            cout << "Do you wish to keep or re-roll any of these die? (y/n) " << endl;
                            cin >> ans;
                      
                                while (ans != 'N' && ans != 'n') 
                                {
                                    for (int i=0; i < DICE; i++)
                                    {
                                        if (!keep[i]) //If not kept
                                        {
                                            char dAns;
                                            cout << "Keep Die #" << i+1 << "? (y/n) " << endl;
                                            cin >> dAns;
                                            if (dAns == 'Y' || dAns == 'y')
                                                mark[i] = 'X', keep[i] = true;
                                        }
                                        else //else it's marked as kept, re-roll
                                        {
                                            char dAns;
                                            cout << "Do you wish to re-roll Die #" << i+1 << "? (y/n) " << endl;
                                            cin >> dAns;
                                            if (dAns == 'Y' || dAns == 'y')
                                                mark[i] = ' ', keep[i] = false;
                                        }
                                    }

                                    cout << endl << "Selected Die...";
                                    cout << "\t\tDie #1\tDie #2\tDie #3\tDie #4\tDie #5" << endl;
                                    cout << "\t\t\t------\t------\t------\t------\t------" << endl;

                                    cout << "\t\t";
                                    for (int i=0; i < DICE; i++)
                                        cout << "\t  " << die[i];
                                    cout << endl;
                            
                                    cout << "Marked to keep = X";
                                        for (int i=0; i < DICE; i++)
                                        cout << "\t  " << mark[i];
                                    cout << endl;
                                    
                                    cout << endl << "Do you want to make any changes? (y/n) " << endl;
                                    cin >> ans;
                                }//end while
                            }//end if
                            
                            if (roll < 4) //if this was roll three, flow through to
                                          //case 3 and score the round
                                break;
                        }
                        
                        case '3': //Game Play - Score the Round
                        {
                            short int scrOpt = 0; //Input the scoring option
                            bool scrFlg = false;  //flag to assure score for round was obtained
                            
                            do //execute routine until score obtained
                            {
                                //scoring option menu
                                cout << endl << "Select Scoring Choice..." << endl << endl;
                                cout << "1. Score Ones: " << endl;
                                cout << "2. Score Twos: " << endl;
                                cout << "3. Score Threes: " << endl;
                                cout << "4. Score Fours: " << endl;
                                cout << "5. Score Fives: " << endl;
                                cout << "6. Score Sixes: " << endl;
                                cout << "7. Score a Yahtzee: " << endl;
                                cout << "8. Score a Chance: " << endl;
                            
                                cin >> scrOpt;
                                
                                switch(scrOpt)
                                { 
                                    case 1:
                                    case 2:
                                    case 3:
                                    case 4:
                                    case 5:
                                    case 6: // this function can be used for any score options 1-6
                                    {
                                        scrFlg = scr1to6(score, sFlg, die, DICE, scrOpt, dName);
                                        break;
                                    }// end case 1
                                    
                                    case 7: //Yahtzee!!
                                    {
                                        if (!sFlg[6]) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            string congrat = "";
                                            if (die[0] == die[1] && die[0] == die[2] && die[0] == die[3] && die[0] == die[4]) //it is a Yahtzee
                                            {
                                                score[6] = 50; //score 50
                                                congrat = "Congratulations on the Yahtzee!!";
                                            }
                                            else //or score 0
                                                score[6] = 0;
                                            
                                            cout << endl << congrat << " You will score "
                                                 << score[6] << " points for the Yahtzee" << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sFlg[6] = true;
                                                scrFlg = true;
                                                break;
                                            }                                        
                                            else
                                            {
                                                score[6] = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Yahtzee has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    }//end case 7
                                    
                                    case 8: //Chance!!
                                    {
                                        if (!sFlg[7]) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            score[7] = die[0] + die[1] + die[2] + die[3] + die[4]; //add all die
                                                                                        
                                            cout << endl << "You will score "
                                                 << score[7] << " points for the Chance" << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sFlg[7] = true;
                                                scrFlg = true;
                                                break;
                                            }                                        
                                            else
                                            {
                                                score[7] = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Chance has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    }//end case 8
                                    
                                    default:
                                    {
                                        cout << endl << "Error: Incorrect Scoring Choice selected.\n  Please Re-enter";
                                        break;
                                    }
                               }
                            } //End do
                            while (!scrFlg);
                            
                            round++; //increase the round
                            
                            //reset round variables
                            roll = 1;
                            for (int i=0; i < DICE; i++)
                                die[i] = 0, keep[i] = false, mark[i] = ' '; // reset die markers
    
                            if (round <= ROUNDS) //if rounds > max rounds, flow through to score card
                                break; //else break
                        }
                        
                        case '4': //Display the Score Card
                        {
                            short int uttl; //upper section total
                            short int lttl; //Lower section total
                            short int bonus = 0; //bonus if upper section >= 63
                            short int gttl; //grand total
                            
                            cout << endl << "\t\tScore Card:" << endl << endl;
                            cout << "UPPER SECTION" << endl;
                            cout << "Ones        = " << setw(3) << right << score[0] << endl;
                            cout << "Twos        = " << setw(3) << right << score[1] << endl;
                            cout << "Threes      = " << setw(3) << right << score[2] << endl;
                            cout << "Fours       = " << setw(3) << right << score[3] << endl;
                            cout << "Fives       = " << setw(3) << right << score[4] << endl;
                            cout << "Sixes       = " << setw(3) << right << score[5] << endl;
                            uttl = score[0]+score[1]+score[2]+score[3]+score[4]+score[5];
                            if (uttl >= 63)
                                bonus = 35;
                            cout << "TOTAL       = " << setw(3) << right << uttl << endl;
                            cout << "Bonus       = " << setw(3) << right << bonus << endl << endl;
                            cout << "LOWER SECTION" << endl;
                            cout << "Yahtzee     = " << setw(3) << right << score[6] << endl;
                            cout << "Chance      = " << setw(3) << right << score[7] << endl;
                            lttl = score[6] + score[7];
                            cout << "TOTAL       = " << setw(3) << right << lttl << endl;
                            gttl = uttl + bonus + lttl;
                            cout << "GRAND TOTAL = " << setw(3) << right << gttl << endl << endl;
                            
                            break;
                        }
                        
                        case '5': //save the game and exit
                        {
                            char ans; //input for answer
                            cout << endl << "Save Game and Exit..." << endl << endl;
                            cout << "Do you wish to save the game and exit to the"
                                    " Main Menu? (y/n) " << endl;
                            cin >> ans;
                            
                            if (ans == 'Y' || ans == 'y')
                            {
                                ofstream oFile; //declare output file object
                                oFile.open("Yahtzee.sav");
                                oFile << pName << endl; //write player name
                                oFile << round << endl; //write round
                                oFile << roll << endl; //write roll
                                oFile << score[0] << "\t" << score[1] << "\t" << score[2] << "\t"
                                      << score[3] << "\t" << score[4] << "\t" << score[5] << "\t"
                                      << score[6] << "\t" << score[7] << endl; //write scores
                                oFile << sFlg[0] << "\t" << sFlg[1] << "\t" << sFlg[2] << "\t"
                                      << sFlg[3] << "\t" << sFlg[4] << "\t" << sFlg[5] << "\t"
                                      << sFlg[6] << "\t" << sFlg[7] << endl; //write score flags
                                oFile << die[0] << "\t" << die[1] << "\t" << die[2] << "\t"
                                      << die[3] << "\t" << die[4] << endl; //write scores
                                oFile << keep[0] << "\t" << keep[1] << "\t" << keep[2] << "\t"
                                      << keep[3] << "\t" << keep[4] << endl; //write die keeps
                                oFile << mark[0] << "\t" << mark[1] << "\t" << mark[2] << "\t"
                                      << mark[3] << "\t" << mark[4] << endl; //write die markers
                                oFile.close();
                            }
                            else
                            {
                                pChoice = '0'; //set player choice to0 so it doesn't exit
                                break;
                            }
                        }
                        
                        case '9': //Exit to Main Menu
                        {
                            break;
                        }
                        
                        default:
                        {
                            cout << endl << "Error: Incorrect Play Choice selected\n.  Please Re-enter";
                            break;
                        }
                    }
                }
                while((pChoice != '9') && (pChoice != '5'));
                break;
            }
        
            case '2': //Play a saved game
            {
                cout << endl << "Continue Saved Game" << endl;
                break;
            }
            
            case '9':
            {
                cout << endl << "Good Bye, I hope you had fun!" << endl;
                break;
            }
            
            default:
            {
                cout << endl << "Error: Please enter a valid menu choice..." << endl;
                break;
            }
        }
    }
    while (mChoice != '9');
    
    //Display
    
    //Exit Routine
    return 0;
}

void rollDie(short int p1[], bool p2[], char p3)
{
    //arguments: p1[]=dice array; p2[[]=keeper array; p3=SIZE of dice array
    
    //roll only the die that have not been marked to keep.
    //on first roll there are no kept die, but roll two and three will.
    //each die will have it's own roll - could use for-loop here if
    // arrays could be used
    
    for (int i=0; i < p3; i++)
    {
        if (!p2[i])
            p1[i] = rand() % 6 + 1;//roll of the un-kept die
    }
}

bool scr1to6(short int p1[], bool p2[], short int p3[], char p4, char p5, string p6[])
{
    //arguments: p1[]=scoring array; p2[]=score flag array; p3[]=dice array
    //           p4=SIZE of dice array; p5=passed scoring option; p6[]=dice names array(Ones, Twos, etc)
    //scoring flag array is used to determine if that scoring option has already been used
    //if so, logic will flow to else statement, displaying a notification
    if (!p2[p5-1]) //if scoring flag is not on, score to this category...
    {
        char ans;

        //add the score for all...
        for (int i=0; i < p4; i++)
            p1[p5-1] += p3[i] == p5 ? p5 : 0;

        cout << endl << "You will score " << p1[p5-1] << " points for " << p6[p5-1] << "." << endl;
        cout << "Is that your final choice? (y/n) " << endl;
        cin >> ans;

        if(ans == 'Y' || ans == 'y')
        {
            p2[p5-1] = true;
            return true;
        }
        else
        {
            p1[p5-1] = 0; // reset the scoring option
            return false;
        }
    }
    else
    {
        //if scoring option has already been used display notification and
        //break to redisplay the scoring option menu
        cout << "Scoring option for " << p6[p5-1] << " has already been used." << endl;
        cout << "Please select another scoring option." << endl;
        return false;
    }
}
