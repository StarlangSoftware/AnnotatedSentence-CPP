//
// Created by olcay on 2.05.2019.
//

#include "TurkishSentenceAutoNER.h"

void TurkishSentenceAutoNER::autoDetectPerson(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getNamedEntity() == nullptr && word->getParse() != nullptr){
            if (Word::isHonorific(word->getName())){
                word->setNamedEntityType("PERSON");
            }
            word->checkGazetteer(personGazetteer);
        }
    }
}

void TurkishSentenceAutoNER::autoDetectLocation(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getNamedEntity() == nullptr && word->getParse() != nullptr){
            word->checkGazetteer(locationGazetteer);
        }
    }
}

void TurkishSentenceAutoNER::autoDetectOrganization(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getNamedEntity() == nullptr && word->getParse() != nullptr){
            if (Word::isOrganization(word->getName())){
                word->setNamedEntityType("ORGANIZATION");
            }
            word->checkGazetteer(organizationGazetteer);
        }
    }
}

void TurkishSentenceAutoNER::autoDetectTime(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        string wordLowercase = Word::toLowerCase(word->getName());
        if (word->getNamedEntity() == nullptr && word->getParse() != nullptr){
            if (Word::isTime(wordLowercase)){
                word->setNamedEntityType("TIME");
                if (i > 0){
                    auto* previous = (AnnotatedWord*) sentence->getWord(i - 1);
                    if (previous->getParse()->containsTag(MorphologicalTag::CARDINAL)){
                        previous->setNamedEntityType("TIME");
                    }
                }
            }
        }
    }
}

void TurkishSentenceAutoNER::autoDetectMoney(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        string wordLowercase = Word::toLowerCase(word->getName());
        if (word->getNamedEntity() == nullptr && word->getParse() != nullptr){
            if (Word::isMoney(wordLowercase)) {
                word->setNamedEntityType("MONEY");
                int j = i - 1;
                while (j >= 0){
                    auto* previous = (AnnotatedWord*) sentence->getWord(j);
                    if (previous->getParse() != nullptr && (previous->getName() == "amerikan" || previous->getParse()->containsTag(MorphologicalTag::REAL) || previous->getParse()->containsTag(MorphologicalTag::CARDINAL) || previous->getParse()->containsTag(MorphologicalTag::NUMBER))){
                        previous->setNamedEntityType("MONEY");
                    } else {
                        break;
                    }
                    j--;
                }
            }
        }
    }

}
