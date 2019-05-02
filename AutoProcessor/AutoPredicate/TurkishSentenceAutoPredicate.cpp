//
// Created by olcay on 2.05.2019.
//

#include "TurkishSentenceAutoPredicate.h"

TurkishSentenceAutoPredicate::TurkishSentenceAutoPredicate(FramesetList &xmlParser) {
    this->xmlParser = xmlParser;
}

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
