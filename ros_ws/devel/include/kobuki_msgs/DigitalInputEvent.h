// Generated by gencpp from file kobuki_msgs/DigitalInputEvent.msg
// DO NOT EDIT!


#ifndef KOBUKI_MSGS_MESSAGE_DIGITALINPUTEVENT_H
#define KOBUKI_MSGS_MESSAGE_DIGITALINPUTEVENT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace kobuki_msgs
{
template <class ContainerAllocator>
struct DigitalInputEvent_
{
  typedef DigitalInputEvent_<ContainerAllocator> Type;

  DigitalInputEvent_()
    : values()  {
      values.assign(false);
  }
  DigitalInputEvent_(const ContainerAllocator& _alloc)
    : values()  {
      values.assign(false);
  }



   typedef boost::array<uint8_t, 4>  _values_type;
  _values_type values;




  typedef boost::shared_ptr< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> const> ConstPtr;

}; // struct DigitalInputEvent_

typedef ::kobuki_msgs::DigitalInputEvent_<std::allocator<void> > DigitalInputEvent;

typedef boost::shared_ptr< ::kobuki_msgs::DigitalInputEvent > DigitalInputEventPtr;
typedef boost::shared_ptr< ::kobuki_msgs::DigitalInputEvent const> DigitalInputEventConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace kobuki_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'kobuki_msgs': ['/home/ubuntu/ros_ws/src/kobuki_msgs/msg', '/home/ubuntu/ros_ws/devel/share/kobuki_msgs/msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "93da823c8b121f8a3940ef3830c58e44";
  }

  static const char* value(const ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x93da823c8b121f8aULL;
  static const uint64_t static_value2 = 0x3940ef3830c58e44ULL;
};

template<class ContainerAllocator>
struct DataType< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kobuki_msgs/DigitalInputEvent";
  }

  static const char* value(const ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This message is generated whenever the value of one or more digital input pins changes.\n\
\n\
# Array of values; indices represent pins 0-3 respectively.\n\
bool[4] values\n\
";
  }

  static const char* value(const ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.values);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct DigitalInputEvent_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::kobuki_msgs::DigitalInputEvent_<ContainerAllocator>& v)
  {
    s << indent << "values[]" << std::endl;
    for (size_t i = 0; i < v.values.size(); ++i)
    {
      s << indent << "  values[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.values[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // KOBUKI_MSGS_MESSAGE_DIGITALINPUTEVENT_H
