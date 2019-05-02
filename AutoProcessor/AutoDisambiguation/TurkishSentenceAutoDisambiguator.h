//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_TURKISHSENTENCEAUTODISAMBIGUATOR_H
#define ANNOTATEDSENTENCE_TURKISHSENTENCEAUTODISAMBIGUATOR_H


#include "SentenceAutoDisambiguator.h"

class TurkishSentenceAutoDisambiguator : public SentenceAutoDisambiguator{
public:
    TurkishSentenceAutoDisambiguator(FsmMorphologicalAnalyzer& morphologicalAnalyzer, RootWordStatistics& rootWordStatistics);
protected:
    void autoFillSingleAnalysis(AnnotatedSentence* sentence) override;
    void autoDisambiguateMultipleRootWords(AnnotatedSentence* sentence) override;
    void autoDisambiguateSingleRootWords(AnnotatedSentence* sentence) override;
private:
    void setParseAutomatically(FsmParseList fsmParseList, AnnotatedWord* word);
};


#endif //ANNOTATEDSENTENCE_TURKISHSENTENCEAUTODISAMBIGUATOR_H
