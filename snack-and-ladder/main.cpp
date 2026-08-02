//players start moving after getting 1
//dice->1 to 6
//players turn will come in clockwise direction
//1 or 5 player will get extra opportunity
//slider and ladders are fixed
//gifts fcfs
//game stops after player reaching 30th box
//exceeded they remain ideal
//if none wins print tie

//output: player name | current position | remaining count to win the game | gifts | sliders | ladders
//players lost, ... , ... 
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Box{
    int playerIndex;  //player index in undefined for position 1
    int ladder,slider,gift;
    Box(){
        this->playerIndex=-1;
        this->ladder=0;
        this->slider=0;
        this->gift=0;
    }
};
struct Player{
    string name;
    int pos,gifts,ladders,sliders;
    bool isMoving;
};
vector<Box>boxes(31);  //one indexing
vector<Player>players;  //zero indexing
vector<int>roll;
int startingPlayer;

void print(){
   
    vector<string>losedPlayers;
    for(int i=0;i<players.size();i++){
        cout<<(players[i].name)<<"|";
        cout<<(players[i].pos)<<"|";
        cout<<(30-players[i].pos)<<"|";
        cout<<(players[i].ladders)<<"|";
        cout<<(players[i].sliders)<<"|";
        cout<<(players[i].gifts)<<endl;
        
        if(players[i].pos!=30){
            losedPlayers.push_back(players[i].name);
        }
    }
    for(int i=0;i<losedPlayers.size()-1;i++){
        cout<<losedPlayers[i]<<",";
    }
    cout<<losedPlayers.back()<<" lost the game";
    exit(0);
}
void move(int currentPlayer,int dice){
    int currentPosition=players[currentPlayer].pos;
    
    
    //conditions for rejecting the move
    if( currentPosition==1 ) {
        if(!players[currentPlayer].isMoving){
            if(dice==1)players[currentPlayer].isMoving=1;
            return;
        }
    }
    if( currentPosition+dice>30 )return;
    
    boxes[currentPosition].playerIndex=-1;
    //moving the player
    currentPosition+=dice;
    if(currentPosition==30){
        players[currentPlayer].pos=30;
        print();
    }
    
    //check for gift
    if(boxes[currentPosition].gift==1){
        players[currentPlayer].gifts++;
        boxes[currentPosition].gift=0;
    }
    //check for slider
    if(boxes[currentPosition].slider!=0){
        players[currentPlayer].sliders++;
        currentPosition=boxes[currentPosition].slider;
    }
    //check for ladder
    if(boxes[currentPosition].ladder!=0){
        players[currentPlayer].ladders++;
        currentPosition=boxes[currentPosition].ladder;
    }
    //check for player 
    if(boxes[currentPosition].playerIndex!=-1){
        //move the old player to 1;
        int oldPlayer=boxes[currentPosition].playerIndex;
        players[oldPlayer].pos=1;
        players[oldPlayer].isMoving=false;
    }
    
    //check for gift again (we might get gift after sliding and climbing the ladder)
    if(boxes[currentPosition].gift==1){
        players[currentPlayer].gifts++;
        boxes[currentPosition].gift=0;
    }
    
    players[currentPlayer].pos=currentPosition;
    boxes[currentPosition].playerIndex=currentPlayer;
}
void rollDice(){
    int n;
    n=roll.size();
    int currentPlayer=startingPlayer;
    for(int i=0;i<21;i++){
        int dice=roll[i];
        // cout<<roll[i]<<"->"<<players[currentPlayer].name<<endl;
        if(dice==5 || dice==1){
            //player gets another chance
            move(currentPlayer,dice);
        }
        else{
            //next player
            move(currentPlayer,dice);
            currentPlayer=(currentPlayer+1)%(players.size());
        }
    }
    print();
}


void getInput(){
    int playerCount;
    cin>>playerCount;  //number of players
    players.resize(playerCount);
    for(int i=0;i<playerCount;i++){
        cin>>players[i].name;
        players[i].pos=1;
        players[i].gifts=0;
        players[i].ladders=0;
        players[i].sliders=0;
        players[i].isMoving=false;
    }

    string name;
    cin>>name;
    for(int i=0;i<playerCount;i++){
        if(name==players[i].name){
            startingPlayer=i;
            break;
        }
    }


    int numberOfGifts;
    cin>>numberOfGifts;  //number of gifts
    
    for(int i=0;i<numberOfGifts;i++){
        int pos;
        cin>>pos;
        boxes[pos].gift=1;
    }

    
    int n;
    cin>>n;   //number of rolls
    roll.resize(n);
    for(int i=0;i<n;i++){
        cin>>roll[i];
    }

    // fixing the boxes
    boxes.resize(31);
    boxes[4].ladder=9;
    boxes[7].ladder=19;
    boxes[8].ladder=28;
    boxes[15].ladder=26;

    boxes[13].slider=2;
    boxes[29].slider=20;
    boxes[25].slider=14;
    
    
    //board check:
    // for(int i=1;i<=30;i++){
    //     cout<<i<<"->"<<boxes[i].playerIndex<<" | "<<boxes[i].ladder
    //     <<" | "<<boxes[i].slider<<" | "<<boxes[i].gift<<endl;
    // }
    
    
    // player check:
    // for(int i=0;i<playerCount;i++){
    //     cout<<i<<"->"<<players[i].pos<<" | "<<players[i].name<<" | "<<players[i].gifts<<" | "<<players[i].ladders<<" | "<<players[i].sliders<<endl;
    // }
}


int main(){
    getInput();
    
    rollDice();
}
