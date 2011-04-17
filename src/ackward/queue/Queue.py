from ackward import (Class,
                     Function,
                     method,
                     Module,
                     Namespace,
                     TranslationUnit)

def modname(env):
    if env['PYTHON_VERSION'] == 2:
        return 'Queue'
    else:
        return 'queue'

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_QUEUE_QUEUE_HPP',
        impl_includes=[('ackward', 'queue', 'Queue.hpp')],
        )

def queueClass(env, qtype):
    with Class(name=qtype,
               wrapped_class='{0}.{1}'.format(modname(env), qtype)):

        method('unsigned int qsize() const')
        # method('bool empty() const')

        method('void put(boost::python::object item)')
        method('void put(boost::python::object item, bool block)')
        method('void put(boost::python::object item, bool block, unsigned int timeout)')

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'queue'):
            
            Module(name=modname(env))

            for qtype in ['Queue', 'LifoQueue', 'PriorityQueue']:

                queueClass(env, qtype)

                Function(
                    name='make{0}'.format(qtype),
                    return_type='Queue',
                    signature=[('int', 'maxsize')],
                    python_name='Queue')

    return t

# Queue.full()
#     Return True if the queue is full, False otherwise. If full() returns True it doesnt guarantee that a subsequent call to get() will not block. Similarly, if full() returns False it doesnt guarantee that a subsequent call to put() will not block.

# Queue.put(item[, block[, timeout]])
#     Put item into the queue. If optional args block is true and timeout is None (the default), block if necessary until a free slot is available. If timeout is a positive number, it blocks at most timeout seconds and raises the Full exception if no free slot was available within that time. Otherwise (block is false), put an item on the queue if a free slot is immediately available, else raise the Full exception (timeout is ignored in that case).

# Queue.put_nowait(item)
#     Equivalent to put(item, False).

# Queue.get([block[, timeout]])
#     Remove and return an item from the queue. If optional args block is true and timeout is None (the default), block if necessary until an item is available. If timeout is a positive number, it blocks at most timeout seconds and raises the Empty exception if no item was available within that time. Otherwise (block is false), return an item if one is immediately available, else raise the Empty exception (timeout is ignored in that case).

# Queue.get_nowait()
#     Equivalent to get(False).

# Two methods are offered to support tracking whether enqueued tasks have been fully processed by daemon consumer threads.

# Queue.task_done()

#     Indicate that a formerly enqueued task is complete. Used by queue consumer threads. For each get() used to fetch a task, a subsequent call to task_done() tells the queue that the processing on the task is complete.

#     If a join() is currently blocking, it will resume when all items have been processed (meaning that a task_done() call was received for every item that had been put() into the queue).

#     Raises a ValueError if called more times than there were items placed in the queue.

# Queue.join()

#     Blocks until all items in the queue have been gotten and processed.

#     The count of unfinished tasks goes up whenever an item is added to the queue. The count goes down whenever a consumer thread calls task_done() to indicate that the item was retrieved and all work on it is complete. When the count of unfinished tasks drops to zero, join() unblocks.