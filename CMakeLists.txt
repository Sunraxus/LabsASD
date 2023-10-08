# CMakeList.txt: проект CMake для Labs1ASD; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Labs1ASD")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Labs1ASD "Labs1ASD.cpp" "Labs1ASD.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Labs1ASD PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
