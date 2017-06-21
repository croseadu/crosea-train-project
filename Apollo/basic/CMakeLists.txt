add_executable(sorting sorting.c)
target_link_libraries(sorting utils)

add_executable(dataConversion dataConversion.c)
target_link_libraries(dataConversion utils)

add_executable(calc calExpression.c)
target_link_libraries(calc utils)

add_executable(polyAdd polyAdd.c)
target_link_libraries(polyAdd utils)


