//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H


#include "../../AnnotatedSentence.h"

class SentenceAutoPredicate {
public:
    /**
     * The method should set determine all predicates in the sentence.
     * @param sentence The sentence for which predicates will be determined automatically.
     */
    virtual bool autoPredicate(AnnotatedSentence* sentence) = 0;
};


#endif //ANNOTATEDSENTENCE_SENTENCEAUTOPREDICATE_H
