md ..\pbsrc
protoc.exe -I. --cpp_out=../pbsrc addressbook.proto
protoc.exe -I. --cpp_out=../pbsrc person.proto
protoc.exe -I. --cpp_out=../pbsrc SDPath.proto
protoc.exe -I. --cpp_out=../pbsrc testChinese.proto
protoc.exe -I. --cpp_out=../pbsrc testoneof.proto