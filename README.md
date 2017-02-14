# embedded python sample

compile sample 1

```
$ gcc `/usr/local/bin/python-config --cflags` `/usr/local/bin/python-config --ldflags`  call_function.c
```

run

```
$ ./a.out py_function multiply
```

---

compile sample 2

```
$ gcc `/usr/local/bin/python-config --cflags` `/usr/local/bin/python-config --ldflags`  call_function_withstr.c
```

run ( 3rd arg will ignored in this version.)
```
$ ./a.out py_function withstr "sometext"
```
