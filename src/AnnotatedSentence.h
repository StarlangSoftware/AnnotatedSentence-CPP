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
    bool updateConnectedPredicate(const string& previousId, const string& currentId) const;
    vector<AnnotatedWord*> predicateCandidates(FramesetList& framesetList) const;
    vector<AnnotatedWord *> predicateFrameCandidates(FrameNet& frameNet) const;
    vector<AnnotatedPhrase*> getShallowParseGroups() const;
    string getPredicate(int index) const;
    string toStems() const;
    void removeWord(int index);
    ParserEvaluationScore compareParses(const AnnotatedSentence* sentence) const;
    vector<Literal> constructLiterals(const WordNet& wordNet, const FsmMorphologicalAnalyzer& fsm, int wordIndex) const;
    vector<SynSet> constructSynSets(WordNet& wordNet, const FsmMorphologicalAnalyzer& fsm, int wordIndex) const;
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H
