SET(SRC_LIST testDoubleLinkList.c)
ADD_EXECUTABLE(testDoubleLinkList ${SRC_LIST})
TARGET_LINK_LIBRARIES(testDoubleLinkList utils)
