cmake_minimum_required(VERSION 3.13)
project(AnnotatedSentence)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(AnnotatedSentence ViewLayerType.h AnnotatedWord.cpp AnnotatedWord.h AnnotatedSentence.cpp AnnotatedSentence.h)

target_link_libraries(AnnotatedSentence Dictionary MorphologicalAnalysis NamedEntityRecognition Propbank WordNet)