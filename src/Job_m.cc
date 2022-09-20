//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Job.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Job_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace lfs {

Register_Class(Job)

Job::Job(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
    take(&this->pkg);
}

Job::Job(const Job& other) : ::omnetpp::cMessage(other)
{
    take(&this->pkg);
    copy(other);
}

Job::~Job()
{
    drop(&this->pkg);
}

Job& Job::operator=(const Job& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Job::copy(const Job& other)
{
    this->cached = other.cached;
    this->back_from_ost = other.back_from_ost;
    this->work_type = other.work_type;
    this->assigned_oss_id = other.assigned_oss_id;
    this->assigned_ost_id = other.assigned_ost_id;
    this->job_id = other.job_id;
    this->task_id = other.task_id;
    this->init_data_size = other.init_data_size;
    this->generate_time = other.generate_time;
    this->arrive_time_queue = other.arrive_time_queue;
    this->leave_time_queue = other.leave_time_queue;
    this->arrive_time_server = other.arrive_time_server;
    this->leave_time_server = other.leave_time_server;
    this->pkg = other.pkg;
    this->pkg.setName(other.pkg.getName());
}

void Job::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cached);
    doParsimPacking(b,this->back_from_ost);
    doParsimPacking(b,this->work_type);
    doParsimPacking(b,this->assigned_oss_id);
    doParsimPacking(b,this->assigned_ost_id);
    doParsimPacking(b,this->job_id);
    doParsimPacking(b,this->task_id);
    doParsimPacking(b,this->init_data_size);
    doParsimPacking(b,this->generate_time);
    doParsimPacking(b,this->arrive_time_queue);
    doParsimPacking(b,this->leave_time_queue);
    doParsimPacking(b,this->arrive_time_server);
    doParsimPacking(b,this->leave_time_server);
    doParsimPacking(b,this->pkg);
}

void Job::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cached);
    doParsimUnpacking(b,this->back_from_ost);
    doParsimUnpacking(b,this->work_type);
    doParsimUnpacking(b,this->assigned_oss_id);
    doParsimUnpacking(b,this->assigned_ost_id);
    doParsimUnpacking(b,this->job_id);
    doParsimUnpacking(b,this->task_id);
    doParsimUnpacking(b,this->init_data_size);
    doParsimUnpacking(b,this->generate_time);
    doParsimUnpacking(b,this->arrive_time_queue);
    doParsimUnpacking(b,this->leave_time_queue);
    doParsimUnpacking(b,this->arrive_time_server);
    doParsimUnpacking(b,this->leave_time_server);
    doParsimUnpacking(b,this->pkg);
}

bool Job::getCached() const
{
    return this->cached;
}

void Job::setCached(bool cached)
{
    this->cached = cached;
}

bool Job::getBack_from_ost() const
{
    return this->back_from_ost;
}

void Job::setBack_from_ost(bool back_from_ost)
{
    this->back_from_ost = back_from_ost;
}

char Job::getWork_type() const
{
    return this->work_type;
}

void Job::setWork_type(char work_type)
{
    this->work_type = work_type;
}

int Job::getAssigned_oss_id() const
{
    return this->assigned_oss_id;
}

void Job::setAssigned_oss_id(int assigned_oss_id)
{
    this->assigned_oss_id = assigned_oss_id;
}

int Job::getAssigned_ost_id() const
{
    return this->assigned_ost_id;
}

void Job::setAssigned_ost_id(int assigned_ost_id)
{
    this->assigned_ost_id = assigned_ost_id;
}

unsigned int Job::getJob_id() const
{
    return this->job_id;
}

void Job::setJob_id(unsigned int job_id)
{
    this->job_id = job_id;
}

int Job::getTask_id() const
{
    return this->task_id;
}

void Job::setTask_id(int task_id)
{
    this->task_id = task_id;
}

uint64_t Job::getInit_data_size() const
{
    return this->init_data_size;
}

void Job::setInit_data_size(uint64_t init_data_size)
{
    this->init_data_size = init_data_size;
}

::omnetpp::simtime_t Job::getGenerate_time() const
{
    return this->generate_time;
}

void Job::setGenerate_time(::omnetpp::simtime_t generate_time)
{
    this->generate_time = generate_time;
}

::omnetpp::simtime_t Job::getArrive_time_queue() const
{
    return this->arrive_time_queue;
}

void Job::setArrive_time_queue(::omnetpp::simtime_t arrive_time_queue)
{
    this->arrive_time_queue = arrive_time_queue;
}

::omnetpp::simtime_t Job::getLeave_time_queue() const
{
    return this->leave_time_queue;
}

void Job::setLeave_time_queue(::omnetpp::simtime_t leave_time_queue)
{
    this->leave_time_queue = leave_time_queue;
}

::omnetpp::simtime_t Job::getArrive_time_server() const
{
    return this->arrive_time_server;
}

void Job::setArrive_time_server(::omnetpp::simtime_t arrive_time_server)
{
    this->arrive_time_server = arrive_time_server;
}

::omnetpp::simtime_t Job::getLeave_time_server() const
{
    return this->leave_time_server;
}

void Job::setLeave_time_server(::omnetpp::simtime_t leave_time_server)
{
    this->leave_time_server = leave_time_server;
}

const ::omnetpp::cPacket& Job::getPkg() const
{
    return this->pkg;
}

void Job::setPkg(const ::omnetpp::cPacket& pkg)
{
    this->pkg = pkg;
}

class JobDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cached,
        FIELD_back_from_ost,
        FIELD_work_type,
        FIELD_assigned_oss_id,
        FIELD_assigned_ost_id,
        FIELD_job_id,
        FIELD_task_id,
        FIELD_init_data_size,
        FIELD_generate_time,
        FIELD_arrive_time_queue,
        FIELD_leave_time_queue,
        FIELD_arrive_time_server,
        FIELD_leave_time_server,
        FIELD_pkg,
    };
  public:
    JobDescriptor();
    virtual ~JobDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(JobDescriptor)

JobDescriptor::JobDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(lfs::Job)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

JobDescriptor::~JobDescriptor()
{
    delete[] propertyNames;
}

bool JobDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Job *>(obj)!=nullptr;
}

const char **JobDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *JobDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int JobDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 14+base->getFieldCount() : 14;
}

unsigned int JobDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cached
        FD_ISEDITABLE,    // FIELD_back_from_ost
        FD_ISEDITABLE,    // FIELD_work_type
        FD_ISEDITABLE,    // FIELD_assigned_oss_id
        FD_ISEDITABLE,    // FIELD_assigned_ost_id
        FD_ISEDITABLE,    // FIELD_job_id
        FD_ISEDITABLE,    // FIELD_task_id
        FD_ISEDITABLE,    // FIELD_init_data_size
        FD_ISEDITABLE,    // FIELD_generate_time
        FD_ISEDITABLE,    // FIELD_arrive_time_queue
        FD_ISEDITABLE,    // FIELD_leave_time_queue
        FD_ISEDITABLE,    // FIELD_arrive_time_server
        FD_ISEDITABLE,    // FIELD_leave_time_server
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_pkg
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *JobDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cached",
        "back_from_ost",
        "work_type",
        "assigned_oss_id",
        "assigned_ost_id",
        "job_id",
        "task_id",
        "init_data_size",
        "generate_time",
        "arrive_time_queue",
        "leave_time_queue",
        "arrive_time_server",
        "leave_time_server",
        "pkg",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int JobDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cached") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "back_from_ost") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "work_type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "assigned_oss_id") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "assigned_ost_id") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "job_id") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "task_id") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "init_data_size") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "generate_time") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "arrive_time_queue") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "leave_time_queue") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "arrive_time_server") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "leave_time_server") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "pkg") == 0) return baseIndex + 13;
    return base ? base->findField(fieldName) : -1;
}

const char *JobDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_cached
        "bool",    // FIELD_back_from_ost
        "char",    // FIELD_work_type
        "int",    // FIELD_assigned_oss_id
        "int",    // FIELD_assigned_ost_id
        "unsigned int",    // FIELD_job_id
        "int",    // FIELD_task_id
        "uint64_t",    // FIELD_init_data_size
        "omnetpp::simtime_t",    // FIELD_generate_time
        "omnetpp::simtime_t",    // FIELD_arrive_time_queue
        "omnetpp::simtime_t",    // FIELD_leave_time_queue
        "omnetpp::simtime_t",    // FIELD_arrive_time_server
        "omnetpp::simtime_t",    // FIELD_leave_time_server
        "omnetpp::cPacket",    // FIELD_pkg
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **JobDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *JobDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int JobDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void JobDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Job'", field);
    }
}

const char *JobDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JobDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        case FIELD_cached: return bool2string(pp->getCached());
        case FIELD_back_from_ost: return bool2string(pp->getBack_from_ost());
        case FIELD_work_type: return long2string(pp->getWork_type());
        case FIELD_assigned_oss_id: return long2string(pp->getAssigned_oss_id());
        case FIELD_assigned_ost_id: return long2string(pp->getAssigned_ost_id());
        case FIELD_job_id: return ulong2string(pp->getJob_id());
        case FIELD_task_id: return long2string(pp->getTask_id());
        case FIELD_init_data_size: return uint642string(pp->getInit_data_size());
        case FIELD_generate_time: return simtime2string(pp->getGenerate_time());
        case FIELD_arrive_time_queue: return simtime2string(pp->getArrive_time_queue());
        case FIELD_leave_time_queue: return simtime2string(pp->getLeave_time_queue());
        case FIELD_arrive_time_server: return simtime2string(pp->getArrive_time_server());
        case FIELD_leave_time_server: return simtime2string(pp->getLeave_time_server());
        case FIELD_pkg: return pp->getPkg().str();
        default: return "";
    }
}

void JobDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        case FIELD_cached: pp->setCached(string2bool(value)); break;
        case FIELD_back_from_ost: pp->setBack_from_ost(string2bool(value)); break;
        case FIELD_work_type: pp->setWork_type(string2long(value)); break;
        case FIELD_assigned_oss_id: pp->setAssigned_oss_id(string2long(value)); break;
        case FIELD_assigned_ost_id: pp->setAssigned_ost_id(string2long(value)); break;
        case FIELD_job_id: pp->setJob_id(string2ulong(value)); break;
        case FIELD_task_id: pp->setTask_id(string2long(value)); break;
        case FIELD_init_data_size: pp->setInit_data_size(string2uint64(value)); break;
        case FIELD_generate_time: pp->setGenerate_time(string2simtime(value)); break;
        case FIELD_arrive_time_queue: pp->setArrive_time_queue(string2simtime(value)); break;
        case FIELD_leave_time_queue: pp->setLeave_time_queue(string2simtime(value)); break;
        case FIELD_arrive_time_server: pp->setArrive_time_server(string2simtime(value)); break;
        case FIELD_leave_time_server: pp->setLeave_time_server(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job'", field);
    }
}

omnetpp::cValue JobDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        case FIELD_cached: return pp->getCached();
        case FIELD_back_from_ost: return pp->getBack_from_ost();
        case FIELD_work_type: return pp->getWork_type();
        case FIELD_assigned_oss_id: return pp->getAssigned_oss_id();
        case FIELD_assigned_ost_id: return pp->getAssigned_ost_id();
        case FIELD_job_id: return (omnetpp::intval_t)(pp->getJob_id());
        case FIELD_task_id: return pp->getTask_id();
        case FIELD_init_data_size: return (omnetpp::intval_t)(pp->getInit_data_size());
        case FIELD_generate_time: return pp->getGenerate_time().dbl();
        case FIELD_arrive_time_queue: return pp->getArrive_time_queue().dbl();
        case FIELD_leave_time_queue: return pp->getLeave_time_queue().dbl();
        case FIELD_arrive_time_server: return pp->getArrive_time_server().dbl();
        case FIELD_leave_time_server: return pp->getLeave_time_server().dbl();
        case FIELD_pkg: return omnetpp::toAnyPtr(&pp->getPkg()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Job' as cValue -- field index out of range?", field);
    }
}

void JobDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        case FIELD_cached: pp->setCached(value.boolValue()); break;
        case FIELD_back_from_ost: pp->setBack_from_ost(value.boolValue()); break;
        case FIELD_work_type: pp->setWork_type(omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_assigned_oss_id: pp->setAssigned_oss_id(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_assigned_ost_id: pp->setAssigned_ost_id(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_job_id: pp->setJob_id(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_task_id: pp->setTask_id(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_init_data_size: pp->setInit_data_size(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_generate_time: pp->setGenerate_time(value.doubleValue()); break;
        case FIELD_arrive_time_queue: pp->setArrive_time_queue(value.doubleValue()); break;
        case FIELD_leave_time_queue: pp->setLeave_time_queue(value.doubleValue()); break;
        case FIELD_arrive_time_server: pp->setArrive_time_server(value.doubleValue()); break;
        case FIELD_leave_time_server: pp->setLeave_time_server(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job'", field);
    }
}

const char *JobDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_pkg: return omnetpp::opp_typename(typeid(::omnetpp::cPacket));
        default: return nullptr;
    };
}

omnetpp::any_ptr JobDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        case FIELD_pkg: return omnetpp::toAnyPtr(&pp->getPkg()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void JobDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Job *pp = omnetpp::fromAnyPtr<Job>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job'", field);
    }
}

}  // namespace lfs

namespace omnetpp {

}  // namespace omnetpp

