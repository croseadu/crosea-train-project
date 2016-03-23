add_executable(lineEdit lineEdit.c)
target_link_libraries(lineEdit utils)

add_executable(parenthesesMatch parenthesesMatching.c)
target_link_libraries(parenthesesMatch utils)

add_executable(calculator calculator.c)
target_link_libraries(calculator utils)


add_executable(decimalToBinary decimalToBinary.c)
target_link_libraries(decimalToBinary utils)
