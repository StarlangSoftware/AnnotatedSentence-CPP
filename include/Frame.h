//
// Created by Olcay Taner YILDIZ on 22.10.2020.
//

#ifndef FRAMENET_FRAME_H
#define FRAMENET_FRAME_H
#include <string>
#include <vector>
#include <XmlElement.h>
#include <XmlDocument.h>
#include "LexicalUnit.h"

using namespace std;

class Frame {
private:
    string name;
    vector<LexicalUnit> lexicalUnits;
public:
    Frame(string name, XmlDocument xmlDocument);
    bool lexicalUnitExists(string synSetId);
    LexicalUnit getLexicalUnitWithId(string synSetId);
    void removeLexicalUnit(LexicalUnit toBeRemoved);
    LexicalUnit getLexicalUnit(int index);
    int size();
    string getName();
};


#endif //FRAMENET_FRAME_H
