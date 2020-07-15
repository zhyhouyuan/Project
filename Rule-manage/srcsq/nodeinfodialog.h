#ifndef NODEINFODIALOG_H
#define NODEINFODIALOG_H

#include <QDialog>

class Node;
class QLabel;
class QLineEdit;
class NodeInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodeInfoDialog(Node *node, QWidget *parent = 0);
    ~NodeInfoDialog();

    void initNodeInfoDialog();

private:
    QLabel    *m_nameLabel;
    QLineEdit *m_nameEdit;
    QLabel    *m_xLabel;
    QLineEdit *m_xEdit;
    QLabel    *m_yLabel;
    QLineEdit *m_yEdit;
    QLabel    *m_parentCountLabel;
    QLineEdit *m_parentCountEdit;
    QLabel    *m_childCountLabel;
    QLineEdit *m_childCountEdit;

    Node      *m_node;

};

#endif // NODEINFODIALOG_H
