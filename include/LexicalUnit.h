//
// Created by Olcay Taner YILDIZ on 22.10.2020.
//

#ifndef FRAMENET_LEXICALUNIT_H
#define FRAMENET_LEXICALUNIT_H
#include <string>
#include <vector>
#include <XmlElement.h>

using namespace std;


class LexicalUnit {
private:
    string synSetId;
    vector<string> frameElements;
public:
    explicit LexicalUnit(XmlElement* node);
    int size();
    string getSynSetId();
    vector<string> getFrameElements();
};


#endif //FRAMENET_LEXICALUNIT_H
