#include "myview.h"

QSize myView::sizeHint() const
{
    return QSize(sceneRect().width(),sceneRect().height());
}
