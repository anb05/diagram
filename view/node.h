#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>

namespace dia {
class Link;
} // namespace dia

namespace dia {

class Node : public QGraphicsItem
{
public:
	Node();
	~Node();

public:
	void addLink(Link* link);
	void removeLink(Link* link);
};

} // namespace dia

#endif // NODE_H
