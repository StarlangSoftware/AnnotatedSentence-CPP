//
// Created by Olcay Taner YILDIZ on 30.11.2020.
//

#include "TurkishSentenceAutoFramePredicate.h"

/**
 * Constructor for {@link TurkishSentenceAutoPredicate}. Gets the FrameSets as input from the user, and sets
 * the corresponding attribute.
 * @param framesetList FramesetList containing the Turkish propbank frames.
 */
TurkishSentenceAutoFramePredicate::TurkishSentenceAutoFramePredicate(FrameNet &frameNet) {
    this->frameNet = frameNet;
}

/**
 * The method uses predicateCandidates method to predict possible predicates. For each candidate, it sets for that
 * word PREDICATE tag.
 * @param sentence The sentence for which predicates will be determined automatically.
 * @return If at least one word has been tagged, true; false otherwise.
 */
bool TurkishSentenceAutoFramePredicate::autoPredicate(AnnotatedSentence *sentence) {
    vector<AnnotatedWord*> candidateList = sentence->predicateFrameCandidates(frameNet);
    for (AnnotatedWord* word : candidateList){
        word->setArgument("PREDICATE$NONE$" + word->getSemantic());
    }
    if (!candidateList.empty()){
        return true;
    }
    return false;
}
