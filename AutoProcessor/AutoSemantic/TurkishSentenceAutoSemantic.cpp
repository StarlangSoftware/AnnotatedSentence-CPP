//
// Created by olcay on 2.05.2019.
//

#include "TurkishSentenceAutoSemantic.h"

TurkishSentenceAutoSemantic::TurkishSentenceAutoSemantic(WordNet &turkishWordNet, FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

void TurkishSentenceAutoSemantic::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    AnnotatedWord* twoPrevious = nullptr, *previous = nullptr, *current, *twoNext = nullptr, *next = nullptr;
    for (int i = 0; i < sentence->wordCount(); i++){
        current = (AnnotatedWord*) sentence->getWord(i);
        if (i > 1){
            twoPrevious = (AnnotatedWord*) sentence->getWord(i - 2);
        }
        if (i > 0){
            previous = (AnnotatedWord*) sentence->getWord(i - 1);
        }
        if (i != sentence->wordCount() - 1){
            next = (AnnotatedWord*) sentence->getWord(i + 1);
        }
        if (i < sentence->wordCount() - 2){
            twoNext = (AnnotatedWord*) sentence->getWord(i + 2);
        }
        if (current->getSemantic().empty() && current->getParse() != nullptr){
            if (twoPrevious != nullptr && twoPrevious->getParse() != nullptr && previous->getParse() != nullptr){
                vector<SynSet> idioms = turkishWordNet.constructIdiomSynSets(*(twoPrevious->getParse()), *(previous->getParse()), *(current->getParse()), *(twoPrevious->getMetamorphicParse()), *(previous->getMetamorphicParse()), *(current->getMetamorphicParse()), fsm);
                if (idioms.size() == 1){
                    current->setSemantic(idioms.at(0).getId());
                    continue;
                }
            }
            if (previous != nullptr && previous->getParse() != nullptr && next != nullptr && next->getParse() != nullptr){
                vector<SynSet> idioms = turkishWordNet.constructIdiomSynSets(*(previous->getParse()), *(current->getParse()), *(next->getParse()), *(previous->getMetamorphicParse()), *(current->getMetamorphicParse()), *(next->getMetamorphicParse()), fsm);
                if (idioms.size() == 1){
                    current->setSemantic(idioms.at(0).getId());
                    continue;
                }
            }
            if (next != nullptr && next->getParse() != nullptr && twoNext != nullptr && twoNext->getParse() != nullptr){
                vector<SynSet> idioms = turkishWordNet.constructIdiomSynSets(*(current->getParse()), *(next->getParse()), *(twoNext->getParse()), *(current->getMetamorphicParse()), *(next->getMetamorphicParse()), *(twoNext->getMetamorphicParse()), fsm);
                if (idioms.size() == 1){
                    current->setSemantic(idioms.at(0).getId());
                    continue;
                }
            }
            if (previous != nullptr && previous->getParse() != nullptr){
                vector<SynSet> idioms = turkishWordNet.constructIdiomSynSets(*(previous->getParse()), *(current->getParse()), *(previous->getMetamorphicParse()), *(current->getMetamorphicParse()), fsm);
                if (idioms.size() == 1){
                    current->setSemantic(idioms.at(0).getId());
                    continue;
                }
            }
            if (current->getSemantic().empty() && next != nullptr && next->getParse() != nullptr){
                vector<SynSet> idioms = turkishWordNet.constructIdiomSynSets(*(current->getParse()), *(next->getParse()), *(current->getMetamorphicParse()), *(next->getMetamorphicParse()), fsm);
                if (idioms.size() == 1){
                    current->setSemantic(idioms.at(0).getId());
                    continue;
                }
            }
            vector<SynSet> meanings = turkishWordNet.constructSynSets(current->getParse()->getWord()->getName(), *(current->getParse()), *(current->getMetamorphicParse()), fsm);
            if (current->getSemantic().empty() && meanings.size() == 1){
                current->setSemantic(meanings.at(0).getId());
            }
        }
    }
}
