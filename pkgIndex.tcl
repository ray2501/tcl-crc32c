# -*- tcl -*-
# Tcl package index file, version 1.1
#
if {[package vsatisfies [package provide Tcl] 9.0-]} {
    package ifneeded crc32c 0.1 \
	    [list load [file join $dir libtcl9crc32c0.1.so] [string totitle crc32c]]
} else {
    package ifneeded crc32c 0.1 \
	    [list load [file join $dir libcrc32c0.1.so] [string totitle crc32c]]
}
