SET(SRC_LIST testSingleLinkList.c)
ADD_EXECUTABLE(testSingleLinkList ${SRC_LIST})
TARGET_LINK_LIBRARIES(testSingleLinkList utils)
