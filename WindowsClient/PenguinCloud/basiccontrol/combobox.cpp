#include "combobox.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QLineEdit>
#include <QMessageBox>
ComboBox::ComboBox(QWidget *parent):QComboBox(parent)
{
	init();
}


ComboBox::~ComboBox()
{
	
}


void ComboBox::init()
{
	//初始设置
	listWidget = new QListWidget;
	this->setEditable(true);
	setModel(listWidget->model());
	setView(listWidget);
	setInsertPolicy(QComboBox::NoInsert); //自己插入ITEM
}
void ComboBox::focusOutEvent(QFocusEvent *e)
{
	QComboBox::focusOutEvent(e);
	QString s = lineEdit()->text();
	if ( s != "" && !vec.contains(s)) {
		vec.push_front(s);
		ComboBoxItem *item = new ComboBoxItem;
		item->setText(vec.front());
		QListWidgetItem *l_item = new QListWidgetItem();
		l_item->setSizeHint(QSize(180, 38));
		listWidget->addItem(l_item);
		listWidget->setItemWidget(l_item, item);
        connect(item, &ComboBoxItem::sendText, this, &ComboBox::setText);
        connect(item, &ComboBoxItem::deleteItem, this, &ComboBox::myRemoveItem);
		lineEdit()->setText(vec.front());
	}
	
}
void ComboBox::setText(const QString &str)
{
	this->setEditText(str);
	this->hidePopup();
}

void ComboBox::myRemoveItem(const QString &str)
{
	qDebug() << this->model()->rowCount();
	int ret = QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("确认删除?"), QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		for (int i = 0; i < model()->rowCount(); ++i)
		{
			ComboBoxItem *item = (ComboBoxItem *)(listWidget->itemWidget(listWidget->item(i)));
			if (item->getUserAccount() == str)
			{
				listWidget->takeItem(i);
				
				for (auto i = vec.begin(); i != vec.end();)
				{
					if (*i == str) {
						i = vec.erase(i);
					}
					else
						++i;
				}
				break;
			}
		}
	}
}

ComboBoxItem::ComboBoxItem(QWidget *parent) : QWidget(parent)
{
	
	userAccount = new QLabel("liuzheng");
	delete_button = new QPushButton;

	delete_button->setStyleSheet("border:none");
    QPixmap p(":/resource/image/comboboxitem_delete.png");
	delete_button->setIcon(p);
	delete_button->setIconSize(p.size());
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(userAccount);
	layout->addStretch();
	layout->addWidget(delete_button);
	layout->setContentsMargins(5, 5, 5, 5);
	layout->addSpacing(9);
	this->setLayout(layout);

	connect(delete_button, &QPushButton::clicked, this, [&]() {emit deleteItem(userAccount->text()); });
}

ComboBoxItem::~ComboBoxItem()
{
	delete userAccount;
	delete delete_button;
}

void ComboBoxItem::setText(const QString &str)
{
	userAccount->setText(str);
}
void ComboBoxItem::mouseReleaseEvent(QMouseEvent *e)
{
	//QWidget::mouseReleaseEvent(e);
	if (e->button() == Qt::LeftButton)
	{
		emit sendText(userAccount->text());
	}
}
QString ComboBoxItem::getUserAccount()
{
	return userAccount->text();
}
