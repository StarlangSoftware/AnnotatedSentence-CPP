//
// Created by Olcay Taner Yıldız on 2019-04-30.
//

#ifndef ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOARGUMENT_H
#define ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOARGUMENT_H


#include "SentenceAutoArgument.h"

class TurkishSentenceAutoArgument : public SentenceAutoArgument {
public:
    bool autoArgument(AnnotatedSentence* sentence) override;
};


#endif //ANNOTATEDSENTENCE_TURKISHSENTENCEAUTOARGUMENT_H
