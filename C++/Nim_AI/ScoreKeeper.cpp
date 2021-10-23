/* 
 * File: ScoreKeeper.cpp
 * Author: Michael Coughlin
 * Honors Computer Science, Fall 2013
 */

#include "nim.H"


void ScoreKeeperInfo::start() {
     welcome();
     flipCoin();
     playRepeatedly();
    
}

int ScoreKeeperInfo::playerScore(int score1){
    return score1;
    this->score1 = score1;
}
int ScoreKeeperInfo::computerScore(int score2){
    return score2;
    this->score2 = score2;
}

void ScoreKeeperInfo::welcome() {
 string name = new char[10];
    cout << "Welcome to the game of Nim!" << endl;
    cout << endl << "What is you name?";
    cin >> name;
    this->name = name;
    player1 = new PlayerInfo(name);
    player2 = new AutomatedPlayerInfo("HAL 9000", new IntermediateStrategyInfo);
    playerScore(0);
    computerScore(0);
}

void ScoreKeeperInfo::flipCoin() {
    int random = rand() % 2;
    headsOrTails = new char[5];
    end = false;
    finished = false;
    while(finished == false)
    {
    cout << "Please choose heads or tails." << endl;
    cin >> headsOrTails;
    this->headsOrTails = headsOrTails;
    if(headsOrTails == "heads")
    {
        choice = 0;
        finished = true;
    }
    else if(headsOrTails == "tails")
    {
        choice = 1;
        finished = true;
    }
    else cout << "Incorrect Input." << endl;
    }
    if(random == choice && headsOrTails == "heads"){
        cout << "Correct! It was heads, you will go first." << endl;
        firstToPlay = player1;
        setToPlay = player2;
        }
        else if(random == choice && headsOrTails == "tails") {
        cout << "Correct! It was tails, you will go first." << endl;
        firstToPlay = player1;
        setToPlay = player2;
        }
        else if(random ==! choice && headsOrTails == "heads") {    
        cout << "It was tails, I will go first." << endl;
        firstToPlay = player2;
        setToPlay = player1;
        }
        else if(random ==! choice && headsOrTails == "tails") {
        cout << "It was heads, I will go first." << endl;
        firstToPlay = player2; 
        setToPlay = player1;
        this->setToPlay = setToPlay;
        this->firstToPlay = firstToPlay;
        }       
}

void ScoreKeeperInfo::makeRandomStartState(){
    A = Utils::generateRandomInt(6,12);
    B = A;
    C = A;
    while(A == B){
        B = Utils::generateRandomInt(6,12);
    }
    while(A == C || B == C){
        C = Utils::generateRandomInt(6,12); 
    }   
            this->A = A;
            this->B = B;
            this->C = C;
            
}
void ScoreKeeperInfo::playRepeatedly(){
   makeRandomStartState();
    initialState = new GameStateInfo(A, B, C);
    Game game = new GameInfo(firstToPlay, setToPlay, initialState);
    Player winner = game->play();
    if(winner == player1){
        playerScore(score1++);
        cout << name << " wins!" << endl;
    }else{ 
        computerScore(score2++);
        cout << "HAL 9000 wins." << endl;
}
    cout << name << ": " << this->score1 << endl;
    cout << "HAL 9000: " << this->score2 << endl;
    finished = false;
    while(finished == false){
        cout << "Another game (yes or no)?" << endl;
        cin >> yesOrNo;
    if(yesOrNo == "yes"){
    finished = true;
    temp = setToPlay;
    setToPlay = firstToPlay;
    firstToPlay = temp;
        playRepeatedly();}
    else if(yesOrNo == "no"){
    finished = true;
        break;}
    else cout << "Invalid input" << endl;         

    }
}