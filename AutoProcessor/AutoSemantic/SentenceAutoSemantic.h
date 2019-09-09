//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H
#define ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H


#include "../../AnnotatedSentence.h"

class SentenceAutoSemantic {
protected:
    /**
     * The method should set the senses of all words, for which there is only one possible sense.
     * @param sentence The sentence for which word sense disambiguation will be determined automatically.
     */
    virtual void autoLabelSingleSemantics(AnnotatedSentence* sentence) = 0;
public:
    void autoSemantic(AnnotatedSentence* sentence);
};


#endif //ANNOTATEDSENTENCE_SENTENCEAUTOSEMANTIC_H
