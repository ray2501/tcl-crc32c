# tcl-crc32c

Tcl bindings for [crc32c](https://github.com/google/crc32c) library.


License
=====

MIT


Commands
=====

crc32c::value data  
crc32c::extend value data


UNIX BUILD
=====

I only test tcl-crc32c under openSUSE LEAP 15.1.

Users need install crc32c library and development files first.

Building under most UNIX systems is easy, just run the configure script
and then run make. For more information about the build process, see the
tcl/unix/README file in the Tcl src dist. The following minimal example
will install the extension in the /opt/tcl directory.

        $ cd tcl-crc32c
        $ ./configure --prefix=/opt/tcl
        $ make
        $ make install

If you need setup directory containing tcl configuration (tclConfig.sh),
below is an example:

        $ cd tcl-crc32c
        $ ./configure --with-tcl=/opt/activetcl/lib
        $ make
        $ make install

Example
=====

Below is an example:

        package require crc32c
        set value [crc32c::value "tcl-crc32c"]

