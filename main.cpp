#define ERROR_COLOR 12
#define DEFAULT_COLOR 7

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <vector>

#include <windows.h>

#include "card.hpp"
#include "quicksort.hpp"

using namespace std;

HANDLE hConsole;
bool game_loop = true;
bool round_ends;
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
bool VectorContains(vector<T>, T);
void GiveCard(vector<Card*>&);
void PrintCards(vector<Card*>, const char*, bool);
void PrintDecisions();
bool HandlePlayerMove();
void Hit();
void Stand();
void Split();
void Insurance();
int CalculateHandSum(vector<Card*>);
void printerr(const char*);
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

        // Player round
        round_ends = false;
        while(!round_ends){
            system("cls");
            printf("Input was: %d\n\n", input);
            PrintCards(dealer_hand, "Dealer", false);
            PrintCards(player_hand, "Player", true);
            PrintDecisions();
            int sum = CalculateHandSum(player_hand);
            if(sum >= 21) {
                break;
            }
            printf("\n\nSum: %d", sum);
            while(!HandlePlayerMove());
        }

        /* NEED TO WRITE HANDLE TO PLAYER LOSE*/

        // Dealer round
        round_ends = false;
        while(!round_ends){
            system("cls");
            printf("Input was: %d\n\n", input);
            PrintCards(dealer_hand, "Dealer", false);
            PrintCards(player_hand, "Player", true);
            int sum = CalculateHandSum(dealer_hand);
            
            // Simulate decisions
            Sleep(2 * 1000);
            if (sum < 17){
                GiveCard(dealer_hand);
            } else break;
        }
        // Debug print
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
    printf("Moves:\n");
    printf("\n%d. Hit\n", k++);
    printf("%d. Stand\n", k++);
    if(player_hand.size() == 2){
        if(player_hand[0]->Value == player_hand[1]->Value) printf("%d. Split\n", k++);
        if(dealer_hand[0]->Value == 14) printf("%d. Insurance\n", k++);
    } 
}
bool HandlePlayerMove(){
    getinput();
    if (input == '1') {Hit(); return true;}
    else if (input == '2') {Stand(); return true;}
    else if (player_hand.size() == 2){
        if (input == '3'){
            if (player_hand[0]->Value == player_hand[1]->Value) {Split(); return true;}
            else if (dealer_hand[0]->Value == 14) {Insurance(); return true;}
        }
        else if (input == '4' && dealer_hand[0]->Value == 14) {Insurance(); return true;}
    }
    printerr("Invalid move...\n");
    return false;
}

// Moves
void Hit(){
    GiveCard(player_hand);
}
void Stand(){
    round_ends = true;
}
void Split(){
    
}
void Insurance(){

}
int CalculateHandSum(vector<Card*> hand){
    int* values = new int[hand.size()];
    for (int i = 0; i < hand.size(); i++)
        values[i] = hand.at(i)->GetValue();
    quickSort(values, 0, hand.size() - 1);
    /*printf("\n\n"); // Debug
    for (int i = 0; i < hand.size(); i++)
        printf("%d|", values[i]);
    */
    int sum = 0;
    for(int i = 0; i < hand.size(); i++){
        sum += values[i];
        if(values[i] == 11 && sum > 21) sum -= 10;
    }
    delete values;
    return sum;
}
void printerr(const char* info){
    SetConsoleTextAttribute(hConsole, ERROR_COLOR);
    printf("\33[2K\r  %s", info);
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
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