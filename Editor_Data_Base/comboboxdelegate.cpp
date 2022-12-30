#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString     deviceName;
    QComboBox *editor = new QComboBox(parent);
    QSqlQuery query("SELECT name FROM Devices");
    while (query.next())
    {
       editor->addItem(query.value(0).toString());
       qDebug() << editor;
    }
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

