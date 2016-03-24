add_executable(bubbleSort bubbleSort.c)
target_link_libraries(bubbleSort utils)

add_executable(selectionSort selectionSort.c)
target_link_libraries(selectionSort utils)

add_executable(insertSort insertSort.c)
target_link_libraries(insertSort utils)

#add_executable(mergeSort mergetSort.c)
#target_link_libraries(mergetSort utils)

#add_executable(heapSort heapSort.c)
#target_link_libraries(heapSort utils)

#add_executable(shellInsertSort shellInsertSort.c)
#target_link_libraries(shellInsertSort utils)

