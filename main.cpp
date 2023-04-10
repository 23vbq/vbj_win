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
char input;

Card card_deck[52];
const char* type_icon[] = {"♣", "♦", "♠", "♥"};
vector<int> shuffle;

vector<Card*> player_hand;
vector<Card*> dealer_hand;

void SetupDeck();
void ShuffleDeck();
template<typename T>
bool VectorContains(vector<T> v, T value);
void GiveCard(vector<Card*> &hand);
void Test();
//void FreeMem();

int main(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    SetupDeck();
    
    while(game_loop){
        if(shuffle.size() == 0) ShuffleDeck();
        for(int i = 0; i < 2; i++)
            GiveCard(player_hand);
        for(int i = 0; i < 2; i++)
            GiveCard(dealer_hand);
        printf("Debug: %d\n", player_hand.size());
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
/*void FreeMem(){
    for(int i = 0; i < 52; i++){
        delete card_deck[i];
    }
}*/