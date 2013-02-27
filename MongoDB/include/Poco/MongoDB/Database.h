//
// Database.h
//
// $Id$
//
// Library: MongoDB
// Package: MongoDB
// Module:  Database
//
// Definition of the Database class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
#ifndef _MongoDB_Database_included
#define _MongoDB_Database_included

#include "Poco/MongoDB/MongoDB.h"
#include "Poco/MongoDB/Connection.h"
#include "Poco/MongoDB/Document.h"
#include "Poco/MongoDB/QueryRequest.h"
#include "Poco/MongoDB/InsertRequest.h"

namespace Poco {
namespace MongoDB {


class MongoDB_API Database
	/// Database is a helper class for creating requests. MongoDB works with
	/// collection names and uses the part before the first dot as the name of
	/// the database.
{
public:
	Database(const std::string& db);
		/// Constructor


	virtual ~Database();
		/// Destructor


	double count(Connection& connection, const std::string& collectionName) const;
		/// Sends a count request for the given collection to MongoDB. When
		/// the command fails, -1 is returned.


	Poco::SharedPtr<Poco::MongoDB::QueryRequest> createCommand() const;
		/// Creates a QueryRequest for a command.


	Poco::SharedPtr<Poco::MongoDB::QueryRequest> createCountRequest(const std::string& collectionName) const;
		/// Creates a QueryRequest to count the given collection. The collectionname must not contain
		/// the database name!


	Poco::SharedPtr<Poco::MongoDB::InsertRequest> createInsertRequest(const std::string& collectionName) const;
		/// Creates an InsertRequest to insert new documents in the given collection.
		/// The collectionname must not contain the database name!


	Poco::SharedPtr<Poco::MongoDB::QueryRequest> createQueryRequest(const std::string& collectionName) const;
		/// Creates a QueryRequest. The collectionname must not contain the database name!


	Poco::MongoDB::Document::Ptr ensureIndex(Connection& connection, const std::string& collection, const std::string& indexName, Poco::MongoDB::Document::Ptr keys, bool unique = false, bool background = false, int version = 0, int ttl = 0);
		/// Creates an index. The document returned is the result of a getLastError call.
		/// For more info look at the ensureIndex information on the MongoDB website.

 
	Document::Ptr getLastErrorDoc(Connection& connection) const;
		/// Sends the getLastError command to the database and returns the document


	std::string getLastError(Connection& connection) const;
		/// Sends the getLastError command to the database and returns the err element
		/// from the error document. When err is null, an empty string is returned.

private:
	std::string _dbname;
};


inline Poco::SharedPtr<Poco::MongoDB::QueryRequest> Database::createCommand() const
{
	Poco::SharedPtr<Poco::MongoDB::QueryRequest> cmd = createQueryRequest("$cmd");
	cmd->setNumberToReturn(1);
	return cmd;
}

}} // Namespace Poco::MongoDB

#endif // _MongoDB_Database_included
