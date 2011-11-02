//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : tags_database.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include <wx/longlong.h>
#include "tags_storage_sqlite3.h"
#include <wx/tokenzr.h>

#if 0
#define SQL_LOG 1
#ifdef __WXMSW__
# define SQL_LOG_NAME "codelite_tags_sql.log"
#else
# define SQL_LOG_NAME "/tmp/codelite_tags_sql.log"
#endif
static FILE* log_fp = NULL;
#endif

//-------------------------------------------------
// Tags database class implementation
//-------------------------------------------------
TagsStorageSQLite::TagsStorageSQLite()
	: ITagsStorage()
{
	m_db    = new clSqliteDB();
	SetUseCache(true);
}

TagsStorageSQLite::~TagsStorageSQLite()
{
	if (m_db) {
		m_db->Close();
		delete m_db;
		m_db = NULL;
	}
}

void TagsStorageSQLite::OpenDatabase(const wxFileName& fileName)
{
	if (m_fileName.GetFullPath() == fileName.GetFullPath())
		return;

	// Did we get a file name to use?
	if (!fileName.IsOk() && !m_fileName.IsOk())
		return;

	// We did not get any file name to use BUT we
	// do have an open database, so we will use it
	if (!fileName.IsOk())
		return;

	try {
		if (!m_fileName.IsOk()) {
			// First time we open the db
			m_db->Open(fileName.GetFullPath());
			CreateSchema();
			m_fileName = fileName;

		} else {
			// We have both fileName & m_fileName and they
			// are different, Close previous db
			m_db->Close();
			m_db->Open(fileName.GetFullPath());
			CreateSchema();
			m_fileName = fileName;

		}

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::CreateSchema()
{
	wxString sql;

	// improve performace by using pragma command:
	// (this needs to be done before the creation of the
	// tables and indices)
	try {
		sql = wxT("PRAGMA synchronous = OFF;");
		m_db->ExecuteUpdate(sql);

		sql = wxT("PRAGMA temp_store = MEMORY;");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create  table if not exists tags (ID INTEGER PRIMARY KEY AUTOINCREMENT, name string, file string, line integer, kind string, access string, signature string, pattern string, parent string, inherits string, path string, typeref string, scope string, return_value string);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create  table if not exists FILES (ID INTEGER PRIMARY KEY AUTOINCREMENT, file string, last_retagged integer);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create  table if not exists MACROS (ID INTEGER PRIMARY KEY AUTOINCREMENT, file string, line integer, name string, is_function_like int, replacement string, signature string);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create  table if not exists SIMPLE_MACROS (ID INTEGER PRIMARY KEY AUTOINCREMENT, file string, name string);");
		m_db->ExecuteUpdate(sql);

		// create unuque index on Files' file column
		sql = wxT("CREATE UNIQUE INDEX IF NOT EXISTS FILES_NAME on FILES(file)");
		m_db->ExecuteUpdate(sql);

		// Create unique index on tags table
		sql = wxT("CREATE UNIQUE INDEX IF NOT EXISTS TAGS_UNIQ on tags(kind, path, signature);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS KIND_IDX on tags(kind);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS FILE_IDX on tags(file);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE UNIQUE INDEX IF NOT EXISTS MACROS_UNIQ on MACROS(name);");
		m_db->ExecuteUpdate(sql);

		// Create search indexes
		sql = wxT("CREATE INDEX IF NOT EXISTS TAGS_NAME on tags(name);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS TAGS_SCOPE on tags(scope);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS TAGS_PATH on tags(path);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS TAGS_PARENT on tags(parent);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS MACROS_NAME on MACROS(name);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("CREATE INDEX IF NOT EXISTS SIMPLE_MACROS_FILE on SIMPLE_MACROS(file);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create table if not exists tags_version (version string primary key);");
		m_db->ExecuteUpdate(sql);

		sql = wxT("create unique index if not exists tags_version_uniq on tags_version(version);");
		m_db->ExecuteUpdate(sql);

		sql = wxString(wxT("insert into tags_version values ('")) << GetVersion() << wxT("');");
		m_db->ExecuteUpdate(sql);

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::RecreateDatabase()
{
	try {
		// commit any open transactions
		Commit();

		// Close the database
		m_db->Close();
		wxString filename = m_fileName.GetFullPath();
		if (wxRemoveFile(m_fileName.GetFullPath()) == false ) {

			// re-open the database
			m_fileName.Clear();
			OpenDatabase( filename );

			// and drop tables
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS TAGS"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS COMMENTS"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS TAGS_VERSION"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS VARIABLES"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS FILES"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS MACROS"));
			m_db->ExecuteUpdate(wxT("DROP TABLE IF EXISTS SIMPLE_MACROS"));

			// drop indexes
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS FILES_NAME"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS TAGS_UNIQ"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS KIND_IDX"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS FILE_IDX"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS TAGS_NAME"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS TAGS_SCOPE"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS TAGS_PATH"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS TAGS_PARENT"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS tags_version_uniq"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS MACROS_UNIQ"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS MACROS_NAME"));
			m_db->ExecuteUpdate(wxT("DROP INDEX IF EXISTS SIMPLE_MACROS_FILE"));

			// Recreate the schema
			CreateSchema();
		} else {
			// We managed to delete the file
			// re-open it

			m_fileName.Clear();
			OpenDatabase(filename);
		}
	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

wxString TagsStorageSQLite::GetSchemaVersion() const
{
	// return the current schema version
	try {
		wxString sql;
		wxString version;
		sql = wxT("SELECT * FROM TAGS_VERSION");
		wxSQLite3ResultSet rs = m_db->ExecuteQuery( sql );

		if ( rs.NextRow() )
			version = rs.GetString(0);
		return version;
	} catch (wxSQLite3Exception &e ) {
		wxUnusedVar(e);
	}
	return wxEmptyString;
}


void TagsStorageSQLite::Store(TagTreePtr tree, const wxFileName& path, bool autoCommit)
{
	if (!path.IsOk() && !m_fileName.IsOk()) {
		// An attempt is made to save the tree into db but no database
		// is provided and none is currently opened to use
		return;
	}

	if ( !tree )
		return;

	OpenDatabase(path);
	TreeWalker<wxString, TagEntry> walker( tree->GetRoot() );

	try {
		// Create the statements before the execution
		std::vector<TagEntry> updateList;

		// AddChild entries to database
		if ( autoCommit )
			m_db->Begin();

		for (; !walker.End(); walker++) {
			// Skip root node
			if (walker.GetNode() == tree->GetRoot())
				continue;

			// does not matter if we insert or update, the cache must be cleared for any related tags

			if (InsertTagEntry(walker.GetNode()->GetData()) == TagExist) {
				// Update the record
				updateList.push_back(walker.GetNode()->GetData());
			}
		}

		if ( autoCommit )
			m_db->Commit();

		// Do we need to update?
		if (!updateList.empty()) {
			if ( autoCommit )
				m_db->Begin();

			for (size_t i=0; i<updateList.size(); i++)
				UpdateTagEntry(updateList.at(i));

			if ( autoCommit )
				m_db->Commit();
		}
	} catch (wxSQLite3Exception& e) {
		try {
			if ( autoCommit )
				m_db->Rollback();
		} catch (wxSQLite3Exception& WXUNUSED(e1)) {
			wxUnusedVar(e);
		}
	}
}

void TagsStorageSQLite::SelectTagsByFile(const wxString& file, std::vector<TagEntryPtr> &tags, const wxFileName& path)
{
	// Incase empty file path is provided, use the current file name
	wxFileName databaseFileName(path);
	path.IsOk() == false ? databaseFileName = m_fileName : databaseFileName = path;
	OpenDatabase(databaseFileName);

	wxString query;
	query << wxT("select * from tags where file='") << file << wxT("' ");

	DoFetchTags(query, tags);
}

void TagsStorageSQLite::DeleteByFileName(const wxFileName& path, const wxString& fileName, bool autoCommit)
{
	// make sure database is open


	try {
		OpenDatabase(path);

		if ( autoCommit )
			m_db->Begin();

		m_db->ExecuteUpdate(wxString::Format(wxT("Delete from tags where File='%s'"), fileName.GetData()));

		if ( autoCommit )
			m_db->Commit();
	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
		if ( autoCommit )
			m_db->Rollback();
	}
}

wxSQLite3ResultSet TagsStorageSQLite::Query(const wxString& sql, const wxFileName& path)
{
	// make sure database is open

	try {
		OpenDatabase(path);
		return m_db->ExecuteQuery(sql);
	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
	return wxSQLite3ResultSet();
}

void TagsStorageSQLite::ExecuteUpdate(const wxString& sql)
{
	try {
		m_db->ExecuteUpdate(sql);
	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
}

const bool TagsStorageSQLite::IsOpen() const
{
	return m_db->IsOpen();
}

void TagsStorageSQLite::GetFiles(const wxString &partialName, std::vector<FileEntryPtr> &files)
{
	try {
		bool match_path = (!partialName.IsEmpty() &&
		                   partialName.Last() == wxFileName::GetPathSeparator());

		wxString query;
		wxString tmpName(partialName);
		tmpName.Replace(wxT("_"), wxT("^_"));
		query << wxT("select * from files where file like '%%") << tmpName << wxT("%%' ESCAPE '^' ")
		      << wxT("order by file");

		wxSQLite3ResultSet res = m_db->ExecuteQuery(query);
		while (res.NextRow()) {

			FileEntryPtr fe(new FileEntry());
			fe->SetId(res.GetInt(0));
			fe->SetFile(res.GetString(1));
			fe->SetLastRetaggedTimestamp(res.GetInt(2));

			wxFileName fileName(fe->GetFile());
			wxString match = match_path ? fileName.GetFullPath() : fileName.GetFullName();

			// Under Windows, all files are stored as lower case in the
			// database (see fc_fileopener.cpp normalize_path method
#ifdef __WXMSW__
			wxString lowerCasePartialName (partialName);
			lowerCasePartialName.MakeLower();
#else
			wxString lowerCasePartialName (partialName);
#endif
			if (match.StartsWith(lowerCasePartialName)) {
				files.push_back(fe);
			}
		}
	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

long TagsStorageSQLite::LastRowId() const
{
	wxLongLong id = m_db->GetLastRowId();
	return id.ToLong();
}

void TagsStorageSQLite::DeleteByFilePrefix(const wxFileName& dbpath, const wxString& filePrefix)
{
	// make sure database is open


	try {
		OpenDatabase(dbpath);
		wxString sql;
		wxString name(filePrefix);
		name.Replace(wxT("_"), wxT("^_"));

		sql << wxT("delete from tags where file like '") << name << wxT("%%' ESCAPE '^' ");
		m_db->ExecuteUpdate(sql);

	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::GetFiles(std::vector<FileEntryPtr>& files)
{
	try {
		wxString query(wxT("select * from files order by file"));
		wxSQLite3ResultSet res = m_db->ExecuteQuery(query);

		while (res.NextRow()) {

			FileEntryPtr fe(new FileEntry());
			fe->SetId(res.GetInt(0));
			fe->SetFile(res.GetString(1));
			fe->SetLastRetaggedTimestamp(res.GetInt(2));

			files.push_back( fe );
		}

	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::DeleteFromFiles(const wxArrayString& files)
{
	if (files.IsEmpty()) {
		return;
	}

	wxString query;
	query << wxT("delete from FILES where file in (");

	for (size_t i=0; i<files.GetCount(); i++) {
		query << wxT("'") << files.Item(i) << wxT("',");
	}

	// remove last ','
	query.RemoveLast();
	query << wxT(")");

	try {
		m_db->ExecuteQuery(query);
	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::DeleteFromFilesByPrefix(const wxFileName& dbpath, const wxString& filePrefix)
{
	// make sure database is open


	try {
		OpenDatabase(dbpath);
		wxString sql;
		wxString name(filePrefix);
		name.Replace(wxT("_"), wxT("^_"));

		sql << wxT("delete from FILES where file like '") << name << wxT("%%' ESCAPE '^' ");
		m_db->ExecuteUpdate(sql);

	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::PPTokenFromSQlite3ResultSet(wxSQLite3ResultSet& rs, PPToken& token)
{
	// set the name
	token.name = rs.GetString(3);

	bool isFunctionLike = rs.GetInt(4) == 0 ? false : true;

	// set the flags
	token.flags = PPToken::IsValid;
	if(isFunctionLike)
		token.flags |= PPToken::IsFunctionLike;

	token.line        = rs.GetInt(2);
	token.replacement = rs.GetString(5);

	wxString sig = rs.GetString(6);
	sig.Replace(wxT("("), wxT(""));
	sig.Replace(wxT(")"), wxT(""));
	token.args = wxStringTokenize(sig, wxT(","), wxTOKEN_STRTOK);
}

TagEntry* TagsStorageSQLite::FromSQLite3ResultSet(wxSQLite3ResultSet& rs)
{
	TagEntry *entry = new TagEntry();
	entry->SetId         (rs.GetInt(0)   );
	entry->SetName       (rs.GetString(1));
	entry->SetFile       (rs.GetString(2));
	entry->SetLine       (rs.GetInt(3)   );
	entry->SetKind       (rs.GetString(4));
	entry->SetAccess     (rs.GetString(5));
	entry->SetSignature  (rs.GetString(6));
	entry->SetPattern    (rs.GetString(7));
	entry->SetParent     (rs.GetString(8));
	entry->SetInherits   (rs.GetString(9));
	entry->SetPath       (rs.GetString(10));
	entry->SetTyperef    (rs.GetString(11));
	entry->SetScope      (rs.GetString(12));
	entry->SetReturnValue(rs.GetString(13));
	return entry;
}

void TagsStorageSQLite::DoFetchTags(const wxString& sql, std::vector<TagEntryPtr>& tags)
{
#if SQL_LOG
	if (!log_fp)
		log_fp = fopen(SQL_LOG_NAME, "w+b");
#endif

	if (GetUseCache()) {
		if (m_cache.Get(sql, tags) == true) {
#if SQL_LOG
			fprintf(log_fp, "[CACHED ITEMS] %s\n", sql.mb_str(wxConvUTF8).data());
			fflush(log_fp);
#endif
			return;
		}
	}

#if SQL_LOG
	fprintf(log_fp, "%s\n", sql.mb_str(wxConvUTF8).data());
	fflush(log_fp);
#endif

	// try the cache first
	tags.reserve( 500 );
	try {
		wxSQLite3ResultSet ex_rs;
		ex_rs = Query(sql);

		// add results from external database to the workspace database
		while ( ex_rs.NextRow() ) {
			// Construct a TagEntry from the rescord set
			TagEntryPtr tag(FromSQLite3ResultSet(ex_rs));
			//conver the path to be real path
			tags.push_back(tag);
		}
		ex_rs.Finalize();
	} catch (wxSQLite3Exception &e) {
		wxUnusedVar ( e );
	}

	if (GetUseCache()) {
		m_cache.Store(sql, tags);
	}
}

void TagsStorageSQLite::DoFetchTags(const wxString& sql, std::vector<TagEntryPtr>& tags, const wxArrayString& kinds)
{
#if SQL_LOG
	if (!log_fp)
		log_fp = fopen(SQL_LOG_NAME, "w+b");
#endif

	if (GetUseCache()) {
		if (m_cache.Get(sql, kinds, tags) == true) {
#if SQL_LOG
			fprintf(log_fp, "[CACHED ITEMS] %s\n", sql.mb_str(wxConvUTF8).data());
			fflush(log_fp);
#endif
			return;
		}
	}

#if SQL_LOG
	fprintf(log_fp, "%s\n", sql.mb_str(wxConvUTF8).data());
	fflush(log_fp);
#endif

	try {
		wxSQLite3ResultSet ex_rs;
		ex_rs = Query(sql);

		// add results from external database to the workspace database
		while ( ex_rs.NextRow() ) {
			// check if this kind is accepted
			if ( kinds.Index(ex_rs.GetString(4)) != wxNOT_FOUND ) {

				// Construct a TagEntry from the rescord set
				TagEntryPtr tag(FromSQLite3ResultSet(ex_rs));

				//conver the path to be real path
				tags.push_back(tag);
			}
		}
		ex_rs.Finalize();

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar ( e );
	}

	if (GetUseCache()) {
		m_cache.Store(sql, kinds, tags);
	}
}

void TagsStorageSQLite::GetTagsByScopeAndName(const wxString& scope, const wxString& name, bool partialNameAllowed, std::vector<TagEntryPtr> &tags)
{
	if(name.IsEmpty())
		return;

	wxString sql;
	sql << wxT("select * from tags where ");

	// did we get scope?
	if ( scope.IsEmpty() == false ) {
		sql << wxT("scope='") << scope << wxT("' ");
	}

	DoAddNamePartToQuery(sql, name, partialNameAllowed, !scope.IsEmpty());

	sql << wxT(" LIMIT ") << this->GetSingleSearchLimit();

	// get get the tags
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByScope(const wxString& scope, std::vector<TagEntryPtr>& tags)
{
	wxString sql;

	// Build the SQL statement
	sql << wxT("select * from tags where scope='") << scope << wxT("' ORDER BY NAME limit ") << GetSingleSearchLimit();

	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByKind(const wxArrayString& kinds, const wxString &orderingColumn, int order, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where kind in (");
	for (size_t i=0; i<kinds.GetCount(); i++) {
		sql << wxT("'") << kinds.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(") ");

	if ( orderingColumn.IsEmpty() == false ) {
		sql << wxT("order by ") << orderingColumn;
		switch (order) {
		case ITagsStorage::OrderAsc:
			sql << wxT(" ASC");
			break;
		case ITagsStorage::OrderDesc:
			sql << wxT(" DESC");
			break;
		case ITagsStorage::OrderNone:
		default:
			break;
		}
	}

	DoFetchTags(sql, tags);
}


void TagsStorageSQLite::GetTagsByPath(const wxArrayString& path, std::vector<TagEntryPtr>& tags)
{
	if (path.empty()) return;

	wxString sql;

	sql << wxT("select * from tags where path IN(");
	for (size_t i=0; i<path.GetCount(); i++) {
		sql << wxT("'") << path.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByNameAndParent(const wxString& name, const wxString& parent, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where name='") << name << wxT("' LIMIT ") << GetSingleSearchLimit();

	std::vector<TagEntryPtr> tmpResults;
	DoFetchTags(sql, tmpResults);

	// Filter by parent
	for (size_t i=0; i<tmpResults.size(); i++) {
		if (tmpResults.at(i)->GetParent() == parent) {
			tags.push_back( tmpResults.at(i) );
		}
	}
}

void TagsStorageSQLite::GetTagsByKindAndPath(const wxArrayString& kinds, const wxString& path, std::vector<TagEntryPtr>& tags)
{
	if ( kinds.empty() ) {
		return;
	}

	wxString sql;
	sql << wxT("select * from tags where path='") << path << wxT("' LIMIT ") << GetSingleSearchLimit();

	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByFileAndLine(const wxString& file, int line, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where file='") << file << wxT("' and line=") << line <<  wxT(" ");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByScopeAndKind(const wxString& scope, const wxArrayString& kinds, std::vector<TagEntryPtr>& tags)
{
	if ( kinds.empty() ) {
		return;
	}

	wxString sql;
	sql << wxT("select * from tags where scope='") << scope << wxT("' LIMIT ") << GetSingleSearchLimit();
	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByKindAndFile(const wxArrayString& kind, const wxString &fileName, const wxString& orderingColumn, int order, std::vector<TagEntryPtr>& tags)
{
	if ( kind.empty() ) {
		return;
	}

	wxString sql;
	sql << wxT("select * from tags where file='") << fileName << wxT("' and kind in (");

	for (size_t i=0; i<kind.GetCount(); i++) {
		sql << wxT("'") << kind.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");

	if ( orderingColumn.IsEmpty() == false ) {
		sql << wxT("order by ") << orderingColumn;
		switch (order) {
		case ITagsStorage::OrderAsc:
			sql << wxT(" ASC");
			break;
		case ITagsStorage::OrderDesc:
			sql << wxT(" DESC");
			break;
		case ITagsStorage::OrderNone:
		default:
			break;
		}
	}
	DoFetchTags(sql, tags);
}

int TagsStorageSQLite::DeleteFileEntry(const wxString& filename)
{
	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("DELETE FROM FILES WHERE FILE=?"));
		statement.Bind(1, filename);
		statement.ExecuteUpdate();

	} catch (wxSQLite3Exception& exc) {
		if (exc.ErrorCodeAsString(exc.GetErrorCode()) == wxT("SQLITE_CONSTRAINT"))
			return TagExist;
		return TagError;
	}
	return TagOk;
}


int TagsStorageSQLite::InsertFileEntry(const wxString& filename, int timestamp)
{
	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("INSERT OR REPLACE INTO FILES VALUES(NULL, ?, ?)"));
		statement.Bind(1, filename);
		statement.Bind(2, timestamp);
		statement.ExecuteUpdate();

	} catch (wxSQLite3Exception& exc) {
		return TagError;
	}
	return TagOk;
}


int TagsStorageSQLite::UpdateFileEntry(const wxString& filename, int timestamp)
{
	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("UPDATE OR REPLACE FILES SET last_retagged=? WHERE file=?"));
		statement.Bind(1,  timestamp);
		statement.Bind(2,  filename);
		statement.ExecuteUpdate();

	} catch (wxSQLite3Exception& exc) {
		return TagError;
	}
	return TagOk;
}

int TagsStorageSQLite::DeleteTagEntry(const wxString& kind, const wxString& signature, const wxString& path)
{
	// Delete this record from database.
	// Delete is done using the index
	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("DELETE FROM TAGS WHERE Kind=? AND Signature=? AND Path=?"));
		statement.Bind(1, kind);        // Kind
		statement.Bind(2, signature);   // Signature
		statement.Bind(3, path);        // Path
		statement.ExecuteUpdate();
	} catch (wxSQLite3Exception& exc) {
		wxUnusedVar(exc);
		return TagError;
	}
	return TagOk;
}

int TagsStorageSQLite::InsertTagEntry(const TagEntry& tag)
{
	// If this node is a dummy, (IsOk() == false) we dont insert it to database
	if ( !tag.IsOk() )
		return TagOk;

	if (GetUseCache()) {
		ClearCache();
	}

	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("INSERT OR REPLACE INTO TAGS VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));
		statement.Bind(1,  tag.GetName());
		statement.Bind(2,  tag.GetFile());
		statement.Bind(3,  tag.GetLine());
		statement.Bind(4,  tag.GetKind());
		statement.Bind(5,  tag.GetAccess());
		statement.Bind(6,  tag.GetSignature());
		statement.Bind(7,  tag.GetPattern());
		statement.Bind(8,  tag.GetParent());
		statement.Bind(9,  tag.GetInheritsAsString());
		statement.Bind(10, tag.GetPath());
		statement.Bind(11, tag.GetTyperef());
		statement.Bind(12, tag.GetScope());
		statement.Bind(13, tag.GetReturnValue());
		statement.ExecuteUpdate();
	} catch (wxSQLite3Exception& exc) {
		return TagError;
	}
	return TagOk;
}

int TagsStorageSQLite::UpdateTagEntry(const TagEntry& tag)
{
	if ( !tag.IsOk() )
		return TagOk;

	try {
		wxSQLite3Statement statement = m_db->GetPrepareStatement(wxT("UPDATE OR REPLACE TAGS SET Name=?, File=?, Line=?, Access=?, Pattern=?, Parent=?, Inherits=?, Typeref=?, Scope=?, Return_Value=? WHERE Kind=? AND Signature=? AND Path=?"));
		// update
		statement.Bind(1,  tag.GetName());
		statement.Bind(2,  tag.GetFile());
		statement.Bind(3,  tag.GetLine());
		statement.Bind(4,  tag.GetAccess());
		statement.Bind(5,  tag.GetPattern());
		statement.Bind(6,  tag.GetParent());
		statement.Bind(7,  tag.GetInheritsAsString());
		statement.Bind(8,  tag.GetTyperef());
		statement.Bind(9,  tag.GetScope());
		statement.Bind(10, tag.GetReturnValue());

		// where?
		statement.Bind(11, tag.GetKind());
		statement.Bind(12, tag.GetSignature());
		statement.Bind(13, tag.GetPath());

		statement.ExecuteUpdate();
	} catch (wxSQLite3Exception& exc) {
		return TagError;
	}
	return TagOk;
}

bool TagsStorageSQLite::IsTypeAndScopeContainer(wxString& typeName, wxString& scope)
{
	wxString sql;

	// Break the typename to 'name' and scope
	wxString typeNameNoScope(typeName.AfterLast(wxT(':')));
	wxString scopeOne       (typeName.BeforeLast(wxT(':')));

	if (scopeOne.EndsWith(wxT(":")))
		scopeOne.RemoveLast();

	wxString combinedScope;

	if (scope != wxT("<global>"))
		combinedScope << scope;

	if (scopeOne.IsEmpty() == false) {
		if (combinedScope.IsEmpty() == false)
			combinedScope << wxT("::");
		combinedScope << scopeOne;
	}


	sql << wxT("select scope,kind from tags where name='") << typeNameNoScope << wxT("'");

	bool found_global(false);

	try {
		wxSQLite3ResultSet rs = Query(sql);
		while (rs.NextRow()) {
			wxString scopeFounded (rs.GetString(0));
			wxString kindFounded  (rs.GetString(1));

			bool containerKind = kindFounded == wxT("struct") || kindFounded == wxT("class");
			if (scopeFounded == combinedScope && containerKind) {
				scope    = combinedScope;
				typeName = typeNameNoScope;
				//we got an exact match
				return true;

			} else if (scopeFounded == scopeOne && containerKind) {
				// this is equal to cases like this:
				// class A {
				// typedef std::list<int> List;
				// List l;
				// };
				// the combinedScope will be: 'A::std'
				// however, the actual scope is 'std'
				scope    = scopeOne;
				typeName = typeNameNoScope;
				//we got an exact match
				return true;

			} else if ( containerKind && scopeFounded == wxT("<global>") ) {
				found_global = true;
			}
		}

	} catch ( wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}

	// if we reached here, it means we did not find any exact match
	if ( found_global ) {
		scope    = wxT("<global>");
		typeName = typeNameNoScope;
		return true;
	}

	return false;
}


bool TagsStorageSQLite::IsTypeAndScopeExist(wxString& typeName, wxString& scope)
{
	wxString sql;
	wxString strippedName;
	wxString secondScope;
	wxString bestScope;
	wxString parent;
	wxString tmpScope(scope);

	strippedName = typeName.AfterLast(wxT(':'));
	secondScope  = typeName.BeforeLast(wxT(':'));

	if (secondScope.EndsWith(wxT(":")))
		secondScope.RemoveLast();

	if (strippedName.IsEmpty())
		return false;

	sql << wxT("select scope,parent from tags where name='") << strippedName << wxT("' and kind in ('class', 'struct', 'typedef') LIMIT 50");
	int     foundOther(0);
	wxString scopeFounded;
	wxString parentFounded;

	if (secondScope.IsEmpty() == false)
		tmpScope << wxT("::") << secondScope;

	parent = tmpScope.AfterLast(wxT(':'));

	try {
		wxSQLite3ResultSet rs = Query(sql);
		while (rs.NextRow()) {

			scopeFounded  = rs.GetString(0);
			parentFounded = rs.GetString(1);

			if ( scopeFounded == tmpScope ) {
				// exact match
				scope    = scopeFounded;
				typeName = strippedName;
				return true;

			} else if (parentFounded == parent) {
				bestScope  = scopeFounded;

			} else {
				foundOther++;
			}
		}

	} catch ( wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}

	// if we reached here, it means we did not find any exact match
	if ( bestScope.IsEmpty() == false ) {
		scope    = bestScope;
		typeName = strippedName;
		return true;

	} else if ( foundOther == 1) {
		scope    = scopeFounded;
		typeName = strippedName;
		return true;
	}
	return false;
}

void TagsStorageSQLite::GetScopesFromFileAsc(const wxFileName& fileName, std::vector<wxString>& scopes)
{
	wxString sql;
	sql << wxT("select distinct scope from tags where file = '")
	    << fileName.GetFullPath() << wxT("' ")
	    << wxT(" and kind in('prototype', 'function', 'enum')")
	    << wxT(" order by scope ASC");

	//we take the first entry
	try {
		wxSQLite3ResultSet rs = Query(sql);
		while ( rs.NextRow() ) {
			scopes.push_back(rs.GetString(0));
		}
		rs.Finalize();
	} catch ( wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::GetTagsByFileScopeAndKind(const wxFileName& fileName, const wxString& scopeName, const wxArrayString& kind, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where file = '")
	    << fileName.GetFullPath() << wxT("' ")
	    << wxT(" and scope='") << scopeName << wxT("' ");

	if ( kind.IsEmpty() == false ) {
		sql << wxT(" and kind in(");
		for (size_t i=0; i<kind.GetCount(); i++) {
			sql << wxT("'") << kind.Item(i) << wxT("',");
		}
		sql.RemoveLast();
		sql << wxT(")");
	}

	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetAllTagsNames(wxArrayString& names)
{
	try {

		wxString query(wxT("SELECT distinct name FROM tags order by name ASC LIMIT "));
		query  << GetMaxWorkspaceTagToColour();

		wxSQLite3ResultSet res = Query(query);
		while (res.NextRow()) {
			// add unique strings only
			names.Add( res.GetString(0) );
		}

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::GetTagsNames(const wxArrayString& kind, wxArrayString& names)
{
	if ( kind.IsEmpty() ) return;
	try {

		wxString whereClause;
		whereClause << wxT(" kind IN (");
		for (size_t i=0; i<kind.GetCount(); i++) {
			whereClause << wxT("'") << kind.Item(i) << wxT("',");
		}

		whereClause = whereClause.BeforeLast(wxT(','));
		whereClause << wxT(") ");

		wxString query(wxT("SELECT distinct name FROM tags WHERE "));
		query << whereClause << wxT(" order by name ASC LIMIT ") << GetMaxWorkspaceTagToColour();

		wxSQLite3ResultSet res = Query(query);
		while (res.NextRow()) {
			// add unique strings only
			names.Add( res.GetString(0) );
		}

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}
}

void TagsStorageSQLite::GetTagsByScopesAndKind(const wxArrayString& scopes, const wxArrayString& kinds, std::vector<TagEntryPtr>& tags)
{
	if ( kinds.empty() || scopes.empty() ) {
		return;
	}

	wxString sql;
	sql << wxT("select * from tags where scope in (");
	for (size_t i=0; i<scopes.GetCount(); i++) {
		sql << wxT("'") << scopes.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(") ORDER BY NAME LIMIT ") << GetSingleSearchLimit();

	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByScopesAndKindNoLimit(const wxArrayString& scopes, const wxArrayString& kinds, std::vector<TagEntryPtr>& tags)
{
	if ( kinds.empty() || scopes.empty() ) {
		return;
	}

	wxString sql;
	sql << wxT("select * from tags where scope in (");
	for (size_t i=0; i<scopes.GetCount(); i++) {
		sql << wxT("'") << scopes.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(") ORDER BY NAME");

	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByPath(const wxString& path, std::vector<TagEntryPtr>& tags)
{
	if (path.empty()) return;

	wxString sql;
	sql << wxT("select * from tags where path ='") << path << wxT("' LIMIT 1");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByScopeAndName(const wxArrayString& scope, const wxString& name, bool partialNameAllowed, std::vector<TagEntryPtr>& tags)
{
	if (scope.empty())  return;
	if (name.IsEmpty()) return;

	wxString sql;
	sql << wxT("select * from tags where scope in(");

	for (size_t i=0; i<scope.GetCount(); i++) {
		sql <<wxT("'") <<scope.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(") ");

	DoAddNamePartToQuery(sql, name, partialNameAllowed, true);
	sql << wxT(" LIMIT ") << GetSingleSearchLimit();
	// get get the tags
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetGlobalFunctions(std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where scope = '<global>' AND kind IN ('function', 'prototype') LIMIT ") << GetSingleSearchLimit();
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByFiles(const wxArrayString& files, std::vector<TagEntryPtr>& tags)
{
	if(files.IsEmpty())
		return;

	wxString sql;
	sql << wxT("select * from tags where file in (");
	for(size_t i=0; i<files.GetCount(); i++) {
		sql << wxT("'") << files.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByFilesAndScope(const wxArrayString& files, const wxString& scope, std::vector<TagEntryPtr>& tags)
{
	if(files.IsEmpty())
		return;

	wxString sql;
	sql << wxT("select * from tags where file in (");
	for(size_t i=0; i<files.GetCount(); i++) {
		sql << wxT("'") << files.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");

	sql << wxT(" AND scope='") << scope << wxT("'");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetTagsByFilesKindAndScope(const wxArrayString& files, const wxArrayString& kinds, const wxString& scope, std::vector<TagEntryPtr>& tags)
{
	if(files.IsEmpty())
		return;

	wxString sql;
	sql << wxT("select * from tags where file in (");
	for(size_t i=0; i<files.GetCount(); i++) {
		sql << wxT("'") << files.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");

	sql << wxT(" AND scope='") << scope << wxT("'");
	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByFilesScopeTyperefAndKind(const wxArrayString& files, const wxArrayString& kinds, const wxString& scope, const wxString& typeref, std::vector<TagEntryPtr>& tags)
{
	if(files.IsEmpty())
		return;

	wxString sql;
	sql << wxT("select * from tags where file in (");
	for(size_t i=0; i<files.GetCount(); i++) {
		sql << wxT("'") << files.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(")");

	sql << wxT(" AND scope='") << scope << wxT("'");
	sql << wxT(" AND typeref='") << typeref << wxT("'");
	DoFetchTags(sql, tags, kinds);
}

void TagsStorageSQLite::GetTagsByKindLimit(const wxArrayString& kinds, const wxString& orderingColumn, int order, int limit, const wxString &partName, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where kind in (");
	for (size_t i=0; i<kinds.GetCount(); i++) {
		sql << wxT("'") << kinds.Item(i) << wxT("',");
	}
	sql.RemoveLast();
	sql << wxT(") ");

	if ( orderingColumn.IsEmpty() == false ) {
		sql << wxT("order by ") << orderingColumn;
		switch (order) {
		case ITagsStorage::OrderAsc:
			sql << wxT(" ASC");
			break;
		case ITagsStorage::OrderDesc:
			sql << wxT(" DESC");
			break;
		case ITagsStorage::OrderNone:
		default:
			break;
		}
	}

	DoAddNamePartToQuery(sql, partName, true, true);
	if (limit > 0) {
		sql << wxT(" LIMIT ") << limit;
	}

	DoFetchTags(sql, tags);

}
bool TagsStorageSQLite::IsTypeAndScopeExistLimitOne(const wxString& typeName, const wxString& scope)
{
	wxString sql;
	wxString path;

	// Build the path
	if (scope.IsEmpty() == false && scope != wxT("<global>"))
		path << scope << wxT("::");

	path << typeName;
	sql << wxT("select ID from tags where path='") << path << wxT("' and kind in ('class', 'struct', 'typedef') LIMIT 1");

	try {
		wxSQLite3ResultSet rs = Query(sql);
		if (rs.NextRow()) {
			return true;
		}

	} catch ( wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}
	return false;
}

void TagsStorageSQLite::GetDereferenceOperator(const wxString& scope, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where scope ='") << scope << wxT("' and name like 'operator%->%' LIMIT 1");
	DoFetchTags(sql, tags);
}

void TagsStorageSQLite::GetSubscriptOperator(const wxString& scope, std::vector<TagEntryPtr>& tags)
{
	wxString sql;
	sql << wxT("select * from tags where scope ='") << scope << wxT("' and name like 'operator%[%]%' LIMIT 1");
	DoFetchTags(sql, tags);
}

//---------------------------------------------------------------------
//-----------------------------TagsStorageSQLiteCache -----------------
//---------------------------------------------------------------------

TagsStorageSQLiteCache::TagsStorageSQLiteCache()
{
}

TagsStorageSQLiteCache::~TagsStorageSQLiteCache()
{
	m_cache.clear();
}

bool TagsStorageSQLiteCache::Get(const wxString& sql, std::vector<TagEntryPtr>& tags)
{
	return DoGet(sql, tags);
}

bool TagsStorageSQLiteCache::Get(const wxString& sql, const wxArrayString& kind, std::vector<TagEntryPtr>& tags)
{
	wxString key;
	key << sql;
	for (size_t i=0; i<kind.GetCount(); i++) {
		key << wxT("@") << kind.Item(i);
	}

	return DoGet(key, tags);
}

void TagsStorageSQLiteCache::Store(const wxString& sql, const std::vector<TagEntryPtr>& tags)
{
	DoStore(sql, tags);
}

void TagsStorageSQLiteCache::Clear()
{
#if SQL_LOG
	if (!log_fp)
		log_fp = fopen(SQL_LOG_NAME, "w+b");
#endif

#if SQL_LOG
	fprintf(log_fp, "[CACHE CLEARED]\n");
	fflush(log_fp);
#endif

	m_cache.clear();
}

void TagsStorageSQLiteCache::Store(const wxString& sql, const wxArrayString& kind, const std::vector<TagEntryPtr>& tags)
{
	wxString key;
	key << sql;
	for (size_t i=0; i<kind.GetCount(); i++) {
		key << wxT("@") << kind.Item(i);
	}
	DoStore(key, tags);
}

bool TagsStorageSQLiteCache::DoGet(const wxString& key, std::vector<TagEntryPtr>& tags)
{
	std::map<wxString, std::vector<TagEntryPtr> >::iterator iter = m_cache.find(key);
	if (iter != m_cache.end()) {
		// Append the results to the output tags
		tags.insert(tags.end(), iter->second.begin(), iter->second.end());
		return true;
	}
	return false;
}

void TagsStorageSQLiteCache::DoStore(const wxString& key, const std::vector<TagEntryPtr>& tags)
{
	m_cache[key].reserve(tags.size());
	m_cache[key] = tags;
}

void TagsStorageSQLite::ClearCache()
{
	m_cache.Clear();
}

void TagsStorageSQLite::SetUseCache(bool useCache)
{
	ITagsStorage::SetUseCache(useCache);
}

PPToken TagsStorageSQLite::GetMacro(const wxString& name)
{
	PPToken token;
	try {
		wxString sql;
		sql << wxT("select * from MACROS where name = '") << name << wxT("'");
		wxSQLite3ResultSet res = m_db->ExecuteQuery(sql);
		if(res.NextRow()) {
			PPTokenFromSQlite3ResultSet(res, token);
			return token;
		}
	} catch (wxSQLite3Exception& exc) {
		wxUnusedVar(exc);
	}

	return token;
}

void TagsStorageSQLite::StoreMacros(const std::map<wxString, PPToken>& table)
{
	try {
		wxSQLite3Statement stmntCC     = m_db->GetPrepareStatement(wxT("insert or replace into MACROS values(NULL, ?, ?, ?, ?, ?, ?)"));
		wxSQLite3Statement stmntSimple = m_db->GetPrepareStatement(wxT("insert or replace into SIMPLE_MACROS values(NULL, ?, ?)"));

		std::map<wxString, PPToken>::const_iterator iter = table.begin();
		for(; iter != table.end(); iter++) {
			wxString replac= iter->second.replacement;
			replac.Trim().Trim(false);

			// Since we are using the MACROS table mainly for the replacement
			// field, dont insert into the database entries which dont have
			// a replacement
			// we take only macros that their replacement is not a number or a string
			if(replac.IsEmpty() || replac.find_first_of(wxT("0123456789")) == 0) {
				// Insert it into the SIMPLE_MACRO instead
				stmntSimple.Bind(1, iter->second.fileName);
				stmntSimple.Bind(2, iter->second.name);
				stmntSimple.ExecuteUpdate();
				stmntSimple.Reset();
			}
			else {
				// macros with replacement.
				stmntCC.Bind(1, iter->second.fileName);
				stmntCC.Bind(2, iter->second.line);
				stmntCC.Bind(3, iter->second.name);
				stmntCC.Bind(4, iter->second.flags & PPToken::IsFunctionLike ? 1 : 0);
				stmntCC.Bind(5, replac);
				stmntCC.Bind(6, iter->second.signature());
				stmntCC.ExecuteUpdate();
				stmntCC.Reset();
			}
		}

	} catch (wxSQLite3Exception &exc) {
		wxUnusedVar(exc);
	}
}

void TagsStorageSQLite::GetMacrosDefined(const std::set<std::string>& files, const std::set<wxString>& usedMacros, wxArrayString& defMacros)
{
	if (files.empty() || usedMacros.empty()) {
		return;
	}

	// Create the file list SQL string, used for IN operator
	wxString sFileList;
	for (std::set<std::string>::const_iterator itFile = files.begin(); itFile != files.end(); ++itFile) {
		sFileList << wxT("'") << wxString::From8BitData(itFile->c_str()) << wxT("',");
	}
	sFileList.RemoveLast();

	// Create the used macros list SQL string, used for IN operator
	wxString sMacroList;
	for (std::set<wxString>::const_iterator itUsedMacro = usedMacros.begin(); itUsedMacro != usedMacros.end(); ++itUsedMacro) {
		sMacroList << wxT("'") << *itUsedMacro << wxT("',");
	}
	sMacroList.RemoveLast();

	try {
		// Step 1 : Retrieve defined macros in MACROS table
		wxString req;
		req << wxT("select name from MACROS where file in (") << sFileList << wxT(")")
			<< wxT(" and name in (") << sMacroList << wxT(")");
		wxSQLite3ResultSet res = m_db->ExecuteQuery(req);
		while (res.NextRow()) {
			defMacros.push_back(res.GetString(0));
		}

		// Step 2 : Retrieve defined macros in SIMPLE_MACROS table
		req.Clear();
		req << wxT("select name from SIMPLE_MACROS where file in (") << sFileList << wxT(")")
			<< wxT(" and name in (") << sMacroList << wxT(")");
		res = m_db->ExecuteQuery(req);
		while (res.NextRow()) {
			defMacros.push_back(res.GetString(0));
		}
	} catch (wxSQLite3Exception &exc) {
		wxLogError(exc.GetMessage());
	}
}

void TagsStorageSQLite::DoAddNamePartToQuery(wxString &sql, const wxString& name, bool partial, bool prependAnd)
{
	if(name.empty())
		return;
	if(prependAnd) {
		sql << wxT(" AND ");
	}

	if(m_enableCaseInsensitive) {
		wxString tmpName(name);
		tmpName.Replace(wxT("_"), wxT("^_"));
		if(partial) {
			sql << wxT(" name LIKE '") << tmpName << wxT("%%' ESCAPE '^' ");
		} else {
			sql << wxT(" name ='") << name << wxT("' ");
		}
	} else {
		// Don't use LIKE
		wxString from  = name;
		wxString until = name;

#if wxVERSION_NUMBER < 2900
		until.Last() = until.Last() + 1;
#else
		wxChar ch = until.Last();
		until.SetChar(until.length() - 1,  ch + 1);
#endif

		// add the name condition
		if (partial) {
			sql << wxT(" name >= '") << from << wxT("' AND  name < '") << until << wxT("'");
		} else {
			sql << wxT(" name ='") << name << wxT("' ");
		}
	}
}
