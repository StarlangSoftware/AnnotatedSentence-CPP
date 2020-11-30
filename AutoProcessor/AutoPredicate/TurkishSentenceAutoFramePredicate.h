//
// Created by Olcay Taner YILDIZ on 30.11.2020.
//

#ifndef ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOFRAMEPREDICATE_H
#define ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOFRAMEPREDICATE_H
#include "FrameNet.h"
#include "SentenceAutoFramePredicate.h"

class TurkishSentenceAutoFramePredicate : public SentenceAutoFramePredicate {
private:
    FrameNet frameNet;
public:
    explicit TurkishSentenceAutoFramePredicate(FrameNet& frameNet);
    bool autoPredicate(AnnotatedSentence* sentence) override;
};


#endif //ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOFRAMEPREDICATE_H
