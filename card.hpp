#ifndef card_hpp
#define card_hpp
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