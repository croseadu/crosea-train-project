add_executable(testQueue testQueue.c)
target_link_libraries(testQueue utils)

add_executable(testVector testVector.c)
target_link_libraries(testVector utils)

add_executable(testSingleLinkList testSingleLinkList.c)
target_link_libraries(testSingleLinkList utils)

add_executable(testDoubleLinkList testDoubleLinkList.c)
target_link_libraries(testDoubleLinkList utils)
