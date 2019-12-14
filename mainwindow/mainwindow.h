#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPair>

#include "../view/node.h"

class QAction;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;

namespace dia {
class Link;
class Node;
} // namespace dia

namespace dia {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: // CONSTRUCTORS
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    explicit MainWindow(const MainWindow& )    = delete;
    explicit MainWindow(MainWindow&& )         = delete;

public: // OPERATORS
    MainWindow& operator= (const MainWindow& ) = delete;
    MainWindow& operator= (MainWindow&& )      = delete;

public slots:
    void addNode();
    void addLink();
    void del();
    void cut();
    void copy();
    void paste();
    void bringToFront();
    void sendToBack();
    void properties();
    void updateActions();

private:
    typedef QPair<Node*, Node*> node_pair;

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void setZValue(int z);
    void setupNode(Node* node);
    Node* selectedNode() const;
    Link* selectedLink() const;
    node_pair selectedNodePair() const;

private:
    QMenu*    _fileMenu           {nullptr};
    QMenu*    _editMenu           {nullptr};
    QToolBar* _editToolBar        {nullptr};

    QAction*  _exitAction         {nullptr};
    QAction*  _addNodeAction      {nullptr};
    QAction*  _addLinkAction      {nullptr};
    QAction*  _deleteAction       {nullptr};
    QAction*  _cutAction          {nullptr};
    QAction*  _copyAction         {nullptr};
    QAction*  _pasteAction        {nullptr};
    QAction*  _bringToFrontAction {nullptr};
    QAction*  _sendToBackAction   {nullptr};
    QAction*  _propertiesAction   {nullptr};

    QGraphicsScene* _scene        {nullptr};
    QGraphicsView*  _view         {nullptr};

    int _minZ;
    int _maxZ;
    int _seqNumber;
};

} // namespace dia

#endif // MAINWINDOW_H
