//
// Created by olcay on 2.05.2019.
//

#include <iostream>
#include "AnnotatedCorpus.h"
#include "AnnotatedSentence.h"

int main(){
    AnnotatedCorpus corpus = AnnotatedCorpus("../../../Penn-Treebank/Turkish-Phrase", "fileList.txt");
    cout << ((AnnotatedSentence*) corpus.getSentence(1))->toStems();
}