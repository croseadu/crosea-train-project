SET(SRC_LIST memory.c
             singleLinkList.c
             doubleLinkList.c
             stack.c
             map.c
             set.c
             circularQueue.c
             queue.c
	     utils.c
             )
ADD_LIBRARY(utils ${SRC_LIST})
