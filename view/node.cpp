#include "node.h"
#include "link.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFontMetricsF>
#include <QInputDialog>
#include <QApplication>
#include <QPainter>
#include <QPen>

namespace dia {

Node::Node()
    : _textColor(Qt::darkGreen)
    , _backgroundColor(Qt::white)
    , _outlineColor(Qt::darkBlue)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

Node::~Node()
{
//	foreach(Link* link, _pLinks) {
//		delete link;
//	}
    for (Link* link: _pLinks) {
        delete link;
    }
    _pLinks.clear();
}

void Node::setText(const QString& text)
{
    prepareGeometryChange();
    _text = text;
    update();
}

QString Node::text() const
{
    return _text;
}

void Node::setTextColor(const QColor& color)
{
    _textColor = color;
    update();
}

QColor Node::textColor() const
{
    return _textColor;
}

void Node::setOutlineColor(const QColor& color)
{
    _outlineColor = color;
    update();
}

QColor Node::outlineColor() const
{
    return _outlineColor;
}

void Node::setBackgroundColor(const QColor color)
{
    _backgroundColor = color;
    update();
}

QColor Node::backgroundColor() const
{
    return _backgroundColor;
}

void Node::addLink(Link* link)
{
    _pLinks.insert(link);
}

void Node::removeLink(Link* link)
{
    _pLinks.remove(link);
}

QRectF Node::boundingRect() const
{
    constexpr int MARGIN = 1;
    return outlineRect().adjusted(-MARGIN, -MARGIN, MARGIN, MARGIN);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();
    QPainterPath path;
    path.addRoundedRect(rect,
                        roundness(rect.width()),
                        roundness(rect.height()));
    return path;
}



void Node::paint(QPainter* painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget* widget)
{
    Q_UNUSED(widget)

    QPen pen(_outlineColor);

    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(_backgroundColor);
    QRectF rect = outlineRect();
    painter->drawRoundedRect(rect,
                             roundness(rect.width()),
                             roundness(rect.height()));
    painter->setPen(_textColor);
    painter->drawText(rect, Qt::AlignCenter, _text);
}


void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QString text = QInputDialog::getText(event->widget(),
                                         tr("Edit Text"),
                                         tr("Enter new text: "),
                                         QLineEdit::Normal,
                                         _text);
    if (!text.isEmpty()) {
        setText(text);
    }
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange changed, const QVariant& value)
{
    if (changed == ItemPositionHasChanged) {
        foreach (Link* link, _pLinks) {
            link->trackNodes();
        }
    }
    return QGraphicsItem::itemChange(changed, value);
}

QRectF Node::outlineRect() const
{
    constexpr int PADDING = 8;

    QFontMetricsF metrics(qApp->font());
    QRectF rect = metrics.boundingRect(_text);
    rect.adjust(-PADDING, -PADDING, PADDING, PADDING);
    rect.translate(-rect.center());
    return rect;
}

int Node::roundness(double size) const
{
    const int DIAMETER = 12;
    return 100 * DIAMETER / int(size);
}

} // namespace dia
