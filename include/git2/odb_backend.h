/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * In addition to the permissions in the GNU General Public License,
 * the authors give you unlimited permission to link the compiled
 * version of this file into combinations with other programs,
 * and to distribute those combinations without any restriction
 * coming from the use of this file.  (The General Public License
 * restrictions do apply in other respects; for example, they cover
 * modification of the file, and distribution when not linked into
 * a combined executable.)
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDE_git_odb_backend_h__
#define INCLUDE_git_odb_backend_h__

#include "common.h"
#include "types.h"
#include "oid.h"
#include "odb.h"

/**
 * @file git2/backend.h
 * @brief Git custom backend functions
 * @defgroup git_backend Git custom backend API
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/** An instance for a custom backend */
struct git_odb_backend {
	git_odb *odb;

	int (* read)(
			git_rawobj *,
			struct git_odb_backend *,
			const git_oid *);

	int (* read_header)(
			git_rawobj *,
			struct git_odb_backend *,
			const git_oid *);

	int (* write)(
			git_oid *id,
			struct git_odb_backend *,
			git_rawobj *obj);

	int (* exists)(
			struct git_odb_backend *,
			const git_oid *);

	void (* free)(struct git_odb_backend *);
};

GIT_EXTERN(int) git_odb_backend_pack(git_odb_backend **backend_out, const char *objects_dir);
GIT_EXTERN(int) git_odb_backend_loose(git_odb_backend **backend_out, const char *objects_dir);

#ifdef GIT2_SQLITE_BACKEND
GIT_EXTERN(int) git_odb_backend_sqlite(git_odb_backend **backend_out, const char *sqlite_db);
#endif

GIT_END_DECL

#endif
