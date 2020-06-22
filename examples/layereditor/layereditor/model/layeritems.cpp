// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVariant>
#include <layereditor/model/item_constants.h>
#include <layereditor/model/layeritems.h>
#include <layereditor/model/materialmodel.h>
#include <mvvm/model/externalproperty.h>

using namespace ModelView;

LayerItem::LayerItem() : CompoundItem(::Constants::LayerType)
{
    addProperty(P_NAME, "Layer")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}

MultiLayerItem::MultiLayerItem() : CompoundItem(::Constants::MultiLayerType)
{
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {::Constants::MultiLayerType, ::Constants::LayerType};
    registerTag(TagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);
}