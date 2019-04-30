//
// Created by Olcay Taner Yıldız on 2019-04-30.
//

#include "TurkishSentenceAutoArgument.h"

bool TurkishSentenceAutoArgument::autoArgument(AnnotatedSentence sentence) {
    bool modified = false;
    string predicateId;
    for (int i = 0; i < sentence.wordCount(); i++){
        AnnotatedWord* word = (AnnotatedWord*) sentence.getWord(i);
        if (word->getArgument() != nullptr && word->getArgument()->getArgumentType() == "PREDICATE"){
            predicateId = word->getArgument()->getId();
            break;
        }
    }
    if (!predicateId.empty()){
        for (int i = 0; i < sentence.wordCount(); i++){
            AnnotatedWord* word = (AnnotatedWord*) sentence.getWord(i);
            if (word->getArgument() == nullptr){
                if (word->getShallowParse() == "ÖZNE"){
                    if (word->getParse() != nullptr && word->getParse()->containsTag(MorphologicalTag::PASSIVE)){
                        word->setArgument("ARG1$" + predicateId);
                    } else {
                        word->setArgument("ARG0$" + predicateId);
                    }
                    modified = true;
                } else {
                    if (word->getShallowParse() == "NESNE"){
                        word->setArgument("ARG1$" + predicateId);
                        modified = true;
                    }
                }
            }
        }
    }
    return modified;
}
