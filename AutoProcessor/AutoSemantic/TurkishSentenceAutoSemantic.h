//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOSEMANTIC_H
#define ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOSEMANTIC_H

#include "SentenceAutoSemantic.h"

class TurkishSentenceAutoSemantic : public SentenceAutoSemantic {
private:
    WordNet turkishWordNet;
    FsmMorphologicalAnalyzer fsm;
public:
    TurkishSentenceAutoSemantic(WordNet& turkishWordNet, FsmMorphologicalAnalyzer& fsm);
protected:
    void autoLabelSingleSemantics(AnnotatedSentence* sentence) override;
};


#endif //ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOSEMANTIC_H
