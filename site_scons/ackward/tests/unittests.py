import unittest

from ..element import Element
from ..method import Method
from ..translate import process

from . import scratch

class ElementTest(unittest.TestCase):
    def test_constructor(self):
        e = Element()
        self.assertEqual(len(e.children), 0)
        self.assertEqual(len(e.symbols), 0)
        self.assertEqual(e.doc, None)

    def test_open_phase(self):
        e = Element()
        self.assertEqual(
            list(e.open_phase(scratch,
                              'test_phase',
                              {})),
            [''])

    def test_close_phase(self):
        e = Element()
        self.assertEqual(
            list(e.close_phase(scratch,
                               'test_phase',
                               {})),
            [''])

class MethodTest(unittest.TestCase):
    def _process(self, m):
        print(
            list(process(m, scratch, 'header',
                         {'class_name': 'MethodTest'})),
            list(process(m, scratch, 'impl',
                         {'class_name': 'MethodTest'})))

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

if __name__ == '__main__':
    unittest.main()