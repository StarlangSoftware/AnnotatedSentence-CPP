//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H
#define ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H

#include <TxtDictionary.h>
#include <FsmMorphologicalAnalyzer.h>
#include <RootWordStatistics.h>
#include <ParserEvaluationScore.h>
#include "Corpus.h"
class AnnotatedCorpus : public Corpus{
public:
    AnnotatedCorpus() = default;
    explicit AnnotatedCorpus(istream& inputFile);
    AnnotatedCorpus(string folder, string fileList);
    TxtDictionary createDictionary();
    RootWordStatistics extractRootWordStatistics(FsmMorphologicalAnalyzer fsm);
    ParserEvaluationScore compareParses(AnnotatedCorpus corpus);
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H
