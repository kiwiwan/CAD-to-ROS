#ifndef __ORIGIN_PROPERTY_H__
#define __ORIGIN_PROPERTY_H__

#include <QtCore>

#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>

#include <urdf_model/joint.h>


namespace urdf_editor
{
  class OriginProperty : public QObject
  {
    Q_OBJECT
  public:
    OriginProperty(urdf::Pose &origin);
    ~OriginProperty();

    void loadFactoryForManager(boost::shared_ptr<QtTreePropertyBrowser> &property_editor);

    void loadData();

    QtProperty *getTopItem() { return top_item_; }

  private slots:
    void onValueChanged(QtProperty *property, const QVariant &val);

  signals:
    void valueChanged(QtProperty *property, const QVariant &val);

  private:
    urdf::Pose &origin_;
    QtVariantPropertyManager *manager_;
    QtVariantEditorFactory *factory_;
    QtProperty *top_item_;
    bool loading_;
  };
}

#endif // __ORIGIN_PROPERTY_H__
