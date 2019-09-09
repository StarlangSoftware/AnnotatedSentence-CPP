//
// Created by Olcay Taner Yıldız on 2019-04-30.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H

#include "../../AnnotatedSentence.h"

class SentenceAutoArgument{
    /**
     * The method should set all the semantic role labels in the sentence. The method assumes that the predicates
     * of the sentences were determined previously.
     * @param sentence The sentence for which semantic roles will be determined automatically.
     */
    virtual bool autoArgument(AnnotatedSentence* sentence) = 0;
};
#endif //ANNOTATEDSENTENCE_SENTENCEAUTOARGUMENT_H
