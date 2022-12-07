# rpath-example

Toy project to show how rpath works

```

mkdir    bin
mkdir -p lib64/sub

g++ -shared -fPIC src/func2.cpp -o lib/sublib/libfunc2.so
g++ -shared -fPIC src/func1.cpp -o lib/libfunc1.so -Llib/sublib/ -lfunc2 -Wl,-rpath,'$ORIGIN/sublib'
g++ src/main.cpp -o ./bin/a.out -L./lib/ -lfunc1 -Wl,-rpath,'$ORIGIN/../$LIB'
```
`a.out` now works from anywhere, without needing `LD_LIBRARY_PATH`.
```
readelf -d ./bin/a.out |head -n 10
./bin/a.out

