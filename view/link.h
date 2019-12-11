#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>

namespace dia {
class Node;
} // namespace dia

namespace dia {

class Link : public QGraphicsLineItem
{
public:
	explicit Link(Node* fromNode, Node* toNode);
	~Link() override;

	explicit Link(const Link& )    = delete;
	explicit Link(Link&& )         = delete;

public:
	Link& operator= (const Link& ) = delete;
	Link& operator= (Link&& )      = delete;

public:
	Node* fromNode();
	Node* toNode();

	void setColor(const QColor& color);
	QColor color() const;

	void trackNodes();

private:
	Node* _fromNode {nullptr};
	Node* _toNode   {nullptr};
};

} // namespace dia

#endif // LINK_H
