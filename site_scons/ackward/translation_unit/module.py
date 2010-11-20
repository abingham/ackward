import string
from ..util import trace

impl_template = '''namespace {

object module()
{
  static object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = import("$module_name");
    initialized = true;
  }

  return mod;
}

}'''

@trace
def generate(mod):
    tmpl = string.Template(impl_template)
    return tmpl.substitute({'module_name' : mod})
