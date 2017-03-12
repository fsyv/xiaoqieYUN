#include <QComboBox>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFocusEvent>
class ComboBox :
	public QComboBox
{
	Q_OBJECT
public:
    ComboBox(QWidget *parent = Q_NULLPTR);
    ~ComboBox();
public slots:
	void setText(const QString &);
	void myRemoveItem(const QString &);
protected:
	void focusOutEvent(QFocusEvent *e)override;
private:
	void init();

	QListWidget *listWidget;
	QVector<QString> vec;
};


class ComboBoxItem:public QWidget
{
	Q_OBJECT
public:
	ComboBoxItem(QWidget *parent = 0);
	~ComboBoxItem();
	void setText(const QString &);
	QString getUserAccount();
protected:
	void mouseReleaseEvent(QMouseEvent *e);
signals:
	void sendText(const QString&);
	void deleteItem(const QString&);
private:
	QLabel *userAccount;
	QPushButton *delete_button;
};

