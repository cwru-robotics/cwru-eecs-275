# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from kobuki_msgs/WheelDropEvent.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class WheelDropEvent(genpy.Message):
  _md5sum = "e102837d89384d67669a0df86b63f33b"
  _type = "kobuki_msgs/WheelDropEvent"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# Provides a wheel drop event.
# This message is generated whenever one of the wheels is dropped (robot fell
# or was raised) or raised (normal condition).
# Note that, despite wheel_drop field on SensorState messages, state field is
# not a bitmask, but the new state of a single sensor.

# wheel
uint8 LEFT  = 0
uint8 RIGHT = 1

# state
uint8 RAISED  = 0
uint8 DROPPED = 1

uint8 wheel
uint8 state

"""
  # Pseudo-constants
  LEFT = 0
  RIGHT = 1
  RAISED = 0
  DROPPED = 1

  __slots__ = ['wheel','state']
  _slot_types = ['uint8','uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       wheel,state

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(WheelDropEvent, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.wheel is None:
        self.wheel = 0
      if self.state is None:
        self.state = 0
    else:
      self.wheel = 0
      self.state = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2B.pack(_x.wheel, _x.state))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.wheel, _x.state,) = _struct_2B.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2B.pack(_x.wheel, _x.state))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.wheel, _x.state,) = _struct_2B.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2B = struct.Struct("<2B")
