//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H


#include "../../AnnotatedSentence.h"

class SentenceAutoPredicate {
public:
    virtual bool autoPredicate(AnnotatedSentence* sentence) = 0;
};


#endif //ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H
