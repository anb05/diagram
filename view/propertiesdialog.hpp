#ifndef PROPERTIESDIALOG_HPP
#define PROPERTIESDIALOG_HPP

#include <QDialog>

namespace dia {
class Node;
} // namespace dia

namespace dia {

class PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PropertiesDialog(Node* node, QWidget* parent = nullptr);
    ~PropertiesDialog() override;

    explicit PropertiesDialog(const PropertiesDialog&)    = delete;
    explicit PropertiesDialog(PropertiesDialog&&)         = delete;

public:
    PropertiesDialog& operator= (const PropertiesDialog&) = delete;
    PropertiesDialog& operator= (PropertiesDialog&&)      = delete;

private:
};

} // namespace dia

#endif // PROPERTIESDIALOG_HPP
