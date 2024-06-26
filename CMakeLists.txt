cmake_minimum_required(VERSION 3.12.3)
project(AnnotatedSentence)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(word_net REQUIRED)
find_package(dependency_parser REQUIRED)
find_package(frame_net REQUIRED)
find_package(named_entity_recognition REQUIRED)
find_package(prop_bank REQUIRED)
find_package(senti_net REQUIRED)

add_library(AnnotatedSentence src/ViewLayerType.h src/AnnotatedWord.cpp src/AnnotatedWord.h src/AnnotatedSentence.cpp src/AnnotatedSentence.h src/AnnotatedCorpus.cpp src/AnnotatedCorpus.h src/AnnotatedPhrase.cpp src/AnnotatedPhrase.h src/Language.h)
add_executable(Test src/ViewLayerType.h src/AnnotatedWord.cpp src/AnnotatedWord.h src/AnnotatedSentence.cpp src/AnnotatedSentence.h src/AnnotatedCorpus.cpp src/AnnotatedCorpus.h src/AnnotatedPhrase.cpp src/AnnotatedPhrase.h Test/AnnotatedSentenceTest.cpp src/Language.h)
target_link_libraries(AnnotatedSentence word_net::word_net dependency_parser::dependency_parser frame_net::frame_net named_entity_recognition::named_entity_recognition prop_bank::prop_bank senti_net::senti_net)
target_link_libraries(Test word_net::word_net dependency_parser::dependency_parser frame_net::frame_net named_entity_recognition::named_entity_recognition prop_bank::prop_bank senti_net::senti_net)