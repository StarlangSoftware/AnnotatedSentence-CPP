//
// Created by Olcay Taner YILDIZ on 2020-01-17.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDPHRASE_H
#define ANNOTATEDSENTENCE_ANNOTATEDPHRASE_H


#include <Sentence.h>

class AnnotatedPhrase : public Sentence {
private:
    int wordIndex;
    string tag;
public:
    AnnotatedPhrase(int wordIndex, const string& tag);
    int getWordIndex() const;
    string getTag() const;
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDPHRASE_H
