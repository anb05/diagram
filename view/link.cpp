#include "link.h"
#include "node.h"

namespace dia {

Link::Link(Node* fromNode, Node* toNode)
	: _fromNode {fromNode}
	, _toNode   {toNode}
{
	_fromNode->addLink(this);
}

Link::~Link() = default;

Node* Link::fromNode()
{
	return _fromNode;
}

Node* Link::toNode()
{
	return _toNode;
}

void Link::setColor(const QColor& color)
{  }

QColor Link::color() const
{
	return QColor();
}

void Link::trackNodes()
{ }


} // namespace dia
