# Lab 1 - Recursion

This repository is built with [Bazel](https://bazel.build)!

This BUILD file shows that we want to build a C++ binary using the ```cc_binary``` rule provided by Bazel.
In the ```cc_binary``` rule, name of the binary is specified in ```name``` attribute (in this example, it's ```hello-world```), required source files to be built are provided in ```srcs``` attribute.

```bzl
cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
)
```

To build this example, use

```bzl
bazel build //main:hello-world
```

If the build is successful, Bazel prints the output similar to

```bzl
____Loading complete.  Analyzing...
____Found 1 target...
____Building...
Target //main:hello-world up-to-date:
  C:/tools/msys64/tmp/_bazel_woden/vqeu6v3v/execroot/__main__/bazel-out/msvc_x64-fastbuild/bin/main/hello-world.exe
____Elapsed time: 0,400s, Critical Path: 0,01s
```

In the run log above you can see where the executable was built so you can locate it and use it.

You can also get the output path with the bazel cquery command. For
example, the command below would print the path to the output file. This
is a useful technique for use in scripts, where you do not want to parse the
`bazel build` output.

```bzl
bazel cquery --output=starlark \
  --starlark:expr="' '.join([f.path for f in target.files.to_list()])" \
  //main:hello-world
```
