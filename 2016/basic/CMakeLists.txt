ADD_EXECUTABLE(calculator expression.c)
TARGET_LINK_LIBRARIES(calculator utils)

ADD_EXECUTABLE(conversion conversion.c)
TARGET_LINK_LIBRARIES(conversion utils)
ADD_EXECUTABLE(polynomialAdd polynomialAdd.c)
TARGET_LINK_LIBRARIES(polynomialAdd utils)
