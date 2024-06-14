# rpath-example

Toy project to show how `rpath`, `$ORIGIN` and `LD_DEBUG` work.

Usage:
```
mkdir    bin
mkdir -p lib/sublib

g++ -shared -fPIC src/func2.cpp -o lib/sublib/libfunc2.so
g++ -shared -fPIC src/func1.cpp -o lib/libfunc1.so -Llib/sublib/ -lfunc2 -Wl,-rpath,'$ORIGIN/sublib'
g++ src/main.cpp -o ./bin/a.out -L./lib/ -lfunc1 -Wl,-rpath,'$ORIGIN/../lib'
```

Note that libfunc1 sees func2 relative to itself, and that main only needs to know about func1.
`a.out` now works from anywhere, without needing `LD_LIBRARY_PATH`:
```
./bin/a.out
```

Several ways to check what happened:
```
readelf -d ./bin/a.out |head -n 10
readelf -d ./lib64/libfunc1.so |head -n 10
```

On multi-arch, it is sometimes desirable to use `lib`, `lib64` or `lib/x86_64-linux-gnu`.
`rpath` uses `$LIB` for that purpose:
```
libdir=lib64  # or lib/x86_64-linux-gnu
mkdir    bin
mkdir -p $libdir/sublib

g++ -shared -fPIC src/func2.cpp -o $libdir/sublib/libfunc2.so
g++ -shared -fPIC src/func1.cpp -o $libdir/libfunc1.so -L$libdir/sublib/ -lfunc2 -Wl,-rpath,'$ORIGIN/sublib'
g++ src/main.cpp -o ./bin/a.out -L./$libdir/ -lfunc1 -Wl,-rpath,'$ORIGIN/../$LIB'
```

`$LIB` is specific to every distro:
- on RHEL-8 is is `lib64`,
- on Ubuntu-20 it is `lib/x86_64-linux-gnu`.

In case of doubt, double check with:
```
LD_DEBUG=libs ./bin/a.out
```

`LD_DEBUG=help ./bin/a.out` shows other interesting options.

To play with `R[UN]PATH`, without recompiling:
```
patchelf --set-rpath '$ORIGIN/sublib' my_lib.so
```

You may like `realpath -s --relative-to=path/to/my/program path/to/my/library` in the previous command.

