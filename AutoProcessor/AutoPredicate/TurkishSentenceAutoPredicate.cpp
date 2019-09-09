//
// Created by olcay on 2.05.2019.
//

#include "TurkishSentenceAutoPredicate.h"

/**
 * Constructor for {@link TurkishSentenceAutoPredicate}. Gets the FrameSets as input from the user, and sets
 * the corresponding attribute.
 * @param framesetList FramesetList containing the Turkish propbank frames.
 */
TurkishSentenceAutoPredicate::TurkishSentenceAutoPredicate(FramesetList &xmlParser) {
    this->xmlParser = xmlParser;
}

/**
 * The method uses predicateCandidates method to predict possible predicates. For each candidate, it sets for that
 * word PREDICATE tag.
 * @param sentence The sentence for which predicates will be determined automatically.
 * @return If at least one word has been tagged, true; false otherwise.
 */
bool TurkishSentenceAutoPredicate::autoPredicate(AnnotatedSentence *sentence) {
    vector<AnnotatedWord*> candidateList = sentence->predicateCandidates(xmlParser);
    for (AnnotatedWord* word : candidateList){
        word->setArgument("PREDICATE$" + word->getSemantic());
    }
    if (candidateList.size() > 0){
        return true;
    }
    return false;
}
