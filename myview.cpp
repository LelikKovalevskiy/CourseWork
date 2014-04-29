#include "myview.h"

QSize myView::sizeHint()
{
    return QSize(sceneRect().width(),sceneRect().height());
}
