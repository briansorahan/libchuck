import os
from distutils.core import setup, Extension

os.environ['CC'] = 'g++'

module1 = Extension('pychuck',
                    language               = 'c++',
                    include_dirs           = [ '../src' ],
                    library_dirs           = [ '../src/.libs' ],
                    libraries              = [ 'chuck' ],
                    runtime_library_dirs   = [ '../src/.libs' ],
                    sources                = [ 'chuckmodule.cpp' ])

setup( name          = 'pychuck',
       version       = '0.0.1',
       description   = 'libchuck python module',
       author        = 'Brian Sorahan',
       author_email  = 'bsorahan@gmail.com',
       ext_modules   = [ module1 ])

