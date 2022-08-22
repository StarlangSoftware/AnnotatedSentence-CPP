cmake_minimum_required(VERSION 3.12.3)
project(AnnotatedSentence)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(AnnotatedSentence src/ViewLayerType.h src/AnnotatedWord.cpp src/AnnotatedWord.h src/AnnotatedSentence.cpp src/AnnotatedSentence.h src/AnnotatedCorpus.cpp src/AnnotatedCorpus.h src/AnnotatedPhrase.cpp src/AnnotatedPhrase.h src/Language.h)
add_executable(Test src/ViewLayerType.h src/AnnotatedWord.cpp src/AnnotatedWord.h src/AnnotatedSentence.cpp src/AnnotatedSentence.h src/AnnotatedCorpus.cpp src/AnnotatedCorpus.h src/AnnotatedPhrase.cpp src/AnnotatedPhrase.h Test/AnnotatedSentenceTest.cpp src/Language.h)
target_link_libraries(AnnotatedSentence ${CONAN_LIBS})
target_link_libraries(Test ${CONAN_LIBS})