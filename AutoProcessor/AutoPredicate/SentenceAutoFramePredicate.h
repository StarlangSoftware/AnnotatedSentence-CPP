//
// Created by Olcay Taner YILDIZ on 30.11.2020.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOFRAMEPREDICATE_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOFRAMEPREDICATE_H


#include "../../AnnotatedSentence.h"

class SentenceAutoFramePredicate {
public:
    /**
     * The method should set determine all predicates in the sentence.
     * @param sentence The sentence for which predicates will be determined automatically.
     */
    virtual bool autoPredicate(AnnotatedSentence* sentence) = 0;
};


#endif //ANNOTATEDSENTENCE_SENTENCEAUTOFRAMEPREDICATE_H
