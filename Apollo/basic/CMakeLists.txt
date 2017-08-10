add_executable(sorting sorting.c)
target_link_libraries(sorting utils)

add_executable(dataConversion dataConversion.c)
target_link_libraries(dataConversion utils)

add_executable(calc calExpression.c)
target_link_libraries(calc utils)

add_executable(polyAdd polyAdd.c)
target_link_libraries(polyAdd utils)

add_executable(maze maze.c)
target_link_libraries(maze utils)

add_executable(binaryTree binaryTree.c)
target_link_libraries(binaryTree utils)

add_executable(glist1 GList1.c)
target_link_libraries(glist1 utils)

add_executable(glist2 GList2.c)
target_link_libraries(glist2 utils)

add_executable(queen queen.c)
target_link_libraries(queen utils)

add_executable(directedGraph directedGraph.c)
target_link_libraries(directedGraph utils)


