// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <iterator>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>

using namespace ModelView;

void Utils::iterate(SessionItem* item, const std::function<void(SessionItem*)>& fun)
{
    if (item)
        fun(item);
    else
        return;

    for (auto child : item->children())
        iterate(child, fun);
}

void Utils::iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun)
{
    bool proceed_with_children(true);

    if (item)
        proceed_with_children = fun(item);

    if (!item || !proceed_with_children)
        return;

    for (auto child : item->children())
        iterate_if(child, fun);
}

int Utils::CopyNumber(const SessionItem* item)
{
    int result(-1);

    if (!item)
        return result;

    int count(0);
    auto model_type = item->modelType();
    if (auto parent = item->parent()) {
        for (auto child : parent->children()) {
            if (child == item)
                result = count;
            if (child->modelType() == model_type)
                ++count;
        }
    }

    return count > 1 ? result : -1;
}

SessionItem* Utils::ChildAt(const SessionItem* parent, int index)
{
    if (!parent)
        return nullptr;

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
               ? container[static_cast<size_t>(index)]
               : nullptr;
}

int Utils::IndexOfChild(const SessionItem* parent, const SessionItem* child)
{
    auto container = parent->children();
    auto pos = find(container.begin(), container.end(), child);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}

std::vector<SessionItem*> Utils::TopLevelItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (!item.isSinglePropertyTag(item.tagOfItem(child)))
            result.push_back(child);
    return result;
}

std::vector<SessionItem*> Utils::SinglePropertyItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (item.isSinglePropertyTag(item.tagOfItem(child)))
            result.push_back(child);
    return result;
}

SessionItem* Utils::FindNextSibling(SessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = item->tagRow();
    return parent->getItem(tagrow.tag, tagrow.row + 1);
}

SessionItem* Utils::FindPreviousSibling(SessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = parent->tagRowOfItem(item);
    return parent->getItem(tagrow.tag, tagrow.row - 1);
}

SessionItem* Utils::FindNextItemToSelect(SessionItem* item)
{
    auto next = FindNextSibling(item);
    auto closest = next ? next : FindPreviousSibling(item);
    return closest ? closest : item->parent();
}

bool Utils::IsItemAncestor(const SessionItem* item, const SessionItem* candidate)
{
    const SessionItem* parent = item->parent();
    while (parent) {
        if (parent == candidate)
            return true;
        else
            parent = parent->parent();
    }
    return false;
}
