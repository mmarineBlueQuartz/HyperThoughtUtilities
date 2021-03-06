/* ============================================================================
 * Copyright (c) 2020-2020 BlueQuartz Software, LLC
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The code contained herein was partially funded by the followig contracts:
 *    United States Air Force Prime Contract FA8650-15-D-5231
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "HTUploadPathFilterParameter.h"

#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::HTUploadPathFilterParameter() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::~HTUploadPathFilterParameter() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::Pointer HTUploadPathFilterParameter::New(const QString& humanLabel, const QString& propertyName, const HTFilePath& defaultValue, Category category,
                                                                      SetterCallbackType setterCallback, GetterCallbackType getterCallback)
{
  HTUploadPathFilterParameter::Pointer ptr = HTUploadPathFilterParameter::New();
  ptr->setHumanLabel(humanLabel);
  ptr->setPropertyName(propertyName);
  QVariant v;
  v.setValue(defaultValue);
  ptr->setDefaultValue(v);
  ptr->setCategory(category);
  ptr->setSetterCallback(setterCallback);
  ptr->setGetterCallback(getterCallback);

  return ptr;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString HTUploadPathFilterParameter::getWidgetType() const
{
  return QString("HTUploadPathWidget");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void HTUploadPathFilterParameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[getPropertyName()];
  if(!jsonValue.isUndefined() && m_SetterCallback)
  {
    QJsonObject jsonObj = jsonValue.toObject();
    HTFilePath path = HTFilePath::FromJson(jsonObj);
    m_SetterCallback(path);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void HTUploadPathFilterParameter::writeJson(QJsonObject& json)
{
  if(m_GetterCallback)
  {
    HTFilePath path = m_GetterCallback();
    QJsonObject jsonObj = path.toJson();
    json[getPropertyName()] = jsonObj;
  }
}

// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::Pointer HTUploadPathFilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::Pointer HTUploadPathFilterParameter::New()
{
  Pointer sharedPtr(new(HTUploadPathFilterParameter));
  return sharedPtr;
}

// -----------------------------------------------------------------------------
QString HTUploadPathFilterParameter::getNameOfClass() const
{
  return QString("HTUploadPathFilterParameter");
}

// -----------------------------------------------------------------------------
QString HTUploadPathFilterParameter::ClassName()
{
  return QString("HTUploadPathFilterParameter");
}

// -----------------------------------------------------------------------------
void HTUploadPathFilterParameter::setSetterCallback(const HTUploadPathFilterParameter::SetterCallbackType& value)
{
  m_SetterCallback = value;
}

// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::SetterCallbackType HTUploadPathFilterParameter::getSetterCallback() const
{
  return m_SetterCallback;
}

// -----------------------------------------------------------------------------
void HTUploadPathFilterParameter::setGetterCallback(const HTUploadPathFilterParameter::GetterCallbackType& value)
{
  m_GetterCallback = value;
}

// -----------------------------------------------------------------------------
HTUploadPathFilterParameter::GetterCallbackType HTUploadPathFilterParameter::getGetterCallback() const
{
  return m_GetterCallback;
}
