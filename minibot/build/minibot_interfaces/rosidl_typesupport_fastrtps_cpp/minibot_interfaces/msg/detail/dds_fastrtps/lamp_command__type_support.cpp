// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from minibot_interfaces:msg/LampCommand.idl
// generated code does not contain a copyright notice
#include "minibot_interfaces/msg/detail/lamp_command__rosidl_typesupport_fastrtps_cpp.hpp"
#include "minibot_interfaces/msg/detail/lamp_command__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace minibot_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_minibot_interfaces
cdr_serialize(
  const minibot_interfaces::msg::LampCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: l_command
  cdr << ros_message.l_command;
  // Member: r_command
  cdr << ros_message.r_command;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_minibot_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  minibot_interfaces::msg::LampCommand & ros_message)
{
  // Member: l_command
  cdr >> ros_message.l_command;

  // Member: r_command
  cdr >> ros_message.r_command;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_minibot_interfaces
get_serialized_size(
  const minibot_interfaces::msg::LampCommand & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: l_command
  {
    size_t item_size = sizeof(ros_message.l_command);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: r_command
  {
    size_t item_size = sizeof(ros_message.r_command);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_minibot_interfaces
max_serialized_size_LampCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: l_command
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: r_command
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = minibot_interfaces::msg::LampCommand;
    is_plain =
      (
      offsetof(DataType, r_command) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _LampCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const minibot_interfaces::msg::LampCommand *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _LampCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<minibot_interfaces::msg::LampCommand *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _LampCommand__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const minibot_interfaces::msg::LampCommand *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _LampCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_LampCommand(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _LampCommand__callbacks = {
  "minibot_interfaces::msg",
  "LampCommand",
  _LampCommand__cdr_serialize,
  _LampCommand__cdr_deserialize,
  _LampCommand__get_serialized_size,
  _LampCommand__max_serialized_size
};

static rosidl_message_type_support_t _LampCommand__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_LampCommand__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace minibot_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_minibot_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<minibot_interfaces::msg::LampCommand>()
{
  return &minibot_interfaces::msg::typesupport_fastrtps_cpp::_LampCommand__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, minibot_interfaces, msg, LampCommand)() {
  return &minibot_interfaces::msg::typesupport_fastrtps_cpp::_LampCommand__handle;
}

#ifdef __cplusplus
}
#endif
