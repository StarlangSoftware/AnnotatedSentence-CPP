cmake_minimum_required(VERSION 3.12.3)
project(AnnotatedSentence)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(AnnotatedSentence ViewLayerType.h AnnotatedWord.cpp AnnotatedWord.h AnnotatedSentence.cpp AnnotatedSentence.h AnnotatedCorpus.cpp AnnotatedCorpus.h AnnotatedPhrase.cpp AnnotatedPhrase.h Language.h)
add_executable(Test ViewLayerType.h AnnotatedWord.cpp AnnotatedWord.h AnnotatedSentence.cpp AnnotatedSentence.h AnnotatedCorpus.cpp AnnotatedCorpus.h AnnotatedPhrase.cpp AnnotatedPhrase.h Test/AnnotatedSentenceTest.cpp Language.h)

target_link_libraries(AnnotatedSentence Corpus XmlParser Dictionary MorphologicalAnalysis NamedEntityRecognition Propbank WordNet MorphologicalDisambiguation DependencyParser FrameNet SentiNet)
target_link_libraries(Test Corpus XmlParser Dictionary MorphologicalAnalysis NamedEntityRecognition Propbank WordNet MorphologicalDisambiguation DependencyParser FrameNet SentiNet)