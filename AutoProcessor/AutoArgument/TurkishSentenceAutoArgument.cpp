//
// Created by Olcay Taner Yıldız on 2019-04-30.
//

#include "TurkishSentenceAutoArgument.h"

/**
 * Given the sentence for which the predicate(s) were determined before, this method automatically assigns
 * semantic role labels to some/all words in the sentence. The method first finds the first predicate, then assuming
 * that the shallow parse tags were preassigned, assigns ÖZNE tagged words ARG0; NESNE tagged words ARG1. If the
 * verb is in passive form, ÖZNE tagged words are assigned as ARG1.
 * @param sentence The sentence for which semantic roles will be determined automatically.
 * @return If the method assigned at least one word a semantic role label, the method returns true; false otherwise.
 */
bool TurkishSentenceAutoArgument::autoArgument(AnnotatedSentence* sentence) {
    bool modified = false;
    string predicateId;
    for (int i = 0; i < sentence->wordCount(); i++){
        AnnotatedWord* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getArgument() != nullptr && word->getArgument()->getArgumentType() == "PREDICATE"){
            predicateId = word->getArgument()->getId();
            break;
        }
    }
    if (!predicateId.empty()){
        for (int i = 0; i < sentence->wordCount(); i++){
            AnnotatedWord* word = (AnnotatedWord*) sentence->getWord(i);
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
