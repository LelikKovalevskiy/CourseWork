#include "myview.h"

QSize myView::sizeHint()const
{
    return QSize(200/*sceneRect().width()*/,200/*sceneRect().height()*/);
}
