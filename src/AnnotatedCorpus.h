//
// Created by olcay on 2.05.2019.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H
#define ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H

#include "Dictionary/TxtDictionary.h"
#include <FsmMorphologicalAnalyzer.h>
#include <ParserEvaluationScore.h>
#include "Corpus.h"
class AnnotatedCorpus : public Corpus{
public:
    AnnotatedCorpus() = default;
    explicit AnnotatedCorpus(istream& inputFile);
    explicit AnnotatedCorpus(const string& folder);
    TxtDictionary createDictionary();
    ParserEvaluationScore compareParses(AnnotatedCorpus corpus);
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDCORPUS_H
