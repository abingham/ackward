from ackward import (Class,
                     Function,
                     InlineFunction,
                     method,
                     Module,
                     Namespace,
                     TranslationUnit)

queue_doc = '''\\rst
A wrapper for {0} objects in the ``queue`` module. See `<http://docs.python.org/py3k/library/queue.html#queue-objects>`_.
\\endrst'''
qsize_doc = '''Return the approximate size of the queue. Note, qsize() > 0 doesn't
guarantee that a subsequent get() will not block, nor will qsize() <
maxsize guarantee that put() will not block.

\\rst
See `<http://docs.python.org/py3k/library/queue.html#queue.Queue.qsize>`_.
\\endrst

@return The current size of the queue.
'''

put_doc = '''
Put item into the queue.

\\rst
See `<http://docs.python.org/py3k/library/queue.html#queue.Queue.put>`_.
\\endrst

@param item The item to place in the queue.
{0}
@throws ackward::queue::Full There is no space in the queue.
'''

get_doc = '''
Remove and return an item from the queue.

\\rst
See `<http://docs.python.org/py3k/library/queue.html#queue.Queue.get>`_.
\\endrst

{0}
@return The item retrieved from the queue.
@throws ackward::queue::Empty The queue is empty.
'''

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

def queueClass(env, qtype, parent):
    cls = Class(name=qtype,
                wrapped_class='{0}.{1}'.format(modname(env), qtype),
                parent=parent,
                doc=queue_doc.format(qtype))

    method('unsigned int qsize() const',
           parent=cls).doc = qsize_doc
    # method('bool empty() const')

    # put
    InlineFunction('''
template <typename T>
void put(const T& t) {
  try { obj().attr("put")(t); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = put_doc.format('')

    InlineFunction('''
template <typename T>
void put(const T& t, bool block) {
  try { obj().attr("put")(t, block); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = put_doc.format(
        '@param block Whether to block until the queue has space.')

    InlineFunction('''
template <typename T>
void put(const T& t, bool block, unsigned int timeout) {
  try { obj().attr("put")(t, block, timeout); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = put_doc.format(
        '''@param block Whether to block until the queue has space.
        @param timeout How long to wait for queue to have space.''')

        # get
    InlineFunction('''
template <typename T>
T get() {
  try { return boost::python::extract<T>(obj().attr("get")()); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = get_doc.format('')

    InlineFunction('''
template <typename T>
T get(bool block) {
  try { return boost::python::extract<T>(obj().attr("get")(block)); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = get_doc.format(
        '@param block Whether to block until there\'s an item in the queue.')

    InlineFunction('''
template <typename T>
T get(bool block, unsigned int timeout) {
  try { return boost::python::extract<T>(obj().attr("get")(block, timeout)); }
  TRANSLATE_PYTHON_EXCEPTION()
}''',
    parent=cls).doc = get_doc.format(
        '''@param block Whether to block until there\'s an item in the queue.
        @param timeout How long to wait until there's an item in the queue.''')

    method('bool full() const',
           parent=cls).doc = 'Return True if the queue is full, False otherwise.'
    method('void task_done()',
           parent=cls).doc = 'Indicate that a formerly enqueued task is complete.'
    method('void join()',
           parent=cls).doc = 'Blocks until all items in the queue have been gotten and processed.'

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'queue', parent=t)

    Module(name=modname(env), parent=ns)

    for qtype in ['Queue', 'LifoQueue', 'PriorityQueue']:

        queueClass(env, qtype, parent=ns)

        Function(
            name='make{0}'.format(qtype),
            return_type='Queue',
            signature=[('int', 'maxsize')],
            python_name='Queue',
            parent=ns)

    return t
