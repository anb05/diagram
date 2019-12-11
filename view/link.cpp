#include "link.h"
#include "node.h"

#include <QPen>

namespace dia {

Link::Link(Node* fromNode, Node* toNode)
	: _fromNode {fromNode}
	, _toNode   {toNode}
{
	_fromNode->addLink(this);
	_toNode->addLink(this);
	setFlags(QGraphicsItem::ItemIsSelectable);
	setZValue(-1);
	setColor(Qt::darkRed);
	trackNodes();
}

Link::~Link()
{
	_fromNode->removeLink(this);
	_toNode->removeLink(this);
}

Node* Link::fromNode()
{
	return _fromNode;
}

Node* Link::toNode()
{
	return _toNode;
}

void Link::setColor(const QColor& color)
{
//	setPen(QPen(QBrush(color), 1.0));
	setPen(QPen(color, 1.0));
}

QColor Link::color() const
{
	return pen().color();
}

void Link::trackNodes()
{
	setLine(QLineF(_fromNode->pos(), _toNode->pos()));
}

} // namespace dia
