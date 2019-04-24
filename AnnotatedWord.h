//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDWORD_H
#define ANNOTATEDSENTENCE_ANNOTATEDWORD_H

#include <Word.h>
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <NamedEntityType.h>
#include <Argument.h>

class AnnotatedWord : public Word{
private:
    MorphologicalParse parse;
    MetamorphicParse metamorphicParse;
    string semantic;
    NamedEntityType namedEntityType;
    Argument argument = Argument("");
    string shallowParse;
public:
    explicit AnnotatedWord(string word);
    AnnotatedWord(string name, NamedEntityType namedEntityType);
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDWORD_H
