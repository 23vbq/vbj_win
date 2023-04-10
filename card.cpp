#include "card.hpp"

Card::Card(){
    Value = 0;
    Type = CardType::CLUBS;
}

int Card::GetValue(){
    if(Value < 11) return Value;
    else if(Value == 14) return 11;
    else return 10;
}
/*Card::Card(int id, CardType type){
    Id = id;
    Type = type;
}*/