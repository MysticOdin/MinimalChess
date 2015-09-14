#include "Serialization.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <map>
#include "ChessGenericTypes.h"

static const char columnMap[8] =
{
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h'
};

static const char rowMap[8] =
{
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8'
};

static std::map<char, coord_t> columnReverseMap = {
    {'a',COLUMN_A},
    {'b',COLUMN_B},
    {'c',COLUMN_C},
    {'d',COLUMN_D},
    {'e',COLUMN_E},
    {'f',COLUMN_F},
    {'g',COLUMN_G},
    {'h',COLUMN_H}
};

static std::map<char, coord_t> rowReverseMap = {
    {'1',ROW_1},
    {'2',ROW_2},
    {'3',ROW_3},
    {'4',ROW_4},
    {'5',ROW_5},
    {'6',ROW_6},
    {'7',ROW_7},
    {'8',ROW_8}
};

void serializeMoveList(const std::list<Move> *l, std::ofstream * fs)
{
    for(std::list<Move>::const_iterator i = l->begin();
        i != l->end();
        i++)
    {
        (*fs)<<columnMap[i->startColumn]<<rowMap[i->startRow]<<'-'
             <<columnMap[i->endColumn]<<rowMap[i->endRow]<<std::endl;
    }
}

bool deSerializeMoveList(std::list<Move> *l, std::ifstream * fs)
{
    bool returned = true;
    std::string s;
    while((returned == true) && (std::getline(*fs, s)))
    {
        boost::algorithm::trim(s);
        if(s.compare("") != 0)
        {
            const char * line = s.data();
            if((s.length() != 5) || (line[2] != '-'))
            {
                returned = false;
            }
            else
            {
                Move appendedMove;
                if(  (columnReverseMap.find(line[0]) != columnReverseMap.end())
                   &&(rowReverseMap.find(line[1]) != rowReverseMap.end())
                   &&(columnReverseMap.find(line[3]) != columnReverseMap.end())
                   &&(rowReverseMap.find(line[4]) != rowReverseMap.end()))
                {
                    appendedMove.startColumn = columnReverseMap[line[0]];
                    appendedMove.startRow = rowReverseMap[line[1]];
                    appendedMove.endColumn = columnReverseMap[line[3]];
                    appendedMove.endRow = rowReverseMap[line[4]];
                    l->push_back(appendedMove);
                }
                else
                {
                    returned = false;
                }
            }

        }
    }
    return returned;
}
