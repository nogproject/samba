/*

The VFS module `disable_chmod` disables all mode changes by pretending that
`*chmod*()` calls were successful.

The implementation is based on `examples/VFS/skel_opaque.c`.

*/

#include "../source3/include/includes.h"
#include "lib/util/tevent_ntstatus.h"

static int disable_chmod_chmod(vfs_handle_struct *handle, const char *path,
			       mode_t mode)
{
	return 0;
}

static int disable_chmod_fchmod(vfs_handle_struct *handle, files_struct *fsp,
				mode_t mode)
{
	return 0;
}

static int disable_chmod_chmod_acl(vfs_handle_struct *handle,
				       const char *name, mode_t mode)
{
	return 0;
}

static int disable_chmod_fchmod_acl(vfs_handle_struct *handle,
				        files_struct *fsp, mode_t mode)
{
	return 0;
}

struct vfs_fn_pointers disable_chmod_fns = {
	.chmod_fn = disable_chmod_chmod,
	.fchmod_fn = disable_chmod_fchmod,
	.chmod_acl_fn = disable_chmod_chmod_acl,
	.fchmod_acl_fn = disable_chmod_fchmod_acl,
};

NTSTATUS vfs_disable_chmod_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION, "disable_chmod",
				&disable_chmod_fns);
}
