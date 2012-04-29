import unittest

from ..cls import Class

from . import scratch

class TestClass(unittest.TestCase):
    def _process(self, m):
        list(m.process(
            scratch, 'header',
            {'class_name': 'MethodTest'}))
        list(m.process(
            scratch, 'impl',
            {'class_name': 'MethodTest'}))

    def test_simple(self):
        c = Class('Jones', 'names.Jones')
        self._process(c)

    def test_bases(self):
        c = Class('TestBases', 'test.Bases',
                  bases=['private core::Object',
                         'public Smurfable'])
        self._process(c)

if __name__ == '__main__':
    unittest.main()