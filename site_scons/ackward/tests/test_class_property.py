import unittest

from ..class_property import ClassProperty
from ..translate import process

from . import scratch

class TestClassProperty(unittest.TestCase):
    def _process(self, m):
        list(process(m, scratch, 'header',
                     {'class_name': 'MethodTest'}))
        list(process(m, scratch, 'impl',
                     {'class_name': 'MethodTest'}))

    def test_simple(self):
        m = ClassProperty('foo', 'int')
        self._process(m)

    def test_read_only(self):
        m = ClassProperty('bar', 'float',
                          read_only=True)
        self._process(m)

if __name__ == '__main__':
    unittest.main()