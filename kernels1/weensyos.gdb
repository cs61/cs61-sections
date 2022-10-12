set $loaded = 1
set arch i386:x86-64
file obj/kernel.full
add-symbol-file obj/bootsector.full 0x7c00
add-symbol-file obj/p-hello.full 0x100000
add-symbol-file obj/p-bigdata.full 0x100000
add-symbol-file obj/p-alice.full 0x100000
add-symbol-file obj/p-eve.full 0x140000
add-symbol-file obj/p-spawn.full 0x140000
add-symbol-file obj/p-recurse.full 0x100000
add-symbol-file obj/p-pipewriter.full 0x100000
add-symbol-file obj/p-pipereader.full 0x140000
target remote localhost:12949
source build/functions.gdb
display/5i $pc
