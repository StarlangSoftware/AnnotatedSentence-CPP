//
// Created by Olcay Taner YILDIZ on 8.01.2021.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../AnnotatedSentence.h"

TEST_CASE("AnnotatedSentenceTest-testGetShallowParseGroups") {
    AnnotatedSentence *sentence0, *sentence1, *sentence2, *sentence3, *sentence4;
    AnnotatedSentence *sentence5, *sentence6, *sentence7, *sentence8, *sentence9;
    ifstream inputFile;
    inputFile.open("sentences/0000.dev", ifstream::in);
    sentence0 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0001.dev", ifstream::in);
    sentence1 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0002.dev", ifstream::in);
    sentence2 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0003.dev", ifstream::in);
    sentence3 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0004.dev", ifstream::in);
    sentence4 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0005.dev", ifstream::in);
    sentence5 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0006.dev", ifstream::in);
    sentence6 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0007.dev", ifstream::in);
    sentence7 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0008.dev", ifstream::in);
    sentence8 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0009.dev", ifstream::in);
    sentence9 = new AnnotatedSentence(inputFile);
    inputFile.close();
    REQUIRE(4 == sentence0->getShallowParseGroups().size());
    REQUIRE(5 == sentence1->getShallowParseGroups().size());
    REQUIRE(3 == sentence2->getShallowParseGroups().size());
    REQUIRE(5 == sentence3->getShallowParseGroups().size());
    REQUIRE(5 == sentence4->getShallowParseGroups().size());
    REQUIRE(5 == sentence5->getShallowParseGroups().size());
    REQUIRE(6 == sentence6->getShallowParseGroups().size());
    REQUIRE(5 == sentence7->getShallowParseGroups().size());
    REQUIRE(5 == sentence8->getShallowParseGroups().size());
    REQUIRE(3 == sentence9->getShallowParseGroups().size());
}

TEST_CASE("AnnotatedSentenceTest-testContainsPredicate") {
    AnnotatedSentence *sentence0, *sentence1, *sentence2, *sentence3, *sentence4;
    AnnotatedSentence *sentence5, *sentence6, *sentence7, *sentence8, *sentence9;
    ifstream inputFile;
    inputFile.open("sentences/0000.dev", ifstream::in);
    sentence0 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0001.dev", ifstream::in);
    sentence1 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0002.dev", ifstream::in);
    sentence2 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0003.dev", ifstream::in);
    sentence3 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0004.dev", ifstream::in);
    sentence4 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0005.dev", ifstream::in);
    sentence5 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0006.dev", ifstream::in);
    sentence6 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0007.dev", ifstream::in);
    sentence7 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0008.dev", ifstream::in);
    sentence8 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0009.dev", ifstream::in);
    sentence9 = new AnnotatedSentence(inputFile);
    inputFile.close();
    REQUIRE_FALSE(!sentence0->containsPredicate());
    REQUIRE_FALSE(!sentence1->containsPredicate());
    REQUIRE_FALSE(sentence2->containsPredicate());
    REQUIRE_FALSE(!sentence3->containsPredicate());
    REQUIRE_FALSE(!sentence4->containsPredicate());
    REQUIRE_FALSE(sentence5->containsPredicate());
    REQUIRE_FALSE(sentence6->containsPredicate());
    REQUIRE_FALSE(!sentence7->containsPredicate());
    REQUIRE_FALSE(!sentence8->containsPredicate());
    REQUIRE_FALSE(!sentence9->containsPredicate());
}

TEST_CASE("AnnotatedSentenceTest-testGetPredicate") {
    AnnotatedSentence *sentence0, *sentence1, *sentence3, *sentence4;
    AnnotatedSentence *sentence7, *sentence8, *sentence9;
    ifstream inputFile;
    inputFile.open("sentences/0000.dev", ifstream::in);
    sentence0 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0001.dev", ifstream::in);
    sentence1 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0003.dev", ifstream::in);
    sentence3 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0004.dev", ifstream::in);
    sentence4 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0007.dev", ifstream::in);
    sentence7 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0008.dev", ifstream::in);
    sentence8 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0009.dev", ifstream::in);
    sentence9 = new AnnotatedSentence(inputFile);
    inputFile.close();
    REQUIRE("bulandırdı" == sentence0->getPredicate(0));
    REQUIRE("yapacak" == sentence1->getPredicate(0));
    REQUIRE("ediyorlar" == sentence3->getPredicate(0));
    REQUIRE("yazmıştı" == sentence4->getPredicate(0));
    REQUIRE("olunacaktı" == sentence7->getPredicate(0));
    REQUIRE("gerekiyordu" == sentence8->getPredicate(0));
    REQUIRE("ediyor" == sentence9->getPredicate(0));
}

TEST_CASE("AnnotatedSentenceTest-testToStems") {
    AnnotatedSentence *sentence0, *sentence1, *sentence2, *sentence3, *sentence4;
    AnnotatedSentence *sentence5, *sentence6, *sentence7, *sentence8, *sentence9;
    ifstream inputFile;
    inputFile.open("sentences/0000.dev", ifstream::in);
    sentence0 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0001.dev", ifstream::in);
    sentence1 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0002.dev", ifstream::in);
    sentence2 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0003.dev", ifstream::in);
    sentence3 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0004.dev", ifstream::in);
    sentence4 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0005.dev", ifstream::in);
    sentence5 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0006.dev", ifstream::in);
    sentence6 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0007.dev", ifstream::in);
    sentence7 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0008.dev", ifstream::in);
    sentence8 = new AnnotatedSentence(inputFile);
    inputFile.close();
    inputFile.open("sentences/0009.dev", ifstream::in);
    sentence9 = new AnnotatedSentence(inputFile);
    inputFile.close();
    REQUIRE("devasa ölçek yeni kanun kullan karmaşık ve çetrefil dil kavga bulan ." == sentence0->toStems());
    REQUIRE("gelir art usul komite gel salı gün kanun tasarı hakkında bir duruşma yap ." == sentence1->toStems());
    REQUIRE("reklam ve tanıtım iş yara yara gör üzere ." == sentence2->toStems());
    REQUIRE("bu defa , daha da hız hareket et ." == sentence3->toStems());
    REQUIRE("shearson lehman hutton ınc. dün öğle sonra kadar yeni tv reklam yaz ." == sentence4->toStems());
    REQUIRE("bu kez , firma hazır ." == sentence5->toStems());
    REQUIRE("`` diyalog sür kesinlikle temel önem haiz ." == sentence6->toStems());
    REQUIRE("cuma gün bu üzerine düşün çok geç kal ol ." == sentence7->toStems());
    REQUIRE("bu hakkında önceden düşün gerek . ''" == sentence8->toStems());
    REQUIRE("isim göre çeşit göster birkaç kefaret fon reklam yap için devam et ." == sentence9->toStems());
}
