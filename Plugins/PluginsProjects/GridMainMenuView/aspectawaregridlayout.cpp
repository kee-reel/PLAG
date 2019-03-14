#include "aspectawaregridlayout.h"

AspectAwareGridLayout::AspectAwareGridLayout(QWidget *parent) : QGridLayout(parent)
{
}

int AspectAwareGridLayout::heightForWidth(int w) const
{
    return w;
}

bool AspectAwareGridLayout::hasHeightForWidth() const
{
    return true;
}
