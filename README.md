
# 동적 라이브러리 vs 정적 라이브러리
- 동적 라이브러리: .so
  : 라이브러리가 변경되어도, 다시 컴파일할 필요가 없다.

- 정적 라이브러리: .a
  : 라이브버리가 실행 파일에 포함되어, 빌드되기 때문에, 라이브러리가 변경되면,
    새롭게 빌드해야 한다.
   - 구글 테스트는 정적 라이브러리 빌드를 권장하고 있습니다.


# Google Test 라이브러리 빌드 방법 - 1
```
$ g++ googletest/googletest/src/gtest-all.cc -I googletest/googletest/include/ -I googletest/googletest/ -c
$ ar rcv libgtest.a gtest-all.o
$ g++ main.cpp -lgtest -L. -Igoogletest/googletest/include/ -pthread

```

# Google Test 라이브러리 빌드 방법 - 2
```
$ cd ./googletest/googletest/scripts
$ ./fuse_gtest_files.py ~/chansik.yun/
$ cd ~/chansik.yun
$ g++ ./gtest/gtest-all.cc -c -I.
$ ar rcv libgtest.a gtest-all.o
$ g++ main.cpp -lgtest -L. -I. -pthread
```
