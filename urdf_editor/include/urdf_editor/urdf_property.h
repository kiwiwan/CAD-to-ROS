#ifndef __URDF_PROPERTY_H__
#define __URDF_PROPERTY_H__

#include <QtCore>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>

#include <qttreepropertybrowser.h>
#include <urdf_editor/urdf_property_tree.h>
#include <urdf_editor/my_rviz.h>

#include <urdf_editor/urdf_types.h>
#include <urdf_editor/property_types.h>
#include <urdf_editor/qt_types.h>


namespace urdf_editor
{
  class URDFProperty : public QObject
  {
    Q_OBJECT
  public:
    URDFProperty(URDFPropertyTree *tree_widget, QWidget *browser_parent, QWidget *rviz_parent);
    ~URDFProperty();

    bool loadURDF(QString file_path);

    bool saveURDF(QString file_path);

    bool clear();

    bool unsavedChanges;

  private slots:
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemDragDrop(QTreeWidgetItem *drag, QTreeWidgetItem *drop);

    void on_propertyWidget_customContextMenuRequested(const QPoint &pos);

    void on_propertyWidget_linkNameChanged(LinkProperty *property, const QVariant &val);

    void on_propertyWidget_jointNameChanged(JointProperty *property, const QVariant &val);

    void on_propertyWidget_jointParentLinkChanged(JointProperty *property, const QVariant &val);

    void on_propertyWidget_valueChanged();

    void on_unsavedChanges();

  signals:
    void jointAddition();

    void jointDeletion();

    void linkAddition();

    void linkDeletion();

  private:
    bool populateTreeWidget();

    /*! Set expanded value for all children for a QTreeWidgetItem (recursively) */
    void setAllChildrenExpandedValue(QTreeWidgetItem *parent, bool expanded);

    void addToTreeWidget(urdf::LinkSharedPtr link, QTreeWidgetItem* parent);
    void addToTreeWidget(urdf::JointSharedPtr joint, QTreeWidgetItem* parent);

    urdf::LinkSharedPtr addModelLink(QTreeWidgetItem* parent);
    QTreeWidgetItem* addLinkTreeItem(QTreeWidgetItem* parent, urdf::LinkSharedPtr link);
    LinkPropertySharedPtr addLinkProperty(QTreeWidgetItem* item, urdf::LinkSharedPtr link);

    void removeModelLink(QString link_name);
    void removeLinkTreeItem(QTreeWidgetItem *item);

    urdf::JointSharedPtr addModelJoint(QTreeWidgetItem *parent, QString child_link_name);
    QTreeWidgetItem* addJointTreeItem(QTreeWidgetItem* parent, urdf::JointSharedPtr joint);
    JointPropertySharedPtr addJointProperty(QTreeWidgetItem *item, urdf::JointSharedPtr joint);

    void removeModelJoint(QString joint_name);
    void removeJointTreeItem(QTreeWidgetItem *item);

    QString getValidName(QString prefix, QList<QString> &current_names);

    bool isJoint(QTreeWidgetItem *item);
    bool isLink(QTreeWidgetItem *item);

    boost::shared_ptr<QtTreePropertyBrowser> property_editor_;
    urdf::ModelInterfaceSharedPtr model_;

    // this map urdf::LinkSharedPtr to link-tree-items
    QMap<urdf::LinkSharedPtr, QTreeWidgetItem *> link_to_ltree_;

    // this map joint child link to chain-tree-items
    QMap<urdf::LinkSharedPtr, QTreeWidgetItem *> joint_child_to_ctree_;

    // these map chain-tree-items to joint properties
    QMap<QTreeWidgetItem *, JointPropertySharedPtr> ctree_to_joint_property_;
    // and joint properties to chain-tree-items
    QMap<JointProperty *, QTreeWidgetItem *> joint_property_to_ctree_;

    // these map link-tree-items to link properties
    QMap<QTreeWidgetItem *, LinkPropertySharedPtr> ltree_to_link_property_;
    // and link properties to link-tree-items
    QMap<LinkProperty *, QTreeWidgetItem *> link_property_to_ltree_;

    QStringList link_names_, joint_names_;
    QTreeWidgetItem *root_;
    QTreeWidgetItem *link_root_;
    QTreeWidgetItem *joint_root_;
    URDFPropertyTree *tree_widget_;
    QWidget *browser_parent_;
    urdf_editor::MyRviz *rviz_widget_;
  };
}

#endif // __URDF_PROPERTY_H__
