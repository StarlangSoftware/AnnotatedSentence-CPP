//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOPREDICATE_H
#define ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOPREDICATE_H
#include "SentenceAutoPredicate.h"

class TurkishSentenceAutoPredicate : public SentenceAutoPredicate {
private:
    FramesetList xmlParser;
public:
    explicit TurkishSentenceAutoPredicate(FramesetList& xmlParser);
    bool autoPredicate(AnnotatedSentence* sentence) override;
};


#endif //ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOPREDICATE_H
