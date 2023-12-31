/* 
 * Solution: Project #1 - Yahtzee
 * Version 0.6
 * File:   main.cpp
 * Author: Jay Blakeborough
 * Created on July 30, 2023
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
 *          examples:(dice, keeper flags, markers, scores & score flags)
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
const char ROUNDS = 8; //ROUNDS will be 8 for lite version. change to 13 once logic is built for full version 
const char DICE = 5; //number of die


//Function Prototypes
void rollDie(short int[], bool[]);

//Execution Begins Here
int main(int argc, char** argv)
{
    //Local constants
    const unsigned RSEED = time(0);  //use system time for seed
    //seed the random number generator
    srand(RSEED);
    
    //Declare Variables/Data Types
    
    short int die[DICE];
    bool keep[DICE];
    char mark[DICE];
    bool sf1, sf2, sf3, sf4, sf5, sf6, sf7, sf8; // scoring flags - if true that scoring option has been selected
    bool scrflg[ROUNDS];
    short int s1, s2, s3, s4, s5, s6, s7, s8; //scoring variables
    short int score[ROUNDS];
    char mChoice;  //input the Main Menu choice
    char pChoice;  //input the Play Option choice
    short int choice; //cin input variable - will cast to mChoice
    short int round;  // round counter x of 8
    short int roll; // role counter x of 3
    string pName = "";
    
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
                
                for (int i=0; i < DICE; i++)
                    score[i]=0, scrflg[i] = false;
                
                s1 = s2 = s3 = s4 = s5 = s6 = s7 = s8 = 0; //reset individual scores
                sf1 = sf2 = sf3 = sf4 = sf5 = sf6 = sf7 = sf8 = false;  //reset a;; scoring flags
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
                            rollDie(die, keep); //execute the roll die function
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
                                    case 1: //score the Ones
                                    {
                                        if (!sf1) //if scoring flag is not on, score to this category...
                                        {
                                            char ans;
                                            
                                            //add the score for all ones
                                            s1 += die[0] == 1 ? 1 : 0; //if die #1 is a one add one to score option #1
                                            s1 += die[1] == 1 ? 1 : 0; //if die #2 is a one add one to score option #1
                                            s1 += die[2] == 1 ? 1 : 0; //if die #3 is a one add one to score option #1
                                            s1 += die[3] == 1 ? 1 : 0; //if die #4 is a one add one to score option #1
                                            s1 += die[4] == 1 ? 1 : 0; //if die #5 is a one add one to score option #1
                                            
                                            cout << endl << "You will score " << s1 << " points for ones." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf1 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                            else
                                            {
                                                s1 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            //if scoring option has already been used display notification and
                                            //break to redisplay the scoring option menu
                                            cout << "Scoring option for Ones has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    }// end case 1
                                    
                                    case 2: //score the Twos
                                    {
                                        if (!sf2) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            //add the score for all twos
                                            s2 += die[0] == 2 ? 2 : 0; //if die #1 is a two add two to score option #2
                                            s2 += die[1] == 2 ? 2 : 0; //if die #2 is a twp add two to score option #2
                                            s2 += die[2] == 2 ? 2 : 0; //if die #3 is a two add two to score option #2
                                            s2 += die[3] == 2 ? 2 : 0; //if die #4 is a two add two to score option #2
                                            s2 += die[4] == 2 ? 2 : 0; //if die #5 is a two add two to score option #2
                                            
                                            cout << endl << "You will score " << s2 << " points for twos." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf2 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                            else
                                            {
                                                s2 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Twos has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    } //end case 2
                                    
                                    case 3: //score the Threes
                                    {
                                        if (!sf3) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            //add the score for all threes
                                            s3 += die[0] == 3 ? 3 : 0; //if die #1 is a three add three to score option #3
                                            s3 += die[1] == 3 ? 3 : 0; //if die #2 is a three add three to score option #3
                                            s3 += die[2] == 3 ? 3 : 0; //if die #3 is a three add three to score option #3
                                            s3 += die[3] == 3 ? 3 : 0; //if die #4 is a three add three to score option #3
                                            s3 += die[4] == 3 ? 3 : 0; //if die #5 is a three add three to score option #3
                                            
                                            cout << endl << "You will score " << s3 << " points for Threes." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf3 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                            else
                                            {
                                                s3 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Threes has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    } //end case 3
                                    
                                    case 4: //score the Fours
                                    {
                                        if (!sf4) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            //add the score for all fours
                                            s4 += die[0] == 4 ? 4 : 0; //if die #1 is a four add four to score option #4
                                            s4 += die[1] == 4 ? 4 : 0; //etc
                                            s4 += die[2] == 4 ? 4 : 0; //etc
                                            s4 += die[3] == 4 ? 4 : 0; //etc
                                            s4 += die[4] == 4 ? 4 : 0; //etc
                                            
                                            cout << endl << "You will score " << s4 << " points for Fours." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf4 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                        
                                            else
                                            {
                                                s4 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Fours has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    } //end case 4                                
                                    
                                    case 5: //score the Fives
                                    {
                                        if (!sf5) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            //add the score for all fives
                                            s5 += die[0] == 5 ? 5 : 0; //if die #1 is a five add five to score option #5
                                            s5 += die[1] == 5 ? 5 : 0; //etc
                                            s5 += die[2] == 5 ? 5 : 0; //etc
                                            s5 += die[3] == 5 ? 5 : 0; //etc
                                            s5 += die[4] == 5 ? 5 : 0; //etc
                                            
                                            cout << endl << "You will score " << s5 << " points for Fives." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf5 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                        
                                            else
                                            {
                                                s5 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Fives has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    } //end case 5
                                    
                                    case 6: //score the Sixes
                                    {
                                        if (!sf6) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            //add the score for all sixes
                                            s6 += die[0] == 6 ? 6 : 0; //if die #1 is a six add six to score option #6
                                            s6 += die[1] == 6 ? 6 : 0; //etc
                                            s6 += die[2] == 6 ? 6 : 0; //etc
                                            s6 += die[3] == 6 ? 6 : 0; //etc
                                            s6 += die[4] == 6 ? 6 : 0; //etc
                                            
                                            cout << endl << "You will score " << s6 << " points for Sixes." << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf6 = true;
                                                scrFlg = true;
                                                break;
                                            }
                                        
                                            else
                                            {
                                                s6 = 0; // reset the scoring option
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Scoring option for Sixes has already been used." << endl;
                                            cout << "Please select another scoring option." << endl;
                                            break;
                                        }
                                    } //end case 6
                                    
                                    case 7: //Yahtzee!!
                                    {
                                        if (!sf7) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            string congrat = "";
                                            if (die[0] == die[1] && die[0] == die[2] && die[0] == die[3] && die[0] == die[4]) //it is a Yahtzee
                                            {
                                                s7 = 50; //score 50
                                                congrat = "Congratulations on the Yahtzee!!";
                                            }
                                            else //or score 0
                                                s7 = 0;
                                            
                                            cout << endl << congrat << " You will score "
                                                 << s7 << " points for the Yahtzee" << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf7 = true;
                                                scrFlg = true;
                                                break;
                                            }                                        
                                            else
                                            {
                                                s7 = 0; // reset the scoring option
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
                                        if (!sf8) //if scoring flag is not on score to this category
                                        {
                                            char ans;
                                            
                                            s8 = die[0] + die[1] + die[2] + die[3] + die[4]; //add all die
                                                                                        
                                            cout << endl << "You will score "
                                                 << s8 << " points for the Chance" << endl;
                                            cout << "Is that your final choice? (y/n) " << endl;
                                            cin >> ans;
                                            
                                            if(ans == 'Y' || ans == 'y')
                                            {
                                                sf8 = true;
                                                scrFlg = true;
                                                break;
                                            }                                        
                                            else
                                            {
                                                s8 = 0; // reset the scoring option
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
                            cout << "Ones        = " << setw(3) << right << s1 << endl;
                            cout << "Twos        = " << setw(3) << right << s2 << endl;
                            cout << "Threes      = " << setw(3) << right << s3 << endl;
                            cout << "Fours       = " << setw(3) << right << s4 << endl;
                            cout << "Fives       = " << setw(3) << right << s5 << endl;
                            cout << "Sixes       = " << setw(3) << right << s6 << endl;
                            uttl = s1+s2+s3+s4+s5+s6;
                            if (uttl >= 63)
                                bonus = 35;
                            cout << "TOTAL       = " << setw(3) << right << uttl << endl;
                            cout << "Bonus       = " << setw(3) << right << bonus << endl << endl;
                            cout << "LOWER SECTION" << endl;
                            cout << "Yahtzee     = " << setw(3) << right << s7 << endl;
                            cout << "Chance      = " << setw(3) << right << s8 << endl;
                            lttl = s7 + s8;
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
                                oFile << s1 << "\t" << s2 << "\t" << s3 << "\t"
                                      << s4 << "\t" << s5 << "\t" << s6 << "\t"
                                      << s7 << "\t" << s8 << endl; //write scores
                                oFile << sf1 << "\t" << sf2 << "\t" << sf3 << "\t"
                                      << sf4 << "\t" << sf5 << "\t" << sf6 << "\t"
                                      << sf7 << "\t" << sf8 << endl; //write score flags
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

void rollDie(short int p1[], bool p2[])
{
    //roll only the die that have not been marked to keep
    //on first roll there are no kept die, but roll two and three will
    //each die will have it's own roll - could use for-loop here if
    // arrays could be used
    for (int i=0; i < DICE; i++)
    {
        if (!p2[i])
            p1[i] = rand() % 6 + 1;
    }
}

