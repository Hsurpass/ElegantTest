# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: test.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from demo.proto import person_pb2 as demo_dot_proto_dot_person__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\ntest.proto\x1a\x17\x64\x65mo/proto/person.proto\"(\n\x04Test\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x12\n\x01p\x18\x02 \x01(\x0b\x32\x07.Personb\x06proto3')



_TEST = DESCRIPTOR.message_types_by_name['Test']
Test = _reflection.GeneratedProtocolMessageType('Test', (_message.Message,), {
  'DESCRIPTOR' : _TEST,
  '__module__' : 'test_pb2'
  # @@protoc_insertion_point(class_scope:Test)
  })
_sym_db.RegisterMessage(Test)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _TEST._serialized_start=39
  _TEST._serialized_end=79
# @@protoc_insertion_point(module_scope)
