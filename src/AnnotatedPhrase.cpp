//
// Created by Olcay Taner YILDIZ on 2020-01-17.
//

#include "AnnotatedPhrase.h"

/**
 * Constructor for AnnotatedPhrase. AnnotatedPhrase stores information about phrases such as
 * Shallow Parse phrases or named entity phrases.
 * @param wordIndex Starting index of the first word in the phrase w.r.t. original sentence the phrase occurs.
 * @param tag Tag of the phrase. Corresponds to the shallow parse or named entity tag.
 */
AnnotatedPhrase::AnnotatedPhrase(int wordIndex, string tag) {
    this->wordIndex = wordIndex;
    this->tag = move(tag);
}

/**
 * Accessor for the wordIndex attribute.
 * @return Starting index of the first word in the phrase w.r.t. original sentence the phrase occurs.
 */
int AnnotatedPhrase::getWordIndex() {
    return this->wordIndex;
}

/**
 * Accessor for the tag attribute.
 * @return Tag of the phrase. Corresponds to the shallow parse or named entity tag.
 */
string AnnotatedPhrase::getTag() {
    return this->tag;
}
