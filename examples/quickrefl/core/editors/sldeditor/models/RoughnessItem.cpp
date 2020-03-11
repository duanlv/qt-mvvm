// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "RoughnessItem.h"
#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

RoughnessItem::RoughnessItem() : ModelView::CompoundItem("RoughnessItem")
{
    addProperty(P_ROUGHNESS, 10.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Roughness");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
}

void RoughnessItem::setLayerIdentifier(std::string layer_identifier_in)
{
    layer_identifier = layer_identifier_in;
}

std::string RoughnessItem::layerIdentifier(std::string layer_identifier_in)
{
    return layer_identifier;
}
