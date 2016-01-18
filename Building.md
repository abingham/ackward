# Building ackward #

## The Short Version ##

  * Copy custom.py.TEMPLATE to custom.py.
  * Modify custom.py to match your system.
  * Run scons.

## The Long Version ##

ackward is built using scons, so make sure you have a fairly recent version of scons installed. You can get scons at scons.org. If you’re running almost any modern linux distribution, you can probably get scons through your package management system.

Once you have scons, you’ll probably need to customize the build for your particular system. While it’s possible that your system perfectly matches the build defaults, it’s more likely that you’ll need to set something or the other. Build configuration is done by providing custom.py at the root of the build. There is a file custom.py.TEMPLATE in the source distribution; copy this to custom.py, edit it as needed, and that should be all of the customization you need.

Now you should be ready to build. From the root of the project (the directory containing SConstruct) just run:

`scons`

By default, this will make the release versions of the libs. To build the debug version, you can use:

`scons VARIANT=debug`

You can also run multiple build steps at once with the -jN options. For example, to run up to 4 build steps parallel (e.g. 4 compilations), use:

`scons -j4`

The various libraries will be built in their respective source directories, e.g. libackward\_uuid.so will be in ROOT/src/ackward/uuid and so forth.

## Testing ##

A normal build will also build a test program, src/test/ackward\_test. The simplest way to run this is from the project root:

`./src/test/ackward_test`

You can, of course, execute the test from anywhere, but you’ll need to set up your library search path manually in that case.