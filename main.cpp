#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <vector>

#include <windows.h>

#include "card.hpp"

using namespace std;

HANDLE hConsole;
bool game_loop = true;
int input;

Card card_deck[52];
const char* type_icon[] = {"♣", "♦", "♠", "♥"};
const char* special_card_names[] = {"J", "Q", "K", "A"};
vector<int> shuffle;

vector<Card*> player_hand;
vector<Card*> dealer_hand;

void getinput();
void SetupDeck();
void ShuffleDeck();
template<typename T>
bool VectorContains(vector<T> v, T value);
void GiveCard(vector<Card*> &hand);
void PrintCards(vector<Card*> hand, const char* title, bool printAll);
void PrintDecisions();
void Test();
//void signalHandler(int signum);
//void FreeMem();

int main(){
    //signal(SIGINT, signalHandler);
    // Setup game
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    SetupDeck();
    
    // Game start
    while(game_loop){
        system("cls");
        if(shuffle.size() == 0) ShuffleDeck();
        player_hand.clear();
        dealer_hand.clear();
        for(int i = 0; i < 2; i++)
            GiveCard(player_hand);
        for(int i = 0; i < 2; i++)
            GiveCard(dealer_hand);

        bool game_ends = false;
        while(!game_ends){
            //system("cls");
            printf("Input was: %d\n\n", input);
            PrintCards(dealer_hand, "Dealer", false);
            PrintCards(player_hand, "Player", true);
            PrintDecisions();
            getinput();
        }
        for(auto p : player_hand){
            printf("%d - %d\n", p->GetValue(), p->Type);
        }
        for(auto p : dealer_hand){
            printf("%d - %d\n", p->GetValue(), p->Type);
        }
        input = _getch();
    }
    //FreeMem();
    return 0;
}

void getinput(){
    input = _getch();
    if(input == 3) exit(1);
}
void SetupDeck(){
    Card * p;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            //card_deck[j + i * 13] = new Card(j+2, (CardType)i);
            p = &card_deck[j + i * 13];
            p->Value = j+2;
            p->Type = (CardType)i;
        }
    }
    p = NULL;
}
void ShuffleDeck(){
    int random;
    shuffle.clear();
    for(int i = 0; i < 52; i++){
        bool contains;
        do{
            random = rand() % 52;
        } while(VectorContains<int>(shuffle, random));
        shuffle.push_back(random);
    }
}
template<typename T>
bool VectorContains(vector<T> v, T value){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == value) return true;
    }
    return false;
}
void GiveCard(vector<Card*> &hand){
    Card* p = &card_deck[shuffle[shuffle.size() - 1]];
    hand.push_back(p);
    shuffle.pop_back();
}
void PrintCards(vector<Card*> hand, const char* title, bool printAll){
    printf("%*s%*s\n", 10 + strlen(title)/2, title, 10 - strlen(title)/2, "");
    for(int i = 0; i < hand.size(); i++){
        if(i != 0 && !printAll){
            printf("%3s###", "");
            continue;
        }
        const char* cardName;
        if(hand[i]->Value < 11) cardName = to_string(hand[i]->Value).c_str();
        else cardName = special_card_names[hand[i]->Value - 11];
        printf("%3s%s %s", "", cardName, type_icon[hand[i]->Type]);
    }
    printf("\n");
}
void PrintDecisions(){
    int k = 1;
    printf("\n%d. Hit\n", k++);
    printf("%d. Stand\n", k++);
    if(player_hand.size() == 2){
        if(player_hand[0]->Value == player_hand[1]->Value) printf("%d. Split\n", k++);
        if(dealer_hand[0]->Value == 14) printf("%d. Insurance\n", k++);
    } 
}
void Test(){
    int index;
        while(true){
            cin>>index;
            if(index < 0) break;
            cout<<card_deck[index].GetValue()<<" : "<<type_icon[2]<<"\n";
            printf("%d | %s", card_deck[index].GetValue(), type_icon[2]);
        }
    cout<<"Closing...";
}
/*void signalHandler(int signum){
    printf("Ch");
    exit(signum);
}*/
/*void FreeMem(){
    for(int i = 0; i < 52; i++){
        delete card_deck[i];
    }
}*/