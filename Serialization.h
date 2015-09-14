#ifndef SERIALIZATION
#define SERIALIZATION
#include <fstream>
#include <list>
#include "Move.h"

extern void serializeMoveList(const std::list<Move>* l, std::ofstream* fs);
extern bool deSerializeMoveList(std::list<Move> *l, std::ifstream * fs);

#endif // SERIALIZATION

