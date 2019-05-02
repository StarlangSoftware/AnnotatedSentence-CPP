//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H


#include "../../AnnotatedSentence.h"

class SentenceAutoSemantic {
protected:
    virtual void autoLabelSingleSemantics(AnnotatedSentence* sentence) = 0;
public:
    void autoSemantic(AnnotatedSentence* sentence);
};


#endif //ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H
