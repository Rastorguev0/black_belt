// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: working_time.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_working_5ftime_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_working_5ftime_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_working_5ftime_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_working_5ftime_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_working_5ftime_2eproto;
namespace YellowPages {
class WorkingTime;
class WorkingTimeDefaultTypeInternal;
extern WorkingTimeDefaultTypeInternal _WorkingTime_default_instance_;
class WorkingTimeInterval;
class WorkingTimeIntervalDefaultTypeInternal;
extern WorkingTimeIntervalDefaultTypeInternal _WorkingTimeInterval_default_instance_;
}  // namespace YellowPages
PROTOBUF_NAMESPACE_OPEN
template<> ::YellowPages::WorkingTime* Arena::CreateMaybeMessage<::YellowPages::WorkingTime>(Arena*);
template<> ::YellowPages::WorkingTimeInterval* Arena::CreateMaybeMessage<::YellowPages::WorkingTimeInterval>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace YellowPages {

enum WorkingTimeInterval_Day : int {
  WorkingTimeInterval_Day_EVERYDAY = 0,
  WorkingTimeInterval_Day_MONDAY = 1,
  WorkingTimeInterval_Day_TUESDAY = 2,
  WorkingTimeInterval_Day_WEDNESDAY = 3,
  WorkingTimeInterval_Day_THURSDAY = 4,
  WorkingTimeInterval_Day_FRIDAY = 5,
  WorkingTimeInterval_Day_SATURDAY = 6,
  WorkingTimeInterval_Day_SUNDAY = 7,
  WorkingTimeInterval_Day_WorkingTimeInterval_Day_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  WorkingTimeInterval_Day_WorkingTimeInterval_Day_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool WorkingTimeInterval_Day_IsValid(int value);
constexpr WorkingTimeInterval_Day WorkingTimeInterval_Day_Day_MIN = WorkingTimeInterval_Day_EVERYDAY;
constexpr WorkingTimeInterval_Day WorkingTimeInterval_Day_Day_MAX = WorkingTimeInterval_Day_SUNDAY;
constexpr int WorkingTimeInterval_Day_Day_ARRAYSIZE = WorkingTimeInterval_Day_Day_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* WorkingTimeInterval_Day_descriptor();
template<typename T>
inline const std::string& WorkingTimeInterval_Day_Name(T enum_t_value) {
  static_assert(::std::is_same<T, WorkingTimeInterval_Day>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function WorkingTimeInterval_Day_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    WorkingTimeInterval_Day_descriptor(), enum_t_value);
}
inline bool WorkingTimeInterval_Day_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, WorkingTimeInterval_Day* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<WorkingTimeInterval_Day>(
    WorkingTimeInterval_Day_descriptor(), name, value);
}
// ===================================================================

class WorkingTimeInterval PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:YellowPages.WorkingTimeInterval) */ {
 public:
  inline WorkingTimeInterval() : WorkingTimeInterval(nullptr) {}
  virtual ~WorkingTimeInterval();

  WorkingTimeInterval(const WorkingTimeInterval& from);
  WorkingTimeInterval(WorkingTimeInterval&& from) noexcept
    : WorkingTimeInterval() {
    *this = ::std::move(from);
  }

  inline WorkingTimeInterval& operator=(const WorkingTimeInterval& from) {
    CopyFrom(from);
    return *this;
  }
  inline WorkingTimeInterval& operator=(WorkingTimeInterval&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WorkingTimeInterval& default_instance();

  static inline const WorkingTimeInterval* internal_default_instance() {
    return reinterpret_cast<const WorkingTimeInterval*>(
               &_WorkingTimeInterval_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(WorkingTimeInterval& a, WorkingTimeInterval& b) {
    a.Swap(&b);
  }
  inline void Swap(WorkingTimeInterval* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WorkingTimeInterval* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WorkingTimeInterval* New() const final {
    return CreateMaybeMessage<WorkingTimeInterval>(nullptr);
  }

  WorkingTimeInterval* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WorkingTimeInterval>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WorkingTimeInterval& from);
  void MergeFrom(const WorkingTimeInterval& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WorkingTimeInterval* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "YellowPages.WorkingTimeInterval";
  }
  protected:
  explicit WorkingTimeInterval(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_working_5ftime_2eproto);
    return ::descriptor_table_working_5ftime_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef WorkingTimeInterval_Day Day;
  static constexpr Day EVERYDAY =
    WorkingTimeInterval_Day_EVERYDAY;
  static constexpr Day MONDAY =
    WorkingTimeInterval_Day_MONDAY;
  static constexpr Day TUESDAY =
    WorkingTimeInterval_Day_TUESDAY;
  static constexpr Day WEDNESDAY =
    WorkingTimeInterval_Day_WEDNESDAY;
  static constexpr Day THURSDAY =
    WorkingTimeInterval_Day_THURSDAY;
  static constexpr Day FRIDAY =
    WorkingTimeInterval_Day_FRIDAY;
  static constexpr Day SATURDAY =
    WorkingTimeInterval_Day_SATURDAY;
  static constexpr Day SUNDAY =
    WorkingTimeInterval_Day_SUNDAY;
  static inline bool Day_IsValid(int value) {
    return WorkingTimeInterval_Day_IsValid(value);
  }
  static constexpr Day Day_MIN =
    WorkingTimeInterval_Day_Day_MIN;
  static constexpr Day Day_MAX =
    WorkingTimeInterval_Day_Day_MAX;
  static constexpr int Day_ARRAYSIZE =
    WorkingTimeInterval_Day_Day_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  Day_descriptor() {
    return WorkingTimeInterval_Day_descriptor();
  }
  template<typename T>
  static inline const std::string& Day_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Day>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Day_Name.");
    return WorkingTimeInterval_Day_Name(enum_t_value);
  }
  static inline bool Day_Parse(::PROTOBUF_NAMESPACE_ID::ConstStringParam name,
      Day* value) {
    return WorkingTimeInterval_Day_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kDayFieldNumber = 1,
    kMinutesFromFieldNumber = 2,
    kMinutesToFieldNumber = 3,
  };
  // .YellowPages.WorkingTimeInterval.Day day = 1;
  void clear_day();
  ::YellowPages::WorkingTimeInterval_Day day() const;
  void set_day(::YellowPages::WorkingTimeInterval_Day value);
  private:
  ::YellowPages::WorkingTimeInterval_Day _internal_day() const;
  void _internal_set_day(::YellowPages::WorkingTimeInterval_Day value);
  public:

  // int32 minutes_from = 2;
  void clear_minutes_from();
  ::PROTOBUF_NAMESPACE_ID::int32 minutes_from() const;
  void set_minutes_from(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_minutes_from() const;
  void _internal_set_minutes_from(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 minutes_to = 3;
  void clear_minutes_to();
  ::PROTOBUF_NAMESPACE_ID::int32 minutes_to() const;
  void set_minutes_to(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_minutes_to() const;
  void _internal_set_minutes_to(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:YellowPages.WorkingTimeInterval)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  int day_;
  ::PROTOBUF_NAMESPACE_ID::int32 minutes_from_;
  ::PROTOBUF_NAMESPACE_ID::int32 minutes_to_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_working_5ftime_2eproto;
};
// -------------------------------------------------------------------

class WorkingTime PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:YellowPages.WorkingTime) */ {
 public:
  inline WorkingTime() : WorkingTime(nullptr) {}
  virtual ~WorkingTime();

  WorkingTime(const WorkingTime& from);
  WorkingTime(WorkingTime&& from) noexcept
    : WorkingTime() {
    *this = ::std::move(from);
  }

  inline WorkingTime& operator=(const WorkingTime& from) {
    CopyFrom(from);
    return *this;
  }
  inline WorkingTime& operator=(WorkingTime&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WorkingTime& default_instance();

  static inline const WorkingTime* internal_default_instance() {
    return reinterpret_cast<const WorkingTime*>(
               &_WorkingTime_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(WorkingTime& a, WorkingTime& b) {
    a.Swap(&b);
  }
  inline void Swap(WorkingTime* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WorkingTime* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WorkingTime* New() const final {
    return CreateMaybeMessage<WorkingTime>(nullptr);
  }

  WorkingTime* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WorkingTime>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WorkingTime& from);
  void MergeFrom(const WorkingTime& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WorkingTime* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "YellowPages.WorkingTime";
  }
  protected:
  explicit WorkingTime(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_working_5ftime_2eproto);
    return ::descriptor_table_working_5ftime_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIntervalsFieldNumber = 2,
    kFormattedFieldNumber = 1,
  };
  // repeated .YellowPages.WorkingTimeInterval intervals = 2;
  int intervals_size() const;
  private:
  int _internal_intervals_size() const;
  public:
  void clear_intervals();
  ::YellowPages::WorkingTimeInterval* mutable_intervals(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::YellowPages::WorkingTimeInterval >*
      mutable_intervals();
  private:
  const ::YellowPages::WorkingTimeInterval& _internal_intervals(int index) const;
  ::YellowPages::WorkingTimeInterval* _internal_add_intervals();
  public:
  const ::YellowPages::WorkingTimeInterval& intervals(int index) const;
  ::YellowPages::WorkingTimeInterval* add_intervals();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::YellowPages::WorkingTimeInterval >&
      intervals() const;

  // string formatted = 1;
  void clear_formatted();
  const std::string& formatted() const;
  void set_formatted(const std::string& value);
  void set_formatted(std::string&& value);
  void set_formatted(const char* value);
  void set_formatted(const char* value, size_t size);
  std::string* mutable_formatted();
  std::string* release_formatted();
  void set_allocated_formatted(std::string* formatted);
  private:
  const std::string& _internal_formatted() const;
  void _internal_set_formatted(const std::string& value);
  std::string* _internal_mutable_formatted();
  public:

  // @@protoc_insertion_point(class_scope:YellowPages.WorkingTime)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::YellowPages::WorkingTimeInterval > intervals_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr formatted_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_working_5ftime_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// WorkingTimeInterval

// .YellowPages.WorkingTimeInterval.Day day = 1;
inline void WorkingTimeInterval::clear_day() {
  day_ = 0;
}
inline ::YellowPages::WorkingTimeInterval_Day WorkingTimeInterval::_internal_day() const {
  return static_cast< ::YellowPages::WorkingTimeInterval_Day >(day_);
}
inline ::YellowPages::WorkingTimeInterval_Day WorkingTimeInterval::day() const {
  // @@protoc_insertion_point(field_get:YellowPages.WorkingTimeInterval.day)
  return _internal_day();
}
inline void WorkingTimeInterval::_internal_set_day(::YellowPages::WorkingTimeInterval_Day value) {
  
  day_ = value;
}
inline void WorkingTimeInterval::set_day(::YellowPages::WorkingTimeInterval_Day value) {
  _internal_set_day(value);
  // @@protoc_insertion_point(field_set:YellowPages.WorkingTimeInterval.day)
}

// int32 minutes_from = 2;
inline void WorkingTimeInterval::clear_minutes_from() {
  minutes_from_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkingTimeInterval::_internal_minutes_from() const {
  return minutes_from_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkingTimeInterval::minutes_from() const {
  // @@protoc_insertion_point(field_get:YellowPages.WorkingTimeInterval.minutes_from)
  return _internal_minutes_from();
}
inline void WorkingTimeInterval::_internal_set_minutes_from(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  minutes_from_ = value;
}
inline void WorkingTimeInterval::set_minutes_from(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_minutes_from(value);
  // @@protoc_insertion_point(field_set:YellowPages.WorkingTimeInterval.minutes_from)
}

// int32 minutes_to = 3;
inline void WorkingTimeInterval::clear_minutes_to() {
  minutes_to_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkingTimeInterval::_internal_minutes_to() const {
  return minutes_to_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkingTimeInterval::minutes_to() const {
  // @@protoc_insertion_point(field_get:YellowPages.WorkingTimeInterval.minutes_to)
  return _internal_minutes_to();
}
inline void WorkingTimeInterval::_internal_set_minutes_to(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  minutes_to_ = value;
}
inline void WorkingTimeInterval::set_minutes_to(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_minutes_to(value);
  // @@protoc_insertion_point(field_set:YellowPages.WorkingTimeInterval.minutes_to)
}

// -------------------------------------------------------------------

// WorkingTime

// string formatted = 1;
inline void WorkingTime::clear_formatted() {
  formatted_.ClearToEmpty();
}
inline const std::string& WorkingTime::formatted() const {
  // @@protoc_insertion_point(field_get:YellowPages.WorkingTime.formatted)
  return _internal_formatted();
}
inline void WorkingTime::set_formatted(const std::string& value) {
  _internal_set_formatted(value);
  // @@protoc_insertion_point(field_set:YellowPages.WorkingTime.formatted)
}
inline std::string* WorkingTime::mutable_formatted() {
  // @@protoc_insertion_point(field_mutable:YellowPages.WorkingTime.formatted)
  return _internal_mutable_formatted();
}
inline const std::string& WorkingTime::_internal_formatted() const {
  return formatted_.Get();
}
inline void WorkingTime::_internal_set_formatted(const std::string& value) {
  
  formatted_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void WorkingTime::set_formatted(std::string&& value) {
  
  formatted_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:YellowPages.WorkingTime.formatted)
}
inline void WorkingTime::set_formatted(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  formatted_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:YellowPages.WorkingTime.formatted)
}
inline void WorkingTime::set_formatted(const char* value,
    size_t size) {
  
  formatted_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:YellowPages.WorkingTime.formatted)
}
inline std::string* WorkingTime::_internal_mutable_formatted() {
  
  return formatted_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* WorkingTime::release_formatted() {
  // @@protoc_insertion_point(field_release:YellowPages.WorkingTime.formatted)
  return formatted_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void WorkingTime::set_allocated_formatted(std::string* formatted) {
  if (formatted != nullptr) {
    
  } else {
    
  }
  formatted_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), formatted,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:YellowPages.WorkingTime.formatted)
}

// repeated .YellowPages.WorkingTimeInterval intervals = 2;
inline int WorkingTime::_internal_intervals_size() const {
  return intervals_.size();
}
inline int WorkingTime::intervals_size() const {
  return _internal_intervals_size();
}
inline void WorkingTime::clear_intervals() {
  intervals_.Clear();
}
inline ::YellowPages::WorkingTimeInterval* WorkingTime::mutable_intervals(int index) {
  // @@protoc_insertion_point(field_mutable:YellowPages.WorkingTime.intervals)
  return intervals_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::YellowPages::WorkingTimeInterval >*
WorkingTime::mutable_intervals() {
  // @@protoc_insertion_point(field_mutable_list:YellowPages.WorkingTime.intervals)
  return &intervals_;
}
inline const ::YellowPages::WorkingTimeInterval& WorkingTime::_internal_intervals(int index) const {
  return intervals_.Get(index);
}
inline const ::YellowPages::WorkingTimeInterval& WorkingTime::intervals(int index) const {
  // @@protoc_insertion_point(field_get:YellowPages.WorkingTime.intervals)
  return _internal_intervals(index);
}
inline ::YellowPages::WorkingTimeInterval* WorkingTime::_internal_add_intervals() {
  return intervals_.Add();
}
inline ::YellowPages::WorkingTimeInterval* WorkingTime::add_intervals() {
  // @@protoc_insertion_point(field_add:YellowPages.WorkingTime.intervals)
  return _internal_add_intervals();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::YellowPages::WorkingTimeInterval >&
WorkingTime::intervals() const {
  // @@protoc_insertion_point(field_list:YellowPages.WorkingTime.intervals)
  return intervals_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace YellowPages

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::YellowPages::WorkingTimeInterval_Day> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::YellowPages::WorkingTimeInterval_Day>() {
  return ::YellowPages::WorkingTimeInterval_Day_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_working_5ftime_2eproto
