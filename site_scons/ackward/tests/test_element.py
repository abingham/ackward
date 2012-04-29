import unittest

from ..element import Element

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

if __name__ == '__main__':
    unittest.main()