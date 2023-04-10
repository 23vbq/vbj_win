#ifndef card_h
#define card_h
#include "cardType.hpp"

class Card{
public:
    int Value;
    CardType Type;
    
    Card();
    //Card(int,CardType);
    int GetValue();
};

#endif