//
// Created by Olcay Taner Yıldız on 2019-04-26.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H
#define ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H

#include "Sentence.h"

class AnnotatedSentence : public Sentence {
public:
    AnnotatedSentence() = default;
    explicit AnnotatedSentence(istream& inputFile);
    explicit AnnotatedSentence(string sentence);
    bool containsPredicate();
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDSENTENCE_H
