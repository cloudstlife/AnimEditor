#include "UICanvas.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QCursor>
#include <QtGui/QScrollBar>



UICanvas::UICanvas( QWidget* parent )
: QWidget( parent )
, mTimerUpdate( 0 )
, mTimeStep( 0.f )
{
	setMouseTracking( true );
	setAcceptDrops( true );
	setFocusPolicy( Qt::StrongFocus );
}

UICanvas::~UICanvas()
{

}

void	UICanvas::initialize()
{
	
}

void	UICanvas::paintEvent( QPaintEvent* evt )
{
	
}

void	UICanvas::mousePressEvent( QMouseEvent* evt )
{
	if ( evt->button() == Qt::LeftButton )
	{
	
	}
	else if ( evt->button() == Qt::RightButton )
	{

	}
}

void	UICanvas::mouseMoveEvent( QMouseEvent* evt )
{	
	
}

void	UICanvas::mouseReleaseEvent( QMouseEvent* evt )
{
	if ( evt->button() == Qt::LeftButton )
	{
	}
	else if ( evt->button() == Qt::RightButton )
	{
	}

}

void	UICanvas::mouseDoubleClickEvent( QMouseEvent* evt )
{
	if ( evt->button() == Qt::LeftButton )
	{
		
	}
	else if ( evt->button() == Qt::RightButton )
	{
		
	}
}

void	UICanvas::leaveEvent( QEvent* evt )
{
// 	gUIEditor.mQtUI->labelInfoMouseR->setText( QString( "-" ) );
// 	gUIEditor.mQtUI->labelInfoMouseG->setText( QString( "-" ) );
// 	gUIEditor.mQtUI->labelInfoMouseB->setText( QString( "-" ) );
}

void	UICanvas::dragEnterEvent( QDragEnterEvent* evt )
{
	
// 	if ( evt->mimeData()->hasFormat( "ceguiImage" ) )
// 	{
// 		evt->accept();
// 	}
// 	else
// 	{
// 		evt->ignore();
// 	}
}

void	UICanvas::dragMoveEvent( QDragMoveEvent* evt )
{
	QPoint mousePos = evt->pos();
	//_mouseMove( mousePos.x(), mousePos.y() );
}

void	UICanvas::dropEvent( QDropEvent* evt )
{
// 	const QMimeData *mimeData = evt->mimeData();
// 	QPoint mousePos = evt->pos();
// 
// 	if ( mimeData->hasFormat( "ceguiImage" ) )
// 	{
// 		QByteArray imageData = mimeData->data( "ceguiImage" );
// 		UIResouceNode* node = (UIResouceNode*)imageData.toUInt();
// 		
// 		UMT_CreateWindowData createWindowMsg;
// 		
// 		createWindowMsg.fileName = node->fileName;
// 		createWindowMsg.imageProperty = node->imageProperty;
// 		createWindowMsg.posX = mousePos.x();
// 		createWindowMsg.posY = mousePos.y();
// 		createWindowMsg.imageWidth = node->imageWidth;
// 		createWindowMsg.imageHeight = node->imageHeight;
// 
// 		_procUMT_CreateWindow( &createWindowMsg );
// 	}
}

void	UICanvas::_mouseMove( int mouseX, int mouseY )
{
// 	QImage image = QPixmap::grabWindow( winId(), mouseX, mouseY, 1, 1 ).toImage();
// 	QRgb rgb = image.pixel( 0, 0 );
// 	gUIEditor.mQtUI->labelInfoMouseR->setText( QString( "%1" ).arg( qRed( rgb ) ) );
// 	gUIEditor.mQtUI->labelInfoMouseG->setText( QString( "%1" ).arg( qGreen( rgb ) ) );
// 	gUIEditor.mQtUI->labelInfoMouseB->setText( QString( "%1" ).arg( qBlue( rgb ) ) );
// 
// 	gUIEditor.mQtUI->labelInfoMouseX->setText( QString( "%1" ).arg( mouseX ) );
// 	gUIEditor.mQtUI->labelInfoMouseY->setText( QString( "%1" ).arg( mouseY ) );
}


void	UICanvas::TimerUpdate()
{
	
}


