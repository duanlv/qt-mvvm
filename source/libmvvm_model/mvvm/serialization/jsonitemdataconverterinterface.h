// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H

#include <mvvm/model_export.h>

class QJsonArray;

namespace ModelView
{

class SessionItemData;

//! Base class for all converters of SessionItemData to/from json object

class MVVM_MODEL_EXPORT JsonItemDataConverterInterface
{
public:
    virtual ~JsonItemDataConverterInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual std::unique_ptr<SessionItemData> get_data(const QJsonArray&) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H