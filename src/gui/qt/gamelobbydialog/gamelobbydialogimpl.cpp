//
// C++ Implementation: gamelobbydialogimpl
//
// Description: 
//
//
// Author: FThauer FHammer <webmaster@pokerth.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "gamelobbydialogimpl.h"
#include "session.h"
#include "configfile.h"
#include "gamedata.h"

gameLobbyDialogImpl::gameLobbyDialogImpl(QWidget *parent, ConfigFile *c)
 : QDialog(parent), myConfig(c)
{
    setupUi(this);

	connect( pushButton_CreateGame, SIGNAL( clicked() ), this, SLOT( createGame() ) );
	connect( pushButton_JoinGame, SIGNAL( clicked() ), this, SLOT( joinGame() ) );
	connect( treeWidget_GameList, SIGNAL( itemClicked ( QTreeWidgetItem*, int) ), this, SLOT( gameSelected(QTreeWidgetItem*, int) ) );

	pushButton_JoinGame->setEnabled(false);
}

void gameLobbyDialogImpl::exec()
{

	QDialog::exec();
}


gameLobbyDialogImpl::~gameLobbyDialogImpl()
{
}

void gameLobbyDialogImpl::setSession(Session *session)
{
	mySession = session;
}

void gameLobbyDialogImpl::createGame()
{
	assert(mySession);

	myCreateInternetGameDialog = new createInternetGameDialogImpl(this, myConfig);
	myCreateInternetGameDialog->exec();
	
	if (myCreateInternetGameDialog->result() == QDialog::Accepted ) {
	
		GameData gameData;
		// Set Game Data
		gameData.maxNumberOfPlayers = myCreateInternetGameDialog->spinBox_quantityPlayers->value();
		gameData.startMoney = myCreateInternetGameDialog->spinBox_startCash->value();
		gameData.smallBlind = myCreateInternetGameDialog->spinBox_smallBlind->value();
		gameData.handsBeforeRaise = myCreateInternetGameDialog->spinBox_handsBeforeRaiseSmallBlind->value();
		gameData.guiSpeed = myCreateInternetGameDialog->spinBox_gameSpeed->value();
		gameData.playerActionTimeoutSec = myCreateInternetGameDialog->spinBox_netTimeOutPlayerAction->value();
		
		mySession->clientCreateGame(gameData, myConfig->readConfigString("MyName") + "'s game", "");

		accept();
	}
}

void gameLobbyDialogImpl::joinGame()
{
	QTreeWidgetItem *item = treeWidget_GameList->currentItem();
	if (item)
	{
		QString gameName = item->text(0);

		assert(mySession);
		mySession->clientJoinGame(gameName.toUtf8().constData(), "");

		accept();
	}
}

void gameLobbyDialogImpl::gameSelected(QTreeWidgetItem*, int)
{
	pushButton_JoinGame->setEnabled(true);
}

void gameLobbyDialogImpl::addGame(QString gameName)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget_GameList,0);
	item->setData(0, 0, gameName);
}

void gameLobbyDialogImpl::removeGame(QString gameName)
{
	QList<QTreeWidgetItem *> list = treeWidget_GameList->findItems(gameName, Qt::MatchExactly, 0);
	if(!list.empty()) { 
		treeWidget_GameList->takeTopLevelItem(treeWidget_GameList->indexOfTopLevelItem(list[0]));
	}
}

