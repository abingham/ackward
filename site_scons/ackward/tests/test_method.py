import unittest

from ..method import Method, method

from . import scratch

class MethodTest(unittest.TestCase):
    def _process(self, m):
        list(m.process(
            scratch, 'header',
            {'class_name': 'MethodTest'}))
        list(m.process(
            scratch, 'impl',
            {'class_name': 'MethodTest'}))

    def test_simple(self):
        '''Verify that it runs at all.'''
        m = Method('testMethod')
        self._process(m)

    def test_return_type(self):
        m = Method('testMethod', return_type='int')
        self._process(m)

    def test_signature(self):
        m = Method(
            'testMethod',
            signature=(('int', 'x'),
                       ('Widget', 'w')))
        self._process(m)

    def test_const(self):
        m = Method(
            'testMethod',
            const=True)
        self._process(m)

    def test_python_name(self):
        m = Method(
            'testMethod',
            python_name='wombat')
        self._process(m)

    def test_virtual(self):
        m = Method(
            'testMethod',
            virtual=True)
        self._process(m)

    def test_method(self):
        m = method('virtual int foo() const')
        self._process(m)

if __name__ == '__main__':
    unittest.main()