#include "mainwindow.h"
#include "../view/link.h"
#include "../view/node.h"
#include "../view/propertiesdialog.hpp"

#include <QList>
#include <QAction>
#include <QString>
#include <QMenu>
#include <QClipboard>
#include <QApplication>
#include <QColorDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace dia {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Diagram"));

    _scene = new QGraphicsScene(0, 0, 800, 600);

    _view  = new QGraphicsView();
    _view->setScene(_scene);
    _view->setDragMode(QGraphicsView::RubberBandDrag);
    _view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    _view->setContextMenuPolicy(Qt::ActionsContextMenu);

    setCentralWidget(_view);

    _minZ = 0;
    _maxZ = 0;
    _seqNumber = 0;

    createActions();
    createMenus();
    createToolBars();

    connect(_scene, SIGNAL(selectionChanged()),
            this,   SLOT(updateActions()));
    updateActions();
}

void MainWindow::addNode()
{
    Node* node = new Node;
    node->setText(tr("Node %1").arg(_seqNumber + 1));
    setupNode(node);
}

void MainWindow::addLink()
{
    node_pair nodes = selectedNodePair();
    if (nodes == node_pair()) {
        return;
    }
    Link* link = new Link(nodes.first, nodes.second);
    _scene->addItem(link);
}

void MainWindow::del()
{
    QList<QGraphicsItem*> items = _scene->selectedItems();

    QMutableListIterator<QGraphicsItem* > i(items);

    while (i.hasNext()) {
        Link* link = dynamic_cast<Link*>(i.next());

        if (link) {
            delete link;
            i.remove();
        }
    }
    qDeleteAll(items);
}

void MainWindow::cut()
{
    Node* node = selectedNode();
    if (node == nullptr)
        return;
    copy();
    delete node;
}

void MainWindow::copy()
{
    Node* node = selectedNode();

    if (!node)
        return;

    QString str = QString("Node %1 %2 %3 %4")
            .arg(node->textColor().name())
            .arg(node->outlineColor().name())
            .arg(node->backgroundColor().name())
            .arg(node->text());

    QApplication::clipboard()->setText(str);
}

void MainWindow::paste()
{
    QString str = QApplication::clipboard()->text();

    QStringList parts = str.split(" ");

    if (parts.count() >= 5 && parts.first() == "Node") {
        Node* node = new Node;
        node->setText(QStringList(parts.mid(4)).join(" "));
        node->setTextColor(QColor(parts[1]));
        node->setOutlineColor(QColor(parts[2]));
        node->setBackgroundColor(QColor(parts[3]));

        setupNode(node);
    }
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
    Node* node = selectedNode();
    Link* link = selectedLink();

    if (node) {
        PropertiesDialog dialog(node, this);
        dialog.exec();
    }
    if (link) {
        QColor color = QColorDialog::getColor(link->color());
        if (color.isValid())
            link->setColor(color);
    }
}

void MainWindow::updateActions()
{
    bool hasSelection = !_scene->selectedItems().isEmpty();
    bool isNode = (selectedNode() != 0);
    bool isNodePair = (selectedNodePair() != node_pair());

    _cutAction->setEnabled(isNode);
    _copyAction->setEnabled(isNode);
    _addLinkAction->setEnabled(isNodePair);
    _deleteAction->setEnabled(hasSelection);
    _bringToFrontAction->setEnabled(isNode);
    _sendToBackAction->setEnabled(isNode);
    _propertiesAction->setEnabled(isNode);

    foreach (QAction *action, _view->actions())
        _view->removeAction(action);

    foreach (QAction *action, _editMenu->actions()) {
        if (action->isEnabled())
            _view->addAction(action);
    }
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
    return nullptr;
}

Link* MainWindow::selectedLink() const
{
    QList<QGraphicsItem*> items = _scene->selectedItems();

    if (items.count() == 1) {
        return dynamic_cast<Link*>(items.first());
    }
    return nullptr;
}

MainWindow::node_pair MainWindow::selectedNodePair() const
{
    QList<QGraphicsItem*> items = _scene->selectedItems();

    if (2 == items.count()) {
        Node* first = dynamic_cast<Node*>(items.first());
        Node* second = dynamic_cast<Node*>(items.last());
        if (first && second)
            return node_pair(first, second);
    }
    return node_pair();
}

MainWindow::~MainWindow() = default;

} // namespace dia
