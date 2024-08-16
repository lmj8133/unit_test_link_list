# Build

Choose one to build your project, either qmake or cmake.

## qmake

```mkdir build```

```git clone https://github.com/google/googletest.git build/_deps/googletest-src```

```cp gtest_dependency.pri build/_deps/googletest-src/gtest_dependency.pri```

**Qt Creater**

- press ```Build```-> ```Run qmake```

- press ```Start debugging of startup project``` to run googletest

## CMake

```mkdir build```

```cd build```

```cmake ..; make```

```ctest``` to run googletest
