/*****************************************************************************
 * PokerTH - The open source texas holdem engine                             *
 * Copyright (C) 2006-2016 Felix Hammer, Florian Thauer, Lothar May          *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                           *
 *                                                                           *
 * Additional permission under GNU AGPL version 3 section 7                  *
 *                                                                           *
 * If you modify this program, or any covered work, by linking or            *
 * combining it with the OpenSSL project's OpenSSL library (or a             *
 * modified version of that library), containing parts covered by the        *
 * terms of the OpenSSL or SSLeay licenses, the authors of PokerTH           *
 * (Felix Hammer, Florian Thauer, Lothar May) grant you additional           *
 * permission to convey the resulting work.                                  *
 * Corresponding Source for a non-source form of such a combination          *
 * shall include the source code for the parts of OpenSSL used as well       *
 * as that of the covered work.                                              *
 *****************************************************************************/
/* Async database report inappropriate avatar query. */

#ifndef _ASYNCDBREPORTGAME_H_
#define _ASYNCDBREPORTGAME_H_

#include <dbofficial/singleasyncdbquery.h>


class AsyncDBReportGame : public SingleAsyncDBQuery
{
public:
	AsyncDBReportGame(unsigned queryId, unsigned replyId, unsigned gameId, const std::string &preparedName, const std::list<std::string> &params);
	virtual ~AsyncDBReportGame();

	virtual void Init(DBIdManager& idManager);

	virtual void HandleResult(mysqlpp::Query &query, DBIdManager& idManager, mysqlpp::StoreQueryResult& result, boost::asio::io_service &service, ServerDBCallback &cb);
	virtual void HandleNoResult(mysqlpp::Query &query, DBIdManager& idManager, boost::asio::io_service &service, ServerDBCallback &cb);
	virtual void HandleError(boost::asio::io_service &service, ServerDBCallback &cb);

	virtual bool RequiresResultSet() const
	{
		return false;
	}

private:
	unsigned m_replyId;
	unsigned m_gameId;
};

#endif
