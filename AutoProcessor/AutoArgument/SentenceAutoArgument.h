//
// Created by Olcay Taner Yıldız on 2019-04-30.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H

#include "../../AnnotatedSentence.h"

class SentenceAutoArgument{
    virtual bool autoArgument(AnnotatedSentence* sentence) = 0;
};
#endif //ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H
