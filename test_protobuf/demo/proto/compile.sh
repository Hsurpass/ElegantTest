#!/usr/bin/bash

mkdir -p ../pbsrc
protoc -I. --cpp_out=../pbsrc addressbook.proto
protoc -I. --cpp_out=../pbsrc person.proto
protoc -I. --cpp_out=../pbsrc SDPath.proto
protoc -I. --cpp_out=../pbsrc testChinese.proto
protoc -I. --cpp_out=../pbsrc testoneof.proto