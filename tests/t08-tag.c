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
#include "test_lib.h"
#include "test_helpers.h"

#include "tag.h"

static const char *tag1_id = "b25fa35b38051e4ae45d4222e795f9df2e43f1d1";
static const char *tag2_id = "7b4384978d2493e851f9cca7858815fac9b10980";
static const char *tagged_commit = "e90810b8df3e80c413d903f631643c716887138d";

BEGIN_TEST(read0, "read and parse a tag from the repository")
	git_repository *repo;
	git_tag *tag1, *tag2;
	git_commit *commit;
	git_oid id1, id2, id_commit;

	must_pass(git_repository_open(&repo, REPOSITORY_FOLDER));

	git_oid_mkstr(&id1, tag1_id);
	git_oid_mkstr(&id2, tag2_id);
	git_oid_mkstr(&id_commit, tagged_commit);

	must_pass(git_tag_lookup(&tag1, repo, &id1));

	must_be_true(strcmp(git_tag_name(tag1), "test") == 0);
	must_be_true(git_tag_type(tag1) == GIT_OBJ_TAG);

	tag2 = (git_tag *)git_tag_target(tag1);
	must_be_true(tag2 != NULL);

	must_be_true(git_oid_cmp(&id2, git_tag_id(tag2)) == 0);

	commit = (git_commit *)git_tag_target(tag2);
	must_be_true(commit != NULL);

	must_be_true(git_oid_cmp(&id_commit, git_commit_id(commit)) == 0);

	git_repository_free(repo);
END_TEST

BEGIN_TEST(write0, "write back a tag to the repository")
	git_oid id;
	git_repository *repo;
	git_tag *tag;

	must_pass(git_repository_open(&repo, REPOSITORY_FOLDER));

	git_oid_mkstr(&id, tag1_id);

	must_pass(git_tag_lookup(&tag, repo, &id));

	git_tag_set_name(tag, "This is a different tag LOL");

	must_pass(git_object_write((git_object *)tag));
	must_pass(remove_loose_object(REPOSITORY_FOLDER, (git_object *)tag));

	git_repository_free(repo);
END_TEST


BEGIN_SUITE(tag)
	ADD_TEST(read0);
	ADD_TEST(write0);
END_SUITE
