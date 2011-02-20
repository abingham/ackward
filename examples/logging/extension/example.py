import logging, sys
import log_test

logging.basicConfig(stream=sys.stdout)
l = logging.getLogger()
log_test.log_message(l, "This gets logged by the C++ extension module.")
