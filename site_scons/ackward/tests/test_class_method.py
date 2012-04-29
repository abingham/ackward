import unittest

from ..class_method import ClassMethod, class_method

from . import scratch

class ClassMethodTest(unittest.TestCase):
    def _process(self, m):
        list(m.process(
            scratch, 'header',
            {'class_name': 'MethodTest'}))
        list(m.process(
            scratch, 'impl',
            {'class_name': 'MethodTest'}))

    def test_simple(self):
        m = ClassMethod('foo')
        self._process(m)

    def test_return_type(self):
        m = ClassMethod(
            'foo',
            return_type='float')
        self._process(m)

    def test_signature(self):
        m = ClassMethod(
            'foo',
            signature=(('int', 'x'), ('Widget', 'parent')))
        self._process(m)

    def test_python_name(self):
        m = ClassMethod(
            'foo',
            python_name='jones')
        self._process(m)

    def test_all(self):
        m = ClassMethod(
            'foo',
            return_type='double',
            signature=(('Llama', 'llama'),),
            python_name='yak')
        self._process(m)

    def test_class_method(self):
        m = class_method('char* jones(Monkey m, float x)')

if __name__ == '__name__':
    unittest.main()