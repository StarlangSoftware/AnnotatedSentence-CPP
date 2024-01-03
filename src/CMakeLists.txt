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

add_library(AnnotatedSentence ViewLayerType.h AnnotatedWord.cpp AnnotatedWord.h AnnotatedSentence.cpp AnnotatedSentence.h AnnotatedCorpus.cpp AnnotatedCorpus.h AnnotatedPhrase.cpp AnnotatedPhrase.h Language.h)
target_link_libraries(AnnotatedSentence word_net::word_net dependency_parser::dependency_parser frame_net::frame_net named_entity_recognition::named_entity_recognition prop_bank::prop_bank senti_net::senti_net)
