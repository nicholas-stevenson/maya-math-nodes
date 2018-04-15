// Copyright (c) 2018 Serguei Kalentchouk et al. All rights reserved.
// Use of this source code is governed by an MIT license that can be found in the LICENSE file.
#pragma once

#include <cmath>
#include <string>
#include <type_traits>
#include <vector>

#include <maya/MAngle.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>

#ifdef __APPLE__
    #define TEMPLATE_PARAMETER_LINKAGE constexpr
#else
    #define TEMPLATE_PARAMETER_LINKAGE extern const
#endif

struct Attribute
{
    MObject attr;
    MObject attrX;
    MObject attrY;
    MObject attrZ;
    MObject attrW;
    
    operator const MObject&() const { return attr; }
    
    Attribute& operator=(const MObject& object)
    {
        this->attr = object;
        return *this;
    }
};

// Default value templates
// Note that complex types are always defaulted to zero/identity
template <typename TType>
inline TType DefaultValue()
{
    static TType defaultT;
    return defaultT;
}

template <>
inline MMatrix DefaultValue()
{
    return MMatrix::identity;
}

template <>
inline MEulerRotation DefaultValue()
{
    return MEulerRotation::identity;
}

template <>
inline MQuaternion DefaultValue()
{
    return MQuaternion::identity;
}

template <typename TType>
inline TType DefaultValue(double x, double y, double z);

template <>
inline MVector DefaultValue(double x, double y, double z)
{
    return MVector(x, y, z);
}

template <>
inline MEulerRotation DefaultValue(double x, double y, double z)
{
    return MEulerRotation(x, y, z);
}

// Overloads for createAttribute
inline void createAttribute(Attribute& attr, const char* name, double value, bool isInput = true, bool isArray = false)
{
    MFnNumericAttribute attrFn;
    attr.attr = attrFn.create(name, name, MFnNumericData::kDouble, value);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, int value, bool isInput = true, bool isArray = false)
{
    MFnNumericAttribute attrFn;
    attr.attr = attrFn.create(name, name, MFnNumericData::kInt, value);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, bool value, bool isInput = true, bool isArray = false)
{
    MFnNumericAttribute attrFn;
    attr.attr = attrFn.create(name, name, MFnNumericData::kBoolean, value);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, const MAngle& value, bool isInput = true, bool isArray = false)
{
    MFnUnitAttribute attrFn;
    attr.attr = attrFn.create(name, name, value);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, const MVector& value, bool isInput = true, bool isArray = false)
{
    MFnNumericAttribute attrFn;
    
    const std::string attrXName = (std::string(name) + "X");
    attr.attrX = attrFn.create(attrXName.c_str(), attrXName.c_str(), MFnNumericData::kDouble, value.x);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    const std::string attrYName = (std::string(name) + "Y");
    attr.attrY = attrFn.create(attrYName.c_str(), attrYName.c_str(), MFnNumericData::kDouble, value.y);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    const std::string attrZName = (std::string(name) + "Z");
    attr.attrZ = attrFn.create(attrZName.c_str(), attrZName.c_str(), MFnNumericData::kDouble, value.z);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    attr.attr = attrFn.create(name, name, attr.attrX, attr.attrY, attr.attrZ);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, const MMatrix& value, bool isInput = true, bool isArray = false)
{
    MFnMatrixAttribute attrFn;
    attr.attr = attrFn.create(name, name);
    attrFn.setDefault(value);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, const MQuaternion& value, bool isInput = true, bool isArray = false)
{
    MFnCompoundAttribute cAttrFn;
    MFnNumericAttribute attrFn;
    
    const std::string attrXName = (std::string(name) + "X");
    attr.attrX = attrFn.create(attrXName.c_str(), attrXName.c_str(), MFnNumericData::kDouble, value.x);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    const std::string attrYName = (std::string(name) + "Y");
    attr.attrY = attrFn.create(attrYName.c_str(), attrYName.c_str(), MFnNumericData::kDouble, value.y);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    const std::string attrZName = (std::string(name) + "Z");
    attr.attrZ = attrFn.create(attrZName.c_str(), attrZName.c_str(), MFnNumericData::kDouble, value.z);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    const std::string attrWName = (std::string(name) + "W");
    attr.attrW = attrFn.create(attrWName.c_str(), attrWName.c_str(), MFnNumericData::kDouble, value.w);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    
    attr.attr = cAttrFn.create(name, name);
    cAttrFn.addChild(attr.attrX);
    cAttrFn.addChild(attr.attrY);
    cAttrFn.addChild(attr.attrZ);
    cAttrFn.addChild(attr.attrW);
    cAttrFn.setKeyable(isInput);
    cAttrFn.setStorable(isInput);
    cAttrFn.setWritable(isInput);
    cAttrFn.setArray(isArray);
    cAttrFn.setUsesArrayDataBuilder(isArray);
}

inline void createAttribute(Attribute& attr, const char* name, const MEulerRotation& value, bool isInput = true, bool isArray = false)
{
    MFnNumericAttribute attrFn;
    MFnUnitAttribute uAttrFn;
    
    const std::string attrXName = (std::string(name) + "X");
    attr.attrX = uAttrFn.create(attrXName.c_str(), attrXName.c_str(), MAngle(value.x));
    uAttrFn.setKeyable(isInput);
    uAttrFn.setStorable(isInput);
    uAttrFn.setWritable(isInput);
    
    const std::string attrYName = (std::string(name) + "Y");
    attr.attrY = uAttrFn.create(attrYName.c_str(), attrYName.c_str(), MAngle(value.y));
    uAttrFn.setKeyable(isInput);
    uAttrFn.setStorable(isInput);
    uAttrFn.setWritable(isInput);
    
    const std::string attrZName = (std::string(name) + "Z");
    attr.attrZ = uAttrFn.create(attrZName.c_str(), attrZName.c_str(), MAngle(value.z));
    uAttrFn.setKeyable(isInput);
    uAttrFn.setStorable(isInput);
    uAttrFn.setWritable(isInput);
    
    attr.attr = attrFn.create(name, name, attr.attrX, attr.attrY, attr.attrZ);
    attrFn.setKeyable(isInput);
    attrFn.setStorable(isInput);
    attrFn.setWritable(isInput);
    attrFn.setArray(isArray);
    attrFn.setUsesArrayDataBuilder(isArray);
}

// Explicit specializations for getAttribute
template <typename TType>
inline TType getAttribute(MDataBlock& dataBlock, const Attribute& attribute);

template <>
inline double getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asDouble();
}

template <>
inline std::vector<double> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<double> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        out[index] = arrayHandle.inputValue().asDouble();
        arrayHandle.next();
    }
    
    return out;
}

template <>
inline int getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asInt();
}

template <>
inline std::vector<int> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<int> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        out[index] = arrayHandle.inputValue().asInt();
        arrayHandle.next();
    }

    return out;
}

template <>
inline bool getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asBool();
}

template <>
inline MAngle getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asAngle();
}

template <>
inline std::vector<MAngle> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<MAngle> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        out[index] = arrayHandle.inputValue().asAngle();
        arrayHandle.next();
    }

    return out;
}

template <>
inline MVector getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asVector();
}

template <>
inline std::vector<MVector> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<MVector> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        out[index] = arrayHandle.inputValue().asVector();
        arrayHandle.next();
    }

    return out;
}

template <>
inline MMatrix getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asMatrix();
}

template <>
inline std::vector<MMatrix> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<MMatrix> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        out[index] = arrayHandle.inputValue().asMatrix();
        arrayHandle.next();
    }

    return out;
}

template <>
inline MEulerRotation getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute.attr);
    
    const double x = handle.child(attribute.attrX).asAngle().asRadians();
    const double y = handle.child(attribute.attrY).asAngle().asRadians();
    const double z = handle.child(attribute.attrZ).asAngle().asRadians();
    
    return MEulerRotation(x, y, z);
}

template <>
inline std::vector<MEulerRotation> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<MEulerRotation> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        MDataHandle handle = arrayHandle.inputValue();
        
        const double x = handle.child(attribute.attrX).asAngle().asRadians();
        const double y = handle.child(attribute.attrY).asAngle().asRadians();
        const double z = handle.child(attribute.attrZ).asAngle().asRadians();
        
        out[index] = MEulerRotation(x, y, z);
        arrayHandle.next();
    }
    
    return out;
}

template <>
inline MQuaternion getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute.attr);
    
    const double x = handle.child(attribute.attrX).asDouble();
    const double y = handle.child(attribute.attrY).asDouble();
    const double z = handle.child(attribute.attrZ).asDouble();
    const double w = handle.child(attribute.attrW).asDouble();
    
    return MQuaternion(x, y, z, w);
}

template <>
inline std::vector<MQuaternion> getAttribute(MDataBlock& dataBlock, const Attribute& attribute)
{
    std::vector<MQuaternion> out;
    MArrayDataHandle arrayHandle = dataBlock.inputArrayValue(attribute);
    
    out.resize(arrayHandle.elementCount());
    for (unsigned index = 0u; index < arrayHandle.elementCount(); ++index)
    {
        MDataHandle handle = arrayHandle.inputValue();
        
        const double x = handle.child(attribute.attrX).asDouble();
        const double y = handle.child(attribute.attrY).asDouble();
        const double z = handle.child(attribute.attrZ).asDouble();
        const double w = handle.child(attribute.attrW).asDouble();
        
        out[index] = MQuaternion(x, y, z, w);
        arrayHandle.next();
    }
    
    return out;
}

template <typename TInputType, typename TOutputType>
inline TOutputType getAttribute(MDataBlock& dataBlock, const Attribute& attribute);

template <>
inline double getAttribute<MAngle, double>(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asAngle().asRadians();
}

template <>
inline double getAttribute<double, double>(MDataBlock& dataBlock, const Attribute& attribute)
{
    MDataHandle handle = dataBlock.inputValue(attribute);
    return handle.asDouble();
}

template <typename TType>
inline void setAttribute(MDataBlock& dataBlock, const Attribute& attribute, TType value)
{
    MDataHandle handle = dataBlock.outputValue(attribute);
    handle.set(value);
    handle.setClean();
}

template <>
inline void setAttribute(MDataBlock& dataBlock, const Attribute& attribute, MEulerRotation value)
{
    MDataHandle outputXHandle = dataBlock.outputValue(attribute.attrX);
    outputXHandle.set(MAngle(value.x));
    outputXHandle.setClean();
    
    MDataHandle outputYHandle = dataBlock.outputValue(attribute.attrY);
    outputYHandle.set(MAngle(value.y));
    outputYHandle.setClean();
    
    MDataHandle outputZHandle = dataBlock.outputValue(attribute.attrZ);
    outputZHandle.set(MAngle(value.z));
    outputZHandle.setClean();
}

template <>
inline void setAttribute(MDataBlock& dataBlock, const Attribute& attribute, MQuaternion value)
{
    MDataHandle outputXHandle = dataBlock.outputValue(attribute.attrX);
    outputXHandle.set(value.x);
    outputXHandle.setClean();
    
    MDataHandle outputYHandle = dataBlock.outputValue(attribute.attrY);
    outputYHandle.set(value.y);
    outputYHandle.setClean();
    
    MDataHandle outputZHandle = dataBlock.outputValue(attribute.attrZ);
    outputZHandle.set(value.z);
    outputZHandle.setClean();
    
    MDataHandle outputWHandle = dataBlock.outputValue(attribute.attrW);
    outputWHandle.set(value.w);
    outputWHandle.setClean();
}

// MAngle operator overloads
MAngle operator+(const MAngle& a, const MAngle& b)
{
    return MAngle(a.asRadians() + b.asRadians());
}

MAngle operator-(const MAngle& a, const MAngle& b)
{
    return MAngle(a.asRadians() - b.asRadians());
}

MAngle operator*(const MAngle& a, double b)
{
    return MAngle(a.asRadians() * b);
}

MAngle operator*(const MAngle& a, int b)
{
    return MAngle(a.asRadians() * b);
}

MAngle operator/(const MAngle& a, double b)
{
    return MAngle(a.asRadians() / b);
}

MAngle operator/(const MAngle& a, int b)
{
    return MAngle(a.asRadians() / b);
}

MAngle operator-(const MAngle& a)
{
    return MAngle(-a.asRadians());
}

// Base node type definition used for all math nodes in this library
template<typename TClass, const char* TTypeName>
class BaseNode : public MPxNode
{
public:
    static void registerNode(class MFnPlugin& pluginFn, int typeId)
    {
        kTypeId = typeId;
        pluginFn.registerNode((std::string(NODE_NAME_PREFIX) + TTypeName).c_str(), typeId, []() -> void* { return new TClass(); }, TClass::initialize);
    }
    
    static void deregisterNode(class MFnPlugin& pluginFn)
    {
        pluginFn.deregisterNode(kTypeId);
    }
    
    SchedulingType schedulingType() const override
    {
        return SchedulingType::kParallel;
    }

protected:
    static int kTypeId;
};

template<typename TClass, const char* TTypeName>
int BaseNode<TClass, TTypeName>::kTypeId = -1;
