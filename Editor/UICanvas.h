#ifndef UICANVAS_H
#define UICANVAS_H
#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QTimer>


class UICanvas : public QWidget
{
	Q_OBJECT

public:
	UICanvas( QWidget* parent = 0 );
	~UICanvas();

	void	initialize();

	//	reimplemented QWidget
protected:
	virtual void	paintEvent( QPaintEvent* evt );
	virtual void	mousePressEvent( QMouseEvent* evt );
	virtual void	mouseMoveEvent( QMouseEvent* evt );
	virtual void	mouseReleaseEvent( QMouseEvent* evt );
	virtual void	mouseDoubleClickEvent( QMouseEvent* evt );
	virtual void	leaveEvent( QEvent* evt );

	virtual	void	dragEnterEvent( QDragEnterEvent* evt );
	virtual	void	dragMoveEvent( QDragMoveEvent* evt );
	virtual	void	dropEvent( QDropEvent* evt );

private:
	void	_mouseMove( int mouseX, int mouseY );

public slots:
	void	TimerUpdate();
	
private:
	QTimer*						mTimerUpdate;	
	float						mTimeStep;
};
#endif