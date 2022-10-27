//
// Created by Olcay Taner Yıldız on 2019-04-26.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H
#define ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H

#include "Sentence.h"
#include "AnnotatedWord.h"
#include "FramesetList.h"
#include "Literal.h"
#include "WordNet.h"
#include "FsmMorphologicalAnalyzer.h"
#include "AnnotatedPhrase.h"
#include "FrameNet.h"

class AnnotatedSentence : public Sentence {
public:
    AnnotatedSentence() = default;
    explicit AnnotatedSentence(istream& inputFile);
    explicit AnnotatedSentence(const string& sentence);
    bool containsPredicate() const;
    bool containsFramePredicate() const;
    bool updateConnectedPredicate(const string& previousId, const string& currentId);
    vector<AnnotatedWord*> predicateCandidates(FramesetList& framesetList) const;
    vector<AnnotatedWord *> predicateFrameCandidates(FrameNet& frameNet) const;
    vector<AnnotatedPhrase*> getShallowParseGroups() const;
    string getPredicate(int index) const;
    string toStems() const;
    void removeWord(int index);
    ParserEvaluationScore compareParses(AnnotatedSentence* sentence) const;
    vector<Literal> constructLiterals(WordNet& wordNet, FsmMorphologicalAnalyzer& fsm, int wordIndex);
    vector<SynSet> constructSynSets(WordNet wordNet, FsmMorphologicalAnalyzer& fsm, int wordIndex);
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H
