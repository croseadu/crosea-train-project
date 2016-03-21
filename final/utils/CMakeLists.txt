SET(SRC_LIST memory.c
             singleLinkList.c
             doubleLinkList.c
             inOutHelper.c
             stack.c
             map.c
             set.c
             circularQueue.c
             staticLinkList.c
             queue.c
	     priorityQueue.c
	     utils.c
             )
ADD_LIBRARY(utils ${SRC_LIST})
