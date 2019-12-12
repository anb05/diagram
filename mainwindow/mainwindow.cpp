#include "mainwindow.h"
#include "../view/link.h"
#include "../view/node.h"

#include <QList>
#include <QGraphicsScene>
#include <QGraphicsItem>

namespace dia {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{ }

void MainWindow::addNode()
{

}

void MainWindow::addLind()
{

}

void MainWindow::del()
{

}

void MainWindow::cut()
{

}

void MainWindow::copy()
{

}

void MainWindow::paste()
{

}

void MainWindow::bringToFront()
{
    ++_maxZ;
    setZValue(_maxZ);
}

void MainWindow::sendToBack()
{
    --_minZ;
    setZValue(_minZ);
}

void MainWindow::properties()
{

}

void MainWindow::updateActions()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::createToolBars()
{

}

void MainWindow::setZValue(int z)
{
    Node* node = selectedNode();
    if (node) {
        node->setZValue(z);
    }
}

void MainWindow::setupNode(Node* node)
{
    node->setPos(80 + (100 * (_seqNumber %5 )),
                 80 + (50  * (_seqNumber / 5) %7));
    _scene->addItem(node);

    ++_seqNumber;

    _scene->clearSelection();
    node->setSelected(true);
    bringToFront();
}

Node* MainWindow::selectedNode() const
{
    QList<QGraphicsItem*> items = _scene->selectedItems();

    if (items.count() == 1) {
        return dynamic_cast<Node*>(items.first());
    }
    else {
        return nullptr;
    }
}

Link* MainWindow::selectedLink() const
{

}

MainWindow::node_pair MainWindow::selectedNodePair() const
{

}

MainWindow::~MainWindow() = default;

} // namespace dia
