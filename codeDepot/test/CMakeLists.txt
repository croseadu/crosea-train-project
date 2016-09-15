add_executable(testSingleLinkList testSingleLinkList.c)
target_link_libraries(testSingleLinkList utils)

ADD_EXECUTABLE(testVector testVector.c)
target_link_libraries(testVector utils)

ADD_EXECUTABLE(testMap testMap.c)
target_link_libraries(testMap utils)


ADD_EXECUTABLE(testDoubleLinkList testDoubleLinkList.c)
target_link_libraries(testDoubleLinkList utils)
