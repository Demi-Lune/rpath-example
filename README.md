# rpath-example

Toy project to show how rpath works

```
mkdir    bin
mkdir -p lib64/sublib

g++ -shared -fPIC src/func2.cpp -o lib64/sublib/libfunc2.so
g++ -shared -fPIC src/func1.cpp -o lib64/libfunc1.so -Llib64/sublib/ -lfunc2 -Wl,-rpath,'$ORIGIN/sublib'
g++ src/main.cpp -o ./bin/a.out -L./lib64/ -lfunc1 -Wl,-rpath,'$ORIGIN/../$LIB'
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
LD_DEBUG=libs ./bin/a.out
```

`LD_DEBUG=help ./bin/a.out` has many other options.
